#include <Arduino.h>
#include "SensorToolkitWifi.h"
#include "SensorToolkitMqtt.h"
#include "..\..\arduino\secrets.h"
#include "config.h"

/**
 * @brief This is a sample program that tests some of the functionality offered by this library.
 */

WiFiClient espClient;
SensorToolkitMqtt mqttClient = SensorToolkitMqtt(espClient, CONFIG_MQTT_BROKER_ADDRESS, CONFIG_MQTT_BROKER_PORT, CONFIG_MQTT_CLIENT_ID);

void setup() {
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);
    connectToWifi(SECRET_WIFI_SSID, SECRET_WIFI_PASSWORD, true);
    mqttClient.connect(SECRET_MQTT_USER, SECRET_MQTT_PASSWORD, CONFIG_MQTT_KEEP_ALIVE);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    mqttClient.publish("test", "Hello, world!");
    delay(1000);
}