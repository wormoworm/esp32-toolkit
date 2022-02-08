#include <Wifi.h>
#include <Arduino.h>
#include "SensorToolkitWifi.h"

void SensorToolkitWifi::connectToWifi(const char* ssid, const char* password, boolean debug) {

    int tickDurationMs = 100;

    if (debug) {
        Serial.println();
        Serial.println();
        Serial.print("Connecting to ");
        Serial.println(ssid);
    }
  
    WiFi.begin(ssid, password);

    int connectionTicks = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(tickDurationMs);
        if (_connectionTickCallback) {
            _connectionTickCallback(++connectionTicks);
        }
    }

    if (debug) {
        Serial.println("");
        Serial.println("WiFi connected");  
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }
}

void SensorToolkitWifi::connectToWifi(const char* ssid, const char* password) {
    connectToWifi(ssid, password, false);
}

void SensorToolkitWifi::setConnectionTickCallback(std::function<void(uint16_t)> connectionTickCallback){
    _connectionTickCallback = connectionTickCallback;
}