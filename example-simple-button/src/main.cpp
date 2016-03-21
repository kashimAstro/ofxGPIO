#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"

class noWin : public ofBaseApp{
        public:
		GPIO gpio17;
		string state_button;

		void setup(){
			gpio17.setup("17");
			gpio17.export_gpio();
                        gpio17.setdir_gpio("in");
		}
		
		void update(){
			gpio17.getval_gpio(state_button);
			ofLog()<<state_button;
			usleep(50000);
		}

		void exit(){
			gpio17.unexport_gpio();
		}
};

int main( ){
        ofAppNoWindow window;
	ofSetupOpenGL(&window, 0,0, OF_WINDOW);
	ofRunApp( new noWin() );
}
