#pragma once

#include "SoftwareSerial.h"
#include "Pins.h"

#define COMM_INTERVAL 1000

struct Comms {
        void Init();
        void Handler(float data[]);
        void Debug();

        double getSpDist() {
                return sp_dist;
        }

        double getSpTemp() {
                return sp_temp;
        }

      private:
        double sp_dist;
        double sp_temp;
        uint32_t comTmr;
};

extern Comms com;