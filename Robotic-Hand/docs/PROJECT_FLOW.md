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

# CORE USAGE FLOW

ESP32 Dual-Core Flow: Gesture Control
Core 0 (PRO_CPU) – System / WiFi / Web Server
┌───────────────────────────────┐
│ Browser / JS Interface │
│ - User clicks a gesture │
│ - User moves a finger slider │
└───────────────┬───────────────┘
│ HTTP Request
▼
┌───────────────────────────────┐
│ AsyncWebServer (Core 0) │
│ - /gesture GET handler │
│ - /finger GET handler │
│ - Encodes user input into │
│ Command struct │
│ - Pushes command to Queue │
└───────────────┬───────────────┘
│ xQueueSend
▼
┌─────────┐
│Command │
│Queue │
└─────────┘

Notes:

Core 0 handles all networking and HTTP request parsing.

It doesn’t block the servo updates because it just pushes commands into a FreeRTOS queue.

Queue is thread-safe, so Core 1 can read from it asynchronously.

Core 1 (APP_CPU) – Servo Task
┌───────────────────────────────┐
│ servo_task (Core 1) │
│ - Reads Command from Queue │
│ (xQueueReceive) │
│ │
│ - CMD_GESTURE → init_gesture()│
│ - CMD_FINGER → servo.write() │
└───────────────┬───────────────┘
│
▼
┌───────────────────────────────┐
│ update_gesture() │
│ - Non-blocking state machine │
│ - Executes gestures step by │
│ step using angles & counters│
│ - Yields every loop iteration │
│ via vTaskDelay(8ms) │
└───────────────┬───────────────┘
│
▼
┌───────────────────────────────┐
│ Servos │
│ - thumb, index, middle, ring, │
│ little │
│ - Moves to angles step-by-step│
└───────────────────────────────┘

Notes:

Core 1 is fully dedicated to servo updates.

Because update_gesture() is non-blocking and uses small vTaskDelay, it yields control to the RTOS and other tasks (like sending more commands) can run.

Gestures execute gradually, step-by-step, while the web server remains responsive.

JS Flow (Browser Side)
User Action
├─ Click "Peace" → setGesture("peace")
└─ Move slider → setFingerAngle(finger, angle)

setGesture(name)
├─ Fetch: GET /gesture?name=peace
└─ Updates sliders if "reset"

setFingerAngle(finger, angle)
└─ Fetch: GET /finger?finger=thumb&angle=45

Notes:

JS uses async/await or .then() to avoid blocking the browser.

Only sends a request; servo updates happen asynchronously on Core 1.

No need to wait for gestures to finish before sending new commands (queue buffers them).

Key RTOS Concepts in Use

Queue (commandQueue)

Thread-safe communication between Core 0 (server) and Core 1 (servo task).

Decouples web requests from hardware control.

Task Pinning (xTaskCreatePinnedToCore)

Ensures servo_task runs only on Core 1, leaving Core 0 free for WiFi and web server.

Non-blocking State Machine (update_gesture)

Executes multi-step gestures without halting Core 1.

Uses step, angle, count to track progress.

vTaskDelay yields CPU so RTOS can schedule other tasks.

AsyncWebServer

Event-driven server; callbacks execute on Core 0.

Works naturally with RTOS because callbacks are non-blocking (only send command to queue).

Summary Flow

Browser → Core 0: HTTP request

Core 0 → Queue: Push Command

Core 1 → servo_task: Pull Command

Core 1 → update_gesture: Step-by-step servo motion

Servos move gradually → gesture completed

Browser can continue sending new commands concurrently
