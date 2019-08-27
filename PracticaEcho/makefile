EMISORPORT=/dev/ttyACM0
RECEPTORPORT=/dev/ttyACM1
INCLUDES=-I./include -I./lib
INCLUDEDIR=./include
LIBDIR=./lib
OBJDIR=./obj
CPPDIR=./cpp
BINDIR=./bin


compilar:
	g++ -o $(BINDIR)/pcecho $(CPPDIR)/pcecho.cpp $(LIBDIR)/PCSerialUSB.cpp $(INCLUDES)
	avr-gcc -Os -mmcu=atmega328p -c -o $(OBJDIR)/arduecho.o $(CPPDIR)/arduecho.cpp $(INCLUDES)
	avr-gcc -Os -mmcu=atmega328p $(OBJDIR)/arduecho.o $(INCLUDES) -lm -lArduTIC -L$(LIBDIR) -o $(OBJDIR)/arduecho.bin
	avr-objcopy -O ihex -R .eeprom $(OBJDIR)/arduecho.bin $(BINDIR)/arduecho.hex

sendarduecho:
	avrdude -F -V -c arduino -p ATMEGA328P -P $(EMISORPORT) -b 115200 -U flash:w:$(BINDIR)/arduecho.hex

clean:
	rm -f -r *~
	rm -f -r obj/*
	rm -f -r src/*~

cleanall: clean
	rm -f -r bin/*

