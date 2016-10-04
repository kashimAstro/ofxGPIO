#include <iostream>
#include "ofxGPIO.h"

int main(){
	int a2dVal = 0;
	int a2dChannel = 0;
        unsigned char data[3];
	MCP mcp;
	mcp.setup("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
	while(1)
	{
		 data[0] = 1;
		 data[1] = 0b10000000 |( ((a2dChannel & 7) << 4));
		 data[2] = 0;
		 mcp.readWrite(data);//sizeof(data) );
		 a2dVal = 0;
		 a2dVal = (data[1]<< 8) & 0b1100000000;
		 a2dVal |=  (data[2] & 0xff);
		 cout << "The Result is: " << a2dVal << endl;
		 usleep(5000);
	}
	mcp.xclose();
	return 0;
}
