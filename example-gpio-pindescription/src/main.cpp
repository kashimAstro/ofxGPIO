#include "ofMain.h"
#include "ofxGPIO.h"

class ofApp : public ofBaseApp{
	public:
	GPIOS dgpio;

	void setup()
	{
		dgpio.setup( TYPEGPIOS::PIBP, 10, 10 );
	}

	void draw()
	{
		ofBackgroundGradient(ofColor::grey,ofColor::black);
                dgpio.draw();
	}
	
	void exit()
	{
		dgpio.exit();
	}
};

int main(int argc, char ** argv)
{
	ofSetupOpenGL(380,500, OF_WINDOW);
	ofRunApp( new ofApp(  ) );
}
