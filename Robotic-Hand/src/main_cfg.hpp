/* GUARDS */
#ifndef MAIN_CFG_HPP
#define MAIN_CFG_HPP

/* INCLUSIONS */
#include <Arduino.h>
#include <ESP32Servo.h>
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

/* MACROS */
#define LITTLE_PIN 23
#define RING_PIN 22
#define MIDDLE_PIN 21
#define INDEX_PIN 19
#define THUMB_PIN 18
#define DEFAULT_ANGLE 0
#define CLOSE_FINGER 180

/* GLOBAL VARIABLES */
extern Servo servo_little;
extern Servo servo_ring;
extern Servo servo_middle;
extern Servo servo_index;
extern Servo servo_thumb;

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
void servo_task(void *param);
void init_gesture(const String &gesture);
void update_gesture();
void reset_all(void);
void close_all(void);
void connect_to_server(void);
void setup_routes(void);

#endif