#include "SoftwareSerial.h"

#define COMM_INTERVAL 1000
#define COM_RX_PIN D6
#define COM_TX_PIN D7

SoftwareSerial nanoSerial(COM_TX_PIN, COM_RX_PIN);
int dataInt[3];
String dataStr[3];

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
                String data = String(rxBuffer);

                dataStr[0] = parseString(data, ":", 1);
                dataStr[1] = parseString(data, ":", 2);
                dataStr[2] = parseString(data, ":", 3);

                // data = strchr(data, ':') + 1;
                // strcpy(dataChar[2], data);
                // // data = data;
                // // dataInt[0] = atoi(data);
                // data = strchr(data, ',') + 1;
                // strcpy(dataChar[1], data);
                // // data = data;
                // // dataInt[1] = atoi(data);
                // data = strchr(data, ',') + 1;
                // strcpy(dataChar[2], data);
                // // data = data;
                // // dataInt[2] = atoi(data);

                Serial.print("Data dari Arduino NANO ");
                Serial.print(":");
                Serial.print(dataStr[0]);
                Serial.print(",");
                Serial.print(dataStr[1]);
                Serial.print(",");
                Serial.print(dataStr[2]);
                Serial.println();
        }
}

// https://stackoverflow.com/questions/8941213/split-parse-and-get-value-from-a-char-array
char* getTagValue(char* a_tag_list, char* a_tag) {
        char* tag_list_copy = (char*)malloc(strlen(a_tag_list) + 1);
        char* result = 0;
        char* s;

        strcpy(tag_list_copy, a_tag_list);

        s = strtok(tag_list_copy, "&");
        while (s) {
                char* equals_sign = strchr(s, '=');
                if (equals_sign) {
                        *equals_sign = 0;
                        if (0 == strcmp(s, a_tag)) {
                                equals_sign++;
                                result = (char*)malloc(strlen(equals_sign) + 1);
                                strcpy(result, equals_sign);
                        }
                }
                s = strtok(0, "&");
        }
        free(tag_list_copy);

        return result;
}

String parseString(String data, char separator[], int index) {
        int found = 0;
        int strIndex[] = { 0, -1 };
        int maxIndex = data.length() - 1;
        for (int i = 0; i <= maxIndex && found <= index; i++) {
                if (data.charAt(i) == separator[0] || i == maxIndex) {
                        found++;
                        strIndex[0] = strIndex[1] + 1;
                        strIndex[1] = (i == maxIndex) ? i + 1 : i;
                }
        }
        return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
