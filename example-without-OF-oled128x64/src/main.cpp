#include <iostream>
#include "ofxGPIO.h"
#include "font.h"
#define OLED 0x3C
#define WIDTH_OLED 128
#define HEIGHT_OLED 64
#define DATA 0x40
#define CMD  0x80

void clearDisplay(I2CBus * b)
{
	for(int X = 0; X < WIDTH_OLED; X++)
	{
		for(int Y = 0; Y < HEIGHT_OLED; Y++) 
		{
			b->writeByte(DATA,0);
		}
	}
}

void printChar(I2CBus * b, char Char)
{
    	if (Char < 32 || Char > 127)
        {
		Char = '?';
        }
	for(int i = 0; i < 8; i++)
	{
	       b->writeByte(DATA,OLEDFont[Char - 32][i]);
    	}
}

void printString(I2CBus * b, const char *Data)
{
	int i = 0;
        while(Data[i] && i < WIDTH_OLED)
        {
		printChar(b,Data[i++]);
	}
}

int main(int argc, char *argv[])
{
	if(argc > 1)
	{
		srand (time(NULL));

        	I2CBus * bus;
		bus = new I2CBus("/dev/i2c-1");
       		bus->addressSet(OLED);
		string ar = argv[1];
		if(ar == "rand")
		{
			int b = (int)rand() % 100;
			for(int X = 0; X < WIDTH_OLED; X++)
			{
				for(int Y = 0; Y < HEIGHT_OLED; Y++) 
				{
				    bus->writeByte(DATA,b);
				}
			}
		}
		if(ar == "clear")
		{
			clearDisplay(bus);
		}
		if(ar == "letter")
		{
			printString(bus,"Openframeworks");			
		}
	}
	else{
		cout<<"Error: parameter!\n";
	}
	return 0;
}
