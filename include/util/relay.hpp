#pragma once

#include <Arduino.h>

class Relay {
    private:
        pin_size_t _pin;
        bool _activeLowHigh;
        

    public:
        Relay(pin_size_t pin, bool activeLowHigh = LOW) : _pin(pin), _activeLowHigh(activeLowHigh) {}
        
        // Note: defaults to open
        void setup() {
            pinMode(_pin, OUTPUT);
            open();
        }

        void open() { digitalWrite(_pin, !_activeLowHigh); }
        void close() { digitalWrite(_pin, _activeLowHigh); }
};