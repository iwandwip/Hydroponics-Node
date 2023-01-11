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
        Serial.print(":");
        Serial.print(1);
        Serial.print(",");
        Serial.print(2);
        Serial.print(",");
        Serial.print(3);
        Serial.println();

        espSerial.print(":");
        espSerial.print(1);
        espSerial.print(",");
        espSerial.print(2);
        espSerial.print(",");
        espSerial.print(3);
        espSerial.println();
        
        delay(COMM_INTERVAL);
}
