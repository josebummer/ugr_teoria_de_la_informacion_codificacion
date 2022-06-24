EMISORPORT=/dev/ttyACM0
RECEPTORPORT=/dev/ttyACM1
INCLUDES=-I./include -I./lib
INCLUDEDIR=./include
LIBDIR=./lib
OBJDIR=./obj
CPPDIR=./cpp
BINDIR=./bin


compilar:
	avr-gcc -Os -mmcu=atmega328p -c -o $(OBJDIR)/fotoreceptor.o $(CPPDIR)/fotoreceptor.cpp $(INCLUDES)
	avr-gcc -Os -mmcu=atmega328p $(OBJDIR)/fotoreceptor.o $(INCLUDES) -lm -lArduTIC -L$(LIBDIR) -o $(OBJDIR)/fotoreceptor.bin
	avr-objcopy -O ihex -R .eeprom $(OBJDIR)/fotoreceptor.bin $(BINDIR)/fotoreceptor.hex

sendfotoreceptor:
	avrdude -F -V -c arduino -p ATMEGA328P -P $(EMISORPORT) -b 115200 -U flash:w:$(BINDIR)/fotoreceptor.hex

clean:
	rm -f -r *~
	rm -f -r obj/*
	rm -f -r src/*~

cleanall: clean
	rm -f -r bin/*

