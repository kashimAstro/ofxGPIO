#include <iostream>
#include "ofxGPIO.h"

int main(){
        GPIO gpio17;
        gpio17.setup("17");
        gpio17.export_gpio();
        gpio17.setdir_gpio("out");
                
	while(1)
	{
            gpio17.setval_gpio("1");
            usleep(1000);
            gpio17.setval_gpio("0");
            usleep(1000);
	    sleep(1);
        }

        gpio17.unexport_gpio();
	return 0;
}
