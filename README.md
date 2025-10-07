# Web-Controlled Robotic Hand – IoT-Based Remote Manipulation System

## 📌 Project Overview

**Web-Controlled Robotic Hand** is an **IoT-enabled embedded systems project** that integrates **hardware (servo-actuated robotic fingers)** and **software (web-based control interface)** to demonstrate real-time robotic manipulation over Wi-Fi.

The system allows users to control a robotic hand from any device with a browser, sending commands through a modern web interface to move, flex, or hold specific finger positions.  
It combines **embedded programming**, **web communication**, and **mechanical design**, making it an excellent showcase of cross-disciplinary engineering.

---

## 🎯 Main Objectives

### ⚙️ Embedded System Design

Develop the core embedded system responsible for:

- Servo motor control using PWM signals  
- Wi-Fi connectivity and web server hosting on ESP32  
- Real-time command processing and feedback handling  

### 🌐 Web Interface Development

Design and implement a **responsive control dashboard** that enables users to:

- Send movement commands to individual fingers  
- Trigger pre-defined hand gestures (e.g., open, close, peace sign)  
- Visualize live feedback or system status  

### 🔗 Hardware-Software Integration

Establish a seamless communication layer between the **web interface** and **ESP32 microcontroller** using protocols such as:

- HTTP requests  
- WebSockets for real-time control  
- MQTT (optional, for cloud expansion)  

### 🧠 System Intelligence (Optional Extensions)

Implement advanced features such as:

- Gesture recording and replay  
- Sensor-based feedback (force/flex sensors)  
- AI-based gesture imitation using camera or glove input  

---

## 🔧 Planned Features

### 🖥️ Interactive Web Dashboard
- Control each finger via sliders or buttons  
- Execute saved gestures instantly  
- Monitor servo positions and feedback sensors  

### 🤝 Real-Time Communication
- Instant response through WebSocket or MQTT  
- Bi-directional updates between device and web interface  

### ⚙️ Hardware Integration
- 5-finger robotic hand actuated by servo motors  
- 3D printed or acrylic mechanical structure  
- ESP32-based embedded controller  

### 📶 IoT Connectivity
- Control the robotic hand from any browser over Wi-Fi  
- Optional cloud access for remote operation  

### 📈 Data Logging (Optional)
- Record servo movement history and replay motion sequences  

---

## 🛠️ Tech Stack

### 🧠 Embedded Layer
- **Microcontroller:** ESP32  
- **Language:** C++ (Arduino framework)  
- **Libraries:** Servo.h, WiFi.h, WebServer.h, AsyncWebSocket  

### 🌐 Software Layer
- **Frontend:** HTML, CSS, JavaScript (or React.js)  
- **Backend (Optional):** Node.js / Flask / Firebase  
- **Communication Protocols:** HTTP / WebSocket / MQTT  

### 🧩 Hardware Components
- ESP32 Development Board  
- 5x Servo Motors (SG90 / MG996R)  
- External 5V Power Supply  
- Breadboard & Jumper Wires  
- 3D Printed / Acrylic Hand Frame  
- Optional: Flex or Pressure Sensors  

---

## 🧩 Development Roadmap

| Phase | Description | Output |
|--------|--------------|---------|
| **1. Servo Control** | Basic servo control using ESP32 PWM | Single finger motion |
| **2. Wi-Fi Setup** | Connect ESP32 to local Wi-Fi network | Network connectivity |
| **3. Web Server** | Host control webpage on ESP32 | Browser-based control |
| **4. Multi-Servo Control** | Add all 5 servos with coordinated motion | Functional robotic hand |
| **5. Mechanical Assembly** | Build and mount servos to frame | Fully assembled hand |
| **6. Full Web UI** | Add sliders, presets, and gesture buttons | Interactive interface |
| **7. Feedback System (optional)** | Add sensors for force/flex detection | Real-time data visualization |

---

## 🧠 Learning Outcomes

Through this project, you will gain experience in:

- Embedded systems programming with ESP32  
- Real-time web communication  
- IoT systems design and architecture  
- PWM-based motor control  
- Hardware and software co-design  
- UI/UX for IoT control interfaces  

---

## 📦 Installation & Usage

### ⚙️ Hardware Setup
1. Connect each servo to ESP32 PWM pins (e.g., D13–D17).  
2. Power servos with an external 5V supply (common ground with ESP32).  
3. Assemble servos to hand frame and calibrate positions.  

### 💻 Software Setup
1. Flash ESP32 with Arduino sketch.  
2. Connect ESP32 to Wi-Fi or use Access Point mode.  
3. Open browser and navigate to ESP32 IP address.  
4. Control the hand through the dashboard!  

---

## 🛠️ Tools & Frameworks

- Arduino IDE / PlatformIO  
- Node.js (optional backend)  
- React.js or vanilla JS for frontend  
- TailwindCSS for styling  
- Git & GitHub for version control  

---

## 🧩 Possible Future Enhancements

- Integration with gesture-detecting gloves  
- Cloud dashboard for remote global access  
- Haptic feedback or AI imitation control  
- Mobile app interface  
- Voice commands (via browser API)  

---

## 👨‍💻 Contributors

**Mihai Albu** – Embedded Systems Junior Software Developer

---

## 🧾 License

This project is licensed under the **MIT License** – feel free to modify and improve upon it for educational and research purposes.

---
