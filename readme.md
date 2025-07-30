# picoEEPROM library for Arduino-Pico boards
This library was created to simplify the process of saving data into an EEPROM for boards from [Arduino-Pico by earlephilhower](https://github.com/earlephilhower/arduino-pico). This library WILL NOT WORK with any other boards!

# Instalation

# Documentation
This library is based on EEPROM.h library from Arduino-Pico, max allowed EEPROM size 4096 bytes, in this documentation each byte is going to be refared as address because we need to specify at which byte we will save the data.

## Initializing library
At the beggining of your Arduino program you need to initialize this library and create an object e.g.:
```cpp
#include <picoEEPROM.h>
picoEEPROM picoEEPROM;
```

## Functions
### Begin function
#### begin(eeprom_size)
`begin` function, takes one argument - size of eeprom, max allowed size is 4096. `begin` function returns 0 if everything worked and 1 if eeprom size is invalid. E.g.
```cpp
picoEEPROM.begin(4096); //begin eeprom with it's max allowed size
```

### putEmptyByte/putEmptyBytes functions
#### putEmptyByte(address)
#### putEmptyBytes(num_of_bytes, address)

### Int values
#### putInt(value, address)
#### getInt(address)

### Bool values
#### putBool(value, bit, address)
#### getBool(bit, address)

### String values
#### putString20(value, address)
#### getString20(address)
#### putString(value, address)
#### getString(string_size, address)