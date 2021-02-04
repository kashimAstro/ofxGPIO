#ifndef LED_H
    #define LED_H

#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
	#include "ofMain.h"
#endif
#include <iostream>
#include <vector>


class LED {
	public:
	int xnumLed;
	SPI2 spi;
	int channel;

	static uint8_t gamma[256];

	void setupWS2801(string path="/dev/spidev0.0", int chan=0, int speed=1000000){
		channel = chan;
		int state = spi.setup(path,channel,speed);
                if(state < 0)
		{
       		    #ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
	             	ofLog()<<"Failed to setup SPI!";
		    #else
			std::cout<<"Failed to setup SPI!"<<std::endl;
		    #endif
		}
                else{
		    #ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
                    	ofLog()<<"Open setup SPI!";
		    #else
			std::cout<<"Open setup SPI!"<<std::endl;
		    #endif
		}
	}

	void setWS2801(int numLed, vector<ofColor> colors, int BRIGHTNESS){
		int a;
                uint8_t buffer0[1], buffer1[4];
                srand(time(NULL));
		xnumLed = numLed;
		if(BRIGHTNESS>30)
			BRIGHTNESS=31;

		float fBrightnessMod = float(BRIGHTNESS)/31.f;
		uint8_t* colBuffer = new uint8_t[colors.size()*3];
		for(int c=0;c<numLed;c++)
		{
			colBuffer[(c*3)+0] = uint8_t(fBrightnessMod * gamma[colors[c].r]);
			colBuffer[(c*3)+1] = uint8_t(fBrightnessMod * gamma[colors[c].g]);
			colBuffer[(c*3)+2] = uint8_t(fBrightnessMod * gamma[colors[c].b]);
		}
		spi.readWrite(channel, (unsigned char*)colBuffer, numLed * 3);
		delete [] colBuffer;
	}

	void clearWS2801(int numLed){
                uint8_t* colBuffer = new uint8_t[numLed*3];
		for(int c=0;c<numLed;c++)
		{
			colBuffer[(c*3)+0] = 0;
			colBuffer[(c*3)+1] = 0;
			colBuffer[(c*3)+2] = 0;
		}
		spi.readWrite(channel, (unsigned char*)colBuffer, numLed * 3);
		delete [] colBuffer;
	}

	void setupAPA102(string path="/dev/spidev0.0", int chan=0, int speed=8000000){
		channel = chan;
		int state = spi.setup(path,channel,speed);
                if(state < 0)
		{
       		    #ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
	             	ofLog()<<"Failed to setup SPI!";
		    #else
			std::cout<<"Failed to setup SPI!"<<std::endl;
		    #endif
		}
                else{
		    #ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
                    	ofLog()<<"Open setup SPI!";
		    #else
			std::cout<<"Open setup SPI!"<<std::endl;
		    #endif
		}
	}

	void setAPA102(int numLed, vector<ofColor> colors, int BRIGHTNESS){
		int a;
                uint8_t buffer0[1], buffer1[4];
                srand(time(NULL));
		xnumLed = numLed;
		if(BRIGHTNESS>30)
			BRIGHTNESS=31;

                for(a=0; a<4; a++){
                       buffer0[0]=0x00;//0b00000000;
                      if( spi.readWrite(channel, (unsigned char*)buffer0, 1) == -1)
		       	std::cout << "Error: SPI START failed!" << std::endl;
                }
                for(a=0; a<numLed; a++){
                       buffer1[0]=0b11100000 | (0b00011111 & BRIGHTNESS);//(BRIGHTNESS & 0b00011111) | 0b11100000;
                       buffer1[1]=static_cast<uint8_t>(colors[a].b);  //blue
                       buffer1[2]=static_cast<uint8_t>(colors[a].g);  //green
                       buffer1[3]=static_cast<uint8_t>(colors[a].r);  //red
                       if( spi.readWrite(channel, (unsigned char*)buffer1, 4) == -1)
		       	std::cout << "Error: SPI RGB data failed!" << std::endl;
                }
                for(a=0; a<4; a++){
                       buffer0[0]=0xFF;//0b11111111;
                       if( spi.readWrite(channel, (unsigned char*)buffer0, 1) == -1)
		       	std::cout << "Error: SPI STOP failed!" << std::endl;
                }

	}

	void clearAPA102(int numLed){
                int a;
		uint8_t buffer0[1], buffer1[4];
		srand(time(NULL));
		for(a=0; a<4; a++){
			buffer0[0]=0b00000000;
			spi.readWrite(channel, (unsigned char*)buffer0, 1);
		}
		for(a=0; a<numLed; a++){
			buffer1[0]= 0b11100000 | (0b00011111 & 16);
			buffer1[1]=static_cast<uint8_t>(0);  //green
			buffer1[2]=static_cast<uint8_t>(0);  //blue
			buffer1[3]=static_cast<uint8_t>(0);  //red
			spi.readWrite(channel, (unsigned char*)buffer1, 4);
		}
		for(a=0; a<4; a++){
			buffer0[0]=0b11111111;
			spi.readWrite(channel, (unsigned char*)buffer0, 1);
		}
	}

};
#endif
