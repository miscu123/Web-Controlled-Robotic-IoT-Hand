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

// FingerCmd: date despre un singur deget
// char finger[8] in loc de String — Queue-ul FreeRTOS
// copiaza bytes in memorie, nu poate copia obiecte C++ (String)
typedef struct
{
    char finger[8]; // "thumb", "index", "middle", "ring", "pinky"
    int angle;
} FingerCmd;

// Doua cozi separate, una per tip de comanda
// Asa nu mai ai nevoie de enum/struct care spune "ce tip e comanda asta"
extern QueueHandle_t gestureQueue; // trimite char[32] cu numele gestului
extern QueueHandle_t fingerQueue;  // trimite FingerCmd

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