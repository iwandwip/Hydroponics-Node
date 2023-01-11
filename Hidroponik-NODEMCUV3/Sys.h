#pragma once

struct MainSys {
        void Init(void (*Start)(void),
                  void (*Shutdown)(void));

        void Handler();
        void Reset();

      private:
        uint32_t mainTmr;
};


extern MainSys sys;