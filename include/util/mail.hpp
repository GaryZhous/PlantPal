#pragma once

#include <Serial.h>
#include <ESP_Mail_Client.h>


class Mail {
    public:
        Mail(const char* server, int port, const char* username, const char* password);
        void send_email(const char* sender, const char* recipent, const char* subject, const char* body);
        static void callback(SMTP_Status status);

    private:
        const char* _server;
        int _port;
        const char* _username;
        const char* _password;
};