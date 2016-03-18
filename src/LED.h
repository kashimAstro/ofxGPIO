#include "ofMain.h"

class LED {
	public:
	int xnumLed;
	SPI2 spi;
	void setupAPA102(int port=0, int speed=8000000){
		int state = spi.setup(port,speed);
                if(state < 0)
                    ofLog()<<"Failed to setup SPI!";
                else
                    ofLog()<<"Open setup SPI!";
	}

	void setAPA102(int numLed, vector<ofVec3f> colors, int BRIGHTNESS){
		int a;
                uint8_t buffer0[1], buffer1[4];
                srand(time(NULL));
		xnumLed = numLed;
		if(BRIGHTNESS>29)
			BRIGHTNESS=30;

                for(a=0; a<4; a++){
                       buffer0[0]=0b00000000;
                       spi.readWrite(0, (unsigned char*)buffer0, 1);
                }
                for(a=0; a<numLed; a++){
                       buffer1[0]=(BRIGHTNESS & 0b00011111) | 0b11100000;
                       buffer1[1]=(uint8_t)(colors[a].y);  //green
                       buffer1[2]=(uint8_t)(colors[a].z);  //blue
                       buffer1[3]=(uint8_t)(colors[a].x);  //red
                       spi.readWrite(0, (unsigned char*)buffer1, 4);
                }
                for(a=0; a<4; a++){
                       buffer0[0]=0b11111111;
                       spi.readWrite(0, (unsigned char*)buffer0, 1);
                }

	}

	void clearAPA102(int numLed){
                int a;
		uint8_t buffer0[1], buffer1[4];
		srand(time(NULL));

		for(a=0; a<4; a++){
			buffer0[0]=0b00000000;
			spi.readWrite(0, (unsigned char*)buffer0, 1);
		}
		for(a=0; a<numLed; a++){
			ofLog()<<a;
			buffer1[0]=(1 & 0b00011111) | 0b11100000;
			buffer1[1]=(uint8_t)(1);  //green
			buffer1[2]=(uint8_t)(1);  //blue
			buffer1[3]=(uint8_t)(1);  //red
			spi.readWrite(0, (unsigned char*)buffer1, 4);
		}
		for(a=0; a<4; a++){
			buffer0[0]=0b11111111;
			spi.readWrite(0, (unsigned char*)buffer0, 1);
		}
		ofExit(0);
	}

};
