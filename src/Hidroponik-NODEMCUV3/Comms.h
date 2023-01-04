#pragma once

#include "SoftwareSerial.h"

#define COMM_INTERVAL 1000
#define COM_RX_PIN D6
#define COM_TX_PIN D7

struct Comms {
        void Init();
        void Handler();

        float* getUnoData() {
                static float data[3];
                data[0] = distance;
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

      private:
        uint32_t comTmr;
        float
          distance,
          ph_act,
          tempC;
};

extern Comms com;