#include "Sensors.h"
#include "Servers.h"
#include "Comms.h"
#include "Sys.h"

void Start() {
        // sens.Init();
        com.Init();
        server.connectToWiFi(
          "KASTARA GROUP INDONESIA",
          "KASTARA@2022");
        server.waitConnection(500);
        server.Login();
        server.Init();
}

void Stop() {
        sys.Reset();
}

void setup() {
        sys.Init(Start, Stop);
}

void loop() {
        sys.Handler();
        com.Handler();

        // float *datPtr = com.getUnoData();

        // Serial.println("distance = " + String(datPtr[0]));
        // Serial.println("ph_act = " + String(datPtr[1]));
        // Serial.println("tempC = " + String(datPtr[2]));

        // sens.Handler();
        // sens.Debug();

        // server.sendToFB(sens.getDataToFirebase(),
        //                 sens.getAddressToFirebase());
}
