#include <EEPROM.h>

void setup() {
    Serial.begin(9600);
    beginEEPROM();
    for(int d=0; d<10; d++){
        Serial.println("delayStart");
        delay(500);
    }
    //putInt(-2147483647, 0);
    //Serial.println(getInt(0));

}
void loop() {
    
}



void beginEEPROM(){
    EEPROM.begin(4096);
}

void putInt(int value, int startingEepromByte){
    //=== Generating addresses ===
    int addresses[4];
    for(int i = 0; i < 4; i++) addresses[i] = startingEepromByte + i;
    
    // Array to hold 4 bytes
    byte bytes[4];

    //if(value > 2147483647 || value < -2147483647)

    bytes[0] = value;
    bytes[1] = (value >> 8);
    bytes[2] = (value >> 16);
    bytes[3] = (value >> 24);

    
    for(int i=0; i<4; i++) EEPROM.write(addresses[i], bytes[i]);
    
    //delay(1000);
    if (EEPROM.commit()) {
      Serial.println("EEPROM successfully committed");
    } else {
      Serial.println("ERROR! EEPROM commit failed");
    }
}

int getInt(int startingEepromByte){
    int addresses[4];
    for(int i=0; i<4; i++) addresses[i] = startingEepromByte + i;
    
    byte bytes[4];

    for(int i=0; i<4; i++) bytes[i] = EEPROM.read(addresses[i]);



    int numFromEeprom;
    numFromEeprom = (int)bytes[0] | ((int)bytes[1] << 8) | ((int)bytes[2] << 16) | ((int)bytes[3] << 24);

    

    return numFromEeprom;
}