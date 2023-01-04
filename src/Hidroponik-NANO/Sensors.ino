#include "Sensors.h"

#define TEMP_SAMPLE_TIME 2000
#define DIST_SAMPLE_TIME 50
#define PH_SAMPLE_TIME 100

Sensors sens;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DIST);

void Sensors::Init() {
        sensors.begin();
}

void Sensors::Handler() {
        if (millis() - u_time[0] >= DIST_SAMPLE_TIME) {

                (*this).distance = sonar.ping_cm();

                u_time[0] = millis();
        }

        if (millis() - u_time[1] >= TEMP_SAMPLE_TIME) {

                sensors.requestTemperatures();

                (*this).tempC = sensors.getTempCByIndex(0);
                (*this).tempF = sensors.getTempFByIndex(0);

                u_time[1] = millis();
        }

        if (millis() - u_time[2] >= PH_SAMPLE_TIME) {


                for (int i = 0; i < 10; i++) {
                        buffer_arr[i] = analogRead(PH_PIN);
                        delay(30);
                }

                for (int i = 0; i < 9; i++) {
                        for (int j = i + 1; j < 10; j++) {
                                if (buffer_arr[i] > buffer_arr[j]) {
                                        temp = buffer_arr[i];
                                        buffer_arr[i] = buffer_arr[j];
                                        buffer_arr[j] = temp;
                                }
                        }
                }

                avgval = 0;

                for (int i = 2; i < 8; i++) {
                        avgval += buffer_arr[i];
                }

                ph_volt = (float)avgval * 5.0 / 1024 / 6;
                ph_act = -5.70 * ph_volt + PH_CAL;

                u_time[2] = millis();
        }
}

void Sensors::Debug() {
        if (millis() - dbgTmr >= 50) {

                Serial.println("distance = " + String(distance));
                Serial.println("tempC = " + String(tempC));
                Serial.println("ph_act = " + String(ph_act));

                dbgTmr = millis();
        }
}