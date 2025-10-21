/* Guards */
#ifndef MAIN_CFG_HPP
#define MAIN_CFG_HPP

/* Inclusions */
#include <Arduino.h>
#include <ESP32Servo.h>

/* Pin configurations */
#define LITTLE_PIN 15
#define RING_PIN 16
#define MIDDLE_PIN 17
#define INDEX_PIN 18
#define THUMB_PIN 19
#define WRIST_PIN 35
#define DEFAULT_ANGLE 0
#define CLOSE_FINGER 180

/* Variables declarations */
/* Servos needed */
extern Servo servo_little;
extern Servo servo_ring;
extern Servo servo_middle;
extern Servo servo_index;
extern Servo servo_thumb;
extern Servo servo_wrist;
extern volatile int angle;

/* Function declarations */
void reset_all(void);  // reset to default positions when i want to
void close_all(void);  // close all fingers
void count_up(void);   // count up from 1 -> 5
void count_down(void); // count down from 5 -> 1
void peace(void);      // peace sign
void ok_sign(void);    // make the 'ok' sign (index and thumb finger touch and the rest bend a little)
void go_berserk(void); // let the hand do random gestures
void hold_phone(void); // make the hand hold the phone

#endif