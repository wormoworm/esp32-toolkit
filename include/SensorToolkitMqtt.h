#ifndef SensorToolkitMqtt_H
#define SensorToolkitMqtt_H

#include <WiFi.h>
#include <PubSubClient.h>

class SensorToolkitMqtt {
    public:
        SensorToolkitMqtt(Client& wifiClient, char* address, uint16_t port, char* clientId);
        boolean connect(const char *username, const char *password, uint16_t keepAlive);
        boolean publish(char* topic, char* payload);
        boolean loop();

    private:
        PubSubClient client;
        char *mqttClientId;
};

#endif