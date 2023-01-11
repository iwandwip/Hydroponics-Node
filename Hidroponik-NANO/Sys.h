#pragma once

#define BAUD 9600

#define RELAY_PIN_1 5
#define RELAY_PIN_2 6
#define RELAY_PIN_3 7
#define RELAY_PIN_4 8

struct MainSys {
        void Init(void (*Start)(void));

        void Handler();
        void Reset();

      private:
        uint32_t mainTmr;
};


extern MainSys sys;