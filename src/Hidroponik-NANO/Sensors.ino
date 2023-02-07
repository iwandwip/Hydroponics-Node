#include "Sensors.h"

#define TEMP_SAMPLE_TIME 2000
#define DIST_SAMPLE_TIME 50
#define PH_SAMPLE_TIME 100

#define PH_CAL 21.34 + 2.3 - 2.39  // 21.34 + 4.0

Sensors sens;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DIST);

SimpleKalmanFilter Kf(2, 2, 0.01);

void Sensors::Init() {
        DS18B20.begin();
        pinMode(PH_PIN, INPUT);
}

void Sensors::Handler() {
        if (millis() - u_time[0] >= DIST_SAMPLE_TIME) {
                (*this).distance = sonar.ping_cm();
                u_time[0] = millis();
        }

        if (millis() - u_time[1] >= TEMP_SAMPLE_TIME) {
                DS18B20.requestTemperatures();
                (*this).tempC = regressDS18B20(
                  DS18B20.getTempCByIndex(0));
                (*this).tempF = DS18B20.getTempFByIndex(0);
                u_time[1] = millis();
        }

        for (int i = 0; i < 10; i++) {
                unsigned long t = 30;
                for (static unsigned long e_time; millis() - e_time >= (t); e_time += (t)) {
                        buffer_arr[i] = analogRead(PH_PIN);
                }
        }

        if (millis() - u_time[2] >= PH_SAMPLE_TIME) {
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
                ph_volt = (float)avgval * 5.0 / 1024.0 / 6;
                // ph_act = Kf.updateEstimate(
                //   regressPH(-5.70 * ph_volt + PH_CAL));
                ph_act = (-5.70 * ph_volt + PH_CAL);
                if (ph_act < 0) ph_act = random(1, 10) * 0.1;
                u_time[2] = millis();
        }

        float percentAcid = (1 / pow(10, ph_act)) * 100;
        float percentBase = (1 / pow(10, 14 - ph_act)) * 100;
}

double Sensors::regressDS18B20(double x) {
        double terms[] = {
                3.5367836419193766e+000,
                8.4963579397464684e-001,
                8.6377827469813170e-004
        };

        size_t csz = sizeof terms / sizeof *terms;

        double t = 1;
        double r = 0;
        for (int i = 0; i < csz; i++) {
                r += terms[i] * t;
                t *= x;
        }
        return r;
}

double Sensors::regressPH(double x) {
        double terms[] = {
                1.4789234356773051e+000,
                8.4414032409362727e-001,
                -4.3054194758747766e-003
        };

        size_t csz = sizeof terms / sizeof *terms;

        double t = 1;
        double r = 0;
        for (int i = 0; i < csz; i++) {
                r += terms[i] * t;
                t *= x;
        }
        return r;
}

void Sensors::Debug() {
        if (millis() - dbgTmr >= 50) {
                Serial.print("dist = " + String(distance));
                Serial.print(" | temp = " + String(tempC));
                Serial.println(" | ph = " + String(ph_act));
                dbgTmr = millis();
        }
}