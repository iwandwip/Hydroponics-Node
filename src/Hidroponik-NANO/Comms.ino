#include "Comms.h"

Comms com;

SoftwareSerial espSerial(COM_TX_PIN, COM_RX_PIN);

void Comms::Init() {
        espSerial.begin(9600);
        espSerial.println();
}

void Comms::Handler(float data[]) {
        if (espSerial.available()) {

                char rxBuffer[250];
                uint8_t rxBufferPtr = 0;

                rxBuffer[rxBufferPtr++] = espSerial.read();
                if (rxBuffer[0] != ':') return;

                while (1) {
                        if (espSerial.available()) {
                                rxBuffer[rxBufferPtr++] = espSerial.read();
                                if (rxBuffer[rxBufferPtr - 1] == '\n') break;
                        }
                }

                rxBuffer[rxBufferPtr] = 0;
                char *data = rxBuffer;

                data = strchr(data, ':') + 1;
                (*this).sp_dist = atof(data);
                data = strchr(data, ',') + 1;
                (*this).sp_temp = atof(data);

                // Serial.println("sp_dist " + String(sp_dist));
                // Serial.println("sp_temp " + String(sp_temp));
        }

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