/* INCLUSIONS */
#include "main_cfg.hpp"

/* LOCAL MACROS */

/* GLOBAL VARIABLES */
Servo servo_little;
Servo servo_ring;
Servo servo_middle;
Servo servo_index;
Servo servo_thumb;
Servo servo_wrist;
volatile int angle;

/* LOCAL VARIABLES */

/* LOCAL FUNCTION DECLARATIONS */

/* LOCAL FUNCTION DEFINITIONS */

/* GLOBAL FUNCTION DEFINITIONS */
void setup()
{
  Serial.begin(115200); /* Serial monitor with 115200 baudrate */
  if (!LittleFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }
  Serial.println("LittleFS mounted successfully");
  connect_to_server();

  /* Attach the servos to the pins */
  servo_little.attach(LITTLE_PIN);
  servo_ring.attach(RING_PIN);
  servo_middle.attach(MIDDLE_PIN);
  servo_index.attach(INDEX_PIN);
  servo_thumb.attach(THUMB_PIN);
  servo_wrist.attach(WRIST_PIN);

  /* Every time we restart the hand, we reset the fingers & wrist positions to default */
  reset_all();

  Serial.println("Servo test start");
}

void loop()
{
  get_server_client();
}