#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"

class noWin : public ofBaseApp{
        public:
		ReadRawData gps;
		
		void setup(){
			gps.start("/dev/ttyAMA0");
		}
		
		void update(){

		}

		void exit(){
			gps.stop();
		}

};

int main( ){
        ofAppNoWindow window;
	ofSetupOpenGL(&window, 0,0, OF_WINDOW);
	ofRunApp( new noWin() );
}
