#pragma once

#include "Pins.h"

#define BAUD 9600

struct MainSys {
        void Init(void (*Start)(void));

        void Handler();
        void Reset();

      private:
        Comms* com_mem_t = &com;
        Sensors* sens_mem_t = &sens;
        uint32_t mainTmr;
};


extern MainSys sys;