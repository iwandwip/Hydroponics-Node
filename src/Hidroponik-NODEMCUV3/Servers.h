#pragma once

#define API_KEY "AIzaSyDaIihlYwBSU5OH27s5pjZxeDa_BQyRnVI"
#define DATABASE_URL "https://hydroponics-node-default-rtdb.firebaseio.com/"

#define USER_EMAIL "hydroponic@gmail.com"
#define USER_PASSWORD "hydroponic"

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

      private:
        String parseStr(String data,
                        char separator[],
                        int index);
        int8_t WiFi_f = -1;
        uint32_t taskTmr;
};

extern Server_t server;