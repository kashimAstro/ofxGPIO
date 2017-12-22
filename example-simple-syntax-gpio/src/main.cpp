#include <iostream>
#include "ofxGPIO.h"

int main() try {
        GPIO gpio;
	int i = 0;

        gpio.setup(GPIO17,OUT,LOW);

	while(i<100)
	{
            gpio.setval_gpio(HIGH);
            sleep(2);
            gpio.setval_gpio(LOW);
	    sleep(2);
	    i++;
        }

	gpio.unexport_gpio();
	return 0;
}
catch(int e) 
{
	Log(e,FG_RED,BG_BLUE) << "\n";
}
