#pragma once

#include <Arduino.h>

class MotionSensor {
    private:
        pin_size_t _pin;

    public:
        MotionSensor(pin_size_t pin) : _pin(pin) {}

        void setup() { pinMode(_pin, INPUT); }
        bool read() { return digitalRead(_pin); }
};
