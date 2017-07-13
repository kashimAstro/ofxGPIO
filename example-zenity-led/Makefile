CC       = g++ -Wall
FOLDER   = $(notdir $(CURDIR))
CFLAGS   = -I../src/
SRCFILE  = ../src/gpio.cpp
SRCFILE  += ../src/i2c.cpp
SRCFILE  += ../src/pwm.cpp
SRCFILE  += ../src/smbus.cpp
DEFINE   = -DCOMPILE_WITHOUT_OPENFRAMEWORKS=1 -DENABLE_ZENITY=1
OUTPUT   = bin/$(FOLDER)
SOURCE   = src/main.cpp
BIN      = bin/

DOT      = $(shell which zenity)

all:
ifneq (,$(DOT))
	mkdir -p $(BIN)
	$(CC) -o $(OUTPUT) $(SOURCE) $(SRCFILE) $(DEFINE) $(CFLAGS) -std=c++11 
else
	$(info "Error: install zenity use script ./tools/install_zenity.sh")
endif

clean:
	rm $(OUTPUT) 
	rm $(BIN)$(FOLDER)
