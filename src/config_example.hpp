#pragma once

//pseudo implementation of project-specific variables, you need to replace them with your own credentials or project-specific values
namespace conf{
    const char* SMTP_SERVER = "";
    int SMTP_PORT = 0;
    const char SMTP_USERNAME[] = "";
    const char* SMTP_PASSWORD = "";
    int RELAY_PIN = 0;
    int SOIL_MOISTURE_SENSOR_PIN = 0;
    int DHT_SENSOR_PIN = 0;
    const char* SSID = "";
    const char* PASSWORD = "";
    const char* SENDER_EMAIL = "";
    const char* NOTIFY_EMAIL = "";
    int SOIL_DRY_THRESHOLD = 0;
    int SOIL_WET_THRESHOLD = 0;
};