#ifndef SmoothingBuffer_H
#define SmoothingBuffer_H

#include <Arduino.h>

class SmoothingBuffer {
    public:
        SmoothingBuffer(size_t size);
        void storeValue(double value);
        double getAverage();

    private:
        double *values;
        int pointer;
        int bufferSize;
        int valuesInBuffer;
};

#endif