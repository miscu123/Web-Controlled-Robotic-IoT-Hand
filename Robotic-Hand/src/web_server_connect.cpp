#include "main_cfg.hpp"

/* GLOBAL VARIABLES */
extern const char *ssid;
extern const char *password;

WiFiClient client;
AsyncWebServer server(80);

/* ================= WIFI ================= */
void connect_to_server()
{
    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    WiFi.setSleep(false);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(200);
        Serial.print(".");
    }

    Serial.println();
    Serial.print("---------------------------");
    Serial.print("Connected! IP: ");
    Serial.print("---------------------------");
    Serial.println(WiFi.localIP());
}

/* ================= SERVO TASK ================= */
void servo_task(void *param)
{
    Command cmd;

    while (true)
    {
        if (xQueueReceive(commandQueue, &cmd, 0))
        {
            if (cmd.type == CMD_GESTURE)
                init_gesture(cmd.gesture);
            else if (cmd.type == CMD_FINGER)
            {
                if (cmd.finger == "thumb")
                    servo_thumb.write(cmd.angle);
                if (cmd.finger == "index")
                    servo_index.write(cmd.angle);
                if (cmd.finger == "middle")
                    servo_middle.write(cmd.angle);
                if (cmd.finger == "ring")
                    servo_ring.write(cmd.angle);
                if (cmd.finger == "pinky")
                    servo_little.write(cmd.angle);
            }
        }

        update_gesture();
        vTaskDelay(pdMS_TO_TICKS(8));
    }
}

/* ================= ROUTES ================= */

void setup_routes()
{
    // Serve static files
    server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

    /* -------- Gesture Handler -------- */
    server.on("/gesture", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        if (request->hasParam("name"))
        {
            String gesture = request->getParam("name")->value();

            Command cmd;
            cmd.type = CMD_GESTURE;
            cmd.gesture = gesture;

            if (xQueueSend(commandQueue, &cmd, 0) != pdPASS)
            {
                request->send(500, "text/plain", "Queue full");
                return;
            }

            request->send(200, "text/plain", "OK");
            Serial.println("Gesture queued: " + gesture);
        }
        else
        {
            request->send(400, "text/plain", "Missing name parameter");
        } });

    /* -------- Finger Handler -------- */
    server.on("/finger", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        if (request->hasParam("finger") && request->hasParam("angle"))
        {
            String finger = request->getParam("finger")->value();
            int angle = request->getParam("angle")->value().toInt();

            Command cmd;
            cmd.type = CMD_FINGER;
            cmd.finger = finger;
            cmd.angle = angle;

            if (xQueueSend(commandQueue, &cmd, 0) != pdPASS)
            {
                request->send(500, "text/plain", "Queue full");
                return;
            }

            request->send(200, "text/plain", "OK");
            Serial.println("Finger queued: " + finger + " Angle: " + String(angle));
        }
        else
        {
            request->send(400, "text/plain", "Missing finger or angle parameter");
        } });

    server.begin();
    Serial.println("AsyncWebServer started");
}