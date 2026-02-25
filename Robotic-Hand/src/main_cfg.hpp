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
#include "esp_random.h"

/* MACROS */
#define LITTLE_PIN 17
#define RING_PIN 18
#define MIDDLE_PIN 19
#define INDEX_PIN 21
#define THUMB_PIN 22
#define WRIST_PIN 23
#define DEFAULT_ANGLE 0
#define CLOSE_FINGER 180
#define FINGER_COUNT 5

/* GLOBAL VARIABLES */
extern Servo servo_little;
extern Servo servo_ring;
extern Servo servo_middle;
extern Servo servo_index;
extern Servo servo_thumb;
extern Servo servo_wrist;
extern volatile uint32_t angle;

/* WiFi credentials */
extern const char *ssid;
extern const char *password;

/* Async Server */
extern AsyncWebServer server;

/* GLOBAL FUNCTION DECLARATIONS */
void reset_all(void);
void close_all(void);
void count_up(void);
void count_down(void);
void peace(void);
void ok_sign(void);
void hold_phone(void);
void i_love_you_sign(void);
void come_here_sign(void);
void go_berserk(void);

void connect_to_server(void);
void setup_routes(void);

#endif