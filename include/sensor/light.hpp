#pragma once

#include <Arduino.h>
#include <hp_BH1750.h>

class LightSensor {
    private:
        hp_BH1750 _sensor;
        float _cached_val;
    public:
        void setup() { 
            _sensor.begin(BH1750_TO_GROUND);

            _sensor.start();
            while (!_sensor.hasValue());
            _cached_val = _sensor.getLux();
        }

        // Note: this outputs normalized values in range [0, 1]
        float read() {
            if (_sensor.hasValue()) {
                _cached_val = _sensor.getLux();
                _sensor.start();
            }
            return _cached_val;
        }
};
