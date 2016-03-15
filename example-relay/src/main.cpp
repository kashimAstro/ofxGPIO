#include "ofMain.h"
#include "ofxGPIO.h"

class ofApp : public ofBaseApp{
        public:
		GPIO* gpio17;

		void setup(){
			gpio17  = new GPIO("17");
			gpio17->export_gpio();
                        gpio17->setdir_gpio("out");
		}
		
		void on(){
		        gpio17->setval_gpio("1");
		        usleep(50000);
		}

		void off(){
		        gpio17->setval_gpio("0");
			usleep(50000);
		}

		void update(){

		}
		
		void draw(){

		}

		void keyPressed(int key){
			if(key == '1') { on(); ofLog()<<"ON"; }
			if(key == '2') { off(); ofLog()<<"OFF"; }
		}

		void exit(){
                        gpio17->unexport_gpio();
		}

};

int main( ){
//      ofAppNoWindow window;
//	ofSetupOpenGL(&window, 1280,700, OF_FULLSCREEN);
	ofSetupOpenGL(1280,700, OF_FULLSCREEN);
	ofRunApp( new ofApp() );
}
