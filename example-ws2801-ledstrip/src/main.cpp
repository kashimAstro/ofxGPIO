#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"

class ofApp : public ofBaseApp
{
        public:
		LED WS2801;
		vector<ofColor> colors;
		int numLed;
		int brightness;

	void create_palett()
	{
		for(int i = 0; i < numLed; i++) {
			colors.push_back(ofColor(
				(int)ofRandom(0,255),
				(int)ofRandom(0,255),
				(int)ofRandom(0,255)
			));
		}
	}

	void gen_palett()
	{
		for(int i = 0; i < numLed; i++) {
			colors[i] = ofColor(
				(int)ofRandom(0,255),
				(int)ofRandom(0,255),
				(int)ofRandom(0,255)
			);
		}
	}

	void setup()
	{
		brightness = 5;
		numLed     = 95;
		create_palett();
		WS2801.setupWS2801();
	}

	void update(){
		gen_palett();
		WS2801.setWS2801(numLed,colors,brightness);
		usleep(20000);
		//cycling from blackout up to max brightness
		if(brightness<31) brightness++;
		else brightness=0;
	}

	void exit(){
		ofLog()<<"Exit";
		WS2801.clearWS2801(numLed+5);
		ofExit(0);
	}


};

int main( ){
	ofAppNoWindow w;
	ofSetupOpenGL(&w,0,0, OF_WINDOW);
	ofRunApp( new ofApp() );
}
