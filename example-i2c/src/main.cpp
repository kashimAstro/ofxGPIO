#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"

class ofApp : public ofBaseApp{
        public:
		I2c * bus;

                void setup(){
			bus = new I2c("/dev/i2c-1");
			bus->addressSet(0x04);

		}

                void update(){
	                bus->writeByte(0x04,1);
			usleep(500000);
	                bus->writeByte(0x04,0);
			usleep(500000);
		}

                void draw(){

		}
};

int main( ){
	ofAppNoWindow window;
	ofSetupOpenGL(&window, 1024,768, OF_WINDOW);
	ofRunApp( new ofApp());
}
