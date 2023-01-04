#pragma once

#include "SoftwareSerial.h"

#define COMM_INTERVAL 1000
#define COM_RX_PIN 8
#define COM_TX_PIN 9

struct Comms {
        void Init();
        void Handler(float data[]);

      private:
        uint32_t comTmr;
};

extern Comms com;