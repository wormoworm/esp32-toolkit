#include <Arduino.h>
#include "SensorToolkitWifi.h"
#include "SensorToolkitMqtt.h"
#include "SensorToolkitTime.h"
#include "DemoConfig.h"

/**
 * @brief This is a sample program that tests some of the functionality offered by this library.
 */

SensorToolkitWifi *wifiClient;
WiFiClient espClient;
SensorToolkitMqtt mqttClient = SensorToolkitMqtt(espClient, CONFIG_MQTT_BROKER_ADDRESS, CONFIG_MQTT_BROKER_PORT, CONFIG_MQTT_CLIENT_ID);

void wifiConnectionTickCallback(uint16_t tickNumber) {
    if (tickNumber % 10 == 0) {
        Serial.print(".");
    }
}

/**
 * @brief Callback that is invoked whenever a message is received on a topic that the MQTT client is subscribed to.
 * 
 * @param topic     The topic the message was received on.
 * @param payload   The body of the message.
 * @param length    Length of the message in bytes
 */
void mqttSubscribeCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
}

void connectToWiFi() {
    if (wifiClient->connectToWifi(WIFI_SSID, WIFI_PASSWORD, true)) {
        mqttClient.setCallback(mqttSubscribeCallback);
        mqttClient.connect(MQTT_USERNAME, MQTT_PASSWORD, CONFIG_MQTT_KEEP_ALIVE);
        mqttClient.subscribe("test/incoming", 1);
        syncNtp(0, 3600, "pool.ntp.org", true);
    }
    else {
        Serial.println("Failed to connect to WiFi");
    }
}

void setup() {
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);
    wifiClient = new SensorToolkitWifi();
    wifiClient->setConnectionTickCallback(wifiConnectionTickCallback);
    wifiClient->setIpConfig(CONFIG_WIFI_IP_ADDRESS, CONFIG_WIFI_GATEWAY, CONFIG_WIFI_SUBNET);
}

void loop() {
    if (!wifiClient->isConnected()) {
        connectToWiFi();
    }
    if (mqttClient.isConnected()) {
        mqttClient.publish("test/outgoing", "Hello, world!");
    }
    mqttClient.loop();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(950);
}