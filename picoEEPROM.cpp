#include "picoEEPROM.h"



        /*
         * name:    begin function;
         * desc.:   beggining eeprom for RP**** based boards, 4096 is max size of eeprom set by library;
         * input:   size of eeprom in bytes;
         * output:  true if begin was successful, false if something failed;
        */
        bool picoEEPROM::begin(int size){
            //=== Beggining EEPROM ===
            //---- If size is valid init EEPROM ----
            if(size <= 4096 && size > 0){
                EEPROM.begin(size);
                return true;
            }
            // |
            //---- Else return error ----
            else return false;
        }
        // |
        /*
         * name:    putEmptyByte function;
         * desc.:   puts empty byte on a given eeprom address;
         * input:   eeprom address;
         * output:  0 if everything worked, 1 if error when commiting to eeprom;
        */
        int picoEEPROM::putEmptyByte(int eepromByte){
            //=== Declaring variables ===
            byte emptyByte = 0b00000000;
            
            //=== Writing to eeprom ===
            EEPROM.write(eepromByte, emptyByte);

            //=== Commiting to eeprom ===
            if (EEPROM.commit()) return 0; 
            else return 1;
        }
        // |
        /*
         * name:    putEmptyBytes function;
         * desc.:   puts empty bytes starting at given eeprom address;
         * input:   number of empty bytes to put to eeprom, starting address;
         * output:  0 if everything worked, 1 if error whrn commiting to eeprom;
        */
        int picoEEPROM::putEmptyBytes(int len, int startingEepromByte){
            //=== Declarign variables ===
            byte emptyByte = 0b00000000;
            int addresses[len];

            //=== Saving empty bytes into eeprom ===
            //---- Generating addresses ----
            for(int i=0; i<len; i++) addresses[i] = startingEepromByte + i;
            //|
            //---- Writing to eeprom ----
            for(int i=0; i<len; i++) EEPROM.write(addresses[i], emptyByte);
            //|
            //---- Commiting to eeprom ----
            if (EEPROM.commit()) return 0; 
            else return 1;
        }


        //************************************************************//
        //                  Intiger operations EEPROM                 //
        //************************************************************//
        /*
         * name:    putInt function;
         * desc.:   putting INT into eeprom starting on a given eeprom byte;
         * input:   value of int to put into eeprom, starting address of eeprom;
         * output:  0 if everything worked, 1 if number is not int, 2 if eeprom commit failed;
        */
        int picoEEPROM::putInt(int value, int startingEepromByte){
            //=== Declaring variables ===
            int addresses[4];
            byte bytes[4];
            
            //=== Saving int into EEPROM ===
            //---- If value isn't int return error, else procced ----
            if(value > 2147483647 || value < -2147483647) return 1;
            else{
                //---- Generate addresses ----
                for(int i = 0; i < 4; i++) addresses[i] = startingEepromByte + i;
                // |
                //---- Turn int into an array of 4 bytes ----
                for(int i=0; i<4; i++) bytes[i] = (value >> i*8);
                // |
                //---- Write each byte into eeprom ----
                for(int i=0; i<4; i++) EEPROM.write(addresses[i], bytes[i]);
                // |
                //---- Commit eeprom ----
                if (EEPROM.commit()) return 0; 
                else return 2;
            }
        }
        // |
        /*
         * name:    getInt function;
         * desc.:   getting INT num from eeprom from given address;
         * input:   eeprom address;
         * output:  INT from eeprom;
        */
        int picoEEPROM::getInt(int startingEepromByte){
            //=== Declaring variables ===
            int addresses[4], numFromEeprom;
            byte bytes[4];
            
            //=== Reading int from EEPROM ===
            //---- Generate table of addresses ----
            for(int i=0; i<4; i++) addresses[i] = startingEepromByte + i;
            // |
            //---- Read each byte from 4 addresses----
            for(int i=0; i<4; i++) bytes[i] = EEPROM.read(addresses[i]);
            // |
            //---- Turn bytes back into an INT ----
            numFromEeprom = (int)bytes[0] | ((int)bytes[1] << 8) | ((int)bytes[2] << 16) | ((int)bytes[3] << 24);

            //=== Return int ===
            return numFromEeprom;
        }


        //************************************************************//
        //                  String operations EEPROM                  //
        //************************************************************//
        /*
         * name:    putString20 function;
         * desc.:   saving max 20 char string into eeprom;
         * input:   string data and starting eeprom address;
         * output:  0 if everything worked, 1 if string size is to large, 2 if eeprom commit failed;
        */
        int picoEEPROM::putString20(String data, int startingEepromByte){
            //=== Declaring variables ===
            int dataSize, addresses[20];
            char individualChars[20];
            byte bytes[20];

            //=== Reading length of string ===
            dataSize = data.length();

            //=== If string is too large return an error ===
            if(dataSize > 20) return 1;
            else{
                //---- Generate addresses ----
                for(int i=0; i<20; i++) addresses[i] = startingEepromByte + i;
                // |
                //---- Turn string into an array of bytes ----
                for(int i=0; i<20; i++){
                    individualChars[i] = char(data[i]);
                    bytes[i] = individualChars[i];
                }
                // |
                //---- Save each byte into EEPROM ----
                for(int i=0; i<20; i++) EEPROM.write(addresses[i], bytes[i]);
                // |
                //---- Commit eeprom ----
                if (EEPROM.commit()) return 0; 
                else return 2;
            }
            return 0;
        }
        // |
        /*
         * name:    getString20 function;
         * desc.:   getting 20 chars from eeprom;
         * input:   eeprom starting address;
         * output:  read string;
        */
        String picoEEPROM::getString20(int startingEepromByte){
            //=== Declaring variables ===
            int addresses[20];
            char individualChars[20];
            byte bytes[20];
            String eepromReadString = "";

            //=== Retreving string from EEPROM ===
            //---- Geenrating addresses ----
            for(int i=0; i<20; i++) addresses[i] = startingEepromByte + i;
            // |
            //---- Reading bytes from EEPROM ----
            for(int i=0; i<20; i++) bytes[i] = EEPROM.read(addresses[i]);
            // |
            //---- Turning bytes into chars and then into one string ----
            for(int i=0; i<20; i++){
                individualChars[i] = char(bytes[i]);
                eepromReadString += String(individualChars[i]);
            }

            //=== Returning it ===
            return eepromReadString;
        }
        // |
        // |
        /*
         * name:    putString function;
         * desc.:   puts string of max 4096 size into EEPROM;
         * input:   string data and starting address of eeprom;
         * output:  returns string's length if everything worked, 1 if string is too large, 2 if eeprom commit failed;
        */
        int picoEEPROM::putString(String data, int startingEepromByte){
            //=== Reading length of string ===
            int dataSize = data.length();

            //=== If string is too large return an error ===
            if(dataSize > 4096) return 1;
            else{
                //=== Declaring arrays ===
                int addresses[dataSize];
                char individualChars[dataSize];
                byte bytes[dataSize];

                //=== Saving string into EEPROM ===
                //---- Generate addresses ----
                for(int i=0; i<dataSize; i++) addresses[i] = startingEepromByte + i;
                // |
                //---- Turn string into an array of bytes ----
                for(int i=0; i<dataSize; i++){
                    individualChars[i] = char(data[i]);
                    bytes[i] = individualChars[i];
                }
                // |
                //---- Save each byte into EEPROM ----
                for(int i=0; i<dataSize; i++) EEPROM.write(addresses[i], bytes[i]);
                // |
                //---- Commit eeprom ----
                if (EEPROM.commit()) return dataSize; 
                else return 2;
            }
            return 0;
        }
        // |
        /*
         * name:    getString function;
         * desc.:   get's string of given length from eeprom;
         * input:   string's length, eeprom starting address;
         * output:  read string;
        */
        String picoEEPROM::getString(int dataSize, int startingEepromByte){
            //=== Declaring variables ===
            int addresses[dataSize];
            char individualChars[dataSize];
            byte bytes[dataSize];
            String eepromReadString = "";

            //=== Retreving string from EEPROM ===
            //---- Geenrating addresses ----
            for(int i=0; i<dataSize; i++) addresses[i] = startingEepromByte + i;
            // |
            //---- Reading bytes from EEPROM ----
            for(int i=0; i<dataSize; i++) bytes[i] = EEPROM.read(addresses[i]);
            // |
            //---- Turning bytes into chars and then into one string ----
            for(int i=0; i<dataSize; i++){
                individualChars[i] = char(bytes[i]);
                eepromReadString += String(individualChars[i]);
            }

            //=== Returning it ===
            return eepromReadString;
        }


        //************************************************************//
        //                 Boolean operations EEPROM                  //
        //************************************************************//
        /*
         * name:    putBool function;
         * desc.:   puts bool into a given bit of a given byte of eeprom;
         * input:   boolean value, bit, eeprom address;
         * output:  0 if everything worked, 1 if bit is out of range, 2 if eeprom commit failed;
        */
        int picoEEPROM::putBool(bool value, int bit, int eepromByte){
            //=== Declaring variables ===
            byte data, originalByte;

            //=== Saving bool to eeprom ===
            if(bit < 0 || bit > 7) return 1;
            else{
                //---- put bool into a specified bit of eeprom byte ----
                data = value << 7-bit;
                // |
                //---- Read old eeprom byte and add to it changed bit ----
                originalByte = EEPROM.read(eepromByte);
                data = data | originalByte;
                // |
                //---- Write byte to eeprom ----
                EEPROM.write(eepromByte, data);
                // |
                //---- Commit eeprom chages ----
                if (EEPROM.commit()) return 0; 
                else return 2;
            }
            return 0;
        }
        // |
        /*
         * name:    getBool function;
         * desc.:   reads bool value from a given bit from a given byte of eeprom;
         * input:   bit, eeprom address;
         * output:  boolean value;
        */
        bool picoEEPROM::getBool(int bit, int eepromByte){
            //=== Declaring variables ===
            bool value;
            byte data;

            //=== Reading data from eeprom ===
            data = EEPROM.read(eepromByte);

            //=== Converting data to bool ===
            value = data >> 7-bit;

            //=== Returning it ===
            return value;
        }
