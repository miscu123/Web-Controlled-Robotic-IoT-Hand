# ESP32 MCU documentation (VS Code & PlatformIO)

## Commands to upload to flash and run server:

### Erase memory:

pio run --target erase

---

### Upload C++ CODE to ESP32 Flash memory:

pio run --target upload

---

### Upload static files (html, css, js) to LittleFS (file system) ESP32:

pio run --target uploadfs

---

### Open serial monitor:

pio device monitor -b 115200

# KEY CONCEPTS TO KNOW:

1. Key Components

ESP32 RTOS environment:
FreeRTOS handles multiple tasks concurrently.

Tasks:

servo_task – handles all servo motions via update_gesture() and direct finger angle commands.

AsyncWebServer task – handles incoming HTTP requests from the browser or any client.

Data Passing:

Queue (commandQueue) is used to pass commands (gestures/finger angles) safely between the web server and servo_task.

State Machines:

gesture_ctx keeps track of current gesture, step, angle, and repeat count.

Ensures gestures are executed incrementally, non-blocking.

JS Frontend:

Sends /gesture?name=... or /finger?finger=...&angle=... requests asynchronously.

Updates UI sliders immediately.

2. Async Command Flow

User triggers gesture on webpage.

JS sends HTTP request asynchronously to ESP32:

fetch(`/gesture?name=${name}`)

AsyncWebServer receives request:

Extracts parameters (gesture or finger + angle).

Packs into Command struct.

Pushes into FreeRTOS queue (commandQueue) using xQueueSend().

Responds to client immediately (200 OK or 500 Queue full).

servo_task loop runs continuously:

Checks commandQueue via xQueueReceive() (non-blocking).

If a command is available:

Gesture → call init_gesture(cmd.gesture).

Finger angle → update servo directly (servo_thumb.write(cmd.angle)).

Calls update_gesture() once per loop.

Delays 8ms → yields to other tasks.

update_gesture():

Implements gesture state machine.

Moves servos incrementally based on step and angle.

Exits immediately after one small action → non-blocking.

Returns control to RTOS scheduler.

FreeRTOS scheduler:

Allows Web server, WiFi stack, other tasks to run between update_gesture() calls.

Each gesture completes over multiple iterations (non-blocking).

3. Flowchart Concept

Here’s a textual layout that you can visualize as a flowchart:

[User Browser]
|
v
[JS Fetch /gesture or /finger]
|
v
[ESP32 AsyncWebServer]
|
|-- If gesture/finger param OK
| |
| v
| [Create Command struct]
| |
| v
| [Push Command to commandQueue]
| |
| v
| [Respond 200 OK]
|
v
[servo_task Loop]
|
v
[xQueueReceive(commandQueue)]
|
+----> If CMD_GESTURE: init_gesture()
|
+----> If CMD_FINGER: move servo directly
|
v
[update_gesture()]
|
|-- Increment servo angle / step
|-- Update gesture_ctx
|-- Exit immediately (non-blocking)
|
v
[vTaskDelay(8ms)]
|
v
[Yield to RTOS Scheduler]
|
v
[Other tasks run: Web Server, WiFi, etc.]
|
v
[Next iteration of servo_task loop] 4. Key Insights

RTOS yields every 8ms → gestures and server run concurrently.

Queue decouples tasks → Web server never blocks while gestures are running.

State machine ensures gestures execute in small, incremental steps → fully non-blocking.

JS async fetch → frontend updates instantly, independent of gesture execution.

Code logic architecture:

[ Web Server Task ]
↓ (queue)
[ Command Queue ]
↓
[ Servo Control Task ]
↓
[ Hardware (Servos) ]

Before:
HTTP → directly moves servos ❌

race conditions ❌

unsafe concurrency ❌

Now:
HTTP → sends command → queue → servo task → hardware ✅
