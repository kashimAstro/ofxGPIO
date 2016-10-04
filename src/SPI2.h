#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

class SPI2 { 
    public:
	string      spiDev0 = "/dev/spidev0.0" ;
	string      spiDev1 = "/dev/spidev0.1" ;
	uint8_t     spiMode   = 0 ;
	uint8_t     spiBPW    = 8 ;
	uint16_t    spiDelay  = 0;
	uint32_t    spiSpeeds [2] ;
	int         spiFds [2] ;

	int getFD (int channel) {
	  return spiFds [channel &1];
	}

	int readWrite(int channel, unsigned char *data, int len) {
	  struct spi_ioc_transfer spi ;

	  channel &= 1 ;

	  spi.tx_buf        = (unsigned long)data ;
	  spi.rx_buf        = (unsigned long)data ;
	  spi.len           = len ;
	  spi.delay_usecs   = spiDelay ;
	  spi.speed_hz      = spiSpeeds [channel] ;
	  spi.bits_per_word = spiBPW ;

	  return ioctl (spiFds [channel], SPI_IOC_MESSAGE(1), &spi) ;
	}

	int setup (int channel, int speed) {
	  int fd ;

	  channel &= 1 ;

	  if ((fd = open (channel == 0 ? spiDev0.c_str() : spiDev1.c_str(), O_RDWR)) < 0)
	  {
	     #ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
                  ofLog()<<"Failed to setup SPI!";
             #else
                  std::cout<<"Failed to setup SPI!"<<std::endl;
             #endif   
	     return -1 ;
	  }

	  spiSpeeds [channel] = speed ;
	  spiFds    [channel] = fd ;
	  if (ioctl (fd, SPI_IOC_WR_MODE, &spiMode)         < 0) return -1 ;
	  if (ioctl (fd, SPI_IOC_RD_MODE, &spiMode)         < 0) return -1 ;
	  if (ioctl (fd, SPI_IOC_WR_BITS_PER_WORD, &spiBPW) < 0) return -1 ;
	  if (ioctl (fd, SPI_IOC_RD_BITS_PER_WORD, &spiBPW) < 0) return -1 ;
	  if (ioctl (fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed)   < 0) return -1 ;
	  if (ioctl (fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed)   < 0) return -1 ;
	  return fd ;
	}
};
