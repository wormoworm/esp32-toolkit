#include <Wifi.h>
#include <esp_wifi.h>
#include <Arduino.h>
#include "SensorToolkitWifi.h"

SensorToolkitWifi::SensorToolkitWifi(boolean persistSettings) {
    WiFi.persistent(persistSettings);
}

void SensorToolkitWifi::setIpConfig(IPAddress ipAddress, IPAddress gateway, IPAddress subnet, IPAddress dns1, IPAddress dns2) {
    WiFi.config(ipAddress, gateway, gateway, dns1, dns2);
}

boolean SensorToolkitWifi::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void SensorToolkitWifi::setConnectionTickCallback(std::function<void(uint16_t)> connectionTickCallback){
    _connectionTickCallback = connectionTickCallback;
}

boolean SensorToolkitWifi::connectToWifi(const char* ssid, const char* password, boolean debug, uint16_t connectionTimeoutMs, uint16_t connectionAttemptIntervalMs) {
    if (isConnected()) {
        if (debug) {
            Serial.println("WiFi already connected, skipping connection attempt...");
        }
        return true;
    }

    unsigned long start = millis();
    unsigned long timeSinceLastConnectionAttemptMs = start - _lastConnectionAttemptTimestampMs;
    if (timeSinceLastConnectionAttemptMs < connectionAttemptIntervalMs) {
        if (debug) {
            Serial.println();
            Serial.print("Last connection attempt was ");
            Serial.print(timeSinceLastConnectionAttemptMs);
            Serial.print(" ms ago. Min time between connection attempts is ");
            Serial.print(connectionAttemptIntervalMs);
            Serial.println("ms");
        }
        return false;
    }

    if (debug) {
        Serial.println();
        Serial.print("Connecting to ");
        Serial.println(ssid);
    }
  
    _lastConnectionAttemptTimestampMs = start;
    WiFi.begin(ssid, password);

    int elapsedMs = 0;
    int connectionTicks = 0;
    while (!isConnected()) {
        delay(CONNECTION_TICK_INTERVAL_MS);
        if ((elapsedMs = (millis() - start)) >= connectionTimeoutMs) {
            if (debug) {
                Serial.println();
                Serial.print("WiFi connection timed out after ");
                Serial.print(elapsedMs);
                Serial.println("ms");
                return false;
            }
        }
        if (_connectionTickCallback) {
            _connectionTickCallback(++connectionTicks);
        }
    }

    unsigned long end = millis();
    if (debug) {
        Serial.println();
        Serial.println("");
        Serial.println("WiFi connected");  
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        Serial.print("WiFi connection took ");
        Serial.print(end - start);
        Serial.println("ms");
    }

    return true;
}