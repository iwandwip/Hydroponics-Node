const uint8_t pinRelay[] = { 7, 8, 9, 10 };

void setup() {
        Serial.begin(9600);
        for (int i = 0; i < 4; i++) {
                pinMode(pinRelay[i], OUTPUT);
                digitalWrite(pinRelay[i], HIGH);
        }
}

void loop() {
        for (int i = 0; i < 4; i++) {
                digitalWrite(pinRelay[i], LOW);
                Serial.println("Relay " + String(i + 1) + " Menyala");
                delay(1000);
        }
        for (int i = 0; i < 4; i++) {
                digitalWrite(pinRelay[i], HIGH);
                Serial.println("Relay " + String(i + 1) + " Mati");
                delay(1000);
        }
}
