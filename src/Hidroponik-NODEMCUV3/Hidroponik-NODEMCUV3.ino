#include "Servers.h"
#include "Comms.h"
#include "Sys.h"

void Start() {
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

        server.sendToFB(com.getUnoData(),
                        com.getAddressToFirebase());
}
