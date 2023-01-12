#include "Comms.h"

Comms com;

SoftwareSerial espSerial(COM_TX_PIN, COM_RX_PIN);

void Comms::Init() {
        espSerial.begin(9600);
        espSerial.println();
}

void Comms::Handler(float data[]) {
        if (millis() - comTmr >= COMM_INTERVAL) {

                espSerial.print(":");
                espSerial.print(data[0]);
                espSerial.print(",");
                espSerial.print(data[1]);
                espSerial.print(",");
                espSerial.print(data[2]);
                espSerial.println();

                comTmr = millis();
        }
}