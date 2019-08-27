/* COMPILACION
avr-gcc -Os -mmcu=atmega328p -c -o main.o main.cpp -I carpetasde.h
avr-gcc -Os -mmcu=atmega328p main.o -I carpetasde.h -lm -lArduTIC -Lcarpetade.a -o main.bin
avr-objcopy -O ihex -R .eeprom bin.bin bin.hex

avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -Uflash:w:main.hex
*/
#include "ArduTIC.h"

int main(void)
{
    pinMode(9,OUTPUT);

    while(1){
        digitalWrite(9,HIGH);
        delay(1000);

        digitalWrite(9,LOW);
        delay(1000);
    }
}