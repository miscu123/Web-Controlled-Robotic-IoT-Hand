/* INCLUSIONS */
#include "main_cfg.hpp"

/* GLOBAL FUNCTION DEFINITIONS */
void close_all(void)
{
    servo_little.write(CLOSE_FINGER);
    servo_ring.write(CLOSE_FINGER);
    servo_middle.write(CLOSE_FINGER);
    servo_index.write(CLOSE_FINGER);
    servo_thumb.write(CLOSE_FINGER);
    servo_wrist.write(CLOSE_FINGER);
}

void reset_all(void)
{
    servo_little.write(DEFAULT_ANGLE);
    servo_ring.write(DEFAULT_ANGLE);
    servo_middle.write(DEFAULT_ANGLE);
    servo_index.write(DEFAULT_ANGLE);
    servo_thumb.write(DEFAULT_ANGLE);
    servo_wrist.write(DEFAULT_ANGLE);
}

/* index -> middle -> thumb -> ring -> little */
void count_up(void)
{
    /* First close all fingers to begin counting up */
    close_all();
    delay(200);
    for (angle = 0; angle <= 180; angle += 3) // need to test if we add angle of we substract (+=x / -=x)
    {
        servo_index.write(angle);
        // Serial.print("Unghi: ");
        // Serial.println(angle);
        delay(8);
    }
    delay(100);
    for (angle = 0; angle <= 180; angle += 3)
    {
        servo_middle.write(angle);
        // Serial.print("Unghi: ");
        // Serial.println(angle);
        delay(8);
    }
    delay(100);
    for (angle = 0; angle <= 180; angle += 3)
    {
        servo_thumb.write(angle);
        // Serial.print("Unghi: ");
        // Serial.println(angle);
        delay(8);
    }
    delay(100);
    for (angle = 0; angle <= 180; angle += 3)
    {
        servo_ring.write(angle);
        // Serial.print("Unghi: ");
        // Serial.println(angle);
        delay(8);
    }
    delay(100);
    for (angle = 0; angle <= 180; angle += 3)
    {
        servo_little.write(angle);
        // Serial.print("Unghi: ");
        // Serial.println(angle);
        delay(8);
    }
    delay(100);

    Serial.println("Count UP Done!");
}

void count_down(void)
{
    /* First open all fingers to begin counting up */
    reset_all();
    delay(200);
    for (angle = 0; angle <= 180; angle += 3)
    {
        servo_thumb.write(angle);
        // Serial.print("Unghi: ");
        // Serial.println(angle);
        delay(8);
    }
    delay(100);
    for (angle = 0; angle <= 180; angle += 3) // need to test if we add angle of we substract (+=x / -=x)
    {
        servo_index.write(angle);
        // Serial.print("Unghi: ");
        // Serial.println(angle);
        delay(8);
    }
    delay(100);
    for (angle = 0; angle <= 180; angle += 3)
    {
        servo_middle.write(angle);
        // Serial.print("Unghi: ");
        // Serial.println(angle);
        delay(8);
    }
    delay(100);
    for (angle = 0; angle <= 180; angle += 3)
    {
        servo_ring.write(angle);
        // Serial.print("Unghi: ");
        // Serial.println(angle);
        delay(8);
    }
    delay(100);
    for (angle = 0; angle <= 180; angle += 3)
    {
        servo_little.write(angle);
        // Serial.print("Unghi: ");
        // Serial.println(angle);
        delay(8);
    }
    delay(100);

    Serial.println("Count DOWN Done!");
}

void peace(void)
{
    close_all();
    delay(200);
    for (angle = 0; angle <= 180; angle += 3) // need to test if we add angle of we substract (+=x / -=x)
    {
        servo_index.write(angle);
        // Serial.print("Unghi: ");
        // Serial.println(angle);
        delay(8);
    }
    delay(100);
    for (angle = 0; angle <= 180; angle += 3)
    {
        servo_middle.write(angle);
        // Serial.print("Unghi: ");
        // Serial.println(angle);
        delay(8);
    }

    Serial.println("Peace Done!");
}

void ok_sign(void)
{
    reset_all();
    delay(200);
    for (angle = 0; angle <= 90; angle += 3)
    {
        servo_index.write(angle);
        // Serial.print("Unghi: ");
        // Serial.println(angle);
        delay(8);
    }
    delay(100);
    for (angle = 0; angle <= 90; angle += 3)
    {
        servo_thumb.write(angle);
        // Serial.print("Unghi: ");
        // Serial.println(angle);
        delay(8);
    }
    delay(100);
    servo_middle.write(40);
    servo_ring.write(25);
    servo_little.write(10);
}

void hold_phone(void)
{
    reset_all();
    delay(200);
    for (angle = 0; angle <= 90; angle += 3)
    {
        servo_thumb.write(angle);
        // Serial.print("Unghi: ");
        // Serial.println(angle);
        delay(8);
    }
    delay(100);
    for (angle = 0; angle <= 90; angle += 3)
    {
        servo_little.write(angle);
        // Serial.print("Unghi: ");
        // Serial.println(angle);
        delay(8);
    }
    delay(100);
    servo_index.write(10);
    servo_middle.write(10);
    servo_ring.write(10);
}

void i_love_you_sign(void)
{
    close_all();
    delay(200);

    // I --> little finger up
    servo_little.write(DEFAULT_ANGLE);
    delay(300);
    for (angle = 0; angle <= 180; angle += 3)
    {
        servo_little.write(angle);
        // Serial.print("Unghi: ");
        // Serial.println(angle);
        delay(8);
    }
    delay(100);

    // L --> index & thumb up
    servo_index.write(DEFAULT_ANGLE);
    servo_thumb.write(DEFAULT_ANGLE);
    delay(300);
    for (angle = 0; angle <= 180; angle += 3)
    {
        servo_index.write(angle);
        servo_thumb.write(angle);
        // Serial.print("Unghi: ");
        // Serial.println(angle);
        delay(8);
    }
    delay(100);

    // Y --> thumb & little finger up
    servo_thumb.write(DEFAULT_ANGLE);
    servo_little.write(DEFAULT_ANGLE);
    delay(300);
    for (angle = 0; angle <= 180; angle += 3)
    {
        servo_little.write(angle);
        servo_thumb.write(angle);
        // Serial.print("Unghi: ");
        // Serial.println(angle);
        delay(8);
    }
    delay(100);
}

void come_here_sign(void)
{
    close_all();
    delay(200);
    servo_index.write(DEFAULT_ANGLE);

    uint32_t count = 0; // dont care what count is as long as it increments to do sign
    while (count < 10)
    {
        for (angle = 0; angle <= 180; angle += 3)
        {
            servo_index.write(angle);
            // Serial.print("Unghi: ");
            // Serial.println(angle);
            delay(8);
        }
        delay(200);

        for (angle = 180; angle > 0; angle -= 3)
        {
            servo_index.write(angle);
            // Serial.print("Unghi: ");
            // Serial.println(angle);
            delay(8);
        }
        delay(200);

        count++;
    }
}