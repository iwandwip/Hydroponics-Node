#pragma once

#include "SoftwareSerial.h"

#define COMM_INTERVAL 1000

#define COM_RX_PIN D7
#define COM_TX_PIN D6

struct Comms {
        void Init();
        void Handler(double data_send[]);
        void Debug();

        float* getUnoData() {
                static float data[3];
                data[0] = distance;
                data[1] = ph_act;
                data[2] = tempC;

                return data;
        }

        uint8_t* getState() {
                static uint8_t data[3];
                data[0] = heater;
                data[1] = cooler;
                data[2] = filling;
                return data;
        }

        String* getAddressToFirebase() {
                static String addr[3];
                addr[0] = "/sens/float/distance";
                addr[1] = "/sens/float/ph";
                addr[2] = "/sens/float/temp";
                return addr;
        }

        String* getStateToFirebase() {
                static String addr[3];
                addr[0] = "/sens/relay/heater";
                addr[1] = "/sens/relay/cooler";
                addr[2] = "/sens/relay/filling";
                return addr;
        }

      private:
        uint32_t comTmr;
        float
          distance,
          ph_act,
          tempC;

        uint8_t
          heater,
          cooler,
          filling;
};

extern Comms com;