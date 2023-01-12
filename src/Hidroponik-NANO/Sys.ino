#include "Sys.h"

MainSys sys;

void MainSys::Init(void (*StartCallback)(void)) {
        Serial.begin(BAUD);
        StartCallback();

        for (uint8_t i = 0; i < 4; i++) {
                pinMode(pinRelay[i], OUTPUT);
        }
}

void MainSys::Handler() {
        // Serial.println("test");
        // delay(1000);
}

void MainSys::Reset() {
}