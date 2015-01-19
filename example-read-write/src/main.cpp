#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"

class noWin : public ofBaseApp{
        public:
		GPIO* gpio26;
		GPIO* gpio19;
		GPIO* gpio13;
		GPIO* gpio6;
		GPIO* gpio21;

		string state_button;

		void setup(){
    			gpio26  = new GPIO("26");
			gpio19  = new GPIO("19");
			gpio13  = new GPIO("13");
			gpio6   = new GPIO("6");
			gpio21  = new GPIO("21");

			gpio26->export_gpio();
			gpio19->export_gpio();
			gpio13->export_gpio();
			gpio6->export_gpio();
			gpio21->export_gpio();

		        gpio26->setdir_gpio("out");
                        gpio19->setdir_gpio("out");
                        gpio13->setdir_gpio("out");
                        gpio6->setdir_gpio("out");
                        gpio21->setdir_gpio("in");
		}
		
		void update(){
			usleep(100);
	                gpio21->getval_gpio(state_button);
			if(state_button == "1"){
				        usleep(5000);
				        gpio26->setval_gpio("1");
				        gpio19->setval_gpio("0");
				        gpio13->setval_gpio("0");
				        gpio6->setval_gpio("1");
				        usleep(5000);
				        gpio26->setval_gpio("1");
				        gpio19->setval_gpio("0");
				        gpio13->setval_gpio("1");
				        gpio6->setval_gpio("0");
				        usleep(5000);
				        gpio26->setval_gpio("0");
				        gpio19->setval_gpio("1");
				        gpio13->setval_gpio("1");
				        gpio6->setval_gpio("0");
				        usleep(5000);
				        gpio26->setval_gpio("0");
				        gpio19->setval_gpio("1");
				        gpio13->setval_gpio("0");
				        gpio6->setval_gpio("1");
			}
		}

};

int main( ){
        ofAppNoWindow window;
	ofSetupOpenGL(&window, 1024,768, OF_WINDOW);
	ofRunApp( new noWin() );
}
