#include "Comms.h"

Comms com;

SoftwareSerial nanoSerial(COM_TX_PIN, COM_RX_PIN);

void Comms::Init() {
        nanoSerial.begin(9600);
        nanoSerial.println();
}

void Comms::Handler() {
        if (nanoSerial.available()) {

                char rxBuffer[250];
                uint8_t rxBufferPtr = 0;

                rxBuffer[rxBufferPtr++] = nanoSerial.read();
                if (rxBuffer[0] != ':') return;

                while (1) {
                        if (nanoSerial.available()) {
                                rxBuffer[rxBufferPtr++] = nanoSerial.read();
                                if (rxBuffer[rxBufferPtr - 1] == '\n') break;
                        }
                }

                rxBuffer[rxBufferPtr] = 0;
                char *data = rxBuffer;

                data = strchr(data, ':') + 1;
                (*this).distance = atof(data);
                data = strchr(data, ',') + 1;
                (*this).ph_act = atof(data);
                data = strchr(data, ',') + 1;
                (*this).tempC = atof(data);
        }

        if (millis() - comTmr >= COMM_INTERVAL) {

                // nanoSerial.print(":");
                // nanoSerial.print(data[0]);
                // nanoSerial.print(",");
                // nanoSerial.print(data[1]);
                // nanoSerial.print(",");
                // nanoSerial.print(data[2]);
                // nanoSerial.println();

                comTmr = millis();
        }
}