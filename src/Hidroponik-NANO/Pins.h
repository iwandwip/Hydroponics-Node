#pragma once

#define ONE_WIRE_BUS 4

#define TRIG_PIN 5
#define ECHO_PIN 6
#define MAX_DIST 500

#define PH_PIN A0
#define PH_CAL 21.34 + 4.0

#define RELAY_PIN_1 7
#define RELAY_PIN_2 8
#define RELAY_PIN_3 9
#define RELAY_PIN_4 10

#define COM_RX_PIN 2
#define COM_TX_PIN 3

const uint8_t pinRelay[4] = {RELAY_PIN_1, RELAY_PIN_2, RELAY_PIN_3, RELAY_PIN_4};