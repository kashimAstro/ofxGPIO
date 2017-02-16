#include <iostream>
#include <thread>
#include "ofxGPIO.h"

ReadRawData gps;

void parser(ReadRawData gps)
{
	while(1)
	{
	        string str = "Latitude:"+to_string(gps.getLatitude())+" Longitude:"+to_string(gps.getLongitude())+
			     " Altitude:"+to_string(gps.getAltitude())+" Time"+to_string(gps.getTime());	
		Log(str,FG_GREEN,BG_BLACK)<<"\n";
		sleep(1);
	}
}

int main()
{
	int fd = gps.setup("/dev/ttyAMA0",9600,1);
        thread parsing( parser, gps );
	gps.start();
        parsing.join();
	
	gps.close();
	return 0;
}
