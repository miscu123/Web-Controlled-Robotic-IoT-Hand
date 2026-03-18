ESP32 RTOS Gesture Control – Architecture Overview

1. Key Components

ESP32 RTOS Environment:

- FreeRTOS handles multiple tasks concurrently.

Tasks:

- servo_task – Handles all servo motions via update_gesture() and direct finger angle commands.
- AsyncWebServer task – Handles incoming HTTP requests from the browser or any client.

Data Passing:

- Queue (commandQueue) – Thread-safe communication between web server and servo_task.

State Machines:

- gesture_ctx tracks:
  - current_gesture
  - step
  - angle
  - count (repeat counter)
- Executes gestures incrementally, non-blocking.

JS Frontend:

- Sends /gesture?name=... or /finger?finger=...&angle=... requests asynchronously.
- Updates sliders instantly.

2. Async Command Flow

1. User triggers gesture on webpage.
1. JS sends HTTP request asynchronously to ESP32:
   fetch(`/gesture?name=${name}`)
1. AsyncWebServer receives request:
   - Extracts parameters (gesture or finger+angle)
   - Packs into Command struct
   - Pushes into commandQueue (xQueueSend)
   - Responds 200 OK or 500 Queue full
1. servo_task loop:
   - Checks commandQueue via xQueueReceive (non-blocking)
   - CMD_GESTURE → init_gesture(cmd.gesture)
   - CMD_FINGER → servo.write() directly
   - Calls update_gesture()
   - vTaskDelay(8ms) → yields to other tasks
1. update_gesture():
   - Executes step-by-step gestures
   - Updates gesture_ctx
   - Non-blocking, exits after small action
1. FreeRTOS scheduler allows web server, WiFi, and other tasks to run concurrently.

1. Flowchart Concept (Textual)

User Browser
│
├─ JS Fetch /gesture or /finger
▼
ESP32 AsyncWebServer
│
├─ Validate parameters
│
├─ Create Command struct
│
├─ Push Command to commandQueue
│
└─ Respond 200 OK
▼
servo_task Loop
│
├─ xQueueReceive(commandQueue)
│ ├─ CMD_GESTURE → init_gesture()
│ └─ CMD_FINGER → move servo
│
├─ update_gesture() – increment step/angle
│
└─ vTaskDelay(8ms) → yield
▼
Next iteration

4. Key Insights

- vTaskDelay yields every 8ms → gestures and server run concurrently
- Queue decouples tasks → server never blocks
- State machine executes gestures in small increments → non-blocking
- JS async fetch → frontend updates instantly

Code logic architecture:
[ Web Server Task ] → [ Command Queue ] → [ Servo Control Task ] → [ Hardware (Servos) ]

Before:

- HTTP → directly moves servos ❌
- Race conditions ❌
- Unsafe concurrency ❌

After:

- HTTP → queue → servo task → hardware ✅

5. Core Usage Flow

Core 0 (PRO_CPU) – System / WiFi / Web Server

- Handles HTTP requests
- Pushes Command structs into queue
- Non-blocking, allows Core 1 to run servo_task

Core 1 (APP_CPU) – Servo Task

- Pulls Command from queue
- CMD_GESTURE → init_gesture()
- CMD_FINGER → servo.write()
- update_gesture() runs non-blocking gesture state machine
- vTaskDelay(8ms) yields to RTOS

6. JS Flow (Browser)

- setGesture(name):
  - Sends GET /gesture?name=...
  - Updates sliders if 'reset'
- setFingerAngle(finger, angle):
  - Sends GET /finger?finger=...&angle=...
- Async fetch ensures UI never blocks

7. Summary Flow

Browser → Core 0: HTTP request
Core 0 → Queue: Push Command
Core 1 → servo_task: Pull Command
Core 1 → update_gesture: Step-by-step servo motion
Servos move gradually → gesture completed
Browser can send new commands concurrently
