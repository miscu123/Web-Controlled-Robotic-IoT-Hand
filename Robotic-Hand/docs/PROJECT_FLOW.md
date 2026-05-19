# ESP32 RTOS Gesture Control: Architectural Overview

This document outlines the concurrent, multi-core architecture used to control a robotic hand via an ESP32 running FreeRTOS. By separating the web interface from the hardware control layer, the system ensures a highly responsive user experience and smooth, non-blocking servo motion.

---

## 1. System Architecture & Core Allocation

The ESP32 utilizes its dual-core processing capabilities to completely decouple network communication from real-time hardware execution.

*   **Core 0 (Networking & Ingestion):** Dedicated to the WiFi stack and the asynchronous HTTP web server.
*   **Core 1 (Hardware Execution):** Dedicated to the servo control task, running calculations and writing directly to the motors.
*   **The Bridge:** Communication between Core 0 and Core 1 happens exclusively through a thread-safe FreeRTOS queue (`commandQueue`).

---

## 2. Core Components & Tasks

### FreeRTOS Tasks

#### AsyncWebServer Task (Core 0)
*   **Role:** Acts as the data producer.
*   **Behavior:** Asynchronously listens for incoming frontend requests, parses parameters, packages them into a structured format, and pushes them into the communication queue.

#### servo_task (Core 1)
*   **Role:** Acts as the data consumer.
*   **Behavior:** Continually checks the queue for incoming instructions, maps raw angles to specific fingers, and advances the background gesture state machine.

---

### Thread-Safe Data Passing

Communication across the two cores relies strictly on a FreeRTOS `QueueHandle_t` named `commandQueue`.

> **Key Architectural Insight: Choosing char[32] over String**
> FreeRTOS queues copy data byte-by-byte using raw memory copying (`memcpy`). Standard C++ objects with dynamic constructors/destructors—like `String`—cannot safely be moved this way and will cause memory corruption or crashes. 
> 
> To prevent this, the command architecture uses a primitive fixed-size byte buffer (`char[32]`) handled via safe string copying (`strncpy`).

---

## 3. The Non-Blocking State Machine (gesture_ctx)

Static commands (like setting a single finger to a specific angle) execute instantaneously. However, animated gestures (such as "come here", or counting up and down) take several seconds to complete. 

To prevent these animations from freezing the CPU or lagging the system, a time-slice state machine tracks execution using a context structure:

*   `current_gesture`: The active routine ID.
*   `step`: The current progress index within the routine.
*   `angle`: The localized tracking angle for moving components.
*   `count`: The loop or repetition counter.

Instead of using hard blocking delays (like `delay()`), the loop follows this cycle:
`Read queue` -> `Process any new CMD` -> `Call update_gesture()` -> `vTaskDelay(8ms)` -> `Yield CPU and repeat`

Every time `update_gesture()` runs, it performs a tiny movement step, updates its internal state variables, and immediately exits. This releases the core, allowing FreeRTOS to handle background tasks seamlessly.

---

## 4. End-to-End Command Flow

The transformation of a user interaction into physical movement follows a structured pipeline:

1. **User Interaction:** The user interacts with the web UI dashboard.
2. **Asynchronous Request:** The JavaScript frontend sends a non-blocking fetch request:
   `fetch('/gesture?name=name')` OR `fetch('/finger?finger=finger&angle=angle')`
3. **Ingestion & Queuing:** The ESP32 Async Web Server intercepts the packet on Core 0, parses the arguments, creates a standard `Command` structure, and drops it into `commandQueue`. It immediately returns an HTTP 200 status back to the browser.
4. **Hardware Consumption:** On Core 1, `servo_task` polls the queue:
   * **If CMD_GESTURE arrives:** It calls `init_gesture()` to reset the state machine variables.
   * **If CMD_FINGER arrives:** It bypasses the state machine and writes directly to the specific motor using `servo.write()`.
5. **Incremental Update:** `servo_task` calls `update_gesture()`, processes fractional steps for any active animation, and executes `vTaskDelay(8ms)` to briefly yield execution.

**Simplified Flow:**
User Browser -> Web Server (Core 0) -> commandQueue -> servo_task (Core 1) -> update_gesture() -> Servos

---

## 5. Summary: Architectural Evolutions

The multi-threaded structure offers distinct advantages over traditional monolithic Arduino codebases:

*   **System Flow (Before):** HTTP Request -> Direct Servo Delay()
*   **System Flow (After):** Web Server -> Queue -> Servo Task -> Hardware
*   **UI Responsiveness:** UI remains fully responsive at all times, preventing freezes during long animations.
*   **Servo Motion:** Fluid, uninterrupted execution at a stable 8ms timebase instead of being prone to network jitter.
*   **Memory Safety:** Safe, cross-core memory isolated via FreeRTOS Queues instead of shared variables risking race conditions.