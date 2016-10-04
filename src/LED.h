#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
	#include "ofMain.h"
#endif

class LED {
	public:
	int xnumLed;
	SPI2 spi;
	void setupAPA102(int port=0, int speed=8000000){
		int state = spi.setup(port,speed);
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
			#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
				ofLog()<<a;
			#endif
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
		#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
			ofExit(0);
		#else 
			exit(0);
		#endif
	}

};
