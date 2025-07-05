# ✋ Gesture-Controlled Differential Drive Robot | YOLO + OpenCV + ESP8266

> A vision-based robot control system that recognizes hand gestures using deep learning and keypoint detection, translating them into real-time movement commands for a differential-drive robot powered by ESP8266 and L293D motor driver.

---

## 🎯 Objective

To develop an **AI-powered gesture recognition system** for controlling a differential-drive robot without physical contact, enabling intuitive motion control using only hand gestures captured by a camera.

---

## ⚙️ Technologies Used

| Domain                  | Tools / Libraries                          |
|--------------------------|--------------------------------------------|
| Gesture Recognition      | TensorFlow, OpenCV, YOLOv8, MediaPipe     |
| Keypoint Detection       | TensorFlow Keypoint Classifiers            |
| Image Processing         | OpenCV                                     |
| Robot Control            | ESP8266, Embedded C, WiFi/Serial Protocol |
| Motor Driver             | L293D                                      |
| Embedded Communication   | UART / Wi-Fi (HTTP / TCP)                 |
| Platform                 | PC / Jetson Nano / Raspberry Pi (vision)  |

---

## 🔩 Hardware Stack

| Module               | Purpose                          |
|----------------------|----------------------------------|
| ESP8266 NodeMCU       | Wi-Fi-enabled robot controller   |
| L293D Motor Driver    | Controls 2 DC motors             |
| Differential Drive    | Robot chassis (Left & Right)    |
| Power Supply          | 9V Battery + 7805 Regulator     |
| USB/Webcam            | Captures live gesture images    |

---

## 🛠️ Implementation Steps

### ➤ Gesture Detection Pipeline
- Used **YOLOv8 / MediaPipe** for real-time hand detection.
- Extracted hand landmarks and fed them into a **TensorFlow keypoint classifier** trained on custom gesture datasets (e.g., forward, stop, left, right).
- Classified gestures into motion commands.

### ➤ Robot Communication
- Vision system sends commands (`FORWARD`, `BACKWARD`, `LEFT`, `RIGHT`, `STOP`) to the ESP8266 via:
   - Serial UART communication **OR**
   - Wi-Fi (HTTP requests or TCP sockets).

### ➤ Motor Control Logic
- ESP8266 receives commands and drives the **L293D motor driver** accordingly:
   - **Forward:** Both motors forward.
   - **Backward:** Both motors reverse.
   - **Left / Right:** Differential control.
   - **Stop:** Motors off.

---

## 🔬 Key Features

- Real-time gesture recognition with **~30 FPS** processing on low-end CPUs.
- Modular architecture: vision + classification on PC/RPi, motor control on ESP8266.
- Robust against background clutter using YOLO’s confidence filtering.

---

## 📈 Improvements & Future Work

- Replace YOLO + OpenCV with TensorFlow Lite for embedded deployment.
- Integrate PID for smoother motor speed transitions.
- Optimize gesture dataset for broader hand sizes and lighting conditions.
- Deploy vision module on a Jetson Nano or Raspberry Pi 4 for portability.

---

## 🛡️ Summary

This project demonstrates an end-to-end gesture-controlled robotics system leveraging **computer vision**, **deep learning**, and **microcontroller-based motor control**. It provides a robust example of human-robot interaction in embedded systems.

---
