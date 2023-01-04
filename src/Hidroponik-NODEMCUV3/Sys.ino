#include "Sys.h"

#define BAUD 115200

MainSys sys;

void MainSys::Init(void (*StartCallback)(void),
                   void (*Shutdown)(void)) {
        Serial.begin(BAUD);
        StartCallback();
}

void MainSys::Handler() {
        // Serial.println("test");
        // delay(1000);
}

void MainSys::Reset() {
        
}