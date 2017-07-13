#include <iostream>
#include "ofxGPIO.h"

#define MPU 0x68

int main(){
        I2c * bus;
        float ap = 0.955;

	bus = new I2c("/dev/i2c-1");
        bus->addressSet(MPU);
        int8_t power = bus->readByte(MPU_POWER1);
        bus->writeByte(MPU_POWER1, ~(1 << 6) & power);
	while(1)
	{
	     int16_t temp = bus->readByte(MPU_TEMP1) << 8 | bus->readByte(MPU_TEMP2);
             int16_t xacc  = bus->readByte(MPU_ACCEL_XOUT1) << 8 | bus->readByte(MPU_ACCEL_XOUT2);
	     int16_t yacc  = bus->readByte(MPU_ACCEL_YOUT1) << 8 | bus->readByte(MPU_ACCEL_YOUT2);
	     int16_t zacc  = bus->readByte(MPU_ACCEL_ZOUT1) << 8 | bus->readByte(MPU_ACCEL_ZOUT2);
	     int16_t xgyr  = bus->readByte(MPU_GYRO_XOUT1) << 8 | bus->readByte(MPU_GYRO_XOUT2);
	     int16_t ygyr  = bus->readByte(MPU_GYRO_YOUT1) << 8 | bus->readByte(MPU_GYRO_YOUT2);
	     int16_t zgyr  = bus->readByte(MPU_GYRO_ZOUT1) << 8 | bus->readByte(MPU_GYRO_ZOUT2);

	     std::cout<<"Temp:"<<(temp/340.00+36.53)<<"C"<<std::endl;
	     std::cout<<"x acc:"<<xacc<<std::endl;
	     std::cout<<"y acc:"<<yacc<<std::endl;
	     std::cout<<"z acc:"<<zacc<<std::endl;
	     std::cout<<"x gyro:"<<xgyr<<std::endl;
	     std::cout<<"y gyro:"<<ygyr<<std::endl;
	     std::cout<<"z gyro:"<<zgyr<<std::endl;
	}
	return 0;
}
