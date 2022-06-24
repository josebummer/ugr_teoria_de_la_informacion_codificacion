EMISORPORT=/dev/cu.usbmodem144301
RECEPTORPORT=/dev/cu.usbmodem144301
INCLUDES=-I./include -I./lib
INCLUDEDIR=./include
LIBDIR=./lib
OBJDIR=./obj
CPPDIR=./cpp
BINDIR=./bin


compilar:
	g++ -o $(BINDIR)/receptorPC $(CPPDIR)/receptorPC.cpp $(LIBDIR)/PCSerialUSB.cpp $(INCLUDES)		
	avr-gcc -Os -mmcu=atmega328p -c -o $(OBJDIR)/receptorArdu.o $(CPPDIR)/receptorArdu.cpp $(INCLUDES)
	avr-gcc -Os -mmcu=atmega328p $(OBJDIR)/receptorArdu.o $(INCLUDES) -lm -lArduTIC -L$(LIBDIR) -o $(OBJDIR)/receptorArdu.bin
	avr-objcopy -O ihex -R .eeprom $(OBJDIR)/receptorArdu.bin $(BINDIR)/receptorArdu.hex

sendP1:
	avrdude -F -V -c arduino -p ATMEGA328P -P $(EMISORPORT) -b 115200 -U flash:w:$(BINDIR)/receptorArdu.hex

clean:
	rm -f -r *~
	rm -f -r obj/*
	rm -f -r src/*~

cleanall: clean
	rm -f -r bin/*

