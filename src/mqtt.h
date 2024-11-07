#include <PubSubClient.h>

#ifndef wifi
#define wifi
#include "wifi.h"
#endif

#ifndef utils
#define utils
#include "utils.h"
#endif

PubSubClient mqttClient(wifiClient);

// This function is executed when some device publishes a message to a topic that your ESP8266 is subscribed to
void callback(String topic, byte *message, unsigned int length)
{
    // printDebug("Message arrived on topic: ");
    // printDebug(topic);
    // printDebug(". Message: ");
    String messageTemp;
    String device = topic.substring(topic.lastIndexOf("/") + 1);
    // printDebug("device from callback mqtttopic is " + device);
    for (unsigned int i = 0; i < length; i++)
    {
        messageTemp += (char)message[i];
    }
    Serial.println("{'" + device + "': '" + messageTemp + "'}");
}

void mqttSubscribe(const char *topic)
{
    mqttClient.subscribe(topic);
}

void mqttPublish(String topic, String payload)
{
    mqttClient.publish(topic.c_str(), payload.c_str());
}

// subscribe to array of topics
void mqttSubscribe(const String topics[], int numTopics)
{
    for (int i = 0; i < numTopics; i++)
    {
        printDebug("Subscribing to topic: " + String(topics[i]));
        mqttClient.subscribe(topics[i].c_str());
    }
}

boolean mqttConnect(const char *clientID, const char *mqtt_username, const char *mqtt_password, const String topics[], int numTopics)
{
    if (mqttClient.connected())
    {
        return true;
    }
    int attempts = 0;
    while (!mqttClient.connect(clientID, mqtt_username, mqtt_password))
    {
        printDebug("Failed to connect to MQTT broker. Will try again after 3 seconds");
        attempts++;
        delay(3000);
    }

    printDebug("Connected to MQTT broker after " + String(attempts) + " attempts");
    mqttSubscribe(topics, numTopics);
    return true;
}

void mqttSetup(const char *broker_ip, int broker_port)
{
    mqttClient.setServer(broker_ip, broker_port);
    mqttClient.setCallback(callback);
}

void mqttLoop()
{
    mqttClient.loop();
}