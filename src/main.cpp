#include "eeprom.h"

#include "mqtt.h"
#ifndef wifi
#define wifi
#include "wifi.h"
#endif

#ifndef utils
#define utils
#include "utils.h"
#endif

// Change the credentials below, so your ESP8266 connects to your router
#ifndef CLIENT_ID
const char *DEVICE_ID = "EC01";
#define CLIENT_ID "loadbnk"
#define STASSID "dlink3202"
#define STAPSK "123a3202"
#endif

// MQTT broker IP and port
const char *mqtt__broker_ip = "db1rp5.local";
const int mqtt__broker_port = 1883;

// MQTT broker credentials (set to NULL if not required)
const char *MQTT_username = NULL;
const char *MQTT_password = NULL;

const String mqtt_topic_pub = String(CLIENT_ID) + "/" + String(DEVICE_ID) + "/status";
const String mqtt_topic_subopc1 = String(CLIENT_ID) + "/" + String(DEVICE_ID) + "/OP1";
const String mqtt_topic_subopc2 = String(CLIENT_ID) + "/" + String(DEVICE_ID) + "/OP2";
const String mqtt_topic_subopc3 = String(CLIENT_ID) + "/" + String(DEVICE_ID) + "/OP3";
const String mqtt_topic_subopc4 = String(CLIENT_ID) + "/" + String(DEVICE_ID) + "/OP4";
const String mqtt_topic_subopc5 = String(CLIENT_ID) + "/" + String(DEVICE_ID) + "/OP5";
const String mqtt_topic_subopc6 = String(CLIENT_ID) + "/" + String(DEVICE_ID) + "/OP6";
const String mqtt_topic_subopc7 = String(CLIENT_ID) + "/" + String(DEVICE_ID) + "/OP7";
const String mqtt_topic_subopc8 = String(CLIENT_ID) + "/" + String(DEVICE_ID) + "/OP8";
const String mqtt_topic_subopc9 = String(CLIENT_ID) + "/" + String(DEVICE_ID) + "/OP9";

const String subscribeArray[9] = {mqtt_topic_subopc1, mqtt_topic_subopc2, mqtt_topic_subopc3, mqtt_topic_subopc4, mqtt_topic_subopc5, mqtt_topic_subopc6, mqtt_topic_subopc7, mqtt_topic_subopc8, mqtt_topic_subopc9};

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);                  // Main LED
  eepromSetup(512);                              // connect with eeprom memory using eeprom.h
  connectToWifi(STASSID, STAPSK);                // Connect to Wifi using wifi.h
  mqttSetup(mqtt__broker_ip, mqtt__broker_port); // Connect to MQTT broker using mqtt.h
}

void loop()
{

  mqttConnect(DEVICE_ID, MQTT_username, MQTT_password, subscribeArray, 9); // THis will connect to MQTT broker if not connected

  mqttLoop(); // This will keep the connection alive
  if (Serial.available() > 0)
  {

    blinkMainLed();
    String jsonString = Serial.readStringUntil('\n');
    mqttPublish(mqtt_topic_pub, jsonString);
    blinkMainLed();
  }
  delay(100);
}