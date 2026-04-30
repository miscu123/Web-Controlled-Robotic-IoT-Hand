# ESP32 RTOS Gesture Control – Architecture Overview

---

## Key Components

### ESP32 RTOS Environment

- Runs FreeRTOS for multitasking
- Enables concurrent execution of:
  - Web server
  - Servo control
  - WiFi stack

---

### Tasks

#### servo_task

- Controls all servo movements
- Executes:
  - update_gesture() (state machine)
  - Direct finger commands

#### AsyncWebServer Task

- Handles incoming HTTP requests
- Parses parameters
- Sends commands to queue

---

### Data Passing

#### commandQueue

- Thread-safe FreeRTOS queue
- Decouples:
  - Web server (producer)
  - Servo task (consumer)

---

### State Machine (gesture_ctx)

Tracks gesture execution:

- current_gesture
- step
- angle
- count (repetitions)

Enables non-blocking, incremental execution.

---

### JavaScript Frontend

- Sends async HTTP requests:
  - /gesture?name=...
  - /finger?finger=...&angle=...
- Updates UI instantly

---

## Async Command Flow

- User interacts with UI
- JS sends async request:
  fetch(`/gesture?name=${name}`)

- ESP32 Web Server:
  - Parses request
  - Creates Command struct
  - Pushes to commandQueue
  - Responds with status

- servo_task loop:
  - Reads queue (non-blocking)
  - CMD_GESTURE → init_gesture()
  - CMD_FINGER → servo.write()
  - Calls update_gesture()
  - Uses vTaskDelay(8ms)

- update_gesture():
  - Executes small step
  - Updates state
  - Returns immediately

- FreeRTOS Scheduler runs tasks concurrently

---

## Flow Overview

User Browser → Web Server → Queue → Servo Task → Servos

---

## Key Insights

- vTaskDelay allows multitasking
- Queue prevents blocking
- State machine avoids delays
- Async JS keeps UI responsive

---

## Architecture Comparison

Before:
HTTP → Direct Servo Control

After:
Web Server → Queue → Servo Task → Hardware

---

## Core Usage

Core 0:

- WiFi
- Web Server
- Push commands

Core 1:

- Servo task
- Process queue
- Execute gestures

---

## JavaScript Flow

setGesture(name):

- Sends /gesture request

setFingerAngle(finger, angle):

- Sends /finger request

---

## End-to-End Flow

Browser → Web Server → Queue → Servo Task → update_gesture → Servos

---

## Final Takeaway

- True concurrency
- Safe communication
- Smooth motion
- Responsive UI
