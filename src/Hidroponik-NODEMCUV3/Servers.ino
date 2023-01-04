#include "Servers.h"
#include "Sensors.h"
#include "ESP8266WiFi.h"

#include "Firebase_ESP_Client.h"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

Server_t server;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void Server_t::Init() {
}

void Server_t::Login() {
        config.api_key = API_KEY;
        config.database_url = DATABASE_URL;

        // if (Firebase.signUp(&config, &auth, "", "")) {
        // } else {
        //         Serial.printf("%s\n", config.signer.signupError.message.c_str());
        // }

        auth.user.email = USER_EMAIL;
        auth.user.password = USER_PASSWORD;

        config.token_status_callback = tokenStatusCallback;
        Firebase.begin(&config, &auth);
        Firebase.reconnectWiFi(true);
        Firebase.setDoubleDigits(5);
        config.timeout.serverResponse = 10 * 10000;
}

void Server_t::Handler() {
        // if (Firebase.ready() && millis() - taskTmr >= 5000) {
        //         taskTmr = millis();
        // }
}

void Server_t::sendToFB(float dat[], String addr[]) {
        if (Firebase.ready() && millis() - taskTmr >= 3000) {

                for (uint8_t i = 0; i < 3; i++) {
                        if ((*this).setFloatFB(dat[i], addr[i])) {
                                Serial.println("Yes");
                        }
                }

                taskTmr = millis();
        }
}

bool Server_t::setFloatFB(float dat, String addr) {
        return Firebase.RTDB.setFloat(&fbdo, (addr), dat) ? 1 : 0;
}

void Server_t::connectToWiFi(const char* SSID,
                             const char* PWD) {
        WiFi.mode(WIFI_OFF);
        delay(100);

        WiFi.mode(WIFI_STA);
        WiFi.begin(SSID, PWD);

        Serial.print("Connecting to : ");
        Serial.println(SSID);

        while (WiFi.status() != WL_CONNECTED) {
                Serial.print(".");
                delay(100);
        }

        this->WiFi_f = 1;

        Serial.println(WiFi.localIP());
}

void Server_t::waitConnection(uint32_t tmr) {
        delay(tmr);
}

int8_t Server_t::getStatus() {
        return this->WiFi_f;
}

String Server_t::parseStr(String data, char separator[], int index) {
        int found = 0;
        int strIndex[] = { 0, -1 };
        int maxIndex = data.length() - 1;

        for (int i = 0; i <= maxIndex && found <= index; i++) {
                if (data.charAt(i) == separator[0] || i == maxIndex) {
                        found++;
                        strIndex[0] = strIndex[1] + 1;
                        strIndex[1] = (i == maxIndex) ? i + 1 : i;
                }
        }

        return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}