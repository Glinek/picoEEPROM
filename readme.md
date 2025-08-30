![banner](https://github.com/user-attachments/assets/1bfe8764-16ca-4731-a233-d45c5635e59d)
# picoEEPROM library for Arduino-Pico boards
This library was created to simplify the process of saving data into an EEPROM for boards from [Arduino-Pico by earlephilhower](https://github.com/earlephilhower/arduino-pico). This library WILL NOT WORK with any other boards!

# Instalation
There are two ways to install this library:
1. Download this repository as .zip and include it using Arduino IDE (Sketch>>Include Library>>Add .ZIP Library...)

![image](https://github.com/user-attachments/assets/76835efe-9595-47fe-bc95-d909f662d4a9)
2. **NOT POSSIBLE YET** Add this library from Arduino IDE's library manager by typing *picoEEPROM* and selecting *picoEEPROM by Glinek*

# Documentation
This library is based on EEPROM.h library from Arduino-Pico, max allowed EEPROM size 4096 bytes, in this documentation each byte is going to be referred to as address because we need to specify at which byte we will save the data.

## Initializing library
At the beginning of your Arduino program you need to initialize this library and create an object e.g.:
```cpp
#include <picoEEPROM.h>
picoEEPROM picoEEPROM;
```

## Functions
### Begin function
#### begin(eeprom_size)
`begin` function takes one argument - size of eeprom, max allowed size is 4096. `begin` function returns 0 if everything worked and 1 if eeprom size is invalid. E.g.
```cpp
picoEEPROM.begin(4096); //begin eeprom with it's max allowed size
```

### putEmptyByte/putEmptyBytes functions
Those functions serve as a way to clear a single byte or multiple bytes.
#### putEmptyByte(address)
`putEmptyByte` puts one empty byte at a specified address
```cpp
picoEEPROM.putEmptyByte(0);
```
#### putEmptyBytes(num_of_bytes, address)
`putEmptyBytes` takes two arguments, number of empty bytes and starting address. It puts a specified number of empty bytes starting at a given address.
```cpp
picoEEPROM.putEmptyBytes(7, 1);
```

### Int values
Those functions are used to store integer value and retrieve it from eeprom.
#### putInt(value, address)
`putInt` takes two arguments, integer value and EEPROM address. Important! This function takes 4 bytes/4 EEPROM addresses to store one integer starting at a given address. `putInt` returns 1 if value is out of range, 2 if commiting to eeprom failed and 0 if everything worked.
```cpp
picoEEPROM.putInt(555, 0); //puts int = 555 starting at address 0
```
#### getInt(address)
`getInt()` takes one argument, EEPROM address (the same address as in `putInt`). This function returns int read from EEPROM. If something is wrong with retrieved int check if the correct address is specified.
```cpp
int valueRead = picoEEPROM.getInt(0); //reads int from address 0
```

### Bool values
Those functions are used to store boolean values in EEPROM. Because of the fact that picoEEPROM uses bytes, in each byte you can store up to 8 boolean values (8 bits) to save space in EEPROM.
#### putBool(value, bit, address)
`putBool` takes three arguments, boolean value, bit at which value will be stored and EEPROM address. This function returns 1 if bit is not between 0-7, 2 if commiting to eeprom failed and 0 if everything worked,
```cpp
picoEEPROM.putBool(true, 0, 5); //saving false at bit 0 at EEPROM address 5
```
#### getBool(bit, address)
`getBool` takes 2 arguments, bit at which value is stored and EEPROM address. This function returns a boolean value read from EEPROM.
```cpp
bool boolRead = picoEEPROM.getBool(0, 5); //reads bool from bit 0 at EEPROM address 5
```

### String values
Those functions are used to store string values in EEPROM. Because of the way they are coded, strings should be composed of only ASCII characters from 0 to 255, otherwise something will not work. This library has 2 functions for working with strings. First one takes string of a static size of 20 bytes and second one takes every string smaller that 4096.
#### putString20(value, address)
`putString20` takes two arguments, string value and EEPROM address. This function will always take 20 bytes from EEPROM to save a given string even if it's e.g. 4 characters long. Keep this in mind when allocating addresses. This function returns 1 if the string is larger than 20, 2 if committing to EEPROM failed and 0 if everything worked.
```cpp
picoEEPROM.putString20("testingStuff", 6); //puts string starting at address 6
```
#### getString20(address)
`getString20` takes one argument, EEPROM address and returns a string read starting at that address.
```cpp
String firstStringRead = picoEEPROM.getString20(6); //reads string stored at addresses 6 to 26
```

#### putString(value, address)
`putString` takes 2 arguments, string of any value smaller than 4096 bytes and EEPROM address. This function returns 1 if string is larger than 4096, 2 if committing to EEPROM failed and **String length!** if everything worked. This data can be used with `getString` function.
```cpp
int stringLength = picoEEPROM.putString("this string is longer than 20 characters", 27) //puts string starting at address 27
```
#### getString(string_size, address)
`getString` takes 2 arguments, string length and EEPROM address. String length is returned when saving a given string to eeprom using the `putString` function. This function returns a string read from EEPROM.
```cpp
String secondStringRead = picoEEPROM.getString(stringLength, 27); //reads string stored at addresses 27 to 27+stringLength
```

# License
This library is licensed under Creative Commons CC BY 4.0 available [here](license)
   
**You are free to:**    
- Share — copy and redistribute the material in any medium or format for any purpose, even commercially.    
- Adapt — remix, transform, and build upon the material for any purpose, even commercially. The licensor cannot revoke these freedoms as long as you follow the license terms.

**Under the following terms:**    
- Attribution — You must give appropriate credit , provide a link to the license, and indicate if changes were made . You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.    
- No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits.    

**Notices:**    
You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an applicable exception or limitation .    
No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other rights such as publicity, privacy, or moral rights may limit how you use the material.    

# Author
This library has been created by Szymon *Glinek* Glinka to help with development of custom firmware for PicoCalc




