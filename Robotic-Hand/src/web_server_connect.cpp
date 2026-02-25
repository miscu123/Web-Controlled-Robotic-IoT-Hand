/* INCLUSIONS */
#include "main_cfg.hpp"

/* LOCAL MACROS */

/* GLOBAL VARIABLES */
extern const char *ssid;
extern const char *password;
WiFiClient client;
String header;

/* Async Server on port 80 */
AsyncWebServer server(80);

/* LOCAL VARIABLES */
/* LOCAL FUNCTION DECLARATIONS */
/* LOCAL FUNCTION DEFINITIONS */

/* GLOBAL FUNCTION DEFINITIONS */
/* HELPER: Connect to WiFi */
void connect_to_server()
{
    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    WiFi.setSleep(false); // disable WiFi sleep for low latency

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(200);
        Serial.print(".");
    }

    Serial.println();
    Serial.print("Connected! IP: ");
    Serial.println(WiFi.localIP());
}

/* HELPER: Setup async routes */
void setup_routes()
{
    // Serve all static files from LittleFS root
    server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

    // Gesture handler
    server.on("/gesture", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        if (request->hasParam("name")) {
            String gesture = request->getParam("name")->value();
            
            if (gesture == "close") close_all();
            else if (gesture == "countU") count_up();
            else if (gesture == "countD") count_down();
            else if (gesture == "peace") peace();
            else if (gesture == "ok") ok_sign();
            else if (gesture == "hold") hold_phone();
            else if (gesture == "come") come_here_sign();
            else if (gesture == "love") i_love_you_sign();
            else if (gesture == "berserk") go_berserk();

            request->send(200, "text/plain", "OK");
            Serial.println("Gesture requested: " + gesture);
        } else {
            request->send(400, "text/plain", "Missing name parameter");
        } });

    server.begin();
    Serial.println("AsyncWebServer started");
}