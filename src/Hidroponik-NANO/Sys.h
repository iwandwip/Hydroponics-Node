#pragma once

#define BAUD 9600

struct MainSys {
        void Init(void (*Start)(void));

        void Handler();
        void Reset();

      private:
        uint32_t mainTmr;
};


extern MainSys sys;