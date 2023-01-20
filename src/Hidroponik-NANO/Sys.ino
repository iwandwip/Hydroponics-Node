#include "Sys.h"
#include "Comms.h"
#include "Sensors.h"

#define TEMP_TOLERANCE 3

MainSys sys;

void MainSys::Init(void (*StartCallback)(void)) {
        Serial.begin(BAUD);
        StartCallback();

        for (uint8_t i = 0; i < 4; i++) {
                pinMode(pinRelay[i], OUTPUT);
                digitalWrite(pinRelay[i], HIGH);
        }
}

void MainSys::Handler() {
        if (sens_mem_t->getTemperature() < com_mem_t->getSpTemp() - TEMP_TOLERANCE) {
                digitalWrite(RELAY_PIN_4, LOW);   // Water Heat On
                digitalWrite(RELAY_PIN_2, HIGH);  // Water Cold Off
                digitalWrite(RELAY_PIN_3, HIGH);
        }

        if (sens_mem_t->getTemperature() > com_mem_t->getSpTemp() + TEMP_TOLERANCE) {
                digitalWrite(RELAY_PIN_4, HIGH);  // Water Heat Off
                digitalWrite(RELAY_PIN_2, LOW);   // Water Cold On
                digitalWrite(RELAY_PIN_3, LOW);
        }
        double realDist = sens_mem_t->getDistance() - 20;
        if (realDist > com_mem_t->getSpDist()) {
                digitalWrite(RELAY_PIN_1, LOW);
        } else {
                digitalWrite(RELAY_PIN_1, HIGH);
        }
}

void MainSys::Reset() {
}