#pragma once

//this is the mockup values, you need to replace them with your own credentials and project-specific values
namespace conf {
    const char SSID[] =             "";
    const char PASSWORD[] =         "";

    const char SMTP_SERVER[] =      "smtp.sendgrid.net";
    const int SMTP_PORT =           465;                    // 465 for SSL, 587 for TLS
    const char SMTP_USERNAME[] =    "apikey";
    const char SMTP_PASSWORD[] =    "";

    const char SENDER_EMAIL[] =     "";
    const char NOTIFY_EMAIL[] =     "";

    const int RELAY_PIN =                   2;
    const int SOIL_MOISTURE_SENSOR_PIN =    A0;
    const int DHT_SENSOR_PIN =              8;
    const int MOTION_SENSOR_PIN =           7;

    const double SOIL_DRY_THRESHOLD =   0.5;    // higher is dryer
    const double SOIL_WET_THRESHOLD =   0.4;    // lower is wetter
}
