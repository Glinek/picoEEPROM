#include <EEPROM.h>

class picoEEPROM{
    public:
        bool begin(int size){
            /*
             * name:    begin function
             * desc.:   beggining eeprom for RP**** based boards, 4096 is max size of eeprom set by library
             * input:   size of eeprom in bytes
             * output:  true if begin was successful, false if something failed
            */

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


        //************************************************************//
        //                  Intiger operations EEPROM                 //
        //************************************************************//
        int putInt(int value, int startingEepromByte){
            /*
             * name:    putInt function
             * desc.:   putting INT into eeprom starting on a given eeprom byte
             * input:   value of int to put into eeprom, starting address of eeprom
             * output:  0 if everything worked, 1 if number is not int, 2 if eeprom commit failed
            */

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
        int getInt(int startingEepromByte){
            /*
             * name:    getInt function
             * desc.:   getting INT num from eeprom from given address
             * input:   eeprom address
             * output:  INT from eeprom
            */

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
        int putString20(String data, int startingEepromByte){
            /*
             * name:    putString20 function
             * desc.:   saving max 20 char string into eeprom
             * input:   string data and starting eeprom address
             * output:  0 if everything worked, 1 if string size is to large, 2 if eeprom commit failed
            */

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
        String getString20(int startingEepromByte){
            /*
             * name:    getString20 function
             * desc.:   getting 20 chars from eeprom
             * input:   eeprom starting address
             * output:  read string
            */

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
        int putString(String data, int startingEepromByte){
            /*
             * name:    putString function
             * desc.:   puts string of max 4096 size into EEPROM
             * input:   string data and starting address of eeprom
             * output:  returns string's length if everything worked, 1 if string is too large, 2 if eeprom commit failed
            */

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
        String getString(int dataSize, int startingEepromByte){
            /*
             * name:    getString function
             * desc.:   get's string of given length from eeprom
             * input:   string's length, eeprom starting address
             * output:  read string
            */

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
        int putBool(bool data, int bit, int startingEepromByte){
            return 0;
        }

        bool getBool(int bit, int startingEepromByte){
            return 0;
        }
};

picoEEPROM picoEEPROM;

void setup() {
    Serial.begin(9600);

    for(int d=0; d<10; d++){
        Serial.println(".");
        delay(500);
    }
    picoEEPROM.begin(4096);
}

void loop(){
}