#pragma once

#include "Pins.h"

#define BAUD 9600

#define HEATER 0
#define COOLER 1
#define FILLING 2

struct MainSys {
        void Init(void (*Start)(void));

        void Handler();
        void Reset();

        uint8_t getCoolerState() {
                return cooler;
        }

        uint8_t* getState() {
                static uint8_t data[3];
                data[0] = heater;
                data[1] = cooler;
                data[2] = filling;
                return data;
        }

      private:
        uint8_t heater = 0,
                cooler = 0,
                filling = 0;

        Comms* com_mem_t = &com;
        Sensors* sens_mem_t = &sens;
        uint32_t mainTmr;
};


extern MainSys sys;