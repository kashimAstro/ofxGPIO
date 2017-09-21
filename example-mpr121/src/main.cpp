#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"

// MPR121 capacitive touch example
// most of this code is copied and pasted from the adafruit mpr121 arduino library

// The default I2C address
#define MPR121_I2CADDR_DEFAULT 0x5A

#define MPR121_TOUCHSTATUS_L 0x00
#define MPR121_TOUCHSTATUS_H 0x01
#define MPR121_FILTDATA_0L  0x04
#define MPR121_FILTDATA_0H  0x05
#define MPR121_BASELINE_0   0x1E
#define MPR121_MHDR         0x2B
#define MPR121_NHDR         0x2C
#define MPR121_NCLR         0x2D
#define MPR121_FDLR         0x2E
#define MPR121_MHDF         0x2F
#define MPR121_NHDF         0x30
#define MPR121_NCLF         0x31
#define MPR121_FDLF         0x32
#define MPR121_NHDT         0x33
#define MPR121_NCLT         0x34
#define MPR121_FDLT         0x35

#define MPR121_TOUCHTH_0    0x41
#define MPR121_RELEASETH_0    0x42
#define MPR121_DEBOUNCE 0x5B
#define MPR121_CONFIG1 0x5C
#define MPR121_CONFIG2 0x5D
#define MPR121_CHARGECURR_0 0x5F
#define MPR121_CHARGETIME_1 0x6C
#define MPR121_ECR 0x5E
#define MPR121_AUTOCONFIG0 0x7B
#define MPR121_AUTOCONFIG1 0x7C
#define MPR121_UPLIMIT   0x7D
#define MPR121_LOWLIMIT  0x7E
#define MPR121_TARGETLIMIT  0x7F

#define MPR121_GPIODIR  0x76
#define MPR121_GPIOEN  0x77
#define MPR121_GPIOSET  0x78
#define MPR121_GPIOCLR  0x79
#define MPR121_GPIOTOGGLE  0x7A



#define MPR121_SOFTRESET 0x80



class ofApp : public ofBaseApp{
public:
    I2c * bus;

    void setThreshholds( uint8_t touch, uint8_t release ){
        for (uint8_t i=0; i<12; i++) {
            bus->writeByte(MPR121_TOUCHTH_0 + 2*i, touch);
            bus->writeByte(MPR121_RELEASETH_0 + 2*i, release);
        }
    }

    void setup(){
        bus = new I2c("/dev/i2c-1");
        bus->addressSet(MPR121_I2CADDR_DEFAULT);
        
        // soft reset
        bus->writeByte(MPR121_SOFTRESET, 0x63);
        usleep(1000); // 1ms sleep

        bus->writeByte(MPR121_ECR, 0x0);

        uint8_t c =  bus->readByte(MPR121_CONFIG2);
        if (c != 0x24) {
            ofLogError()<<"failed to initialize";
        } else {

            setThreshholds(12, 6);

            bus->writeByte(MPR121_MHDR, 0x01);
            bus->writeByte(MPR121_NHDR, 0x01);
            bus->writeByte(MPR121_NCLR, 0x0E);
            bus->writeByte(MPR121_FDLR, 0x00);

            bus->writeByte(MPR121_MHDF, 0x01);
            bus->writeByte(MPR121_NHDF, 0x05);
            bus->writeByte(MPR121_NCLF, 0x01);
            bus->writeByte(MPR121_FDLF, 0x00);

            bus->writeByte(MPR121_NHDT, 0x00);
            bus->writeByte(MPR121_NCLT, 0x00);
            bus->writeByte(MPR121_FDLT, 0x00);

            bus->writeByte(MPR121_DEBOUNCE, 0);
            bus->writeByte(MPR121_CONFIG1, 0x10); // default, 16uA charge current
            bus->writeByte(MPR121_CONFIG2, 0x20); // 0.5uS encoding, 1ms period

            //  bus->writeByte(MPR121_AUTOCONFIG0, 0x8F);

            //  bus->writeByte(MPR121_UPLIMIT, 150);
            //  bus->writeByte(MPR121_TARGETLIMIT, 100); // should be ~400 (100 shifted)
            //  bus->writeByte(MPR121_LOWLIMIT, 50);
            
            // enable all electrodes
            bus->writeByte(MPR121_ECR, 0x8F);  // start with first 5 bits of baseline tracking
        }
    }
    
    void update(){
        
        int16_t touched  = bus->readByte(MPR121_TOUCHSTATUS_L);
        
        string report = "touches:";
        
        for (uint8_t i=0; i<12; i++) {

            uint16_t mask = 1;
            mask = mask<<i;
            bool i_touched = (touched & mask) > 0;

            report+=ofToString( (int)i );
            report+=":";
            if( i_touched ){
                report+="on ";
            }else{
                report+="off";
            }
            report+=" ";
        }
        
        ofLog()<<report;
    }

};

int main( ){
	ofAppNoWindow window;
	ofSetupOpenGL(&window, 0,0, OF_WINDOW);
	ofRunApp( new ofApp());
}
