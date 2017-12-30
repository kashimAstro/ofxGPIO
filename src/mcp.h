#ifndef MCP_H
    #define MCP_H

#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string>
#include <iostream>

enum MCP_DESC {
	MCP3002 = 2,
	MCP3008 = 8
};

class MCP {
public: 
	unsigned char mode;
	unsigned char bitsPerWord;
	unsigned int speed;
	int a2dVal = 0;
        unsigned char data[3];
	int spifd;

	int opened(std::string devspi){
	    int statusVal = -1;
	    this->spifd = open(devspi.c_str(), O_RDWR);
	    if(this->spifd < 0){
		#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
		     ofLog()<<"Could not open SPI device!";
		#else
		     std::cout<<"Could not open SPI device!"<<std::endl;
		#endif
		exit(1);
	    }
	 
	    statusVal = ioctl (this->spifd, SPI_IOC_WR_MODE, &(this->mode));
	    if(statusVal < 0){
		#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
		     ofLog()<<"Could not set SPIMode (WR)...ioctl fail!";
		#else
		     std::cout<<"Could not set SPIMode (WR)...ioctl fail!"<<std::endl;
		#endif
		exit(1);
	    }
	 
	    statusVal = ioctl (this->spifd, SPI_IOC_RD_MODE, &(this->mode));
	    if(statusVal < 0) {
	      #ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
		     ofLog()<<"Could not set SPIMode (RD)...ioctl fail!";
	      #else
		     std::cout<<"Could not set SPIMode (RD)...ioctl fail!"<<std::endl;
	      #endif
	      exit(1);
	    }
	 
	    statusVal = ioctl (this->spifd, SPI_IOC_WR_BITS_PER_WORD, &(this->bitsPerWord));
	    if(statusVal < 0) {
	      //ofLog()<<"Could not set SPI bitsPerWord (WR)...ioctl fail";
	      #ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
		     ofLog()<<"Could not set SPI bitsPerWord (WR)...ioctl fail!";
	      #else
		     std::cout<<"Could not set SPI bitsPerWord (WR)...ioctl fail!"<<std::endl;
	      #endif
	      exit(1);
	    }
	 
	    statusVal = ioctl (this->spifd, SPI_IOC_RD_BITS_PER_WORD, &(this->bitsPerWord));
	    if(statusVal < 0) {
	      #ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
		     ofLog()<<"Could not set SPI bitsPerWord(RD)...ioctl fail!";
	      #else
		     std::cout<<"Could not set SPI bitsPerWord(RD)...ioctl fail!"<<std::endl;
	      #endif
	      exit(1);
	    }  
	 
	    statusVal = ioctl (this->spifd, SPI_IOC_WR_MAX_SPEED_HZ, &(this->speed));    
	    if(statusVal < 0) {
	      #ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
		     ofLog()<<"Could not set SPI speed (WR)...ioctl fail!";
	      #else
		     std::cout<<"Could not set SPI speed (WR)...ioctl fail!"<<std::endl;
	      #endif
	      exit(1);
	    }
	 
	    statusVal = ioctl (this->spifd, SPI_IOC_RD_MAX_SPEED_HZ, &(this->speed));    
	    if(statusVal < 0) {
	      #ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
		     ofLog()<<"Could not set SPI speed (RD)...ioctl fail!";
	      #else
		     std::cout<<"Could not set SPI speed (RD)...ioctl fail!"<<std::endl;
	      #endif
	      exit(1);
	    }
	    return statusVal;
	}
	 
	int quit(){
	    int statusVal = -1;
	    statusVal = close(this->spifd);
	    if(statusVal < 0) {
	      #ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
		     ofLog()<<"Close Device!";
	      #else
		     std::cout<<"Close Device!"<<std::endl;
	      #endif

	      exit(1);
	    }
	    return statusVal;
	}
	 
	int readWrite( unsigned char *data){//, int len){
	  struct spi_ioc_transfer spi[3];
	  int i = 0;
	  int retVal = -1; 
	  bzero(spi, sizeof spi); // ioctl struct must be zeroed 
	  for (i = 0 ; i < 3; i++){
	    spi[i].tx_buf        = (unsigned long)(data + i); // transmit from "data"
	    spi[i].rx_buf        = (unsigned long)(data + i) ; // receive into "data"
	    spi[i].len           = sizeof(*(data + i)) ;
	    spi[i].delay_usecs   = 0 ;
	    spi[i].speed_hz      = this->speed ;
	    spi[i].bits_per_word = this->bitsPerWord ;
	    spi[i].cs_change = 0;
	 }
	 retVal = ioctl (this->spifd, SPI_IOC_MESSAGE(3), &spi) ;
	 if(retVal < 0){
	      #ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
		     ofLog()<<"Problem transmitting spi data..ioctl!";
	      #else
		     std::cout<<"Problem transmitting spi data..ioctl!"<<std::endl;
	      #endif
	    exit(1);
	 }
	 return retVal; 
	}
	 
	MCP(){
	    this->mode = SPI_MODE_0 ;
	    this->bitsPerWord = 8;
	    this->speed = 1000000;
	    this->spifd = -1;
	    this->opened(std::string("/dev/spidev0.0"));
	}

	MCP(std::string devspi, unsigned char spiMode, unsigned int spiSpeed, unsigned char spibitsPerWord){
	    this->mode = spiMode ;
	    this->bitsPerWord = spibitsPerWord;
	    this->speed = spiSpeed;
	    this->spifd = -1;
	    this->opened(devspi);
	}

	void setup(std::string devspi, unsigned char spiMode, unsigned int spiSpeed, unsigned char spibitsPerWord){
	    this->mode = spiMode ;
	    this->bitsPerWord = spibitsPerWord;
	    this->speed = spiSpeed;
	    this->spifd = -1;
	    this->opened(devspi);
	}

	int getValueChannel(int channel)
	{
	    data[0] = 1;
            data[1] = 0b10000000 |( ((channel & 7) << 4));
            data[2] = 0;
            this->readWrite(data);
            a2dVal = 0;
            a2dVal = (data[1]<< 8) & 0b1100000000;
            a2dVal |= (data[2] & 0xff);
		
            return a2dVal;
	}
	 
	vector<int> getValueAllChannel(MCP_DESC num)
	{
	    vector<int> result;
	    for(int i = 0; i < num; i++)
	    {
		result.push_back( this->getValueChannel(i) );
	    }
            return result;
	}

	~MCP(){
	    this->quit();
	}
};
#endif
