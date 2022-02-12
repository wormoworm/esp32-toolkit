#ifndef DemoConfig_H
#define DemoConfig_H

#include "IPAddress.h"

// For static IP configuration on local LAN.
IPAddress CONFIG_WIFI_IP_ADDRESS, CONFIG_WIFI_GATEWAY, CONFIG_WIFI_SUBNET;
boolean _1 = CONFIG_WIFI_IP_ADDRESS.fromString("10.0.1.80");
boolean _2 = CONFIG_WIFI_GATEWAY.fromString("10.0.0.1");
boolean _3 = CONFIG_WIFI_SUBNET.fromString("255.255.252.0");

// For MQTT broker connection.
#define CONFIG_MQTT_BROKER_ADDRESS "10.0.1.2"
#define CONFIG_MQTT_BROKER_PORT 8884
#define CONFIG_MQTT_CLIENT_ID "mqtt_test"
#define CONFIG_MQTT_KEEP_ALIVE 10

#endif