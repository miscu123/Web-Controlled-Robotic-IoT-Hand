#include <Arduino.h>
#include <ESP32Servo.h>

Servo servo;
const int servoPin = 18;

void setup()
{
  Serial.begin(115200);
  servo.attach(servoPin);
  Serial.println("Servo test automat");
}

void loop()
{
  for (int angle = 0; angle <= 180; angle += 3)
  {
    servo.write(angle);
    Serial.print("Unghi: ");
    Serial.println(angle);
    delay(8);
  }
  delay(200);
  for (int angle = 180; angle >= 0; angle -= 3)
  {
    servo.write(angle);
    Serial.print("Unghi: ");
    Serial.println(angle);
    delay(8);
  }
  delay(500);
}