#include "main_cfg.hpp"

/* GLOBAL VARIABLES */
Servo servo_little;
Servo servo_ring;
Servo servo_middle;
Servo servo_index;
Servo servo_thumb;

QueueHandle_t commandQueue;

const char *ssid = "DIGI-j4aJ";
const char *password = "teAeJVK3Dn";
// const char *ssid = "Mihai's iPhone";
// const char *password = "vericu12";

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

  // Reset positions
  reset_all();

  // Create command queue
  commandQueue = xQueueCreate(10, sizeof(Command));
  if (commandQueue == NULL)
  {
    Serial.println("Failed to create command queue!");
    while (1)
      ;
  }

  // Start servo task
  xTaskCreatePinnedToCore(
      servo_task,
      "Servo Task",
      4096,
      NULL,
      2,
      NULL,
      1);

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