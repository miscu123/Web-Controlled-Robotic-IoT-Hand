# Web-Controlled Robotic Hand – IoT-Based Remote Manipulation System

## The Project Overview

**Web-Controlled Robotic Hand** is an **IoT-enabled embedded systems project** that integrates **HW (servo-actuated robotic fingers)** & **SW (web-based control interface)** to demonstrate real-time robotic manipulation over Wi-Fi.

The system allows users to control a robotic hand from any device with a browser, sending commands through a modern web interface to move, flex, or hold specific finger positions.  
It combines **embedded programming**, **web communication**, **animatroniocs** & **mechanical design**, making it an excellent showcase of cross-disciplinary engineering.

---

## Main Objectives

### Embedded System Design

Develop the core embedded system responsible for:

- Servo motor control using PWM signals
- Wi-Fi connectivity and web server hosting on ESP32
- Real-time command processing and feedback handling

### Web Interface Development

Design and implement a **responsive control dashboard** that enables users to:

- Send movement commands to individual fingers
- Trigger pre-defined hand gestures (e.g., open, close, peace sign)
- Visualize live feedback or system status

### Hardware-Software Integration

Establish a seamless communication layer between the **WEB Interface** & **ESP32 MCU** using protocols such as:

- HTTP requests
- WebSockets for real-time control

---

## Planned Features

### Interactive Web Dashboard

- Control each finger via sliders / buttons
- Execute saved gestures instantly
- Monitor servo positions and feedback sensors

### Real-Time Communication

- Instant response through WebSocket or MQTT
- Bi-directional updates between device and web interface

### Hardware Integration

- 6-finger robotic hand actuated by servo motors (5 for fingers, 1 for wrist rotation)
- 03D printed or acrylic mechanical structure / straight up bought hand
- ESP32-based embedded controller

### IoT Connectivity

- Control the robotic hand from any browser over Wi-Fi

### Data Logging (Optional)

- Record action logs and store them into a database

---

## Development Roadmap

| Phase                      | Description                               | Output                  |
| -------------------------- | ----------------------------------------- | ----------------------- |
| **1. Servo Control**       | Basic servo control using ESP32 PWM       | Single finger motion    |
| **2. Wi-Fi Setup**         | Connect ESP32 to local Wi-Fi network      | Network connectivity    |
| **3. Web Server**          | Host control webpage on ESP32             | Browser-based control   |
| **4. Multi-Servo Control** | Add all 6 servos with coordinated motion  | Functional robotic hand |
| **5. Mechanical Assembly** | Build and mount servos to frame           | Fully assembled hand    |
| **6. Full Web UI**         | Add sliders, presets, and gesture buttons | Interactive interface   |

---

## Tools & Frameworks

- VS Code & PlatformIO
- Node.js (optional backend)
- Vanilla JS for frontend
- CSS for styling
- Git & GitHub for version control

---

## Contributors

**Mihai Albu** – Automotive Embedded Systems Junior Software Developer

---

## License

This project is licensed under the **MIT License** – feel free to modify and improve upon it for educational and research purposes.

---
