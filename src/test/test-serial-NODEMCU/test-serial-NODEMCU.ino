#include "SoftwareSerial.h"

#define COMM_INTERVAL 1000
#define COM_RX_PIN D6
#define COM_TX_PIN D7

SoftwareSerial nanoSerial(COM_TX_PIN, COM_RX_PIN);
int data[3];

void setup() {
        Serial.begin(115200);
        nanoSerial.begin(9600);
}

void loop() {
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
                data[0] = atoi(data);
                data = strchr(data, ',') + 1;
                data[1] = atoi(data);
                data = strchr(data, ',') + 1;
                data[2] = atoi(data);
        }

        Serial.print(":");
        Serial.print(data[0]);
        Serial.print(",");
        Serial.print(data[1]);
        Serial.print(",");
        Serial.print(data[2]);
        Serial.println();
}
