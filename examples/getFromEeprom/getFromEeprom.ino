/*
 * Title:       Example of getting data back from eeprom using picoEEPROM library
 * Made by:     Szymon "Glinek" Glinka
 * Date:        29.07.2025
 * Rev.:        1
 * Description:
 * This is an example of getting data back from an EEPROM using picoEEPROM library created
 * for arduino-pico https://github.com/earlephilhower/arduino-pico boards.
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

    //=== Reading int from EEPROM ===
    /*
     * getInt function takes one argument, eeprom address and returns int read from eeprom.
    */
    int i = picoEEPROM.getInt(0);

    //=== Reading bool from EEPROM ===
    /*
     * getBool takes 2 arguments, bit and eeprom address. Each eeprom cell is one byte long
     * so this library saves up to 8 boolean values in one cell that's why you need to provide
     * at which bit of selected cell is your bool value stored. getBool return boolean value 
     * read from eeprom.
    */
    bool b = picoEEPROM.getBool(0, 4);
    
    //=== Reading string20 from EEPROM ===
    /*
     * getString20 takes one argument, eeprom address and returnes string stored starting 
     * at given address.
    */
    String s20 = picoEEPROM.getString20(5);

    //=== Reading string from EEPROM ===
    /*
     * getString takes 2 arguments, size of string (can be obtained using putString function) 
     * and eeprom address. This function returns string stored in eeprom starting at given address.
    */
    String s = picoEEPROM.getString(40, 25);
}

void loop() {
  // put your main code here, to run repeatedly:

}
