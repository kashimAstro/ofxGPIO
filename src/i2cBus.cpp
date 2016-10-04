#include <fcntl.h>
#include "smbus.h"
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include "i2cBus.h"

I2CBus::I2CBus(const char * deviceName)
{
	fd = open(deviceName, O_RDWR);
	if (fd == -1)
	{
		#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
                        ofLog()<<"Failed to open I2C device!";
                #else
                        std::cout<<"Failed to open I2C device!"<<std::endl;
                #endif
	}
}

I2CBus::~I2CBus()
{
	close(fd);
}

void I2CBus::setup(const char * deviceName)
{
	fd = open(deviceName, O_RDWR);
	if (fd == -1)
	{
		#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
                        ofLog()<<"Failed to open I2C device!";
                #else
                        std::cout<<"Failed to open I2C device!"<<std::endl;
                #endif
	}
}

void I2CBus::addressSet(uint8_t address)
{
	int result = ioctl(fd, I2C_SLAVE, address);
	if (result == -1)
	{
		#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
                        ofLog()<<"Failed to set address.";
                #else
                        std::cout<<"Failed to set address."<<std::endl;
                #endif
	}
}

void I2CBus::write(uint8_t command)
{
	int result = i2c_smbus_write_byte(fd, command);
	if (result == -1)
	{
		#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
                        ofLog()<<"Failed to write byte to I2C.";
                #else
                        std::cout<<"Failed to write byte to I2C."<<std::endl;
                #endif

	}
}

void I2CBus::writeByte(uint8_t command, uint8_t data)
{
	int result = i2c_smbus_write_byte_data(fd, command, data);
	if (result == -1)
	{
		#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
                        ofLog()<<"Failed to write byte to I2C.";
                #else
                        std::cout<<"Failed to write byte to I2C."<<std::endl;
                #endif

	}
}

void I2CBus::writeBlockData(uint8_t command, uint8_t size, __u8 * data)
{
        int result = i2c_smbus_write_i2c_block_data(fd, command, size, data);
	if (result == -1)
	{
		#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
                        ofLog()<<"Failed to write block data byte to I2C.";
                #else
                        std::cout<<"Failed to write block data byte to I2C."<<std::endl;
                #endif
	}
}

uint16_t I2CBus::readByte(uint8_t command)
{
	int result = i2c_smbus_read_byte_data(fd, command);
	if (result == -1)
	{
		#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
                        ofLog()<<"Failed to read byte from I2C.";
                #else
                        std::cout<<"Failed to read byte from I2C."<<std::endl;
                #endif
	}
	return result;
}

uint16_t I2CBus::tryReadByte(uint8_t command)
{
	return i2c_smbus_read_byte_data(fd, command);
}

uint16_t I2CBus::readBlock(uint8_t command, uint8_t size, uint8_t * data)
{
	int result = i2c_smbus_read_i2c_block_data(fd, command, size, data);
	if (result != size)
	{
		#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
                        ofLog()<<"Failed to read block from I2C.";
                #else
                        std::cout<<"Failed to read block from I2C."<<std::endl;
                #endif
	}
	return result;
}

