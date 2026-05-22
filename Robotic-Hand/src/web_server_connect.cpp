#include "main_cfg.hpp"

/* GLOBAL VARIABLES */
extern const char *ssid;
extern const char *password;

WiFiClient client;
AsyncWebServer server(80);

// WIFI
void connect_to_server()
{
    Serial.println("Connecting to WiFi...");

    WiFi.disconnect(true, true);
    vTaskDelay(pdMS_TO_TICKS(1000));

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);

    WiFi.begin(ssid, password);

    int tries = 0;
    while (WiFi.status() != WL_CONNECTED && tries < 40)
    {
        vTaskDelay(pdMS_TO_TICKS(500));
        Serial.print(".");
        Serial.println(WiFi.status());
        tries++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("WiFi connected!");
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.println("WiFi failed. Starting fallback AP...");
        WiFi.softAP("RobotHand-Setup", "12345678");
        Serial.print("AP IP: ");
        Serial.println(WiFi.softAPIP());
    }
}

// SERVO TASK
void servo_task(void *param)
{
    char gesture[32];
    FingerCmd fcmd;

    while (true)
    {
        if (xQueueReceive(gestureQueue, &gesture, 0))
        {
            init_gesture(gesture);
        }

        if (xQueueReceive(fingerQueue, &fcmd, 0))
        {
            if (strcmp(fcmd.finger, "thumb") == 0)
                servo_thumb.write(fcmd.angle);
            else if (strcmp(fcmd.finger, "index") == 0)
                servo_index.write(fcmd.angle);
            else if (strcmp(fcmd.finger, "middle") == 0)
                servo_middle.write(fcmd.angle);
            else if (strcmp(fcmd.finger, "ring") == 0)
                servo_ring.write(fcmd.angle);
            else if (strcmp(fcmd.finger, "pinky") == 0)
                servo_little.write(fcmd.angle);
        }

        update_gesture();
        vTaskDelay(pdMS_TO_TICKS(8));
    }
}

// ROUTES
void setup_routes()
{
    server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

    // Gesture Handler — directly send the string
    server.on("/gesture", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        if (request->hasParam("name"))
        {
            char gesture[32];
            // strncpy copies 32 byte buffer so that it can enter Queue (Queue does not accept C++ objects with constructors)
            strncpy(gesture, request->getParam("name")->value().c_str(), sizeof(gesture));

            if (xQueueSend(gestureQueue, &gesture, 0) != pdPASS)
            {
                request->send(500, "text/plain", "Queue full");
                return;
            }

            request->send(200, "text/plain", "OK");
            Serial.println("Gesture queued: " + String(gesture));
        }
        else
        {
            request->send(400, "text/plain", "Missing name parameter");
        } });

    server.on("/finger", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        if (request->hasParam("finger") && request->hasParam("angle"))
        {
            FingerCmd fcmd;
            strncpy(fcmd.finger, request->getParam("finger")->value().c_str(), sizeof(fcmd.finger));
            fcmd.angle = request->getParam("angle")->value().toInt();

            if (xQueueSend(fingerQueue, &fcmd, 0) != pdPASS)
            {
                request->send(500, "text/plain", "Queue full");
                return;
            }

            request->send(200, "text/plain", "OK");
            Serial.println("Finger queued: " + String(fcmd.finger) + " Angle: " + String(fcmd.angle));
        }
        else
        {
            request->send(400, "text/plain", "Missing finger or angle parameter");
        } });

    server.begin();
    Serial.println("AsyncWebServer started");
}