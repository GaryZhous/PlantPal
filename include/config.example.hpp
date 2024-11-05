#pragma once

//this is the mockup values, you need to replace them with your own credentials and project-specific values
namespace conf {
    const char SSID[] =             "<WIFI SSID HERE>";
    const char PASSWORD[] =         "<WIFI PASSWORD HERE>";


    const char SMTP_SERVER[] =      "smtp.sendgrid.net";
    const int SMTP_PORT =           465;                    // 465 for SSL, 587 for TLS
    const char SMTP_USERNAME[] =    "apikey";
    const char SMTP_PASSWORD[] =    "<API KEY HERE>";

    const char SENDER_EMAIL[] =     "<TERRARIUM EMAIL HERE>";
    const char NOTIFY_EMAIL[] =     "<YOUR EMAIL HERE>";

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
