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

// BASIC FINGER HELPERS
void close_all()
{
    servo_little.write(CLOSE_FINGER);
    servo_ring.write(CLOSE_FINGER);
    servo_middle.write(CLOSE_FINGER);
    servo_index.write(CLOSE_FINGER);
    servo_thumb.write(CLOSE_FINGER);
}

void reset_all()
{
    servo_little.write(DEFAULT_ANGLE);
    servo_ring.write(DEFAULT_ANGLE);
    servo_middle.write(DEFAULT_ANGLE);
    servo_index.write(DEFAULT_ANGLE);
    servo_thumb.write(DEFAULT_ANGLE);
}

void init_gesture(const String &gesture)
{
    gesture_ctx.current_gesture = gesture;
    gesture_ctx.step = 0;
    gesture_ctx.angle = 0;
    gesture_ctx.count = 0;
    gesture_ctx.state = GESTURE_RUNNING;
}

// Non-blocking gesture update
void update_gesture()
{
    if (gesture_ctx.state != GESTURE_RUNNING)
        return;

    const uint32_t increment = 3;
    const uint32_t max_angle = 180;

    if (gesture_ctx.current_gesture == "close")
    {
        close_all();
        gesture_ctx.state = GESTURE_IDLE;
        Serial.println("Close All Done!");
    }
    else if (gesture_ctx.current_gesture == "reset")
    {
        reset_all();
        gesture_ctx.state = GESTURE_IDLE;
        Serial.println("Reset Done!");
    }
    else if (gesture_ctx.current_gesture == "countU")
    {
        // Index -> Middle -> Thumb -> Ring -> Little
        Servo *order[] = {&servo_index, &servo_middle, &servo_thumb, &servo_ring, &servo_little};

        if (gesture_ctx.step < 5)
        {
            Servo *s = order[gesture_ctx.step];
            if (gesture_ctx.angle <= max_angle)
            {
                s->write(gesture_ctx.angle);
                gesture_ctx.angle += increment;
            }
            else
            {
                gesture_ctx.angle = 0;
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
        // Thumb -> Index -> Middle -> Ring -> Little
        Servo *order[] = {&servo_thumb, &servo_index, &servo_middle, &servo_ring, &servo_little};

        if (gesture_ctx.step < 5)
        {
            Servo *s = order[gesture_ctx.step];
            if (gesture_ctx.angle <= max_angle)
            {
                s->write(gesture_ctx.angle);
                gesture_ctx.angle += increment;
            }
            else
            {
                gesture_ctx.angle = 0;
                gesture_ctx.step++;
            }
        }
        else
        {
            gesture_ctx.state = GESTURE_IDLE;
            Serial.println("Count DOWN Done!");
        }
    }
    else if (gesture_ctx.current_gesture == "peace")
    {
        if (gesture_ctx.step == 0)
        {
            close_all();
            gesture_ctx.step++;
        }
        else if (gesture_ctx.step == 1)
        {
            if (gesture_ctx.angle <= max_angle)
            {
                servo_index.write(gesture_ctx.angle);
                servo_middle.write(gesture_ctx.angle);
                gesture_ctx.angle += increment;
            }
            else
            {
                gesture_ctx.state = GESTURE_IDLE;
                Serial.println("Peace Done!");
            }
        }
    }
    else if (gesture_ctx.current_gesture == "ok")
    {
        if (gesture_ctx.step == 0)
        {
            reset_all();
            gesture_ctx.step++;
            gesture_ctx.angle = 0;
        }
        else if (gesture_ctx.step == 1)
        {
            if (gesture_ctx.angle <= 90)
            {
                servo_index.write(gesture_ctx.angle);
                servo_thumb.write(gesture_ctx.angle);
                gesture_ctx.angle += increment;
            }
            else
            {
                servo_middle.write(40);
                servo_ring.write(25);
                servo_little.write(10);
                gesture_ctx.state = GESTURE_IDLE;
                Serial.println("OK Sign Done!");
            }
        }
    }
    else if (gesture_ctx.current_gesture == "hold")
    {
        if (gesture_ctx.step == 0)
        {
            reset_all();
            gesture_ctx.step++;
            gesture_ctx.angle = 0;
        }
        else if (gesture_ctx.step == 1)
        {
            if (gesture_ctx.angle <= 90)
            {
                servo_thumb.write(gesture_ctx.angle);
                servo_little.write(gesture_ctx.angle);
                gesture_ctx.angle += increment;
            }
            else
            {
                servo_index.write(10);
                servo_middle.write(10);
                servo_ring.write(10);
                gesture_ctx.state = GESTURE_IDLE;
                Serial.println("Hold Phone Done!");
            }
        }
    }
    else if (gesture_ctx.current_gesture == "come")
    {
        if (gesture_ctx.step == 0)
        {
            close_all();
            servo_index.write(DEFAULT_ANGLE);
            gesture_ctx.step++;
            gesture_ctx.angle = 0;
            gesture_ctx.count = 0;       
        }
        else if (gesture_ctx.step == 1)
        {
            if (gesture_ctx.count < 10)
            {
                if (gesture_ctx.angle <= max_angle)
                {
                    servo_index.write(gesture_ctx.angle);
                    gesture_ctx.angle += increment;
                }
                else
                {
                    gesture_ctx.step++;
                }
            }
            else
            {
                gesture_ctx.state = GESTURE_IDLE;
                Serial.println("Come Here Done!");
            }
        }
        else if (gesture_ctx.step == 2)
        {
            if (gesture_ctx.angle > 0)
            {
                servo_index.write(gesture_ctx.angle);
                gesture_ctx.angle -= increment;
            }
            else
            {
                gesture_ctx.angle = 0;
                gesture_ctx.count++;
                gesture_ctx.step = 1;
            }
        }
    }

    vTaskDelay(pdMS_TO_TICKS(8)); // RTOS friendly
}