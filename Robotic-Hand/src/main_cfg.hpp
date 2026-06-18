/* GUARDS */
#ifndef MAIN_CFG_HPP
#define MAIN_CFG_HPP

/* INCLUSIONS */
#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi.h>
#include <FS.h>
#include <LittleFS.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

/* PCA9685 CHANNELS */
#define THUMB_PIN_A 0
#define THUMB_PIN_B 5
#define INDEX_PIN   1
#define MIDDLE_PIN  2
#define RING_PIN    3
#define LITTLE_PIN  4

/* SERVO ANGLES & PULSE RANGE */
#define DEFAULT_ANGLE 180
#define CLOSE_FINGER  0
#define SERVO_MIN     112  // pulse ticks at 0°  (~544µs, matches ESP32Servo default)
#define SERVO_MAX     492  // pulse ticks at 180° (~2400µs, matches ESP32Servo default)

/* GLOBAL VARIABLES */
extern Adafruit_PWMServoDriver pwm;

// FingerCmd: data abt 1 finger
// char finger[8] instead of String — FreeRTOS Queue copies bytes in memory, can not copy C++ objects (String)
typedef struct
{
    char finger[8]; // "thumb", "index", "middle", "ring", "pinky"
    int angle;
} FingerCmd;

extern QueueHandle_t gestureQueue; // send char[32] with gesture name
extern QueueHandle_t fingerQueue;  // send FingerCmd

extern const char *ssid;
extern const char *password;
extern AsyncWebServer server;

/* GLOBAL FUNCTION DECLARATIONS */
void servoWrite(uint8_t channel, uint8_t angle);
void servo_task(void *param);
void init_gesture(const String &gesture);
void update_gesture();
void connect_to_server(void);
void setup_routes(void);

#endif
