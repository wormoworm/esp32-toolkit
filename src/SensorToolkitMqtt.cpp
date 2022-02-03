#include <Wifi.h>
#include "SensorToolkitMqtt.h"

SensorToolkitMqtt::SensorToolkitMqtt(Client& wifiClient, const char* address, uint16_t port, const char* clientId) {
    client = PubSubClient(wifiClient);
    client.setServer(address, port);
    mqttClientId = clientId;
}

boolean SensorToolkitMqtt::setCallback(MQTT_CALLBACK_SIGNATURE) {
    client.setCallback(callback);
    return true;
}

boolean SensorToolkitMqtt::connect(const char *username, const char *password, uint16_t keepAlive) {
    client.setKeepAlive(keepAlive);
    while (!client.connected()) {
        Serial.println("Connecting to MQTT...");
        if (client.connect(mqttClientId, username, password)) {
            Serial.println("Connected to MQTT");
            yield();
        }
        else {
            Serial.print("Failed to connect to MQTT: ");
            Serial.print(client.state());
            yield();
            return false;
        }
    }
    return true;
}

boolean SensorToolkitMqtt::publish(const char* topic, const char* payload) {
    return client.publish(topic, payload);
}

boolean SensorToolkitMqtt::subscribe(const char* topic) {
    return client.subscribe(topic);
}

boolean SensorToolkitMqtt::loop() {
    return client.loop();
}