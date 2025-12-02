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
    Serial.print("ESP32 IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
}

void get_server_client()
{
    client = server.available(); // Listen for incoming clients

    if (client)
    {
        Serial.println("New client connected");
        header = "";
        String currentLine = "";

        while (client.connected())
        {
            if (client.available())
            {
                char c = client.read();
                header += c;

                if (c == '\n')
                {
                    if (currentLine.length() == 0)
                    {
                        // Extract path from GET
                        String path = "/";
                        int getIndex = header.indexOf("GET ");
                        int httpIndex = header.indexOf(" HTTP");
                        if (getIndex >= 0 && httpIndex > getIndex)
                        {
                            path = header.substring(getIndex + 4, httpIndex);
                        }
                        if (path == "/")
                            path = "/index.html";
                        if (!path.startsWith("/"))
                            path = "/" + path;

                        Serial.print("Client requested: ");
                        Serial.println(path);

                        // ---- Handle gestures ----
                        if (path.startsWith("/gesture"))
                        {
                            // Parse the "name" parameter
                            int nameIndex = path.indexOf("name=");
                            String gesture = "";
                            if (nameIndex >= 0)
                            {
                                gesture = path.substring(nameIndex + 5);
                                int ampIndex = gesture.indexOf('&'); // ignore extra parameters
                                if (ampIndex >= 0)
                                    gesture = gesture.substring(0, ampIndex);
                            }

                            Serial.println("Gesture requested: " + gesture);

                            // Call your C++ gesture functions
                            if (gesture == "close")
                                close_all();
                            else if (gesture == "countU")
                                count_up();
                            else if (gesture == "countD")
                                count_down();
                            else if (gesture == "peace")
                                peace();
                            else if (gesture == "ok")
                                ok_sign();
                            else if (gesture == "hold")
                                hold_phone();
                            else if (gesture == "come")
                                come_here_sign();
                            else if (gesture == "love")
                                i_love_you_sign();
                            else if (gesture == "berserk")
                                go_berserk();

                            // Send HTTP response
                            client.println("HTTP/1.1 200 OK");
                            client.println("Content-Type: text/plain");
                            client.println("Connection: close");
                            client.println();
                            client.println("OK: " + gesture);

                            break; // End of response
                        }
                        // ---- Serve files ----
                        else
                        {
                            File file = LittleFS.open(path, "r");

                            if (file)
                            {
                                Serial.print("Sending ");
                                Serial.println(path);

                                // Set correct content type
                                if (path.endsWith(".css"))
                                    client.println("HTTP/1.1 200 OK\r\nContent-Type: text/css\r\n\r\n");
                                else if (path.endsWith(".js"))
                                    client.println("HTTP/1.1 200 OK\r\nContent-Type: application/javascript\r\n\r\n");
                                else
                                    client.println("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");

                                while (file.available())
                                    client.write(file.read());

                                file.close();
                                Serial.println("File sent successfully!");
                            }
                            else
                            {
                                Serial.println(path + " not found!");
                                client.println("HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>404 Not Found</h1>");
                            }

                            client.println();
                            break; // End of response
                        }
                        // -------------------------------
                    }
                    else
                    {
                        currentLine = "";
                    }
                }
                else if (c != '\r')
                {
                    currentLine += c;
                }
            }
        }

        client.stop();
        Serial.println("Client disconnected");
        Serial.println();
    }
}
