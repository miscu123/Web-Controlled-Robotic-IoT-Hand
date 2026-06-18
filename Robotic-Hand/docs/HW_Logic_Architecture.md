# Hardware Logic Overview

This document outlines the logic behind the hardware used, such as: wire color for each servo, PCA9685 channel number, and I2C wiring.

---

## I2C Bus — ESP32 → PCA9685

The ESP32 communicates with the PCA9685 servo driver over I2C using only 2 signal wires.

| Wire | ESP32 Pin | PCA9685 Pin | Role |
|------|-----------|-------------|------|
| SDA  | GPIO 21   | SDA         | Serial data |
| SCL  | GPIO 22   | SCL         | Clock signal |
| —    | 3.3V      | VCC         | Logic power for PCA9685 |
| —    | 5V        | V+          | Power supply for servos |
| —    | GND       | GND         | Common ground |

---

## Finger WIRE / CHANNEL logic

**Purpose:**  
Easier understanding of the project hardware & a simple way to keep track of available / used parts.

_Little finger_
WIRE: white
CHANNEL: 4

_Ring finger_
WIRE: yellow
CHANNEL: 3

_Middle finger_
WIRE: brown
CHANNEL: 2

_Index finger_
WIRE: purple
CHANNEL: 1

_Thumb finger (A)_
WIRE: green
CHANNEL: 0

_Thumb finger (B)_
WIRE: orange
CHANNEL: 5

---
