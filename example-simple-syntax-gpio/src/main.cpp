#include <iostream>
#include "ofxGPIO.h"

int main() try {
        GPIO gpio;
	string state;
	int i = 0;

        gpio.setup(GPIO17,OUT,LOW);

	while(i<100)
	{
            gpio.set(HIGH);
	    state = "State pin17: "+to_string(gpio.get());
	    Log(state,FG_RED,BG_WHITE) <<"\n";
            sleep(2);
            gpio.set(LOW);
	    state = "State pin17: "+to_string(gpio.get());
	    Log(state,FG_BLUE,BG_WHITE) <<"\n";
	    sleep(2);
	    i++;
        }

	gpio.close();
	return 0;
}
catch(int e) 
{
	Log(e,FG_RED,BG_BLUE) << "\n";
}
