#include <iostream>
#include "ofxGPIO.h"

int main()
{
	Zenity zen;
        GPIO gpio17;
        gpio17.setup("17");
        gpio17.export_gpio();
        gpio17.setdir_gpio("out");
        
	while (1)
	{
		string onoff = zen.dialog("on or off Led ?","OFF","ON");
		Log("dialog-value: "+onoff,Color::FG_YELLOW);
        	gpio17.setval_gpio(onoff);
	}

        gpio17.unexport_gpio();
	return 0;
}
