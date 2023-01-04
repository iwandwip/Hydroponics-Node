#include "Sensors.h"

Sensors sens;

#ifdef USING_ONEWIRE

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#endif
#ifdef USING_PING

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

#endif
void Sensors::Init() {

#ifdef USING_ONEWIRE
        sensors.begin();
#endif
#if defined(NO_PING)
        pinMode(TRIGGER_PIN, OUTPUT);
        pinMode(ECHO_PIN, INPUT);
#endif
        pinMode(TRIG_PIN, OUTPUT);
        pinMode(ECHO_PIN, INPUT);
}

void Sensors::Handler() {
        if (millis() - sensTmr[1] >= 50) {

                digitalWrite(TRIG_PIN, LOW);
                delayMicroseconds(2);
                digitalWrite(TRIG_PIN, HIGH);
                delayMicroseconds(10);
                digitalWrite(TRIG_PIN, LOW);

                (*this).duration = pulseIn(ECHO_PIN, HIGH);
                (*this).distCM = duration * SOUND_VELOCITY / 2;
                (*this).distINCH = distCM * CM_TO_INCH;

                sensTmr[1] = millis();
        }

#ifdef USING_ONEWIRE
        if (millis() - sensTmr[0] >= 300) {
                sensors.requestTemperatures();

                (*this).tempC = sensors.getTempCByIndex(0);
                (*this).tempF = sensors.getTempFByIndex(0);

                sensTmr[0] = millis();
        }
#endif
#ifdef USING_PING
        if (millis() - sensTmr[1] >= 50) {

                (*this).dist = sonar.ping_cm();

                sensTmr[1] = millis();
        }
#endif
#if defined(NO_PING)
        if (millis() - sensTmr[1] >= 50) {

                digitalWrite(TRIGGER_PIN, LOW);
                delayMicroseconds(2);
                digitalWrite(TRIGGER_PIN, HIGH);
                delayMicroseconds(10);
                digitalWrite(TRIGGER_PIN, LOW);

                (*this).duration = pulseIn(ECHO_PIN, HIGH);
                (*this).distance = duration * 0.034 / 2;

                sensTmr[1] = millis();
        }
#endif
}

void Sensors::Debug() {
        if (millis() - dbgTmr >= 300) {

                Serial.println("Dist (CM)   = " + String(distCM));
                Serial.println("Dist (INCH) = " + String(distINCH));

                dbgTmr = millis();
        }
}