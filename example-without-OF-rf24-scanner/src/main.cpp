#include <iostream>
#include "ofxGPIO.h"

#define CHANNELS  64
int channel[CHANNELS];

int  line;
char grey[] = " .:-=+*aRW";
uint8_t spi_rxbuff[32] ;
uint8_t spi_txbuff[32+1] ;

#define _NRF24_CONFIG      0x00
#define _NRF24_EN_AA       0x01
#define _NRF24_RF_CH       0x05
#define _NRF24_RF_SETUP    0x06
#define _NRF24_RPD         0x09
#define byte unsigned char
#define NOP           0xFF
#define R_REGISTER    0x00
#define REGISTER_MASK 0x1F
#define W_REGISTER    0x20

uint8_t ce_pin =RPI_V2_GPIO_P1_22 ;
uint8_t csn_pin =RPI_V2_GPIO_P1_24 ;

byte getRegister(uint8_t reg)
{
	uint8_t result;
	uint8_t * prx = spi_rxbuff;
	uint8_t * ptx = spi_txbuff;
	*ptx++ = ( R_REGISTER | ( REGISTER_MASK & reg ) );
	*ptx = NOP;
	bcm2835_gpio_write(csn_pin, LOW);
	bcm2835_spi_transfernb( (char *) spi_txbuff, (char *) spi_rxbuff, 2);
	bcm2835_gpio_write(csn_pin,HIGH);
	result = *++prx;
	return (result);
}

void setRegister(uint8_t reg, uint8_t value)
{
	uint8_t status;
	uint8_t * prx = spi_rxbuff;
	uint8_t * ptx = spi_txbuff;
	*ptx++ = ( W_REGISTER | ( REGISTER_MASK & reg ) );
	*ptx = value ;
	bcm2835_gpio_write(csn_pin, LOW);
	bcm2835_spi_transfernb( (char *) spi_txbuff, (char *) spi_rxbuff, 2);
	bcm2835_gpio_write(csn_pin,HIGH);
	status = *prx++;
}

void powerUp()
{
	setRegister(_NRF24_CONFIG,getRegister(_NRF24_CONFIG)|0x02);
	delayMicroseconds(130);//130
}

void powerDown() { setRegister(_NRF24_CONFIG,getRegister(_NRF24_CONFIG)&~0x02); }
void enable()    { bcm2835_gpio_write(ce_pin, HIGH); }
void disable()   { bcm2835_gpio_write(ce_pin, LOW);  }

void setRX()
{
	setRegister(_NRF24_CONFIG,getRegister(_NRF24_CONFIG)|0x01);
	enable();
	delayMicroseconds(130); //130
}

void scanChannels(void)
{
	disable();
	for( int j=0 ; j<200  ; j++)
	{
		for( int i=0 ; i<CHANNELS ; i++)
		{
			setRegister(_NRF24_RF_CH,(128*i)/CHANNELS);
			setRX();
			delayMicroseconds(40); //40
			disable();
			if( getRegister(_NRF24_RPD)>0 )   channel[i]++;
		}
	}
}

void printChannels(void)
{
	printf("\n>    1    2    3    4    5    6    7    8    9    10    11    12    13    14   <\n");
}

void outputChannels(void)
{
	int norm = 0;
	for( int i=0 ; i<CHANNELS ; i++)
	{ 
		if( channel[i]>norm ) norm = channel[i];
	}
	printf("|");
	for( int i=0 ; i<CHANNELS ; i++)
	{
		int pos;
		if( norm!=0 ) pos = (channel[i]*10)/norm;
		else          pos = 0;
		if( pos==0 && channel[i]>0 ) pos++;
		if( pos>9 ) pos = 9;
		printf("%c",grey[pos]);
		channel[i] = 0;
	}
	printf("|");
	printf("%d\n",norm);
}

void outputRawChannel()
{
	printf("#   ");
	for( int i=0 ; i<CHANNELS ; i++)
	{
		printf("%i", channel[i]);
		channel[i] = 0;
	}
	printf("   #\n");
}

int main()
{
	/*
	0         1         2         3         4         5         6
	0123456789012345678901234567890123456789012345678901234567890123
	   1 2  3 4  5  6 7 8  9 10 11 12 13  14                     | 
	*/
	printChannels();
	bcm2835_init();
	bcm2835_gpio_fsel(ce_pin, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(csn_pin, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(ce_pin, LOW);
	bcm2835_gpio_write(csn_pin, HIGH);
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
	bcm2835_spi_setClockSpeed(BCM2835_SPI_SPEED_1MHZ);
	bcm2835_spi_begin(csn_pin);
	delay(100);
	disable();
	powerUp();
	setRegister(_NRF24_EN_AA,0x0);
	setRegister(_NRF24_RF_SETUP,0x0F);
	line = 0;

	while(1)
	{
		scanChannels();
		outputRawChannel();
		//outputChannels();
		if( line++>12 )
		{
			printChannels();
			line = 0;
		}
	}
	return 0;
}
