#include "Sys.h"

#define BAUD 115200

MainSys sys;

void MainSys::Init(void (*StartCallback)(void),
                   void (*Shutdown)(void)) {
        Serial.begin(BAUD);
        StartCallback();
}

void MainSys::Handler() {
        if (millis() - mainTmr >= 1000) {
                // Serial.println("test");
                mainTmr = millis();
        }
}

void MainSys::Reset() {
}