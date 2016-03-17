#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"

class noWin : public ofBaseApp{
        public:
		ReadRawData gps;
		
		void setup(){
			gps.start("/dev/ttyAMA0",1000);
		}
		
		void update(){
		  ofLog()<<"Time:"<<gps.getTime();
		  ofLog()<<"Latitude:"<<gps.getLatitude();
	          ofLog()<<"Longitude:"<<gps.getLongitude();
		  ofLog()<<"Altitude:"<<gps.getAltitude();
		  ofLog()<<"RawData:"<<gps.getRawData();
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
