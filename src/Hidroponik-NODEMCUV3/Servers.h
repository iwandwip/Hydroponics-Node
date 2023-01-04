#pragma once

#define API_KEY "AIzaSyDPNr0V4GZqh5_K7Rxp6n-cHTM6mJYX8Zk"
#define DATABASE_URL "https://greenhouse-8e545-default-rtdb.firebaseio.com/"

#define USER_EMAIL "greenhouse@gmail.com"
#define USER_PASSWORD "greenhouse"

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