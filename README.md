
<img src="/assets/images/AthletIQ/banner.png">

#### Publish Date: 2026-05-24

#### Title: AthletIQ: An Agentic AI Biomechanical Coach for Athletes Using the MYOSA Mini IoT Kit

#### A unified smart-belt wearable that turns a single low-cost inertial sensor into lab-grade biomechanical feedback, delivering real-time, multi-mode athletic and postural coaching through an on-device intelligence layer and an interactive dashboard.

---

## Contributors

- **Dhakshatha M K** - [@DhakshathaMylsamy](https://github.com/DhakshathaMylsamy)
- **Nimalan P** - [@nimalan-parameswaran](https://github.com/nimalan-parameswaran)

---

## Acknowledgement

We express our sincere gratitude to **Dr. Allwyn Gnanadas**, Department of Biomedical Engineering, KPR Institute of Engineering and Technology, for his valuable guidance, technical direction, and continuous mentorship throughout this project.

We would also like to acknowledge our classmate, **Sudarshan** - [@suducodes](https://github.com/Suducodes) for his valuable contribution as the athlete model during the physical testing and demonstration of the AthletIQ system.

We also extend our heartfelt thanks to the **IEEE Sensors Council** for sponsoring the **MYOSA Mini IoT Kit**, which played a crucial role in enabling the development and implementation of this work.

---

## Table of Contents

| No. | Section                                                    |
| --- | ---------------------------------------------------------- |
| 1   | [Overview](#overview)                                      |
| 2   | [Background](#background)                                  |
| 3   | [Problem Statement](#problem-statement)                    |
| 4   | [Project Objectives](#project-objectives)                  |
| 5   | [Solution](#solution)                                      |
| 6   | [System Architecture](#system-architecture)                |
| 7   | [Process Flow](#process-flow)                              |
| 8   | [Prototype](#prototype)                                    |
| 9   | [Measured Parameters](#measured-parameters)                |
| 10  | [Novelty](#novelty)                                        |
| 11  | [Scope of the Project](#scope-of-the-project)              |
| 12  | [Outcomes](#outcomes)                                      |
| 13  | [Features](#features)                                      |
| 14  | [Usage Instructions](#usage-instructions)                  |
| 15  | [Tech Stack](#tech-stack)                                  |
| 16  | [Requirements / Installation](#requirements--installation) |
| 17  | [File Structure](#file-structure)                          |
| 18  | [License](#license)                                        |
| 19  | [Contribution Notes](#contribution-notes)                  |

---

## Overview

**AthletIQ** is a unified smart-belt wearable that delivers real-time biomechanical analysis and adaptive coaching from a single inertial sensor positioned at the body's centre of mass. The entire system is consolidated into one compression waist belt, with all sensing, processing, and feedback co-located at the sacrum — the optimal anatomical location for capturing whole-body kinematics.

The platform is built around the MYOSA Mini IoT Kit and operates as a multi-mode coaching system. A front-mounted gesture sensor allows the athlete to switch between exercise modes with a simple hand swipe, while the inertial sensor at the lower back measures motion, impact, posture, and stability. An on-device intelligence layer evaluates each movement against biomechanical thresholds and generates corrective feedback, which is delivered both as instant haptic alerts on the belt and as a structured coaching review on an interactive dashboard.

AthletIQ is designed to bridge the gap between expensive laboratory biomechanics systems and basic consumer fitness trackers. By extracting clinically meaningful metrics from a single low-cost sensor, the system demonstrates how accessible, professional-grade movement analysis can be democratised for grassroots sports training, injury prevention, and postural health.

---

## Background

Biomechanical analysis of human movement has traditionally required expensive, fixed laboratory infrastructure such as optical motion-capture systems and force plates. These systems deliver high accuracy but are inaccessible to the vast majority of athletes, coaches, and clinicians, particularly in resource-constrained settings. At the opposite end of the spectrum, consumer wearables provide only generalised metrics such as step counts and heart rate, and lack the ability to evaluate the quality of a movement or detect harmful technique.

The body's centre of mass, located near the sacrum, is a well-established anatomical reference for whole-body movement analysis. An inertial measurement unit (IMU) placed at this location can capture jump kinematics, landing forces, trunk posture, and postural stability with strong validity, a principle used by commercial jump-measurement devices and supported by sports-science research. A single, well-placed sensor can therefore yield a surprisingly rich set of biomechanical parameters without the cost and complexity of multi-node or lab-based systems.

Advances in low-cost IMUs, embedded machine learning, and wireless communication now make it possible to perform meaningful biomechanical computation directly on a wearable device and stream the results to an everyday phone or laptop. AthletIQ applies these capabilities to a single MYOSA-based belt, transforming an inexpensive educational IoT kit into a credible biomechanical coaching platform.

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

<video controls width="100%">
  <source src="/assets/your-video-name.mp4" type="video/mp4">
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
- Coin vibration motor (haptic feedback)
- Compression waist belt (housing)

### Firmware

- Arduino (C++)
- High-rate IMU acquisition and on-device biomechanical algorithms
- Threshold-based movement and posture evaluation

### Connectivity

- Bluetooth Low Energy (Nordic UART Service)

### Intelligence

- On-device threshold-based movement and posture evaluation
- LLM-based coaching review (Anthropic API) that narrates the measured session metrics

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
git clone https://github.com/<your-username>/AthletIQ.git
```

2. Firmware:

- Open the firmware sketch in the Arduino IDE
- Install the MYOSA library and the ESP32 board package
- Select the MYOSA (ESP32) board and upload to the motherboard

3. Dashboard:

- Open `athletiq_dashboard.html` in a desktop Chrome or Edge browser (Web Bluetooth is not supported in Safari or Firefox)
- If the Connect button does not respond when opening the file directly, serve it locally (for example, run `python -m http.server` in the dashboard folder and open `localhost:8000`)
- Power the belt, click **Connect belt**, and select **AthletIQ-Belt** to begin streaming
- To enable the AI coaching review, paste an Anthropic API key into the field on the Coach's Review card; the key is held only in the browser session and is never stored or committed

Hardware assembly and sensor mounting are described in the prototype section.

---

## File Structure

```
AthletIQ/
├── firmware/ — Arduino firmware for the smart belt
│   └── AthletIQ_Belt.ino
│
├── dashboard/ — Web Bluetooth dashboard with AI coaching review
│   └── athletiq_dashboard.html
│
├── assets/
│   └── images/
│       └── AthletIQ/ — Project images referenced by this document
│
├── LICENSE — MIT License
└── README.md — Project documentation
```

---

## License

This project is licensed under the MIT License. Refer to the LICENSE file for details.

---

## Contribution Notes

This repository is intended for research and educational use. Contributors are encouraged to document sensor placement, calibration steps, threshold-tuning procedures, and validation measurements clearly when submitting updates.
