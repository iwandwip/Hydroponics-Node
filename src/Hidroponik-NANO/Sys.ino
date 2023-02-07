#include "Sys.h"

#define TEMP_TOLERANCE 3
#define ULTRASONIC_MIN_HEIGHT 20

#define ON 1
#define OFF 0

MainSys sys;

void MainSys::Init(void (*StartCallback)(void)) {
        Serial.begin(BAUD);
        StartCallback();

        pinMode(BUZZER_PIN, OUTPUT);
        pinMode(LED_RED, OUTPUT);
        pinMode(LED_GREEN, OUTPUT);

        for (uint8_t i = 0; i < 4; i++) {
                pinMode(pinRelay[i], OUTPUT);
                digitalWrite(pinRelay[i], HIGH);
        }
}

void MainSys::Handler() {
        if (sens_mem_t->getTemperature() < com_mem_t->getSpTemp() - TEMP_TOLERANCE) {
                digitalWrite(RELAY_PIN_4, LOW);   // Water Heat On
                digitalWrite(RELAY_PIN_2, HIGH);  // Water Cold Off

                // State Info
                heater = ON;
                cooler = OFF;
        }

        if (sens_mem_t->getTemperature() > com_mem_t->getSpTemp() + TEMP_TOLERANCE) {
                digitalWrite(RELAY_PIN_4, HIGH);  // Water Heat Off
                digitalWrite(RELAY_PIN_2, LOW);   // Water Cold On

                // State Info2
                heater = OFF;
                cooler = ON;
        }

        // double realDist = sens_mem_t->getDistance() - ULTRASONIC_MIN_HEIGHT;
        if (sens_mem_t->getDistance() > com_mem_t->getSpDist()) {
                digitalWrite(RELAY_PIN_1, LOW);
                filling = ON;
        } else {
                digitalWrite(RELAY_PIN_1, HIGH);
                filling = OFF;
        }

        digitalWrite(RELAY_PIN_3, LOW);

        // digitalWrite(RELAY_PIN_1, LOW);
        // digitalWrite(RELAY_PIN_2, LOW);
        // digitalWrite(RELAY_PIN_3, LOW);
        // digitalWrite(RELAY_PIN_4, LOW);

        // Serial.print("Heater = " + String(heater));
        // Serial.print(" | Cooler = " + String(cooler));
        // Serial.println(" | Filling = " + String(filling));
}

void MainSys::Reset() {
}