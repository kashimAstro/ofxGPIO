#include "ofMain.h"
#include "ofxGPIO.h"

class ofApp : public ofBaseApp{
	public:
	GPIOS dgpio;
	void setup()
	{
		dgpio.setup();
	}
	void draw()
	{
		ofBackgroundGradient(ofColor::grey,ofColor::black);
		dgpio.gpio(TYPEGPIOS::PIA);
		dgpio.gpio(TYPEGPIOS::PIBP, 350,10);
	}
};

int main(){
	ofSetupOpenGL(1024,768, OF_WINDOW);
	ofRunApp( new ofApp());
}
