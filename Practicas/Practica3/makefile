EMISORPORT=/dev/cu.usbmodem145201
RECEPTORPORT=/dev/cu.usbmodem145201
INCLUDES=-I./include -I./lib
INCLUDEDIR=./include
LIBDIR=./lib
OBJDIR=./obj
CPPDIR=./cpp
BINDIR=./bin


compilar:
	g++ -std=c++11 -o $(BINDIR)/receptorPC $(CPPDIR)/receptorPC.cpp $(LIBDIR)/PCSerialUSB.cpp $(INCLUDES)		
	# avr-gcc -Os -mmcu=atmega328p -c -o $(OBJDIR)/receptorArdu.o $(CPPDIR)/receptorArdu.cpp $(INCLUDES)
	avr-gcc -Os -mmcu=atmega328p -c -o $(OBJDIR)/mainRF2272.o $(CPPDIR)/mainRF2272.cpp $(INCLUDES)
	avr-gcc -Os -mmcu=atmega328p $(OBJDIR)/mainRF2272.o $(INCLUDES) -lm -lArduTIC -L$(LIBDIR) -o $(OBJDIR)/mainRF2272.bin
	avr-objcopy -O ihex -R .eeprom $(OBJDIR)/mainRF2272.bin $(BINDIR)/mainRF2272.hex

sendP3:
	avrdude -F -V -c arduino -p ATMEGA328P -P $(EMISORPORT) -b 115200 -U flash:w:$(BINDIR)/mainRF2272.hex

clean:
	rm -f -r *~
	rm -f -r obj/*
	rm -f -r src/*~

cleanall: clean
	rm -f -r bin/*

