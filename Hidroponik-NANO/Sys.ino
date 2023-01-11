#include "Sys.h"

MainSys sys;

void MainSys::Init(void (*StartCallback)(void)) {
        Serial.begin(BAUD);
        StartCallback();
}

void MainSys::Handler() {
        // Serial.println("test");
        // delay(1000);
}

void MainSys::Reset() {
}