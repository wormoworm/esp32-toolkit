#ifndef SensorToolkitTime_H
#define SensorToolkitTime_H

#include <Arduino.h>
#include <sys/time.h>

#ifdef ARDUINO_ARCH_ESP8266
// This function is not available on ESP8266, so I copied it from esp32-hal-time.c
bool getLocalTime(struct tm * info, uint32_t ms = 5000)
{
    uint32_t start = millis();
    time_t now;
    while((millis()-start) <= ms) {
        time(&now);
        localtime_r(&now, info);
        if(info->tm_year > (2016 - 1900)){
            return true;
        }
        delay(10);
    }
    return false;
}
#endif

void syncNtp(long gmtOffsetS, int daylightOffsetS, const char* serverAddress, boolean debug = false) {
    unsigned long start;
    if (debug) {
       start = millis();
    }
    configTime(gmtOffsetS, daylightOffsetS, serverAddress);
    if (debug) {
        unsigned long end = millis();
        Serial.print("NTP sync took: ");
        Serial.print(end - start);
        Serial.println("ms");
    }
}

// Function that gets current epoch time
unsigned long getEpochTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

// uint64_t getCurrentTimeMs() {
//     struct timeval tv;
//     gettimeofday(&tv, NULL);

//     return (int64_t) tv.tv_sec * 1000ll + tv.tv_usec / 1000ll;
//     // return (int64_t) tv.tv_usec + tv.tv_sec * 1000000ll;
// }

#ifndef ARDUINO_ARCH_ESP8266
// The println() calls below are not correct for ESP8266, so I've removed this function on ESP8266.
void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.print("Day of week: ");
  Serial.println(&timeinfo, "%A");
  Serial.print("Month: ");
  Serial.println(&timeinfo, "%B");
  Serial.print("Day of Month: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Year: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Hour (12 hour format): ");
  Serial.println(&timeinfo, "%I");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Second: ");
  Serial.println(&timeinfo, "%S");

  Serial.println("Time variables");
  char timeHour[3];
  strftime(timeHour,3, "%H", &timeinfo);
  Serial.println(timeHour);
  char timeWeekDay[10];
  strftime(timeWeekDay,10, "%A", &timeinfo);
  Serial.println(timeWeekDay);
  Serial.println();
}
#endif

#endif