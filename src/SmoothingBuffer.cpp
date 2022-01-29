#include <Arduino.h>
#include "SmoothingBuffer.h"

SmoothingBuffer::SmoothingBuffer(int size) {
    bufferSize = size;
    values = new float[bufferSize];
    for(int i = 0; i < bufferSize; i++) {
        values[i] = 0;
    }
}

void SmoothingBuffer::storeValue(float value) {
    values[pointer++] = value;
    if(pointer >= bufferSize) {
        pointer = 0;
    }
    valuesInBuffer++;
    if(valuesInBuffer >= bufferSize) {
        valuesInBuffer = bufferSize;
    }
}

float SmoothingBuffer::getAverage() {
    float total = 0.0;
    for(int i = 0; i < valuesInBuffer; i++) {
        total += values[i];
        // yield();
    }
    return total / (float) valuesInBuffer;
}