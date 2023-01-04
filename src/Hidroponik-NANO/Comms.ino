#include "Comms.h"

Comms com;

SoftwareSerial espSerial(COM_TX_PIN, COM_RX_PIN);

void Comms::Init() {
        espSerial.begin(9600);
        espSerial.println();
}

void Comms::Handler(float data[]) {
        if (millis() - comTmr >= COMM_INTERVAL) {

                Serial.print(":");
                Serial.print(data[0]);
                Serial.print(",");
                Serial.print(data[1]);
                Serial.print(",");
                Serial.print(data[2]);
                Serial.println();

                comTmr = millis();
        }
}