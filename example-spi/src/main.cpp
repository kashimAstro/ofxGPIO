#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"

class noWin : public ofBaseApp{
        public:
		SPI * spi;
	        int i = 20;
	        int a2dVal = 0;
	        int a2dChannel = 0;
	        unsigned char data[3];

		void setup(){
		        spi = new("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
		}
		
		void update(){
			data[0] = 1;
		        data[1] = 0b10000000 |( ((a2dChannel & 7) << 4));
		        data[2] = 0;

		        spi->spiWriteRead(data, sizeof(data) );
 		        a2dVal = 0;
                	a2dVal = (data[1]<< 8) & 0b1100000000;
	                a2dVal |=  (data[2] & 0xff);
        		sleep(2);
		        ofLog()<<"Result: " << a2dVal;
		}
};

int main( ){
        ofAppNoWindow window;
	ofSetupOpenGL(&window, 0,0, OF_WINDOW);
	ofRunApp( new noWin() );
}
