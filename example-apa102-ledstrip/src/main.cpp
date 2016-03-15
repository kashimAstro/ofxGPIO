#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"

#define NUMLED 100
#define BRIGHTNESS 3
#define RED 2
#define GREEN 220
#define BLUE 240

class noWin : public ofBaseApp{
        public:
		SPI * spi;
	        unsigned char data[3];

		void clearStrip(){
			int a;
			uint8_t buffer0[1], buffer1[4];
			srand(time(NULL));

			for(a=0; a<4; a++){
				buffer0[0]=0b00000000;
	                        spi->spiWriteRead((unsigned char*)buffer0, 1 );
			}
			for(a=0; a<NUMLED; a++){
				buffer1[0]=(0 & 0b00011111) | 0b11100000;
				buffer1[1]=(uint8_t)(0);  //green
				buffer1[2]=(uint8_t)(0);    //blue
				buffer1[3]=(uint8_t)(0);    //red
	                        spi->spiWriteRead((unsigned char*)buffer1, 4 );
			}
			for(a=0; a<4; a++){
				buffer0[0]=0b11111111;
				spi->spiWriteRead((unsigned char*)buffer0, 1 );
			}
		}

		void setStrip(){
			int a;
			uint8_t buffer0[1], buffer1[4];
			srand(time(NULL));

			for(a=0; a<4; a++){
				buffer0[0]=0b00000000;
	                        spi->spiWriteRead((unsigned char*)buffer0, 1 );
			}
			for(a=0; a<NUMLED; a++){
				buffer1[0]=(BRIGHTNESS & 0b00011111) | 0b11100000;
				buffer1[1]=(uint8_t)(GREEN);  //green
				buffer1[2]=(uint8_t)(BLUE);    //blue
				buffer1[3]=(uint8_t)(RED);    //red
	                        spi->spiWriteRead((unsigned char*)buffer1, 4 );
			}
			for(a=0; a<4; a++){
				buffer0[0]=0b11111111;
	                        spi->spiWriteRead((unsigned char*)buffer0, 1 );
			}
		}


		void setup(){
		        spi = new SPI("/dev/spidev0.0", SPI_MODE_0, 4000000, 4);
		}
		
		void update(){
			setStrip();
			ofSleepMillis(10);
		}
};

int main( ){
        ofAppNoWindow window;
	ofSetupOpenGL(&window, 0,0, OF_WINDOW);
	ofRunApp( new noWin() );
}
