#pragma once

#include "SimpleKalmanFilter.h"
#include "DallasTemperature.h"
#include "NewPing.h"
#include "OneWire.h"
#include "stdint.h"
#include "Pins.h"

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

      private:
        double regressDS18B20(double x);
        double regressPH(double x);

        uint32_t
          u_time[3],
          dbgTmr, avgTmr;

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