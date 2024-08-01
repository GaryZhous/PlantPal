#pragma once

//this is the mockup values, you need to replace them with your own credentials and project-specific values
namespace conf {
    const char SSID[] =             "";
    const char PASSWORD[] =         "";


    const char SMTP_SERVER[] =      "smtp.sendgrid.net";
    const int SMTP_PORT =           465;                    // 465 for SSL, 587 for TLS
    const char SMTP_USERNAME[] =    "apikey";
    const char SMTP_PASSWORD[] =    "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";

    const char SENDER_EMAIL[] =     "project-terrarium@singularitysys.net";
    const char NOTIFY_EMAIL[] =     "reaahuja21@gmail.com";

    const int RELAY_PIN =                   2;
    const int SOIL_MOISTURE_SENSOR_PIN =    A0;
    const int DHT_SENSOR_PIN =              8;
    const int MOTION_SENSOR_PIN =           7;

    const double SOIL_DRY_THRESHOLD =   0.6;    // higher is dryer
    const double SOIL_WET_THRESHOLD =   0.4;    // lower is wetter

    const double AIR_COLD =  18;    // average minimum temperature for plants
    const double AIR_HOT =  26;    // average maximum temperature for plants

    const double HUMIDITY_LOW = 40.0; 
    const double HUMIDITY_HIGH = 70.0; 

    const double LUX_LOW = 100.0;
    const double LUX_HIGH = 1000.0;
}
