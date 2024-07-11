#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>
#include <ESP_Mail_Client.h>
#include "Arduino_LED_Matrix.h"

#if __has_include("secret.h")
  #define SSID           "<WIFI-SSID>"
  #define PASSWORD       "<WIFI-password>"
  #define SMTP_USERNAME  "<your_email@example.com>"
  #define SMTP_PASSWORD  "<your_generated_app_password>"
#endif

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

// SMTP Server settings
SMTPSession smtp;
const char* smtpServer = "smtp.gmail.com";
const int smtpPort = 465; //465 for SSL, 587 for TSL

// Recipient email
const char* emailRecipient = "recipient_email@gmail.com";

void setup() {
  Serial.begin(115200);
  matrix.begin();
  char*& user_email = const_cast<char*&>(emailRecipient); //cast off the const type for future use
  // Connect to WiFi
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
}

void loop() {
  // put your main code here, to run repeatedly:
  #ifdef TEST
  LEDTest();
  #endif
}

// Function to send an email
void sendEmail(const char* emailRecipient, const char* emailSubject, const char* emailMessage) {

  // Initialize SMTP session
  SMTPSession smtp;
  smtp.debug(1);
  smtp.callback(smtpCallback);

  // Set email properties
  SMTP_Message message;
  message.sender.name = "Arduino";
  message.sender.email = SMTP_USERNAME;
  message.subject = emailSubject;
  message.addRecipient("Recipient", emailRecipient);
  message.text.content = emailMessage;

  // Set SMTP server settings
  Session_Config config;

  /* Set the session config */
  config.server.host_name = smtpServer;
  config.server.port = smtpPort;
  config.login.email = SMTP_USERNAME;
  config.login.password = SMTP_PASSWORD;
  config.login.user_domain = F("127.0.0.1"); //local host
  config.time.ntp_server = F("pool.ntp.org,time.nist.gov");
  config.time.gmt_offset = 3;
  config.time.day_light_offset = 0;

  // Send the email
  if (!MailClient.sendMail(&smtp, &message)) {
    String error_msg = (String)"Error sending Email, " + smtp.errorReason();
    Serial.println(error_msg);
  } else {
    Serial.println("Email sent successfully!");
  }
}

// Callback function to handle SMTP status
void smtpCallback(SMTP_Status status) {
  // Print the current status
  Serial.println(status.info());

  // Print the sending result
  if (status.success()) {
    Serial.println("Email sent successfully!");
  } else {
    Serial.println("Failed to send Email.");
  }
}

String operator+(const String& a, const String& b) { //the String class for Arduino is only half done...
    return a + b;
}
