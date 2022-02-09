#include <Arduino.h>
#include "SmoothingBuffer.h"

SmoothingBuffer::SmoothingBuffer(size_t size) {
    bufferSize = size;
    values = new double[bufferSize];
    for(int i = 0; i < bufferSize; i++) {
        values[i] = 0;
    }
}

void SmoothingBuffer::storeValue(double value) {
    values[pointer++] = value;
    if(pointer >= bufferSize) {
        pointer = 0;
    }
    valuesInBuffer++;
    if(valuesInBuffer >= bufferSize) {
        valuesInBuffer = bufferSize;
    }
}

double SmoothingBuffer::getAverage() {
    double total = 0.0;
    for(int i = 0; i < valuesInBuffer; i++) {
        total += values[i];
    }
    return total / (double) valuesInBuffer;
}