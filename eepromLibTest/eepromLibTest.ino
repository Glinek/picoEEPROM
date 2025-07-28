#include <EEPROM.h>

class picoEEPROM{
    public:
        bool begin(int size){
            if(size <= 4096){
                EEPROM.begin(size);
                return true;
            }
            else return false;
        }

        int putInt(int value, int startingEepromByte){
            int addresses[4];
            byte bytes[4];
            
            if(value > 2147483647 || value < -2147483647) return 1;
            else{
                for(int i = 0; i < 4; i++) addresses[i] = startingEepromByte + i;
                for(int i=0; i<4; i++) bytes[i] = (value >> i*8);
                for(int i=0; i<4; i++) EEPROM.write(addresses[i], bytes[i]);
                
                if (EEPROM.commit()) return 0; 
                else return 2;
            }
        }

        int getInt(int startingEepromByte){
            int addresses[4], numFromEeprom;
            byte bytes[4];
            
            for(int i=0; i<4; i++) addresses[i] = startingEepromByte + i;
            for(int i=0; i<4; i++) bytes[i] = EEPROM.read(addresses[i]);
            numFromEeprom = (int)bytes[0] | ((int)bytes[1] << 8) | ((int)bytes[2] << 16) | ((int)bytes[3] << 24);

            return numFromEeprom;
        }
};

picoEEPROM picoEEPROM;

void setup() {
    Serial.begin(9600);
    for(int d=0; d<10; d++){
        Serial.println("delayStart");
        delay(500);
    }
    picoEEPROM.begin(4096);
    Serial.println(picoEEPROM.getInt(0));
}
void loop() {
}