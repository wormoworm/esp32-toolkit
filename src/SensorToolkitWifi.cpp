#include <Wifi.h>
#include <Arduino.h>
#include "SensorToolkitWifi.h"

void connectToWifi(char* ssid, char* password, boolean debug) {
    if (debug) {
        Serial.println();
        Serial.println();
        Serial.print("Connecting to ");
        Serial.println(ssid);
    }
  
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        yield();
    }

    if (debug) {
        Serial.println("");
        Serial.println("WiFi connected");  
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        yield();
    }
}

void connectToWifi(char* ssid, char* password) {
    connectToWifi(ssid, password, false);
}