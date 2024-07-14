#include "util/mail.hpp"

Mail::Mail(const char* server, int port, const char* username, const char* password) {
    _server = server;
    _port = port;
    _username = username;
    _password = password;
}

// Callback function to handle SMTP status
void Mail::callback(SMTP_Status status) {
    // Print the current status
    Serial.println(status.info());

    // Print the sending result
    // Serial.println(status.success() ? "Email sent successfully!" : "Failed to send Email :(");
}

void Mail::send_email(const char* sender, const char* recipent, const char* subject, const char* body) {
    SMTPSession session;
    // session.debug(1);
    session.callback(callback);

    // Set email properties
    SMTP_Message message;
    message.sender.name = "Arduino Terrarium Notification Service";
    message.sender.email = sender;
    message.subject = subject;
    message.addRecipient("Joe Dai", recipent);
    message.text.content = body;

    // Set SMTP server settings and session config
    Session_Config config;
    config.server.host_name = _server;
    config.server.port = _port;
    config.login.email = _username;
    config.login.password = _password;
    config.login.user_domain = F("local.j0e.ca");
    config.time.ntp_server = "pool.ntp.org,time.nist.gov";
    config.time.gmt_offset = -4;        // Toronto
    config.time.day_light_offset = 1;

    session.connect(&config);

    // Send the email
    if (!MailClient.sendMail(&session, &message)) {
        String error_msg = strcat("Error sending email: ", session.errorReason().c_str());
        Serial.println(error_msg);
    } else {
        Serial.println("Email sent successfully!");
    }
}
