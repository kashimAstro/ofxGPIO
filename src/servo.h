#ifndef SERVO_UTIL
    #define SERVO_UTIL

#define BCM2708_PERI_BASE       0x20000000
#define GPIO_BASE               (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */
#define PWM_BASE                (BCM2708_PERI_BASE + 0x20C000) /* PWM controller */
#define CLOCK_BASE              (BCM2708_PERI_BASE + 0x101000)

#define PWM_CTL  0
#define PWM_RNG1 4
#define PWM_DAT1 5

#define PWMCLK_CNTL 40
#define PWMCLK_DIV  41

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)
#define GPIO_CLR *(gpio+10)

class Servo {
	public:
	void setAngle(int percent)
	{
	}

	void setup()
	{
	}
};
#endif
