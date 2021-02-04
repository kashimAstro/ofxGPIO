#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"

class ofApp : public ofBaseApp
{
        public:
		LED apa;
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
			apa.setupAPA102();
		}

		void update(){
			gen_palett();
			apa.setAPA102(numLed,colors,brightness);
			usleep(100000);
            //cycling from blackout up to max brightness
            if(brightness<31) brightness++;
            else brightness=0;
		}
		
		void exit(){
			ofLog()<<"Exit";
			apa.clearAPA102(numLed+5);
			ofExit(0);
		}

		
};

int main( ){
        ofAppNoWindow w;
	ofSetupOpenGL(&w,0,0, OF_WINDOW);
	ofRunApp( new ofApp() );
}
