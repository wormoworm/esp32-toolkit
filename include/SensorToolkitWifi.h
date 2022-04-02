#ifndef SensorToolkitWifi_H
#define SensorToolkitWifi_H

#include <Arduino.h>
#include <functional>
#include <IPAddress.h>

#define CONNECTION_TICK_INTERVAL_MS 10
#define CONNECTION_TIMEOUT_MS_DEFAULT 10000
#define CONNECTION_ATTEMPT_INTERVAL_MS_DEFAULT 20000

class SensorToolkitWifi {

    public:
        SensorToolkitWifi(boolean persistSettings = false);

        void setIpConfig(IPAddress ipAddress, IPAddress gateway, IPAddress subnet, IPAddress dns1 = (uint32_t) 0, IPAddress dns2 = (uint32_t) 0);

        boolean isConnected();

        void setConnectionTickCallback(std::function<void(uint16_t)> connectionTickCallback);

        boolean connectToWifi(const char* ssid, const char* password, boolean debug = false, uint16_t connectionTimeoutMs = CONNECTION_TIMEOUT_MS_DEFAULT, uint16_t connectionAttemptIntervals = CONNECTION_ATTEMPT_INTERVAL_MS_DEFAULT);

    private:
        long _lastConnectionAttemptTimestampMs = LONG_MIN;

        std::function<void(uint16_t)> _connectionTickCallback;
};

#endif