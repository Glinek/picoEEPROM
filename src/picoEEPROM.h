#ifndef PICOEEPROM_H
#define PICOEEPROM_H
    #include <EEPROM.h>
    #include <Arduino.h>

    class picoEEPROM{
        public:
            picoEEPROM();
            bool begin(int size);
            int putEmptyByte(int eepromByte);
            int putEmptyBytes(int len, int startingEepromByte);
            int putInt(int value, int startingEepromByte);
            int getInt(int startingEepromByte);
            int putString20(String data, int startingEepromByte);
            String getString20(int startingEepromByte);
            int putString(String data, int startingEepromByte);
            String getString(int dataSize, int startingEepromByte);
            int putBool(bool value, int bit, int eepromByte);
            bool getBool(int bit, int eepromByte);
    };
#endif