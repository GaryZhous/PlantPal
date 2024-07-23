#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>
#include <Arduino_LED_Matrix.h>
#include <DHT_U.h>
#include <hp_BH1750.h>

/*#ifdef __has_include
    #if !__has_include("config.hpp")
        #error "config.hpp not found, please copy from config.example.hpp and fill in!"
    #endif 
#endif */

#include "config.hpp"
// #include "config.example.hpp"
#include "util/mail.hpp"
#include "util/relay.hpp"
#include "util/led_symbols.hpp"
#include "sensor/soil_moisture.hpp"
#include "sensor/light.hpp"
#include "sensor/motion.hpp"

#define TEST
ArduinoLEDMatrix matrix;

Mail mail(conf::SMTP_SERVER, conf::SMTP_PORT, conf::SMTP_USERNAME, conf::SMTP_PASSWORD);
Relay pump_relay(conf::RELAY_PIN);
SoilMoistureSensor soil_moisture(conf::SOIL_MOISTURE_SENSOR_PIN);
DHT_Unified dht(conf::DHT_SENSOR_PIN, DHT22);
LightSensor light_sensor;
MotionSensor motion_sensor(conf::MOTION_SENSOR_PIN);

void setup() {
    Serial.begin(115200);
    matrix.begin();

    // Connect to WiFi
    WiFi.begin(conf::SSID, conf::PASSWORD);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected!");

    light_sensor.setup();
    pump_relay.setup();
    soil_moisture.setup();
    dht.begin();

    matrix.loadFrame(led_symbols::hi);
    delay(250);
    matrix.loadFrame(led_symbols::heart);
    delay(250);
    matrix.loadFrame(led_symbols::dry);
    delay(250);
    matrix.loadFrame(led_symbols::cold);
    delay(250);
    matrix.loadFrame(led_symbols::hot);
    delay(250);
    matrix.loadFrame(led_symbols::ok);
    delay(250);
    matrix.loadFrame(led_symbols::hi);
    delay(3000);
}

void test_send() {
    if(Serial.available() > 0) {
        char command = Serial.read();
        if(tolower(command) == 's')
            mail.send_email(
                conf::SENDER_EMAIL, 
                conf::NOTIFY_EMAIL, 
                "Arduino Terrarium Notification", 
                "Hello!\n\nYour plants are overheating with a temperature of XX degrees C, please check them!\n\nYours,\nArduino Terrarium Service"
            );
    }
}

int loop_num = 0;

void loop() {
    double moisture = soil_moisture.read();

    if (moisture > conf::SOIL_DRY_THRESHOLD) {
        matrix.loadFrame(led_symbols::dry);
        pump_relay.close();
    }
    else if (moisture < conf::SOIL_WET_THRESHOLD) {
        matrix.loadFrame(led_symbols::ok);
        pump_relay.open();
    }

    if (loop_num % 25 == 0) {    // run every 2.5 s
        Serial.println("---");

        Serial.print("Soil moisture: "); Serial.println(moisture, 4);

        sensors_event_t dht_event;
        dht.temperature().getEvent(&dht_event);
        Serial.print("Temperature: "); Serial.print(dht_event.temperature); Serial.println("C");
        
        dht.humidity().getEvent(&dht_event);
        Serial.print("Humidity: "); Serial.print(dht_event.relative_humidity); Serial.println("%");

        float reading = light_sensor.read();
        Serial.print("Lux: "); Serial.println(reading);

        bool motion = motion_sensor.read();
        Serial.print("Motion: "); Serial.println(motion);
    }

    delay(100);
    loop_num++;
}

// very sussy
String operator+(const String& a, const String& b) { //the String class for Arduino is only half done...
    return a + b;
}
