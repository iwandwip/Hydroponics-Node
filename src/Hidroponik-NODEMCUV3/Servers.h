#pragma once

#define API_KEY "AIzaSyDaIihlYwBSU5OH27s5pjZxeDa_BQyRnVI"
#define DATABASE_URL "https://hydroponics-node-default-rtdb.firebaseio.com/"

#define USER_EMAIL "hydroponic@gmail.com"
#define USER_PASSWORD "hydroponic"

#define SP_DISTANCE "/sens/control/dist"
#define SP_TEMPERATURE "/sens/control/temp"

struct Server_t {
        void Init();
        void connectToWiFi(const char* SSID,
                           const char* PWD);
        void waitConnection(uint32_t tmr);
        void sendToFB(float dat[],
                      String addr[]);
        bool setFloatFB(float dat,
                        String addr);
        int8_t getStatus();
        void Login();
        void Handler();
        void Debug();

        double* getSetPoint() {
               return sp;
        }

      private:
        String parseStr(String data,
                        char separator[],
                        int index);
        int8_t WiFi_f = -1;
        double sp[2];
        uint32_t taskTmr;
};

extern Server_t server;