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

                        // Open requested file
                        File file = LittleFS.open(path, "r");
                        // if we find a file, we send it and print what we connect to for debugging
                        // can be removed later on
                        if (file)
                        {
                            Serial.print("Sending ");
                            Serial.println(path);

                            // conn to css file
                            if (path.endsWith(".css"))
                                client.println("HTTP/1.1 200 OK\r\nContent-Type: text/css\r\n\r\n");
                            // conn to js file
                            else if (path.endsWith(".js"))
                                client.println("HTTP/1.1 200 OK\r\nContent-Type: application/javascript\r\n\r\n");
                            else
                                client.println("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");

                            while (file.available())
                            {
                                client.write(file.read());
                            }
                            file.close();
                            Serial.println("File sent successfully!");
                        }
                        // err if we can not connect to files
                        else
                        {
                            Serial.println(path + " not found!");
                            client.println("HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>404 Not Found</h1>");
                        }

                        client.println();
                        break; // End of response
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