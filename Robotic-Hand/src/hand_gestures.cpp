/* INCLUSIONS */
#include "main_cfg.hpp"

// STATE MACHINE DEFINITIONS
enum GestureState
{
    GESTURE_IDLE,
    GESTURE_RUNNING
};

struct GestureContext
{
    String current_gesture;
    uint8_t step;   // current step in gesture sequence
    uint32_t angle; // temporary angle for loops
    uint32_t count; // counter for repeated motions
    GestureState state;
} gesture_ctx = {"", 0, 0, 0, GESTURE_IDLE}; // default init

// Finger order: thumb -> index -> middle -> ring -> little
static const uint8_t CLOSE_ORDER[] = {THUMB_PIN_A, INDEX_PIN, MIDDLE_PIN, RING_PIN, LITTLE_PIN};

void init_gesture(const String &gesture)
{
    gesture_ctx.current_gesture = gesture;
    gesture_ctx.step = 0;
    gesture_ctx.angle = 0;
    gesture_ctx.count = 0;
    gesture_ctx.state = GESTURE_RUNNING;
}

// Snaps one finger to CLOSE_FINGER per call. Returns true when all 5 are done.
static bool phase_close_all()
{
    if (gesture_ctx.step < 5)
    {
        servoWrite(CLOSE_ORDER[gesture_ctx.step], CLOSE_FINGER);
        gesture_ctx.step++;
        vTaskDelay(pdMS_TO_TICKS(45));
        return false;
    }
    return true;
}

// Snaps one finger to DEFAULT_ANGLE per call. Returns true when all 5 are done.
static bool phase_reset_all()
{
    if (gesture_ctx.step < 5)
    {
        servoWrite(CLOSE_ORDER[gesture_ctx.step], DEFAULT_ANGLE);
        gesture_ctx.step++;
        vTaskDelay(pdMS_TO_TICKS(45));
        return false;
    }
    return true;
}

// Non-blocking gesture update
void update_gesture()
{
    if (gesture_ctx.state != GESTURE_RUNNING)
        return;

    const uint32_t increment = 3;

    if (gesture_ctx.current_gesture == "close")
    {
        if (!phase_close_all())
            return;
        gesture_ctx.state = GESTURE_IDLE;
        Serial.println("Close All Done!");
    }
    else if (gesture_ctx.current_gesture == "reset")
    {
        if (!phase_reset_all())
            return;
        gesture_ctx.state = GESTURE_IDLE;
        Serial.println("Reset Done!");
    }
    else if (gesture_ctx.current_gesture == "countU")
    {
        // Phase 1: close all fingers
        // Phase 2: raise one finger at a time (thumb -> index -> middle -> ring -> little)
        if (!phase_close_all())
            return;

        // 400 * 8ms per tick = 3200ms
        if (gesture_ctx.count < 400)
        {
            gesture_ctx.count++;
            return;
        }

        uint8_t finger_idx = gesture_ctx.step - 5;
        if (finger_idx < 5)
        {
            if (gesture_ctx.angle < DEFAULT_ANGLE)
            {
                servoWrite(CLOSE_ORDER[finger_idx], gesture_ctx.angle);
                gesture_ctx.angle += increment;
            }
            else
            {
                servoWrite(CLOSE_ORDER[finger_idx], DEFAULT_ANGLE);
                gesture_ctx.angle = CLOSE_FINGER;
                gesture_ctx.step++;
            }
        }
        else
        {
            gesture_ctx.state = GESTURE_IDLE;
            Serial.println("Count UP Done!");
        }
    }
    else if (gesture_ctx.current_gesture == "countD")
    {
        // Phase 1: reset all fingers open
        // Phase 2: close one finger at a time (thumb -> index -> middle -> ring -> little)
        if (!phase_reset_all())
            return;

        // 200 * 8ms per tick = 1600ms
        if (gesture_ctx.count < 200)
        {
            gesture_ctx.count++;
            return;
        }

        if (gesture_ctx.step == 5)
        {
            gesture_ctx.angle = DEFAULT_ANGLE;
            gesture_ctx.step++;
        }
        else
        {
            uint8_t finger_idx = gesture_ctx.step - 6;
            if (finger_idx < 5)
            {
                if (gesture_ctx.angle > CLOSE_FINGER)
                {
                    servoWrite(CLOSE_ORDER[finger_idx], gesture_ctx.angle);
                    gesture_ctx.angle = (gesture_ctx.angle >= increment) ? gesture_ctx.angle - increment : CLOSE_FINGER;
                }
                else
                {
                    servoWrite(CLOSE_ORDER[finger_idx], CLOSE_FINGER);
                    gesture_ctx.angle = DEFAULT_ANGLE;
                    gesture_ctx.step++;
                }
            }
            else
            {
                gesture_ctx.state = GESTURE_IDLE;
                Serial.println("Count DOWN Done!");
            }
        }
    }
    else if (gesture_ctx.current_gesture == "peace")
    {
        // Phase 1: reset all fingers open
        // Phase 2: snap thumb, ring, little closed
        if (!phase_reset_all())
            return;

        // 1600ms
        if (gesture_ctx.count < 200)
        {
            gesture_ctx.count++;
            return;
        }

        servoWrite(THUMB_PIN_A, CLOSE_FINGER);
        servoWrite(RING_PIN, CLOSE_FINGER);
        servoWrite(LITTLE_PIN, CLOSE_FINGER);
        gesture_ctx.state = GESTURE_IDLE;
        Serial.println("Peace Done!");
    }
    else if (gesture_ctx.current_gesture == "ok")
    {
        // Phase 1: reset all fingers open
        // Phase 2: sweep thumb closed to 85, snap rest
        if (!phase_reset_all())
            return;

        if (gesture_ctx.angle <= 85)
        {
            servoWrite(THUMB_PIN_A, gesture_ctx.angle);
            gesture_ctx.angle += increment;
        }
        else
        {
            servoWrite(INDEX_PIN, CLOSE_FINGER);
            servoWrite(MIDDLE_PIN, 150);
            servoWrite(RING_PIN, 170);
            servoWrite(LITTLE_PIN, 170);
            gesture_ctx.state = GESTURE_IDLE;
            Serial.println("OK Sign Done!");
        }
    }
    else if (gesture_ctx.current_gesture == "hold")
    {
        // Phase 1: reset all fingers open
        // Phase 2: sweep thumb closed to 80, snap rest
        if (!phase_reset_all())
            return;

        if (gesture_ctx.angle <= 80)
        {
            servoWrite(THUMB_PIN_A, gesture_ctx.angle);
            gesture_ctx.angle += increment;
        }
        else
        {
            servoWrite(LITTLE_PIN, CLOSE_FINGER);
            servoWrite(INDEX_PIN, CLOSE_FINGER);
            servoWrite(MIDDLE_PIN, CLOSE_FINGER);
            servoWrite(RING_PIN, CLOSE_FINGER);
            gesture_ctx.state = GESTURE_IDLE;
            Serial.println("Hold Phone Done!");
        }
    }

    vTaskDelay(pdMS_TO_TICKS(8)); // RTOS friendly
}
