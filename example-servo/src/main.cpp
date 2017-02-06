#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"

class noWin : public ofBaseApp{
        public:

	        rpiPWM1 *pwm;
		int count;

                void setup(){
			pwm = new rpiPWM1(1000.0, 256, 80.0, rpiPWM1::MSMODE);
			count=0;			
                }
		
                void update(){
			pwm->setDutyCycleCount(count); 
	                count += 16;
			if(count>100)
				count=0;
			printf("Duty Cycle is %3.2lf \n",pwm->getDutyCycle());
		        printf("Divisor is %d\n", pwm->getDivisor());
		        usleep(2000000);
                }

                void exit(){

                }

};

int main( ){
        ofAppNoWindow window;
	ofSetupOpenGL(&window, 1024,768, OF_WINDOW);
	ofRunApp( new noWin() );
}
