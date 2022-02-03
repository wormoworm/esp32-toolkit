#ifndef SensorToolkitMqtt_H
#define SensorToolkitMqtt_H

#include <WiFi.h>
#include <PubSubClient.h>

class SensorToolkitMqtt {
    public:
        SensorToolkitMqtt(Client& wifiClient, const char* address, uint16_t port, const char* clientId);

        boolean setCallback(MQTT_CALLBACK_SIGNATURE);

        boolean connect(const char *username, const char *password, uint16_t keepAlive);

        boolean publish(const char* topic, const char* payload);

        boolean subscribe(const char* topic);

        boolean loop();

    private:
        PubSubClient client;
        const char *mqttClientId;
};

#endif