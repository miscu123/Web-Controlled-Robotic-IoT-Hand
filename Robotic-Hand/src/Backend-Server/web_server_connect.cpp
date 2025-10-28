/* INCLUSIONS */
#include "main_cfg.hpp"

/* LOCAL MACROS */

/* GLOBAL VARIABLES */
const char *ssid = "DIGI-j4aJ";
const char *password = "teAeJVK3Dn";
WiFiServer server(80);
WiFiClient client;
String header;

/* LOCAL VARIABLES */
/* LOCAL FUNCTION DECLARATIONS */
/* LOCAL FUNCTION DEFINITIONS */
/* GLOBAL FUNCTION DEFINITIONS */
void connect_to_server(void)
{
    Serial.print("Connecting to server...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(200);
        Serial.print(".");
    }
    Serial.print("Connected!");
    server.begin();
}

void get_server_client()
{
    client = server.available(); // always listen for incoming clients

    if (client)
    {
        Serial.println("New client connected");
        String currentLine = "";
        while (client.connected()) // while the client is connected
        {
            if (client.available())
            {
                char c = client.read(); // read a byte
                Serial.write(c);        // print the character
                header += c;
                if (c == '\n') // if the byte is newline
                {
                    // if the current line is blank ==> 2 newline chars in a row ==> end of client HTTP request
                    if (currentLine.length() == 0)
                    {
                        // HTTP headers always start with a response code
                        client.println("HTTP/1.1 200 OK");
                        // HTTP headers always have a content-type so the client knows what is coming, then blank line
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();
                    }
                }
            }
        }
    }

    header = "";
    client.stop();
    Serial.println("Client disconnected");
    Serial.println();
}