/* COMPILACION
avr-gcc -Os -mmcu=atmega328p -c -o main.o main.cpp
avr-gcc -mmcu=atmega328p main.o -o main
avr-objcopy -O ihex -R .eeprom main main.hex

sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:main.hex
*/
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int main(void)
{
    DDRB |= _BV(DDB0);

    while(1){
        PORTB |= _BV(PORTB0);
        _delay_ms(BLINK_DELAY_MS);

        PORTB &= ~_BV(PORTB0);
        _delay_ms(BLINK_DELAY_MS);
    }
}