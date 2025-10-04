#include <Arduino.h>
#include <freertos/task.h>

void blinkyTaskRun(void* kvargs);

void setup() {
        Serial.begin(9600);
        pinMode(2, OUTPUT);

        delay(500);
        xTaskCreate(blinkyTaskRun, "Blinky", 1024, NULL, 5, NULL);

        Serial.println("Blinky Task Created!!!");
}

void loop() {
        Serial.println("Main Loop Running");
        delay(50);
}

void blinkyTaskRun(void* kvargs)
{
        Serial.println("Blinky task starts to run!!!");
        while (true) {
                Serial.println("Flashing LED On");
                digitalWrite(2, HIGH);
                delay(200);
                digitalWrite(2, LOW);
                Serial.println("Flashing LED Off");
                delay(200);
        }
}