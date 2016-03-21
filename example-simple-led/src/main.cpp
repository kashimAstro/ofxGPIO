#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"

class noWin : public ofBaseApp{
        public:
		GPIO gpio17;

		void setup(){
			gpio17.setup("17");
			gpio17.export_gpio();
                        gpio17.setdir_gpio("out");
		}
		
		void update(){
		        gpio17.setval_gpio("1");
		        ofSleepMillis(1000);
		        gpio17.setval_gpio("0");
		        ofSleepMillis(1000);
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
