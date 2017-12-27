#include <iostream>
#include "ofxGPIO.h"

int main(){
	int channel = 0;
	MCP_DESC chip = MCP3008;
	MCP mcp;

	mcp.setup("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
	while(1)
	{
		/* single channel */
		cout <<"ADC channel[0] = ("<< mcp.getValueChannel(channel) <<")"<< endl;
		cout <<"ADC channel[*] = ("<< endl;
		/* all channel*/
		for(int i = 0; i < chip; i++)
			cout <<"\t"<<i<<") "<< mcp.getValueAllChannel(chip)[i] << endl;
		cout <<")"<< endl;
		usleep(50000);
	}
	mcp.quit();
	return 0;
}
