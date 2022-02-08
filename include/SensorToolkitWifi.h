#ifndef SensorToolkitWifi_H
#define SensorToolkitWifi_H

#include <Arduino.h>
#include <functional>

class SensorToolkitWifi {

    public:
        void connectToWifi(const char* ssid, const char* password, boolean debug);

        void connectToWifi(const char* ssid, const char* password);

        void setConnectionTickCallback(std::function<void(uint16_t)> connectionTickCallback);

    private:
        std::function<void(uint16_t)> _connectionTickCallback;
};

#endif