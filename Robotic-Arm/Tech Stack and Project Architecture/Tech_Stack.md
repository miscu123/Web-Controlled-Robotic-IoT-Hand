# 🧠 Tech Stack Overview

This document outlines the technologies and tools used to build the **Web Controlled Robotic Hand** — a project that allows users to send commands to ESP32 microcontrollers and log command history.

---

## 🐍 Backend — Python + Flask

**Purpose:**  
Provides the web server, handles API requests from the frontend, executes Python functions, and communicates with the ESP32 (via Serial or Wi-Fi).

**Why Flask?**

- Lightweight and easy to set up.
- Perfect for small web apps or dashboards.
- Flexible — integrates easily with serial communication, REST APIs, and databases.

**Responsibilities:**

- Serve the web interface (HTML/JS/CSS).
- Receive commands from the frontend.
- Communicate with ESP32 (via USB serial or network).
- Log command history to the database.
- Provide REST API endpoints for control and data retrieval.

---

## 🌐 Frontend — HTML, CSS, JavaScript

**Purpose:**  
Provides the user interface for interacting with the ESP32 controller through the browser.

**Technologies:**

- **HTML** — Structure of the web page (buttons, layout, etc.)
- **CSS** — Styling and layout customization for clean UI
- **JavaScript** — Handles user interactions and sends HTTP requests to Flask backend via `fetch()` or AJAX

**Responsibilities:**

- Display control buttons, sliders, and feedback messages.
- Send commands to Flask backend (e.g., `/control`, `/status`).
- Update the UI based on backend responses.

**Example Interaction Flow:**

1. User clicks a button (e.g., “Turn ON”).
2. JS sends a POST request to `/control` with command data.
3. Flask processes the command and responds with JSON.
4. JS updates the page with the response (“LED ON confirmed”).

---

### 🧩 Hardware Components

- ESP32 Development Board
- 7x Servo Motors (SG90 / MG996R)
- External 5V Power Supply
- Breadboard & Jumper Wires
- 3D Printed / Acrylic Hand Frame
- Fishing & elastic rope

---

## 🗃️ Database — MongoDB

**Purpose:**  
Stores a **history of commands** sent to ESP32s, including timestamps and results.

**Why MongoDB?**

- Schemaless and flexible — perfect for simple logging.
- JSON-like documents make it easy to store and retrieve command records.
- Easy integration with Python via `pymongo`.

**Example Document Structure:**

```json
{
  "timestamp": "2025-10-08T12:34:56Z",
  "device_id": "esp32_01",
  "command": "on",
  "result": "success"
}
```
