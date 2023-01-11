#pragma once

#include "Arduino.h"

#define USING_ONEWIRE
#define NO_PING_

#ifdef USING_PING
#include "NewPing.h"
#endif

#ifdef USING_ONEWIRE

#include "OneWire.h"
#include "DallasTemperature.h"
#define ONE_WIRE_BUS 4

#endif

#ifdef USING_PING

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 400

#endif

#if defined(NO_PING)
#define TRIGGER_PIN 5
#define ECHO_PIN 6

#endif

#define TRIG_PIN 12
#define ECHO_PIN 14

#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

#define PH_PIN 33
#define PH_CAL 24.04 - 0.4

struct Sensors {
        void Init();
        void Handler();
        void Debug();

        float* getDataToFirebase() {
                static float data[3];
                data[0] = distCM;
                data[1] = ph_act;
                data[2] = tempC;

                return data;
        }

        String* getAddressToFirebase() {
                static String addr[3];
                addr[0] = "/sens/float/distance";
                addr[1] = "/sens/float/ph";
                addr[2] = "/sens/float/temp";
                return addr;
        }

        volatile float getDistance(bool __inch = false) {
                if (!__inch) return distCM;
                else return distINCH;
        }

        volatile float getPhValue() {
                return ph_act;
        }

        volatile float getPhVolt() {
                return ph_volt;
        }

#ifdef USING_ONEWIRE

        volatile float getTempC() {
                return tempC;
        }

        volatile float getTempF() {
                return tempF;
        }

#endif

#ifdef USING_PING
        volatile uint16_t getDistance() {
                return dist;
        }
#endif
#if defined(NO_PING)
        volatile uint16_t getDistance() {
                return distance;
        }
#endif
      private:
        uint32_t sensTmr[3], dbgTmr;

        long duration;

        volatile float distCM = 0.0,
                       distINCH = 0.0;

        int buffer_arr[10], temp;
        unsigned long int avgval;

        volatile float ph_act = 0.0,
                       ph_volt = 0.0;

#ifdef USING_ONEWIRE
        volatile float tempC, tempF;
#endif
#ifdef USING_PING
        volatile uint16_t dist;
#endif
#if defined(NO_PING)
        volatile long distance;
        long duration;
#endif
};

extern Sensors sens;