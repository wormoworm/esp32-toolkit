#ifndef SmoothingBuffer_H
#define SmoothingBuffer_H

#include <Arduino.h>

class SmoothingBuffer {
    public:
        SmoothingBuffer(size_t size);
        void storeValue(float value);
        float getAverage();

    private:
        float* values;
        int pointer;
        int bufferSize;
        int valuesInBuffer;
};

#endif