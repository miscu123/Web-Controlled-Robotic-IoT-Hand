# Tech Stack Overview

This document outlines the technologies and tools used to build the **Web-Controlled Robotic Hand** — a project that enables users to control servo motors via a web interface hosted directly on an **ESP32** microcontroller.

---

## Backend — C++ (ESP32 Web Server)

**Purpose:**  
Implements an onboard web server using **C++ (Arduino framework)** to handle HTTP requests from the browser, control servo motors, and manage communication between the web interface and the robotic hand hardware.

**Why C++ on ESP32?**

- Runs natively on the microcontroller — no external computer or server needed.
- Efficient memory and performance management.
- Full control over hardware interfaces (GPIO, PWM, Serial, etc.).
- Supports **Wi-Fi** mode for flexible connectivity.

**Responsibilities:**

- Host and serve the HTML/JS web interface.
- Receive and process HTTP requests from the browser.
- Control servo positions based on user commands.
- Maintain connection with all hardware components (motors, sensors, etc.).
- Log command activity.

**Example Flow:**

1. ESP32 connects to Wi-Fi or starts its own access point.
2. ESP32 hosts a web page at a local IP.
3. User opens the page in a browser.
4. When the user sends a command, a **FETCH** request is sent to the ESP32 web server.
5. ESP32 parses the command, moves the servos, and sends a response (JSON or plain text).

---

## Frontend — HTML, CSS, JavaScript

**Purpose:**  
Provides the user interface for controlling the robotic hand from any web browser (PC, tablet, or phone).

**Technologies:**

- **HTML** — Defines the layout and controls (buttons, sliders, etc.).
- **CSS** — Styles the interface for a clean and responsive design.
- **JavaScript** — Sends commands to the ESP32 via HTTP requests and updates the interface dynamically.

**Responsibilities:**

- Display control buttons and sliders for each servo motor.
- Send control commands (e.g., finger positions) to the ESP32.
- Display real-time feedback (e.g., connection status, command confirmation).

**Example Interaction Flow:**

1. User adjusts a slider or presses a control button.
2. JavaScript sends an HTTP request to a specific endpoint on the ESP32 (e.g., `/servo?finger=1&angle=90`).
3. The ESP32 processes the command and moves the corresponding servo.
4. The web interface updates with a confirmation message or animation.

---

## Hardware Components

- **ESP32 Development Board**
- **PCA9685 — 16-channel I2C PWM servo driver**
- **6× Servo Motors (MG90S)** — 5 fingers + 1 additional thumb servo
- **Jumper Wires**
- **3D Printed Hand & Forearm Frame**
- **Fishing Line & Elastic Rope (for finger movement and tendons)**

## Hardware Communication

The ESP32 no longer drives servo PWM signals directly from GPIO pins. Instead, it sends I2C commands over **SDA (GPIO 21)** and **SCL (GPIO 22)** to the PCA9685, which generates the PWM signals for all 6 servo channels independently. This frees up GPIO pins and allows up to 16 servos on just 2 wires.