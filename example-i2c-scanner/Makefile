CC       = g++ -Wall
FOLDER   = $(notdir $(CURDIR))
CFLAGS   = -I../src/
SRCFILE  = ../src/gpio.cpp
SRCFILE  += ../src/i2c.cpp
SRCFILE  += ../src/pwm.cpp
SRCFILE  += ../src/smbus.cpp
DEFINE   = -DCOMPILE_WITHOUT_OPENFRAMEWORKS=1
OUTPUT   = -o bin/$(FOLDER)
SOURCE   = src/main.cpp
BIN      = bin/

all:
	if test -d $(BIN); then echo "Compile $(OUTPUT), wait.."; else mkdir $(BIN); fi
	$(CC) $(OUTPUT) $(SOURCE) $(SRCFILE) $(DEFINE) $(CFLAGS) -std=c++11 
clean:
	rm $(OUTPUT) 
