#pragma once

#include "stdint.h"
#include "NewPing.h"
#include "OneWire.h"
#include "DallasTemperature.h"

#define ONE_WIRE_BUS 5

#define TRIG_PIN 2
#define ECHO_PIN 4
#define MAX_DIST 200

#define PH_PIN 7
#define PH_CAL 24.04 - 0.4

struct Sensors {
        void Init();
        void Handler();
        void Debug();

        float* getSerialDataSend() {
                static float data[3];
                data[0] = distance;
                data[1] = ph_act;
                data[2] = tempC;

                return data;
        }

        volatile float getDistance() {
                return distance;
        }

        volatile float getPhValue() {
                return ph_act;
        }

        volatile float getTemperature(bool __f = false) {
                if (!__f) return tempC;
                else return tempF;
        }


        volatile float getPhVolt() {
                return ph_volt;
        }

      private:
        uint32_t
          u_time[3],
          dbgTmr;

        volatile float
          tempC,
          tempF,
          distance;

        int buffer_arr[10], temp;
        unsigned long int avgval;

        volatile float ph_act = 0.0,
                       ph_volt = 0.0;
};

extern Sensors sens;