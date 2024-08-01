#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>
#include <Arduino_LED_Matrix.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT_U.h>
#include <hp_BH1750.h>

/*#ifdef __has_include
    #if !__has_include("config.hpp")
        #error "config.hpp not found, please copy from config.example.hpp and fill in!"
    #endif 
#endif */

//#include "config.hpp"
#include "config.example.hpp"
#include "util/mail.hpp"
#include "util/relay.hpp"
#include "util/led_symbols.hpp"
#include "sensor/soil_moisture.hpp"
#include "sensor/light.hpp"
#include "sensor/motion.hpp"

#define TEST
ArduinoLEDMatrix matrix;
enum states{
    STABLE,
    HOT,
    COLD,
    DRY,
    WET
};

Mail mail(conf::SMTP_SERVER, conf::SMTP_PORT, conf::SMTP_USERNAME, conf::SMTP_PASSWORD);
Relay pump_relay(conf::RELAY_PIN);
SoilMoistureSensor soil_moisture(conf::SOIL_MOISTURE_SENSOR_PIN);
DHT_Unified dht(conf::DHT_SENSOR_PIN, DHT22);
LightSensor light_sensor;
MotionSensor motion_sensor(conf::MOTION_SENSOR_PIN);
LiquidCrystal_I2C lcd(0x27,20,4);

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

    lcd.init();                      
    lcd.backlight();
    light_sensor.setup();
    pump_relay.setup();
    soil_moisture.setup();
    motion_sensor.setup();
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

int current = STABLE;
void display_status(float moisture, float temperature, float humidity, float lux){
    // LCD: temperature, humidity and lux
    // LED: soil moisture
    const char* problemMessage = {0};

    lcd.clear();
    lcd.setCursor(0, 0);
    char buff[20] = {0};


    sprintf(buff, "T:%.2f C", temperature);
    lcd.print(buff);

    memset(buff, 0, sizeof(buff));
    lcd.setCursor(0, 1);

    sprintf(buff, "H: %.1f L: %.1f", humidity, lux);
    lcd.print(buff);

 
    if (moisture > conf::SOIL_DRY_THRESHOLD) {
        matrix.loadFrame(led_symbols::dry);
        pump_relay.close();
    }
    else if (moisture < conf::SOIL_WET_THRESHOLD) {
        matrix.loadFrame(led_symbols::ok);
        pump_relay.open();
    }




}

// void sendEmail(float moisture, float temperature, float humidity, float lux) {
//     char* problemMessage; 

//     if (moisture > conf::SOIL_DRY_THRESHOLD){
//         problemMessage = "Your plants are too dry!"
//     }
//     if(temperature < conf::AIR_COLD){
//         problemMessage
//     }
//     mail.send_email(
//                 conf::SENDER_EMAIL, 
//                 conf::NOTIFY_EMAIL, 
//                 "Arduino Terrarium Notification", 
//                 problemMessage
//             );

// }

void sendEmail(float moisture, float temperature, float humidity, float lux) {
    
    // Initial buffer size for problemMessage
    size_t bufferSize = 256;
    char* problemMessage = (char*)malloc(bufferSize);
    if (problemMessage == NULL) {
        Serial.print("Failed to allocate memory for problemMessage\n");
        return;
    }

    // Initialize problemMessage with an empty string
    strcpy(problemMessage, "Plant Status Notification:\n");

    // Check each condition and append to problemMessage
    if (moisture > conf::SOIL_DRY_THRESHOLD) {
        strcat(problemMessage, "Your plants are too dry!\n");
    }

    if (temperature < conf::AIR_COLD) {
        strcat(problemMessage, "The air is too cold for your plants!\n");
    } else if (temperature > conf::AIR_HOT) {
        strcat(problemMessage, "The air is too hot for your plants!\n");
    }

    if (humidity < conf::HUMIDITY_LOW) {
        strcat(problemMessage, "The air is too dry for your plants!\n");
    } else if (humidity > conf::HUMIDITY_HIGH) {
        strcat(problemMessage, "The air is too humid for your plants!\n");
    }

    if (lux < conf::LUX_LOW) {
        strcat(problemMessage, "There is not enough light for your plants!\n");
    } else if (lux > conf::LUX_HIGH) {
        strcat(problemMessage, "There is too much light for your plants!\n");
    }

    if (problemMessage != ("Plant Status Notification:\n")){
        Serial.print(problemMessage);
    }
        

    // Send the email
    mail.send_email(
        conf::SENDER_EMAIL, 
        conf::NOTIFY_EMAIL, 
        "Arduino Terrarium Notification", 
        problemMessage
    );

    // Free allocated memory
    free(problemMessage);
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

    delay(2000);

    if (loop_num % 25 == 0) {    // run every 2.5 s
        Serial.println("---");

        moisture = soil_moisture.read();
        Serial.print("Soil moisture: "); Serial.println(moisture, 4);

        sensors_event_t dht_event;
        float temperatureReading = dht.temperature().getEvent(&dht_event);
        float temperature = dht_event.temperature;
        Serial.print("Temperature: "); Serial.print(dht_event.temperature); Serial.println("C");
        
        float humidityReading = dht.humidity().getEvent(&dht_event);
        float humidity = dht_event.relative_humidity;
        Serial.print("Humidity: "); Serial.print(dht_event.relative_humidity); Serial.println("%");

        float lux = light_sensor.read();
        Serial.print("Lux: "); Serial.println(lux);

        bool motion = motion_sensor.read();
        Serial.print("Motion: "); Serial.println(motion);

       if (motion != 0){
            lcd.backlight();
            display_status(moisture, temperature, humidity, lux);
       }else{
            lcd.noBacklight();
            lcd.clear();
       }

       if (loop_num % 250 == 0){
            sendEmail(moisture, temperature, humidity, lux);
       }

    }

    delay(100);
    loop_num++;
}

// very sussy
String operator+(const String& a, const String& b) { //the String class for Arduino is only half done...
    return a + b;
}
