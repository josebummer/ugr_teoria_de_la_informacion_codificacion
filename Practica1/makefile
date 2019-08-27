EMISORPORT=/dev/ttyACM0
RECEPTORPORT=/dev/ttyACM1
INCLUDES=-I./include -I./lib
INCLUDEDIR=./include
LIBDIR=./lib
OBJDIR=./obj
CPPDIR=./cpp
BINDIR=./bin


compilar:
	g++ -std=c++11 -o $(BINDIR)/leercadena $(CPPDIR)/leercadena.cpp $(LIBDIR)/PCSerialUSB.cpp $(INCLUDES)
	avr-gcc -Os -mmcu=atmega328p -c -o $(OBJDIR)/emisor.o $(CPPDIR)/emisor.cpp $(INCLUDES)
	avr-gcc -Os -mmcu=atmega328p $(OBJDIR)/emisor.o $(INCLUDES) -lm -lArduTIC -L$(LIBDIR) -o $(OBJDIR)/emisor.bin
	avr-objcopy -O ihex -R .eeprom $(OBJDIR)/emisor.bin $(BINDIR)/emisor.hex

sendemisor:
	avrdude -F -V -c arduino -p ATMEGA328P -P $(EMISORPORT) -b 115200 -U flash:w:$(BINDIR)/emisor.hex

clean:
	rm -f -r *~
	rm -f -r obj/*
	rm -f -r src/*~

cleanall: clean
	rm -f -r bin/*

