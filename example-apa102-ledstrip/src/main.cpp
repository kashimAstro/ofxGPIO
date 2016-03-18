#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"

class ofApp : public ofBaseApp{
        public:
		LED apa;
		vector<ofVec3f> colors;
		int numLed;

	
		void setup(){
			numLed=20;
			for(int i = 0; i < numLed; i++) {
					colors.push_back(ofVec3f(
						(int)ofRandom(0,255),
						(int)ofRandom(0,255),
						(int)ofRandom(0,255)
					));
			}
			apa.setupAPA102();
		}

		void update(){
			apa.setAPA102(numLed,colors,15);
		}
		
		void exit(){
			ofLog()<<"Exit";
			apa.clearAPA102(numLed);
		}

		
};

int main( ){
        ofAppNoWindow w;
	ofSetupOpenGL(&w,0,0, OF_WINDOW);
	ofRunApp( new ofApp() );
}
