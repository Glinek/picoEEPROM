/*
 * Title:       Example of putting and getting string to and from EEPROM
 * Made by:     Szymon "Glinek" Glinka
 * Date:        29.07.2025
 * Rev.:        1
 * Description:
 * This is an example of putting and getting string to and from EEPROM using picoEEPROM
 * library created for arduino-pico https://github.com/earlephilhower/arduino-pico boards.
 * Warning! It's not going to work with boards other than based od RP chips by Raspberry Pi.
*/

//=== Include picoEEPROM library ===
#include <picoEEPROM.h>

//=== Create picoEEPROM object ===
picoEEPROM picoEEPROM;

void setup() {
    //=== Initialize serial connection ===
    Serial.begin(9600);
    while (!Serial) {
        Serial.print(".");
    }

    //=== Beggining EEPROM ===
    /*
     * begin function takes one argument, size of eeprom in bytes. You can declare it
     * to have a max size of 4096 bytes. If gives size is invalid, this function will 
     * return false, otherwise it will return true.
    */
    picoEEPROM.begin(4096);

    //=== Put string ===
    /*
     * Example below puts string into eeprom using putString function so the one that is
     * dynamic and returns length of inputed string.
    */
    int length = picoEEPROM.putString("Longer...ish string", 0);
    Serial.print("Inputed string's length: ");
    Serial.println(length);

    //=== Get string ===
    /*
     * Example below read's string from eeprom using getString value, that's why additional to
     * eeprom address there is length of string inputed.
    */
    String eepromString = picoEEPROM.getString(length, 0);
    Serial.print("String read from EEPROM: ");
    Serial.println(eepromString);
}

void loop() {
  // put your main code here, to run repeatedly:

}
