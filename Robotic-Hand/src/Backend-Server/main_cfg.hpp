/* GUARDS */
#ifndef MAIN_CFG_HPP
#define MAIN_CFG_HPP

/* INCLUSIONS */
#include <Arduino.h>
#include <ESP32Servo.h>

/* MACROS */
#define LITTLE_PIN 15
#define RING_PIN 16
#define MIDDLE_PIN 17
#define INDEX_PIN 18
#define THUMB_PIN 19
#define WRIST_PIN 35
#define DEFAULT_ANGLE 0
#define CLOSE_FINGER 180

/* GLOBAL VARIABLE DECLARATIONS */
extern Servo servo_little;
extern Servo servo_ring;
extern Servo servo_middle;
extern Servo servo_index;
extern Servo servo_thumb;
extern Servo servo_wrist;
extern volatile int angle;

/* GLOBAL FUNCTION DECLARATIONS */
void reset_all(void);       // reset to default positions when i want to
void close_all(void);       // close all fingers
void count_up(void);        // count up from 1 -> 5
void count_down(void);      // count down from 5 -> 1
void peace(void);           // peace sign
void ok_sign(void);         // make the 'ok' sign (index and thumb finger touch and the rest bend a little)
void hold_phone(void);      // make the hand hold the phone
void i_love_you_sign(void); // make the hand say 'i love you' (1. only little finger up; 2. only index and thumb up; 3. only thumb and little finger up)
void come_here_sign(void);  // make the hand 'call' someone toward itself (only thumb and index up, then make the index slightly move back and forth)
void go_berserk(void);      // let the hand do random gestures

/* END OF FILE */
#endif