#include "Sensors.h"
#include "Comms.h"
#include "Sys.h"

void Initialize() {
        sens.Init();
        com.Init();
}

void setup() {
        sys.Init(Initialize);
}

void loop() {
        sys.Handler();
        sens.Handler(
          sys.getCoolerState());
        sens.Debug();

        com.Handler(
          sens.getSerialDataSend(),
          sys.getState());
}
