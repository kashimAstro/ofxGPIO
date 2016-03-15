#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"

#define I2C_SMBUS_BLOCK_MAX 32

class ofApp : public ofBaseApp{
        public:
		I2CBus * bus;
		int address;
		uint16_t block[I2C_SMBUS_BLOCK_MAX];
      		unsigned short int clear[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		unsigned short int letter[8];

                void setup(){ 
			bus = new I2CBus("/dev/i2c-1");
			bus->addressSet(address);
			address = 0;
                        bus->write(address);
			address = 0x21;
                        bus->write(address);
			address = 0x81;
                        bus->write(address);
			address = 0xef; 
			bus->write(address);
 			address = 0x00;
			bus->write(address);
			letter[0]=FONT8x8[10][0];
			letter[0]=FONT8x8[10][1];
			letter[0]=FONT8x8[10][2];
			letter[0]=FONT8x8[10][3];
			letter[0]=FONT8x8[10][4];
			letter[0]=FONT8x8[10][5];
			letter[0]=FONT8x8[10][6];
			letter[0]=FONT8x8[10][7];
			letter[0]=FONT8x8[10][8];
		}

                void update(){
			
                        bus->writeBlockData(address, 16, (__u8 *)letter);
		        usleep(100000);
	       	}

};

int main( ){
	ofAppNoWindow window;
	ofSetupOpenGL(&window, 1024,768, OF_WINDOW);
	ofRunApp( new ofApp());
}
