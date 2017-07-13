#pragma once

#ifdef I2c
	#undef I2c
#endif

/* system */
#include <iostream>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <stddef.h>
#include <time.h>
#include <sys/time.h>

/* OF */
#ifdef COMPILE_WITHOUT_OPENFRAMEWORKS
	struct ofVec3f {
		float x;
		float y;
		float z;
	};
#endif

/* Output Log Color */
#include "LogHighLight.h"
using namespace LogHighLight;

/* core low level */
#include "gpio.h"
#include "i2c.h"
#include "spi2.h"
#include "pwm.h"

/* core high level */
#include "kalman.h"
#include "mcp.h"
#include "font.h"
#include "readata.h"
/* only openframeworks */
#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS 
	#include "google_image.h"
	#include "gpio_state.h"
#endif
/* end OF */
/* core high level */
#include "led.h"
#include "oled.h"

//#define ENABLE_BCM2835 0 /* 0 for disable bcm2335 */
#if ENABLE_BCM2835 == 1
	#include "bcm2835.h" /* Test new release ofxGPIOv2 */
#endif

#if ENABLE_ZENITY == 1
	#include "zenity.h"
#endif
