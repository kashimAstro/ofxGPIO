#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"

#define MPU 0x68

class ofApp : public ofBaseApp{
        public:
		I2CBus * bus;
		float ap = 0.955;
		
                void setup(){
			bus = new I2CBus("/dev/i2c-1");
			bus->addressSet(MPU);
			int8_t power = bus->readByte(MPU_POWER1);
			bus->writeByte(MPU_POWER1, ~(1 << 6) & power);
		}

                void update(){
			int16_t temp = bus->readByte(MPU_TEMP1) << 8 | bus->readByte(MPU_TEMP2);
			int16_t xacc  = bus->readByte(MPU_ACCEL_XOUT1) << 8 | bus->readByte(MPU_ACCEL_XOUT2);
			int16_t yacc  = bus->readByte(MPU_ACCEL_YOUT1) << 8 | bus->readByte(MPU_ACCEL_YOUT2);
			int16_t zacc  = bus->readByte(MPU_ACCEL_ZOUT1) << 8 | bus->readByte(MPU_ACCEL_ZOUT2);
			int16_t xgyr  = bus->readByte(MPU_GYRO_XOUT1) << 8 | bus->readByte(MPU_GYRO_XOUT2);
			int16_t ygyr  = bus->readByte(MPU_GYRO_YOUT1) << 8 | bus->readByte(MPU_GYRO_YOUT2);
			int16_t zgyr  = bus->readByte(MPU_GYRO_ZOUT1) << 8 | bus->readByte(MPU_GYRO_ZOUT2);

			ofLog()<<"Temp:"<<(temp/340.00+36.53)<<"C";
			ofLog()<<"x acc:"<<xacc;
			ofLog()<<"y acc:"<<yacc;
			ofLog()<<"z acc:"<<zacc;
			ofLog()<<"x gyro:"<<xgyr;
			ofLog()<<"y gyro:"<<ygyr;
			ofLog()<<"z gyro:"<<zgyr;
		}

};

int main( ){
	ofAppNoWindow window;
	ofSetupOpenGL(&window, 0,0, OF_WINDOW);
	ofRunApp( new ofApp());
}
