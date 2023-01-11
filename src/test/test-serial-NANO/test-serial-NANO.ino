#include "SoftwareSerial.h"

#define COMM_INTERVAL 1000
#define COM_RX_PIN 2
#define COM_TX_PIN 3

SoftwareSerial espSerial(COM_TX_PIN, COM_RX_PIN);

void setup() {
        Serial.begin(9600);
        espSerial.begin(9600);
}

void loop() {
        Serial.print("Data ke NODEMCU ");
        Serial.print("DataTigaBelas");
        Serial.print(":");
        Serial.print("DataEmpatBelas");
        Serial.print(",");
        Serial.print("DataLimaBelas");
        Serial.println();

        espSerial.print(":");
        espSerial.print("DataTigaBelas");
        espSerial.print(":");
        espSerial.print("DataEmpatBelas");
        espSerial.print(":");
        espSerial.print("DataLimaBelas");
        espSerial.print(":");
        espSerial.println();

        delay(COMM_INTERVAL);
}
