#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"

class noWin : public ofBaseApp{
        public:

		void setup(){
		}
		
		void update(){
		}

		void exit(){
		}

};

int main( ){
        ofAppNoWindow window;
	ofSetupOpenGL(&window, 0,0, OF_WINDOW);
	ofRunApp( new noWin() );
}
