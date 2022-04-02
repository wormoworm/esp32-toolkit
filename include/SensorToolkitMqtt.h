#ifndef SensorToolkitMqtt_H
#define SensorToolkitMqtt_H

#ifdef ARDUINO_ARCH_ESP32
#include <Wifi.h>
#include <esp_wifi.h>
#endif
#ifdef ARDUINO_ARCH_ESP8266
#include <ESP8266WiFi.h>
#endif

#include <PubSubClient.h>

class SensorToolkitMqtt {
    public:
        SensorToolkitMqtt(Client& wifiClient, const char* address, uint16_t port, const char* clientId);

        boolean isConnected();

        boolean setCallback(MQTT_CALLBACK_SIGNATURE);

        boolean connect(const char *username, const char *password, uint16_t keepAlive);

        boolean publish(const char* topic, const char* payload, boolean retain = false);

        boolean subscribe(const char* topic, uint8_t qos = 1);

        boolean loop();

    private:
        PubSubClient client;
        const char *mqttClientId;
};

#endif