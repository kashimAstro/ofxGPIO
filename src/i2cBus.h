#include <sys/ioctl.h>
#include <stdint.h>
#include <linux/types.h>
#include <iostream>
#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
	#include "ofMain.h"
#endif

#define MPU_ACCEL_XOUT1 0x3b
#define MPU_ACCEL_XOUT2 0x3c
#define MPU_ACCEL_YOUT1 0x3d
#define MPU_ACCEL_YOUT2 0x3e
#define MPU_ACCEL_ZOUT1 0x3f
#define MPU_ACCEL_ZOUT2 0x40

#define MPU_GYRO_XOUT1 0x43
#define MPU_GYRO_XOUT2 0x44
#define MPU_GYRO_YOUT1 0x45
#define MPU_GYRO_YOUT2 0x46
#define MPU_GYRO_ZOUT1 0x47
#define MPU_GYRO_ZOUT2 0x48

#define MPU_TEMP1 0x41
#define MPU_TEMP2 0x42

#define MPU_POWER1 0x6b
#define MPU_POWER2 0x6c

class I2CBus {
	public:
		I2CBus(const char * deviceName);
		~I2CBus();
		void setup(const char * deviceName);
		void addressSet(uint8_t address);
		void write(uint8_t command);
		void writeByte(uint8_t command, uint8_t data);
		void writeBlockData(uint8_t command, uint8_t size, __u8 * data);
		uint16_t readByte(uint8_t command);
		uint16_t tryReadByte(uint8_t command);
		uint16_t readBlock(uint8_t command, uint8_t size, uint8_t * data);
		uint16_t tryReadByte(uint8_t address, uint8_t command) {
			addressSet(address);
			return tryReadByte(command);
		}
	private:
		int fd;
};

