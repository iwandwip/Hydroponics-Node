#include "Sensors.h"
#include "Servers.h"
#include "Sys.h"

void Start() {
        sens.Init();
        server.connectToWiFi(
          "KASTARA GROUP INDONESIA",
          "KASTARA@2022");
        server.waitConnection(500);
        // server.Login();
        // server.Init();
}

void Stop() {
        sys.Reset();
}

void setup() {
        sys.Init(Start, Stop);
}

void loop() {
        sys.Handler();
        sens.Handler();
        sens.Debug();
        // server.Handler();
        // server.sendToFB(buff, addr);
}
