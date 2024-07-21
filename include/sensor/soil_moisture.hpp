#pragma once

#include <Arduino.h>

class SoilMoistureSensor {
    private:
        pin_size_t _pin;
        static const int ADC_RESOLUTION = 14;   // R4 can support 14 bit

    public:
        SoilMoistureSensor(pin_size_t pin) : _pin(pin) {}

        void setup() {
            pinMode(_pin, INPUT);
            analogReadResolution(ADC_RESOLUTION);
        }

        // Note: this outputs normalized values in range [0, 1]
        double read() { 
            int reading = analogRead(_pin);
            return (double) reading / (1 << ADC_RESOLUTION);
        }
};