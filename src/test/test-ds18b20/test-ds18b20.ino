#include <OneWire.h>
#include <DallasTemperature.h>

OneWire pin_DS18B20(4);
DallasTemperature DS18B20(&pin_DS18B20);

void setup(void) {
        Serial.begin(9600);
        DS18B20.begin();
}

void loop(void) {
        DS18B20.requestTemperatures();
        Serial.print("Suhu Celsius: ");
        Serial.print(DS18B20.getTempCByIndex(0));
        Serial.print(" - Suhu Fahrenheit: ");
        Serial.println(DS18B20.getTempFByIndex(0));
}

double regress(double x) {
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