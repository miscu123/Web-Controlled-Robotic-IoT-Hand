#include "main_cfg.hpp"
#include <Wire.h>

/* GLOBAL VARIABLES */
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // default I2C address 0x40

QueueHandle_t gestureQueue;
QueueHandle_t fingerQueue;

// const char *ssid = "DIGI-j4aJ";
// const char *password = "teAeJVK3Dn";
const char *ssid = "Mihai";
const char *password = "12345678";

// Writes an angle (0-180) to a PCA9685 channel.
// Writing to THUMB_PIN_A automatically mirrors to THUMB_PIN_B.
void servoWrite(uint8_t channel, uint8_t angle)
{
  uint16_t pulse = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
  pwm.setPWM(channel, 0, pulse);
  if (channel == THUMB_PIN_A)
    pwm.setPWM(THUMB_PIN_B, 0, pulse); // second thumb servo — invert pulse if mounted mirrored
}

/* SETUP */
void setup()
{
  Serial.begin(115200);

  if (!LittleFS.begin(true))
  {
    Serial.println("Error mounting LittleFS");
    return;
  }
  Serial.println("LittleFS mounted successfully");

  connect_to_server();

  // Init I2C and PCA9685
  Wire.begin(21, 22); // SDA, SCL — explicit for ESP32
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50); // 50Hz for servos
  Serial.println("PCA9685 initialized");

  // Reset positions
  init_gesture("reset");

  gestureQueue = xQueueCreate(10, sizeof(char[32]));
  fingerQueue = xQueueCreate(10, sizeof(FingerCmd));

  if (gestureQueue == NULL || fingerQueue == NULL)
  {
    Serial.println("Failed to create command queue!");
    for (;;)
    {
    }
  }

  // Start servo task
  xTaskCreatePinnedToCore(
      servo_task,
      "Servo Task",
      4096,
      NULL,
      2, // task priority in RTOS
      NULL,
      1); // we use core 1 for tasks, core 0 for wifi server

  // Start server
  setup_routes();

  Serial.println("Setup complete. Server running.");
}

/* LOOP */
void loop()
{
  // Nothing needed here, server is async
  // Async server does not block and is way faster than sync server
}
