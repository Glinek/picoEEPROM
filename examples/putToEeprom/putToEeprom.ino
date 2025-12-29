/*
 * Title:       Example of putting data into eeprom using picoEEPROM library
 * Made by:     Szymon "Glinek" Glinka
 * Date:        29.07.2025
 * Rev.:        1
 * Description:
 * This is an example of putting data into an EEPROM using picoEEPROM library created
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

    //=== Saving int into EEPROM ===
    /*
     * putInt function takes two arguments, first one is int variable and another one is 
     * eeprom address at which this function will start saving given int. Because eeprom
     * is separated into bytes we need to save int in 4 separate bytes. Keep it in mind when
     * saving data. In this example, this library will start saving int at address 0 of eeprom
     * and will end at address 3 so next value should be saved at address 4. This function returns
     * 0 if everything worked, 1 if int is invalind and 2 if commiting to eeprom failed.
    */
    myEEPROM.putInt(37, 0);
    
    //=== Saving bool into EEPROM ===
    /*
     * putBool function takes 3 arguments, boolean value, bit, and eeprom byte. Because one 
     * eeprom cell is one byte we can save 8 bits/8 boolean values in one eeprom cell. That's why
     * you need to declate in which byte/eeprom address you will save your boolean value, and at
     * what bit of this eeprom cell. e.g. cell 4 of eeprom is 00000000 and function below will save
     * true at first bit and 4th cell of eeprom will now look like this 10000000. You can choose 
     * bits starting at 0 and ending at 7. This function outputs 0 if everything worked, 1 if 
     * bit address is out of range and 2 if commiting to eeprom failed
    */
    myEEPROM.putBool(true, 0, 4);
    
    //=== Saving string20 into EEPROM ===
    /*
     * putString20 takes 2 arguments, string value and eeprom starting byte. This function limits
     * max string length (maximum characters) into 20. It will save 20 bytes into eeprom even if your
     * string is shorther! Keep this in mind and start saving next data at address offseted from one 
     * used in this function by 20, e.g. if current address is 5 next should be 25. putString20 returns
     * 0 if everything worked, 1 if string length is too large, 2 if commiting to eeprom failed.
     * This function works by converting characters to ASCII numbers, not every character might work!
    */
    myEEPROM.putString20("picoEEPROM", 5);
    
    //=== Saving string into EEPROM ===
    /*
     * putString takes 2 arguments, string value and eeprom starting byte. This function does not
     * limit size of string. The only limitation is that it has to be smaller than 4096 which is the
     * max size of eeprom. putString returns length of inputed string if everything worked 
     * (usefull for getString), 1 if string is larger than 4096 characters, 2 if commiting to eeprom failed.
     * This function works by converting characters to ASCII numbers, not every character might work!
    */
    myEEPROM.putString("Strings longer than 20 can be put here", 25);

}

void loop() {
  // put your main code here, to run repeatedly:

}
