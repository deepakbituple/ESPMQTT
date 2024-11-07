
#include <ESP8266WiFi.h>

#ifndef utils
#define utils
#include "utils.h"
#endif

WiFiClient wifiClient;

void connectToWifi(String ssid, String pswd)
{

    Serial.println();
    printDebug("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pswd);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }

    printDebug("WiFi connected - ESP IP address: ");
    printDebug(WiFi.localIP().toString());
    blinkMainLed(5);
}