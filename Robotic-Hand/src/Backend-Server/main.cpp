#include <Arduino.h>

void setup()
{
  Serial.begin(115200);
  Serial.println("ESP32 este in functiune!");
}

void loop()
{
  Serial.println("Ruleaza loop...");
  delay(1000);
}
