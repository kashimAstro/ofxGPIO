#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"
#include "ofxNetwork.h"

#define COMPASS 0x1e

class ofApp : public ofBaseApp{
        public:
                I2CBus * busCompass;

                int compassRawData[3];
                float heading;
                ofxUDPManager udp;

                void setup(){
                        busCompass = new I2CBus("/dev/i2c-1");
                        busCompass->addressSet(COMPASS);
                        busCompass->writeByte(0, 0b01110000); // Set to 8 samples @ 15Hz
                        busCompass->writeByte(1, 0b00100000); // 1.3 gain LSb / Gauss 1090 (default)
                        busCompass->writeByte(2, 0b00000000); // Continuous sampling

                        udp.Create();
                        udp.Connect("192.168.0.100",11999);
                        udp.SetNonBlocking(false);
                }

                void update(){
                        uint8_t block[6];
                        busCompass->readBlock(0x80 | 0x04, sizeof(block), block);
                        compassRawData[0] = (int16_t)(block[0] | block[1] << 8);
                        compassRawData[1] = (int16_t)(block[2] | block[3] << 8);
                        compassRawData[2] = (int16_t)(block[4] | block[5] << 8);

                        compassRawData[1] = -compassRawData[1];
                        heading = 180 * atan2(compassRawData[1],compassRawData[0])/M_PI;
                        if(heading < 0)
                              heading += 360;
                        string msg=ofToString(compassRawData[0])+
                               ","+ofToString(compassRawData[1])+
                               ","+ofToString(compassRawData[2])+
                               ","+ofToString(heading)+"\n";

                        udp.Send(msg.c_str(),msg.length());
                }
};

int main( ){
        ofAppNoWindow window;
        ofSetupOpenGL(&window, 0,0, OF_WINDOW);
        ofRunApp( new ofApp());
}
