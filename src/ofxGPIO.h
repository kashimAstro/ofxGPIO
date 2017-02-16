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

//OF tool
#ifdef COMPILE_WITHOUT_OPENFRAMEWORKS
	struct ofVec3f {
		float x;
		float y;
		float z;
	};
#endif

//log color
#include "LogHighLight.h"
using namespace LogHighLight;

//core low level
#include "gpio.h"
#include "i2cBus.h"
#include "SPI2.h"
#include "rpiPWM1.h"

//core high level
#include "kalman.h"
#include "MCP.h"
#include "font.h"
#include "ReadRawData.h"
#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS 
	#include "GETGoogleImage.h"
#endif
#include "LED.h"
#include "OLED.h"
