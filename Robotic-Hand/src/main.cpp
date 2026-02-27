#include "main_cfg.hpp"

/* GLOBAL VARIABLES */
Servo servo_little;
Servo servo_ring;
Servo servo_middle;
Servo servo_index;
Servo servo_thumb;
Servo servo_wrist;
volatile uint32_t angle;

const char *ssid = "DIGI-j4aJ";
const char *password = "teAeJVK3Dn";

/* SETUP */
void setup()
{
  Serial.begin(115200);
  if (!LittleFS.begin(true))
  {
    Serial.println("Error mounting LittleFS");
    return;
  }
  Serial.println("LittleFS mounted successfully");

  connect_to_server();

  // Attach servos
  servo_little.attach(LITTLE_PIN);
  servo_ring.attach(RING_PIN);
  servo_middle.attach(MIDDLE_PIN);
  servo_index.attach(INDEX_PIN);
  servo_thumb.attach(THUMB_PIN);
  servo_wrist.attach(WRIST_PIN);

  // Reset positions
  reset_all();

  // Start server
  setup_routes();

  Serial.println("Setup complete. Server running.");
}

/* LOOP */
void loop()
{
  // Nothing needed here, server is async
  // Async server does not block and is way faster than sync server
}