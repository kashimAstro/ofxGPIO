CC       = @g++ -Wall
FOLDER   = $(notdir $(CURDIR))
CFLAGS   = -I../src/ -Isrc/ -lpthread `pkg-config --cflags --libs gtk+-2.0`
SRCFILE  = ../src/gpio.cpp
SRCFILE  += ../src/i2c.cpp
SRCFILE  += ../src/pwm.cpp
SRCFILE  += ../src/smbus.cpp
DEFINE   = -DCOMPILE_WITHOUT_OPENFRAMEWORKS=1 -DGTK_UI
OUTPUT   = bin/$(FOLDER)
SOURCE   = src/main.cpp
BIN      = bin/

all:
	mkdir -p $(BIN)
	$(CC) -o $(OUTPUT) $(SOURCE) $(SRCFILE) $(DEFINE) $(CFLAGS) -std=c++11 
