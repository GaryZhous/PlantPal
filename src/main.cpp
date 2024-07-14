#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>
#include <Arduino_LED_Matrix.h>

#ifdef __has_include
    #if !__has_include("config.hpp")
        #error "config.hpp not found, please copy from config.example.hpp and fill in!"
    #endif 
#endif 

#include "config.hpp"
#include "util/mail.hpp"

#define TEST
ArduinoLEDMatrix matrix;

const uint32_t heart[] = { //LED grid testing array
    0x3184a444,
    0x44042081,
    0x100a0040
};

const uint32_t off[3] = {0};

void LEDTest(){
    matrix.loadFrame(heart);
    delay(1000);
    matrix.loadFrame(off);
    delay(1000);
}

// Recipient email
Mail mail(conf::SMTP_SERVER, conf::SMTP_PORT, conf::SMTP_USERNAME, conf::SMTP_PASSWORD);

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

void loop() {
    // put your main code here, to run repeatedly:
    #ifdef TEST
        LEDTest();
        test_send();
    #endif
}

// very sussy
String operator+(const String& a, const String& b) { //the String class for Arduino is only half done...
    return a + b;
}