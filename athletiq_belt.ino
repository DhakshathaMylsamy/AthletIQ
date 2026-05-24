/* ============================================================================
   AthletIQ — Unified Smart Belt  |  Firmware v3  (gesture mode-switching)
   ----------------------------------------------------------------------------
   NEW vs v2: the APDS9960 gesture board (front of belt) now drives the mode.
     Swipe UP    -> JUMP
     Swipe DOWN  -> PLANK
     Swipe LEFT  -> POSTURE
   On each switch the belt buzzes a confirm, auto-captures the neutral reference
   for posture/plank, and broadcasts the new mode over BLE so the dashboard
   follows the belt automatically. The dashboard can STILL command modes too
   (M:JUMP / M:POSTURE / M:PLANK / CAL) — both paths coexist.

   GESTURE API (verified from MYOSA src): class LightProximityAndGesture @0x39
     begin(), enableGestureSensor(true), isGestureAvailable(), readGesture()
     -> returns DIR_UP / DIR_DOWN / DIR_LEFT / DIR_RIGHT / DIR_NONE

   >>> PORT YOUR TUNED VALUES into the CONFIG block before flashing.
   ============================================================================ */

#include <Wire.h>
#include "AccelAndGyro.h"
#include "LightProximityAndGesture.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <math.h>

// ----------------------------- USER CONFIG ---------------------------------
#define IMU_I2C_ADDR   0x69
#define GEST_I2C_ADDR  0x39
#define MOTOR_PIN      25
#define SAMPLE_HZ      200
#define LIVE_HZ        25
#define GESTURE_POLL_MS 60        // how often to check the gesture sensor

// Jump thresholds (port tuned v1/v2 values)
const float FREEFALL_ENTER_G = 0.40f;
const float LANDING_EXIT_G    = 2.20f;
const float IMPACT_ALERT_G    = 6.0f;
const float MIN_FLIGHT_S       = 0.10f;
const float MAX_FLIGHT_S       = 1.20f;
const uint32_t LANDING_HOLD_MS = 180;
// Posture thresholds
const float POSTURE_SLOUCH_DEG = 15.0f;
const uint32_t POSTURE_HOLD_MS = 2500;
// Plank thresholds
const float PLANK_BREAK_DEG = 12.0f;
#define SWAY_N 25

const float A_SCALE_G = 16.0f/32768.0f;
const float G_ACCEL   = 9.80665f;
const float RAD2DEG   = 57.29577951f;

#define NUS_SERVICE  "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define NUS_TX_CHAR  "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"
#define NUS_RX_CHAR  "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"

// ----------------------------- GLOBALS -------------------------------------
AccelAndGyro imu(IMU_I2C_ADDR);
LightProximityAndGesture gesture(GEST_I2C_ADDR);
bool gestureOK = false;

BLECharacteristic *txChar = nullptr;
bool bleConnected = false;

enum Mode { JUMP, POSTURE, PLANK };
volatile int  pendingMode = -1;
volatile bool doCapture   = false;
Mode mode = JUMP;

uint32_t sampleInterval_us, liveInterval_us;
uint32_t nextSample_us=0, nextLive_us=0, motorOff_us=0, nextGesture_ms=0;

float gRef[3]={0,0,1}; bool haveRef=false; float curDev=0;

enum JState { GROUNDED, AIRBORNE, LANDING };
JState jst=GROUNDED;
uint32_t tTakeoff_us=0,tLand_us=0,tLastLand_us=0;
bool haveLastLand=false; float peakImpactG=0; uint16_t jumpCount=0;

uint32_t slouchStart_us=0; bool slouching=false;
uint32_t plankStart_us=0;  bool plankBreak=false;
float devRing[SWAY_N]; uint8_t ringIdx=0, ringCnt=0;

// ----------------------------- BLE -----------------------------------------
class ServerCB : public BLEServerCallbacks {
  void onConnect(BLEServer *s) override { bleConnected=true; }
  void onDisconnect(BLEServer *s) override { bleConnected=false; s->getAdvertising()->start(); }
};
class RxCB : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *c) override {
    String v=String(c->getValue().c_str()); v.trim();
    if      (v=="M:JUMP")    { pendingMode=JUMP;    doCapture=false; }
    else if (v=="M:POSTURE") { pendingMode=POSTURE; doCapture=true;  }
    else if (v=="M:PLANK")   { pendingMode=PLANK;   doCapture=true;  }
    else if (v=="CAL")       { doCapture=true; }
  }
};
void bleNotify(const String &m){ if(bleConnected && txChar){ txChar->setValue((uint8_t*)m.c_str(),m.length()); txChar->notify(); } }
void broadcastMode(){ // tell the dashboard which mode the belt is now in
  const char* n = mode==JUMP?"JUMP":mode==POSTURE?"POSTURE":"PLANK";
  bleNotify(String("{\"t\":\"mode\",\"m\":\"")+n+"\"}");
}

// ----------------------------- HELPERS -------------------------------------
void buzz(uint16_t ms){ digitalWrite(MOTOR_PIN,HIGH); motorOff_us=micros()+(uint32_t)ms*1000UL; }
void buzzConfirm(uint8_t pulses){ // distinct multi-pulse so a mode switch FEELS different
  for(uint8_t i=0;i<pulses;i++){ digitalWrite(MOTOR_PIN,HIGH); delay(70); digitalWrite(MOTOR_PIN,LOW); delay(70); }
}

float readAccelMagG(float *axg,float *ayg,float *azg){
  int16_t ax,ay,az; imu.getAccel(&ax,&ay,&az);
  *axg=ax*A_SCALE_G; *ayg=ay*A_SCALE_G; *azg=az*A_SCALE_G;
  return sqrtf((*axg)*(*axg)+(*ayg)*(*ayg)+(*azg)*(*azg));
}
void captureReference(){
  float sx=0,sy=0,sz=0,ax,ay,az; int n=0; uint32_t end=millis()+1200;
  while(millis()<end){ readAccelMagG(&ax,&ay,&az); sx+=ax;sy+=ay;sz+=az;n++; delay(5); }
  float mx=sx/n,my=sy/n,mz=sz/n,m=sqrtf(mx*mx+my*my+mz*mz);
  if(m>0){ gRef[0]=mx/m;gRef[1]=my/m;gRef[2]=mz/m;haveRef=true; }
}
float deviationDeg(float axg,float ayg,float azg){
  if(!haveRef) return 0; float m=sqrtf(axg*axg+ayg*ayg+azg*azg); if(m<=0)return 0;
  float dot=(axg*gRef[0]+ayg*gRef[1]+azg*gRef[2])/m; if(dot>1)dot=1; if(dot<-1)dot=-1;
  return acosf(dot)*RAD2DEG;
}
float swayStdev(){ if(!ringCnt)return 0; float mean=0; for(uint8_t i=0;i<ringCnt;i++)mean+=devRing[i]; mean/=ringCnt;
  float var=0; for(uint8_t i=0;i<ringCnt;i++){float d=devRing[i]-mean;var+=d*d;} return sqrtf(var/ringCnt); }
void resetModeState(){ jst=GROUNDED;haveLastLand=false;peakImpactG=0;slouchStart_us=0;slouching=false;
  plankBreak=false;ringIdx=0;ringCnt=0;plankStart_us=micros(); }

// map a swipe to a mode. UP=JUMP, DOWN=PLANK, LEFT=POSTURE (RIGHT spare)
void applyGesture(int dir){
  Mode nm = mode;
  if(dir==DIR_UP)        nm=JUMP;
  else if(dir==DIR_DOWN) nm=PLANK;
  else if(dir==DIR_LEFT) nm=POSTURE;
  else return;                            // ignore RIGHT / NEAR / FAR / NONE
  if(nm==mode) return;
  pendingMode = nm;
  doCapture   = (nm!=JUMP);
}

// ----------------------------- SETUP ---------------------------------------
void setup(){
  Serial.begin(115200); delay(300);
  pinMode(MOTOR_PIN,OUTPUT); digitalWrite(MOTOR_PIN,LOW);
  Wire.begin(); Wire.setClock(400000);

  if(!imu.begin(false)){ Serial.println(F("MPU6050 not found!")); while(true){buzz(60);delay(400);} }
  imu.setFullScaleAccelRange(3);   // +/-16g
  imu.setFullScaleGyroRange(2);    // +/-1000 dps
  delay(50);

  // gesture sensor is optional — belt still works (dashboard control) if absent
  gestureOK = gesture.begin();
  if(gestureOK){ gesture.enableGestureSensor(true); Serial.println(F("Gesture sensor ready.")); }
  else          Serial.println(F("Gesture sensor not found - using dashboard control only."));

  sampleInterval_us=1000000UL/SAMPLE_HZ;
  liveInterval_us  =1000000UL/LIVE_HZ;

  BLEDevice::init("AthletIQ-Belt");
  BLEDevice::setMTU(185);
  BLEServer *server=BLEDevice::createServer();
  server->setCallbacks(new ServerCB());
  BLEService *svc=server->createService(NUS_SERVICE);
  txChar=svc->createCharacteristic(NUS_TX_CHAR,BLECharacteristic::PROPERTY_NOTIFY);
  txChar->addDescriptor(new BLE2902());
  BLECharacteristic *rxChar=svc->createCharacteristic(NUS_RX_CHAR,BLECharacteristic::PROPERTY_WRITE);
  rxChar->setCallbacks(new RxCB());
  svc->start();
  server->getAdvertising()->addServiceUUID(NUS_SERVICE);
  server->getAdvertising()->start();

  Serial.println(F("Ready in JUMP. Swipe UP=Jump DOWN=Plank LEFT=Posture."));
  nextSample_us=micros(); nextLive_us=micros(); nextGesture_ms=millis();
}

// ----------------------------- LOOP ----------------------------------------
void loop(){
  uint32_t now=micros();
  if(motorOff_us && (int32_t)(now-motorOff_us)>=0){ digitalWrite(MOTOR_PIN,LOW); motorOff_us=0; }

  // ---- poll gesture sensor (throttled; only matters between reps) ----
  if(gestureOK && (int32_t)(millis()-nextGesture_ms)>=0){
    nextGesture_ms = millis()+GESTURE_POLL_MS;
    if(gesture.isGestureAvailable()) applyGesture(gesture.readGesture());
  }

  // ---- apply a pending mode change (from gesture OR dashboard) ----
  if(pendingMode>=0){
    mode=(Mode)pendingMode; pendingMode=-1; resetModeState();
    const char* n = mode==JUMP?"JUMP":mode==POSTURE?"POSTURE":"PLANK";
    buzzConfirm(mode==JUMP?1:mode==POSTURE?2:3);   // 1/2/3 pulses = which mode
    if(doCapture){ doCapture=false; captureReference(); plankStart_us=micros(); }
    broadcastMode();
    Serial.print(F("Mode -> ")); Serial.println(n);
    nextSample_us=micros();                        // resync sampling after the buzz delay
  } else if(doCapture){                            // bare CAL with no mode change
    doCapture=false; if(mode!=JUMP){ captureReference(); plankStart_us=micros(); buzz(120); }
  }

  if((int32_t)(now-nextSample_us)<0) return;
  nextSample_us += sampleInterval_us;

  float axg,ayg,azg; float aMag=readAccelMagG(&axg,&ayg,&azg);
  curDev = (mode==JUMP)?0:deviationDeg(axg,ayg,azg);
  bool liveTick=(int32_t)(now-nextLive_us)>=0; if(liveTick) nextLive_us+=liveInterval_us;

  // -------------------- JUMP --------------------
  if(mode==JUMP){
    switch(jst){
      case GROUNDED: if(aMag<FREEFALL_ENTER_G){tTakeoff_us=now;jst=AIRBORNE;} break;
      case AIRBORNE: if(aMag>LANDING_EXIT_G){tLand_us=now;peakImpactG=aMag;jst=LANDING;} break;
      case LANDING:
        if(aMag>peakImpactG)peakImpactG=aMag;
        if((now-tLand_us)>=LANDING_HOLD_MS*1000UL){
          float flight_s=(tLand_us-tTakeoff_us)/1e6f;
          if(flight_s>=MIN_FLIGHT_S && flight_s<=MAX_FLIGHT_S){
            float h_cm=(G_ACCEL*flight_s*flight_s/8.0f)*100.0f;
            float contact_s=-1,rsi=-1;
            if(haveLastLand){contact_s=(tTakeoff_us-tLastLand_us)/1e6f;
              if(contact_s>0.08f&&contact_s<3.0f) rsi=(h_cm/100.0f)/contact_s;}
            jumpCount++; if(peakImpactG>IMPACT_ALERT_G) buzz(200);
            String j="{\"t\":\"jump\",\"n\":"+String(jumpCount)+",\"h\":"+String(h_cm,1)+
                     ",\"ft\":"+String(flight_s,3)+",\"imp\":"+String(peakImpactG,1);
            if(rsi>0) j+=",\"rsi\":"+String(rsi,2);
            j+="}"; bleNotify(j);
            Serial.printf("JUMP #%u h=%.1f ft=%.3f imp=%.1f\n",jumpCount,h_cm,flight_s,peakImpactG);
            tLastLand_us=tLand_us; haveLastLand=true;
          }
          jst=GROUNDED;
        } break;
    }
    if(liveTick) bleNotify("{\"t\":\"live\",\"s\":"+String((int)jst)+",\"a\":"+String(aMag,2)+"}");
    return;
  }

  // -------------------- POSTURE --------------------
  if(mode==POSTURE){
    if(curDev>POSTURE_SLOUCH_DEG){
      if(slouchStart_us==0) slouchStart_us=now;
      if(!slouching && (now-slouchStart_us)>=POSTURE_HOLD_MS*1000UL){ slouching=true; buzz(250); }
    } else { slouchStart_us=0; slouching=false; }
    if(liveTick) bleNotify("{\"t\":\"posture\",\"dev\":"+String(curDev,1)+",\"slouch\":"+String(slouching?1:0)+"}");
    return;
  }

  // -------------------- PLANK --------------------
  if(mode==PLANK){
    if(curDev>PLANK_BREAK_DEG){ if(!plankBreak){plankBreak=true;buzz(200);} } else plankBreak=false;
    if(liveTick){
      devRing[ringIdx]=curDev; ringIdx=(ringIdx+1)%SWAY_N; if(ringCnt<SWAY_N)ringCnt++;
      float hold_s=(now-plankStart_us)/1e6f;
      bleNotify("{\"t\":\"plank\",\"dev\":"+String(curDev,1)+",\"sway\":"+String(swayStdev(),2)+
                ",\"hold\":"+String(hold_s,1)+",\"break\":"+String(plankBreak?1:0)+"}");
    }
    return;
  }
}
