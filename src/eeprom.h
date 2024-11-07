#include <Arduino.h>
#include <EEPROM.h>

#ifndef utils
#define utils
#include "utils.h"
#endif

uint16_t EEPROM_SIZE;

void eepromSetup(uint16_t size)
{
    if (size > 512 || size < 1)
    {
        size = 512;
    }
    EEPROM_SIZE = size;
    // put your setup code here, to run once:
    printDebug("Starting EEPROM with buffer size" + String(size));
    EEPROM.begin(size);
}

// read a string from EEPROM
String read_EEPROM(uint8_t pos)
{
    String temp;
    for (uint8_t n = pos; n < EEPROM_SIZE; ++n)
    {
        if (char(EEPROM.read(n)) != ';')
        {
            if (isWhitespace(char(EEPROM.read(n))))
            {
                // do nothing
            }
            else
                temp += String(char(EEPROM.read(n)));
        }
        else
        {
            break;
        }
    }
    return temp;
}

// write to memory
void write_EEPROM(String x, uint16_t pos)
{
    char whiteSpace = ' ';
    for (uint16_t n = pos; n < EEPROM_SIZE + pos; n++)
    {
        if (n < x.length())
        {
            EEPROM.write(n, x[n - pos]);
        }
        else
        {
            EEPROM.write(n, whiteSpace);
        }
    }
}