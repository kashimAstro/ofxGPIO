//system
#include <iostream>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

#ifdef COMPILE_WITHOUT_OPENFRAMEWORKS
	struct ofVec3f {
		float x;
		float y;
		float z;
	};
#endif

//core
#include "gpio.h"
#include "i2cBus.h"
//#include "spi.h" //old 
#include "SPI2.h"
#include "rpiPWM1.h"

//custom
#include "MCP.h"
#include "font.h"
#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS 
	#include "ReadRawData.h"
	#include "GETGoogleImage.h"
#endif
#include "LED.h"
