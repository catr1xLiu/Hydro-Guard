#include <Arduino.h>
#include <freertos/task.h>
#include <HTTPClient.h>
#include <WiFi.h>

const char* WIFI_SSID = "Yiran’s iPhone";
const char* WIFI_PASSWORD = "manwhatcanisay";
const char* SERVER_URL = "http://172.20.10.4:8000";
const char* TEMPERATURE_PATH = "/temperature";
const char* ROOM_NUM = "room001";

#define LED_STATUS_LIGHT 2

void temperature_wifi(void* kvargs);

void setup() {
        Serial.begin(9600);

        Serial.println("Connecting to WIFI...");

        WiFi.disconnect(true);  // Disconnect any previous
        delay(1000);

        WiFi.mode(WIFI_STA);    // Set Station mode
        delay(1000);

        bool found = false;
        while (!found) {
                delay(500);
                Serial.print("Searching for Target Network, Available Networks: ");
                int n = WiFi.scanNetworks();
                for (int i = 0; i < n && i < 6; i++) {
                        Serial.print(WiFi.SSID(i));
                        found |= WiFi.SSID(i) == WIFI_SSID;
                        Serial.print(", ");
                }
                Serial.println();
        }

        Serial.println("Establishing Connection...");
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                Serial.printf("Status: %d\n", WiFi.status());
        }

        Serial.println("\n WiFi Connected!");
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());

        xTaskCreate(temperature_wifi, "Temperature Broadcasting", 4096, NULL, 10, NULL);
}

void loop() {

}

void temperature_wifi(void* kvargs)
{
        while (true) {
                delay(1000);
                static float temperature_c = 24.0;
                temperature_c += random(-100, 200) / 100.0;

                if (WiFi.status() != WL_CONNECTED) {
                        Serial.println("WiFi not connected, no data sent...");
                        continue;
                }

                HTTPClient http;

                String url = String(SERVER_URL) + String(TEMPERATURE_PATH)
                        + "?room_num=" + ROOM_NUM
                        + "&temperature_c=" + String(temperature_c);

                http.begin(url);
                int httpCode = http.POST("");

                if (httpCode == 200) {
                        Serial.println("Temperature Data Sent.");
                }
                else {
                        Serial.printf("Error: Cannot Send Tempreature Data, error code: %d\n", httpCode);
                }

                http.end();
        }
}