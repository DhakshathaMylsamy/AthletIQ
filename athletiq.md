---
publishDate: 2026-05-17T00:00:00Z

title: AthletIQ — An Agentic AI Biomechanical Coach for Athletes

excerpt: A unified smart-belt wearable that turns a single low-cost MYOSA sensor into lab-grade biomechanical feedback, coaching athletes through jump, plank, and posture analysis in real time.

image: athletiq/cover.jpg

tags:
  - wearable
  - biomechanics
  - iot
  - edge-ai
  - sports-tech
---

> One belt. One sensor at the centre of mass. Lab-grade biomechanical coaching for everyone.

---

## Acknowledgements

We express our sincere gratitude to **Dr. Allwyn Gnanadas**, Department of Biomedical Engineering, KPR Institute of Engineering and Technology, for his valuable guidance and continuous mentorship throughout this project.

We also thank the **IEEE Sensors Council** for sponsoring the **MYOSA Mini IoT Kit**, which made the development of this work possible.

**Team:** Dhakshatha M K · Nimalan P

---

## Overview

**AthletIQ** is a unified smart-belt wearable that delivers real-time biomechanical analysis and adaptive coaching from a single inertial sensor worn at the body's centre of mass.

Commercial fitness trackers report steps and heart rate but cannot judge whether a movement is good or safe. Professional biomechanics labs can, but they rely on force plates and motion-capture systems that cost a fortune and are confined to a room. **AthletIQ bridges this gap** — it extracts clinically meaningful movement metrics from one low-cost sensor in a waist belt, evaluates the quality of each movement on the device itself, and delivers feedback both as an instant haptic buzz on the belt and as an AI coaching review on a dashboard.

Built entirely on the **MYOSA Mini IoT Kit**, the system consolidates all sensing, processing, and feedback into a single compression belt worn at the lower back (sacrum) — the optimal anatomical location for capturing whole-body movement. A front-mounted gesture sensor lets the athlete switch between three coaching modes with a simple hand swipe.

**Who it is for:** grassroots athletes, coaches, physiotherapists, and anyone needing accessible movement analysis without laboratory infrastructure — particularly in resource-constrained settings.

**Key features:**

* Unified single-belt wearable with all electronics at the centre of mass
* Three coaching modes — Jump, Plank, and Posture — switched by touchless hand gestures
* Real-time jump height, flight time, contact time, RSI, and landing-impact measurement
* Core-stability and postural monitoring with instant haptic alerts
* On-device movement evaluation with no network dependence for safety-critical feedback
* Wireless streaming to an interactive dashboard with an AI coaching review

---

## Demo / Examples

### Images

<p align="center">
  <img src="/assets/images/athletiq/banner.png" width="800"><br/>
  <i>AthletIQ — an agentic AI biomechanical coach built on the MYOSA Mini IoT Kit</i>
</p>

<p align="center">
  <img src="/assets/images/athletiq/prototype-hero.jpg" width="800"><br/>
  <i>The unified smart belt, with all sensing and processing housed at the lower back</i>
</p>

<p align="center">
  <img src="/assets/images/athletiq/architecture.png" width="800"><br/>
  <i>System architecture: on-belt sensing and processing, off-belt visualisation and AI coaching</i>
</p>

<p align="center">
  <img src="/assets/images/athletiq/process-flow.png" width="800"><br/>
  <i>Process flow from gesture selection through on-device evaluation to the coaching review</i>
</p>

<p align="center">
  <img src="/assets/images/athletiq/prototype-design.jpg" width="800"><br/>
  <i>Component layout: MPU6050, ESP32, and battery on the rigid rear panel; gesture sensor on the front</i>
</p>

<p align="center">
  <img src="/assets/images/athletiq/dashboard.jpg" width="800"><br/>
  <i>The interactive dashboard showing live metrics and the AI coach's review</i>
</p>

### Videos

<video controls width="100%">
  <source src="/athletiq-demo.mp4" type="video/mp4">
</video>

<p align="center"><i>Live demonstration of the three coaching modes — Jump, Plank, and Posture</i></p>

---

## Features (Detailed)

### 1. Unified Single-Belt Design

AthletIQ consolidates the entire MYOSA kit into one compression waist belt. The ESP32 motherboard, the MPU6050 inertial sensor, and the BMP180 are housed on the interior rear panel over the sacrum, while the APDS9960 gesture sensor sits on the exterior front for touchless control.

This consolidation removes the long, fragile inter-sensor wiring of distributed wearable designs — improving reliability during vigorous movement and making the device fast to put on. The lower back sits at the body's centre of mass, the research-backed location for whole-body jump, impact, and posture measurement, and the belt's rigid panel and elastic compression hold the sensor steady against the body to minimise motion artefacts.

### 2. Jump Mode — Explosive Performance

In Jump mode the belt measures vertical jump height, flight time, ground-contact time, Reactive Strength Index (RSI), and peak landing impact. It detects the airborne phase (when acceleration drops into free fall) and the landing spike, then computes jump height from flight time:

```plaintext
height = g × (flight_time)² ÷ 8        (g = 9.81 m/s²)
```

This flight-time method is more accurate for fast vertical movement than barometric estimation. If a landing impact exceeds a safe threshold, the belt buzzes instantly to warn the athlete — an eyes-free injury cue.

### 3. Plank Mode — Core Stability

Plank mode tracks isometric hold time and core stability. It captures a neutral reference at the start, then measures how far the trunk drifts and how much it wobbles (sway), flagging the moment form breaks down.

### 4. Posture Mode — Back-Health Sentinel

Posture mode turns the same sensor into a postural guardian. It continuously monitors trunk and pelvic orientation against a captured neutral and alerts the user when a slouch is sustained too long — extending the device beyond sport into everyday back-health.

### 5. Touchless Gesture Control

A hand swipe over the front of the belt switches modes without buttons or a touchscreen: swipe up for Jump, down for Plank, left for Posture. Each switch is confirmed by a distinct number of haptic pulses, so the athlete knows the active mode without looking.

### 6. On-Device Intelligence + AI Coaching Review

All movement evaluation runs locally on the ESP32 against biomechanical thresholds, ensuring instant feedback with no network dependence. At the end of a set, the dashboard sends the measured session metrics to an AI model that returns a structured coaching review — a performance score and prioritised cues. The model coaches strictly from the measured numbers and never invents metrics, keeping the feedback honest.

---

## Usage Instructions

**Wearing and running the belt:**

1. Fasten the belt with the rigid panel over the lower back, snug against the body.
2. Power the MYOSA Mini IoT Kit and allow it to initialise.
3. Stand still briefly so the system can capture its baseline reference.
4. Select a mode with a hand swipe over the front of the belt (up = Jump, down = Plank, left = Posture).
5. Perform the activity — live metrics and alerts are generated in real time.
6. Open the dashboard, connect, and view live metrics and the session coaching review.

**Connecting the dashboard:**

```plaintext
1. Open athletiq-dashboard.html in desktop Chrome or Edge
2. Power the belt (it advertises over Bluetooth as "AthletIQ-Belt")
3. Click "Connect belt" and select AthletIQ-Belt from the chooser
```

**Uploading the firmware** (one time, over USB):

```plaintext
Arduino IDE → install MYOSA library + ESP32 board package
            → select the MYOSA (ESP32) board → upload athletiq-belt.ino
```

---

## Tech Stack

* **MYOSA Mini IoT Kit (ESP32)** — central processor, Bluetooth, motor driver
* **MPU6050** — inertial sensor at the centre of mass
* **APDS9960** — gesture sensor for touchless control
* **BMP180** — environmental context
* **Arduino (C++)** — firmware with high-rate sensing and on-device biomechanics
* **Bluetooth Low Energy (Nordic UART Service)** — belt-to-dashboard link
* **HTML / CSS / JavaScript (Web Bluetooth)** — interactive dashboard
* **LLM coaching layer (Anthropic API)** — narrates the measured session metrics

---

## Requirements / Installation

**Firmware (Arduino IDE):**

```bash
# Install via the Arduino Library Manager / Boards Manager:
#   - MYOSA library
#   - ESP32 board package
# Then open and upload the firmware:
athletiq-belt.ino
```

**Dashboard:**

```bash
# Open in desktop Chrome or Edge (Web Bluetooth is not supported in Safari/Firefox).
# If the Connect button does not respond when opening the file directly,
# serve it locally:
python -m http.server
# then open http://localhost:8000
```

No additional package installation is required for the dashboard — it runs as a single self-contained HTML file.

---

## File Structure (Optional)

```
/athletiq
  ├─ athletiq-belt.ino          # Arduino firmware for the smart belt
  ├─ athletiq-dashboard.html    # Web Bluetooth dashboard with AI coaching
  ├─ athletiq-demo.mp4          # Demonstration video (landscape)
  ├─ athletiq.md                # This documentation
  └─ assets/images/athletiq/    # Project images
       ├─ cover.jpg
       ├─ banner.png
       ├─ prototype-hero.jpg
       ├─ prototype-design.jpg
       ├─ architecture.png
       ├─ process-flow.png
       └─ dashboard.jpg
```

---

## License (Optional)

This project is released under the **MIT License**. The work is original and follows open-source ethics; no copyrighted material is used without permission.

---

## Contribution Notes (Optional)

This project is intended for research and educational use. Contributors are welcome to open issues or submit improvements. When contributing, please document sensor placement, calibration steps, threshold-tuning procedures, and any validation measurements clearly so results remain reproducible.
