/* GUARDS */
#ifndef MAIN_CFG_HPP
#define MAIN_CFG_HPP

/* INCLUSIONS */
#include <Arduino.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <stdint.h>
#include <FS.h>
#include <LittleFS.h>
// LCD libs (optional, if i want to implement it)
// HW-LCD-specific library
#include <SPI.h>
#include <TFT_eSPI.h>
#include "esp_random.h" // random number generation for berserk callback

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

/* GLOBAL VARIABLE DECLARATIONS */
extern Servo servo_little;
extern Servo servo_ring;
extern Servo servo_middle;
extern Servo servo_index;
extern Servo servo_thumb;
extern Servo servo_wrist;
extern volatile uint32_t angle;
extern const char *ssid;
extern const char *password;
extern WiFiServer server;
extern WiFiClient client;
extern uint32_t random_angles[];

/* GLOBAL FUNCTION DECLARATIONS */
void reset_all(void);         // reset to default positions when i want to
void close_all(void);         // close all fingers
void count_up(void);          // count up from 1 -> 5
void count_down(void);        // count down from 5 -> 1
void peace(void);             // peace sign
void ok_sign(void);           // make the 'ok' sign (index and thumb finger touch and the rest bend a little)
void hold_phone(void);        // make the hand hold the phone
void i_love_you_sign(void);   // make the hand say 'i love you'
void come_here_sign(void);    // make the hand 'call' someone toward itself
void go_berserk(void);        // let the hand do random gestures
void connect_to_server(void); // make connection to WIFI server
void get_server_client(void); // listen to connect a client to the server

/* END OF FILE */
#endif