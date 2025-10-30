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
- Supports both **Wi-Fi** and **access point (AP)** modes for flexible connectivity.

**Responsibilities:**

- Host and serve the HTML/JS web interface.
- Receive and process HTTP requests from the browser.
- Control servo positions based on user commands.
- Maintain connection with all hardware components (motors, sensors, etc.).
- Log command activity (optional via EEPROM, SD card, or external server).

**Example Flow:**

1. ESP32 connects to Wi-Fi or starts its own access point.
2. ESP32 hosts a web page at a local IP (e.g., `192.168.4.1`).
3. User opens the page in a browser.
4. When the user sends a command, a **GET** or **POST** request is sent to the ESP32 web server.
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
- **6× Servo Motors (SG90 / MG996R)**
- **External 5V Power Supply**
- **Breadboard & Jumper Wires**
- **3D Printed or Acrylic Hand Frame**
- **Fishing Line & Elastic Rope (for finger movement)**

---

## Database — MongoDB

**Purpose:**  
Stores a **history of commands** sent to ESP32s, including timestamps and results.

**Why MongoDB?**

- Schemaless and flexible — perfect for simple logging.
- JSON-like documents make it easy to store and retrieve command records.

**Example Document Structure:**

```json
{
  "timestamp": "2025-10-08T12:34:56Z",
  "device_id": "esp32_01",
  "command": "on",
  "result": "success"
}
```
