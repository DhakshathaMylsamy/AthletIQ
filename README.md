
<img src="/assets/images/AthletIQ/banner.png">

#### Publish Date: 2026-05-24

#### Title: AthletIQ: An Agentic AI Biomechanical Coach for Athletes Using the MYOSA Mini IoT Kit

#### A unified smart-belt wearable that turns a single low-cost inertial sensor into lab-grade biomechanical feedback, delivering real-time, multi-mode athletic and postural coaching through an on-device intelligence layer and an interactive dashboard.

<p align="center">
  <a href="https://gemini.google.com/" target="_blank">
    <img src="https://cdn.jsdelivr.net/gh/homarr-labs/dashboard-icons/svg/google-gemini.svg" alt="Google Gemini" width="50" />
  </a>
  <br>
  <strong> AthletIQ Powered by Google Gemini</strong>
</p>

---

## Contributors

- **Dhakshatha M K** - [@DhakshathaMylsamy](https://github.com/DhakshathaMylsamy)
- **Nimalan P** - [@nimalan-parameswaran](https://github.com/nimalan-parameswaran)

---

## Acknowledgement

We express our sincere gratitude to **Dr. Allwyn Gnanadas**, Department of Biomedical Engineering, KPR Institute of Engineering and Technology, for his valuable guidance, technical direction, and continuous mentorship throughout this project.

We would also like to acknowledge our classmate, **Sudarshan** - [@suducodes](https://github.com/Suducodes) for his valuable contribution as the athlete model during the physical testing and demonstration of the AthletIQ system.

We also extend our heartfelt thanks to the IEEE International MYOSA 5.0 Committee Members for shortlisting this project and supporting it through the provision of a USD 250 MYOSA Mini IoT Kit.

We also thank the IEEE Sensors Council for encouraging student-led research and applied engineering initiatives.

---

## Overview

**AthletIQ** is a unified smart-belt wearable that delivers real-time biomechanical analysis and adaptive coaching from a single inertial sensor worn at the body's centre of mass.

Commercial fitness trackers report steps and heart rate but cannot judge whether a movement is good or safe. Professional biomechanics labs can, but they rely on force plates and motion-capture systems that cost a fortune and are confined to a room. **AthletIQ bridges this gap** — it extracts clinically meaningful movement metrics from one low-cost sensor in a waist belt, evaluates the quality of each movement on the device itself, and delivers feedback both as an instant haptic buzz on the belt and as an AI coaching review on a dashboard.

Built entirely on the **MYOSA Mini IoT Kit**, the system consolidates all sensing, processing, and feedback into a single compression belt worn at the lower back (sacrum) — the optimal anatomical location for capturing whole-body movement. A front-mounted gesture sensor lets the athlete switch between three coaching modes with a simple hand swipe.

**Who it is for:** grassroots athletes, coaches, physiotherapists, and anyone needing accessible movement analysis without laboratory infrastructure — particularly in resource-constrained settings.

<img src="/assets/images/AthletIQ/prototype.png">

---

## Problem Statement

Existing movement-analysis solutions force a difficult trade-off. Laboratory systems are accurate but prohibitively expensive, immobile, and inaccessible outside specialised facilities. Consumer wearables are affordable and portable but provide only surface-level metrics, with no capacity to assess movement quality, landing safety, or posture.

Multi-sensor wearable approaches that attempt to bridge this gap often introduce their own problems: distributing sensors across the limbs requires long, fragile wiring that is prone to signal loss and mechanical failure during vigorous activity, complicates donning the device, and reduces real-world usability.

There is a need for a single, robust, low-cost wearable that an athlete can put on in seconds, that captures biomechanically meaningful data reliably during intense movement, and that translates that data into actionable coaching feedback — all without dependence on costly infrastructure or unreliable hardware.

---

## Project Objectives

The primary objectives of this project are:

- To design a unified, single-sensor smart belt that captures whole-body biomechanical data from the centre of mass

- To measure athletic performance parameters including vertical jump height, flight time, ground-contact time, Reactive Strength Index, and landing impact

- To extend the same sensor to postural and stability assessment for injury prevention and back-health monitoring

- To implement an on-device intelligence layer that evaluates movement quality and delivers real-time haptic feedback

- To provide gesture-based, touchless mode switching suitable for use during physical activity

- To present metrics and an agentic coaching review through an accessible, interactive dashboard

---

## Solution

AthletIQ is implemented on the MYOSA Mini IoT Kit as a single compression waist belt. The MYOSA motherboard, the inertial sensor, and the barometric sensor are housed on the interior of the belt over the sacrum, while the gesture sensor is mounted on the exterior front for touchless control. This consolidated architecture removes the long inter-limb wiring of distributed designs, improving reliability and making the device fast to wear.

The system operates in three coaching modes, selected by a hand gesture over the front of the belt:

- **Jump mode** measures explosive performance — vertical jump height, flight time, ground-contact time, Reactive Strength Index, and peak landing impact — using a flight-time detection method that is more accurate than barometric estimation for fast vertical movement.

- **Plank mode** measures isometric hold time and core stability, tracking trunk deviation from a captured neutral reference and flagging the moment form breaks down.

- **Posture mode** acts as a back-health sentinel, continuously monitoring trunk and pelvic orientation and alerting the user when a slouch is sustained.

All movement evaluation runs locally on the device against biomechanical thresholds, ensuring instant haptic feedback without network dependence. Metrics are streamed wirelessly to an interactive dashboard, where they are visualised in real time and synthesised into a structured coaching review that summarises performance, highlights faults, and tracks trends across a session.

---

## System Architecture

The architecture is organised around a single sensing node at the centre of mass, an on-belt processing and feedback layer, and an off-belt visualisation and coaching layer.

<img src="/assets/images/AthletIQ/architecture.png">

- **Sensing (on belt):** an inertial sensor at the sacrum captures motion, impact, and orientation; a front-mounted gesture sensor provides touchless mode control; a barometric sensor provides environmental context.
- **Processing (on belt):** the MYOSA motherboard runs the mode-specific biomechanical algorithms and threshold-based fault detection, and drives the haptic feedback.
- **Feedback (on belt):** a vibration motor provides instant, eyes-free alerts for unsafe landings, form breaks, and sustained slouching.
- **Visualisation and coaching (off belt):** metrics are streamed wirelessly to an interactive dashboard that renders live signals, per-mode metric panels, session history, and an agentic coaching review.

---

## Process Flow

<img src="/assets/images/AthletIQ/process_flow.png">

---

## Prototype

### Prototype Design

<img src="/assets/images/AthletIQ/prototype_design.jpg">

The prototype consolidates the MYOSA motherboard, inertial sensor, barometric sensor, actuator, and battery on the rigid rear panel of a compression waist belt, positioned over the sacrum. The gesture sensor is mounted externally on the front closure for touchless mode switching. The rigid panel provides a stable, low-motion mounting surface, and the elastic compression couples the sensor tightly to the body to minimise motion artefacts during dynamic movement.

### Demo Video


https://github.com/user-attachments/assets/88d235dc-c3f2-44bd-8a82-0d6d0d49e3de


<video controls width="100%">
  <source src="/assets/demovideo.mp4" type="video/mp4">
</video>

### Interactive Dashboard

<img src="/assets/images/AthletIQ/dashboard.png">

---

## Measured Parameters

| Mode    | Parameter              | Description                                                        |
| ------- | ---------------------- | ------------------------------------------------------------------ |
| Jump    | Vertical jump height   | Computed from flight time using the flight-time model              |
| Jump    | Flight time            | Duration of the airborne phase                                     |
| Jump    | Ground-contact time    | Time on the ground between consecutive landings and take-offs      |
| Jump    | Reactive Strength Index| Jump height divided by ground-contact time                         |
| Jump    | Peak landing impact    | Maximum landing force at the centre of mass, in g                  |
| Jump    | Jump count             | Repetitions detected within a session                              |
| Plank   | Hold time              | Duration of the isometric hold                                     |
| Plank   | Stability / sway       | Variability of trunk orientation during the hold                   |
| Plank   | Form-break alert       | Triggered when trunk deviation exceeds the threshold               |
| Posture | Trunk deviation        | Angular deviation of the trunk from a captured neutral reference   |
| Posture | Slouch alert           | Triggered when a slouch is sustained beyond a set duration         |
| Posture | Good-posture ratio     | Proportion of session time spent within the neutral posture range  |

---

## Novelty

- Consolidation of the MYOSA kit into a single unified smart belt, eliminating the fragile inter-limb wiring of distributed wearable designs
- Extraction of multiple, clinically meaningful biomechanical parameters from a single low-cost inertial sensor at the centre of mass
- A flight-time jump-measurement method that is more accurate for fast vertical movement than barometric altimetry
- Multi-mode operation spanning athletic performance, core stability, and postural health from one sensor
- Touchless, gesture-based mode switching designed for uninterrupted use during physical activity
- On-device, threshold-based movement evaluation with instant haptic feedback and no network dependence
- An agentic coaching review that converts deterministic biomechanical metrics into prioritised, human-readable guidance
- Modular design using the MYOSA Mini IoT Kit, suitable for educational and research reuse

---

## Scope of the Project

This project covers single-sensor biomechanical measurement at the centre of mass, multi-mode athletic and postural analysis, on-device movement evaluation with haptic feedback, gesture-based control, and dashboard-based visualisation and coaching within controlled demonstration conditions.

Clinical validation, per-joint angle measurement, large-scale field deployment, and industrial manufacturing considerations are outside the present scope. Distance-derived metrics are reported with appropriate caveats, and the device is presented as a development prototype rather than a finished consumer product.

---

## Outcomes

- A functional unified smart-belt prototype capturing biomechanical data from a single sacral sensor
- Reliable detection of jump performance metrics, validated against a physical reference measurement
- Real-time landing-impact monitoring with instant haptic alerts for unsafe technique
- Working core-stability and postural-monitoring modes derived from the same sensor
- Touchless gesture-based mode switching during activity
- An interactive dashboard presenting live metrics, session history, and a structured coaching review
- A reusable, low-cost platform demonstrating accessible biomechanical analysis

---

## Features

- Unified single-belt wearable with all electronics co-located at the centre of mass
- Three coaching modes: Jump, Plank, and Posture
- Gesture-based touchless mode switching
- Vertical jump height, flight time, contact time, RSI, and landing impact measurement
- Core-stability and isometric-hold analysis
- Continuous postural monitoring with slouch detection
- Instant, eyes-free haptic feedback for unsafe movement and posture
- On-device evaluation with no network dependence for safety-critical feedback
- Wireless streaming to an interactive real-time dashboard
- Agentic coaching review with performance trends and prioritised cues

---

## Usage Instructions

1. Fasten the belt with the rigid panel positioned over the lower back, snug against the body
2. Power the MYOSA Mini IoT Kit and allow the device to initialise
3. Stand still briefly to allow the system to capture its baseline reference
4. Select an exercise mode with a hand swipe over the front of the belt
5. Perform the activity; live metrics and alerts are generated in real time
6. Open the dashboard in a desktop Chrome or Edge browser, click **Connect belt**, and select **AthletIQ-Belt** from the Bluetooth chooser to view live signals, metric panels, and the session coaching review

---

## Tech Stack

### Hardware

- MYOSA Motherboard (ESP32)
- MPU6050 (inertial sensor, centre of mass)
- APDS9960 (gesture control)
- BMP180 (environmental context)
- Coin vibration motor/buzzer (haptic feedback)
- Compression waist belt (housing)

### Firmware

- Arduino (C++)
- High-rate IMU acquisition and on-device biomechanical algorithms
- Threshold-based movement and posture evaluation

### Connectivity

- Bluetooth Low Energy (Nordic UART Service)

### Intelligence

- On-device threshold-based movement and posture evaluation
- LLM-based coaching review (Gemini API) that narrates the measured session metrics

### Frontend

- HTML
- CSS
- JavaScript
- Web Bluetooth dashboard

---

## Requirements / Installation

This repository contains the firmware and dashboard for the AthletIQ smart belt.

1. Clone the repository:

```
https://github.com/DhakshathaMylsamy/AthletIQ.git
```

2. Firmware:

- Open firmware/athletiq_belt.ino in the Arduino IDE
- Install the MYOSA library and the ESP32 board package
- Select the MYOSA (ESP32) board and upload to the motherboard

3. Dashboard:

- Open `athletiq_dashboard.html` in a desktop Chrome or Edge browser (Web Bluetooth is not supported in Safari or Firefox)
- If the Connect button does not respond when opening the file directly, serve it locally (for example, run `python -m http.server` in the dashboard folder and open `localhost:8000`)
- Power the belt, click **Connect belt**, and select **AthletIQ-Belt** to begin streaming
- To enable the AI coaching review, paste a Gemini API key into the field on the Coach's Review card; the key is held only in the browser session and is never stored or committed

Hardware assembly and sensor mounting are described in the prototype section.

---

## File Structure

```
AthletIQ/
├── firmware/
│   └── athletiq_belt.ino
│
├── dashboard/
│   └── athletiq_dashboard.html
│
├── assets/
│   ├── prototype_design.png
│   ├── architecture.png
│   ├── process_flow.png
│   ├── dashboard.png
│   └── demovideo.mp4
│
├── LICENSE
└── README.md
```

---

## License

This project is licensed under the MIT License. Refer to the LICENSE file for details.

---

## Contribution Notes

This repository is intended for research and educational use. Contributors are encouraged to document sensor placement, calibration steps, threshold-tuning procedures, and validation measurements clearly when submitting updates.
