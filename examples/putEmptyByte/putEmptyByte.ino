/*
 * Title:       Example of putting empty bytes into eeprom using picoEEPROM library
 * Made by:     Szymon "Glinek" Glinka
 * Date:        29.07.2025
 * Rev.:        1
 * Description:
 * This is an example of putting empty bytes into an EEPROM using picoEEPROM library created
 * for arduino-pico https://github.com/earlephilhower/arduino-pico boards.
 * Warning! It's not going to work with boards other than based od RP chips by Raspberry Pi.
*/

//=== Include picoEEPROM library ===
#include <picoEEPROM.h>

//=== Create picoEEPROM object ===
picoEEPROM myEEPROM;

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
    myEEPROM.begin(4096);

    //=== Putting one empty byte into EEPROM ===
    /*
     * putEmptyByte function takes one argument, eeprom address and puts empty byte (0b00000000)
     * at this address. This function returns 0 if everything worked and 1 if commiting to
     * eeprom failed.
    */
    myEEPROM.putEmptyByte(0);

    //=== Putting multiple empty bytes into EEPROM ===
    /*
     * putEmptyBytes function takes 2 arguments, number of empty bytes to put and address at
     * which this function will start placing empty bytes. putEmptyBytes returns 0 if everything
     * worked and 1 if commiting to eeprom failed
    */
    myEEPROM.putEmptyBytes(64, 1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
