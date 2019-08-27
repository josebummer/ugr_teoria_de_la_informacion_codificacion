EMISORPORT=/dev/ttyACM0
RECEPTORPORT=/dev/ttyACM1
INCLUDES=-I./include -I./lib
INCLUDEDIR=./include
LIBDIR=./lib
OBJDIR=./obj
CPPDIR=./cpp
BINDIR=./bin


vaciar:
	avr-gcc -Os -mmcu=atmega328p -c -o $(OBJDIR)/main.o $(CPPDIR)/main.cpp $(INCLUDES)
	avr-gcc -Os -mmcu=atmega328p $(OBJDIR)/main.o $(INCLUDES) -lm -lArduTIC -L$(LIBDIR) -o $(OBJDIR)/main.bin
	avr-objcopy -O ihex -R .eeprom $(OBJDIR)/main.bin $(BINDIR)/main.hex

sendmain:
	avrdude -F -V -c arduino -p ATMEGA328P -P $(EMISORPORT) -b 115200 -U flash:w:$(BINDIR)/main.hex



clean:
	rm -f -r *~
	rm -f -r obj/*
	rm -f -r src/*~

cleanall: clean
	rm -f -r bin/*

