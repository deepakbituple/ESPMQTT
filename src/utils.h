

#include <Arduino.h>

void printDebug(String msg)
{
    Serial.println("@debug:" + msg);
}

void blinkMainLed(uint8_t times = 1)
{
    for (uint8_t i = 0; i < times; i++)
    {
        digitalWrite(LED_BUILTIN, LOW);
        delay(50);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(50);
    }
}
