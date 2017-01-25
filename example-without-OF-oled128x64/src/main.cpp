#include <iostream>
#include "ofxGPIO.h"
#include "font.h"
#include "bitmap.h"

#define OLED 0x3C
#define WIDTH_OLED 128
#define HEIGHT_OLED 64
#define COMMAND_BLACK_BACKGROUND 0xA6
#define COMMAND_WHITE_BACKGROUND 0xA7
#define COMMAND_MIRROR_VERTICAL 0xA0 | 0x1
#define COMMAND_MIRROR_HORIZONTAL 0xC8
#define COMMAND_CHARGE_PUMP_SETTING     0x8d
#define COMMAND_CHARGE_PUMP_ENABLE 0x14
#define COMMAND_DISPLAY_OFF 0xAE
#define COMMAND_DISPLAY_ON 0xAF
#define COMMAND_SET_BRIGHTNESS 0x81
#define PAGE_ADDRESSING 0x02

#define DATA 0x40
#define CMD  0x80

static I2CBus * bus;

void setDisplayOff()
{
        bus->writeByte(CMD,COMMAND_DISPLAY_OFF);
}

void setDisplayOn()
{
        bus->writeByte(CMD,COMMAND_DISPLAY_ON);
}

void setBrightness(int Brightness)
{
        bus->writeByte(CMD,COMMAND_SET_BRIGHTNESS);
        bus->writeByte(CMD,Brightness);
}

void setPageMode()
{
        bus->writeByte(CMD,0x20);
        bus->writeByte(CMD,PAGE_ADDRESSING);
}

void rotateDisplay180()
{
        bus->writeByte(CMD,COMMAND_MIRROR_VERTICAL);
        bus->writeByte(CMD,COMMAND_MIRROR_HORIZONTAL);
}

void setWhiteBackground()
{
        bus->writeByte(CMD,COMMAND_WHITE_BACKGROUND);
}

void setBlackBackground()
{
        bus->writeByte(CMD,COMMAND_BLACK_BACKGROUND);
}

void setCursor(int x, int y)
{
	bus->writeByte(CMD,0x00 + ( 8 * x & 0x0F));
	bus->writeByte(CMD,0x10 + ((8 * x >> 4) & 0x0F));
        bus->writeByte(CMD,0xB0 + y);
}

void drawBitmap(int *Bitmaparray, int x, int y, int w, int h)
{
	setCursor(x,y);
        int Column = 0;
	for(int i = 0; i < w * 8 * h; i++)
	{
		bus->writeByte(DATA,Bitmaparray[i]);
		if (++Column == w * 8)
                {
                        Column = 0;
                        setCursor(x, ++y);
                }
	}
}

void clearDisplay()
{
	for(int x = 0; x < 8; x++)
        {
                setCursor(0, x);
                for(int y = 0; y < 128; y++)
                {
                        bus->writeByte(DATA,0);
                }
        }
        setCursor(0, 0);
}

void printChar(char Char)
{
    	if (Char < 32 || Char > 127)
        {
		Char = '?';
        }
	for(int i = 0; i < 8; i++)
	{
	       bus->writeByte(DATA,OLEDFont[Char - 32][i]);
    	}
}

void printString(char *Data)
{
	int i = 0;
        while(Data[i] && i < WIDTH_OLED)
        {
		printChar(Data[i++]);
	}
}

void printNumber(long Data)
{
        char Buffer[10] = "";
        int IntPart = 0;
        int FloatPart = 0;
        if (Data < 0)
        {
                FloatPart++;
                printChar('-');
                Data = -Data;
        }
        else if (Data == 0)
        {
                FloatPart++;
                printChar('0');
        }
        while (Data > 0)
        {
                Buffer[IntPart++] = Data % 10;
                Data /= 10;
        }
        FloatPart += IntPart;
        for(; IntPart > 0; IntPart--)
        {
                printChar('0' + Buffer[IntPart - 1]);
        }
}

int main(int argc, char *argv[])
{
	if(argc > 1)
	{
		srand (time(NULL));

		bus = new I2CBus("/dev/i2c-1");
		bus->addressSet(OLED);
		bus->writeByte(CMD,COMMAND_CHARGE_PUMP_SETTING);
	        bus->writeByte(CMD,COMMAND_CHARGE_PUMP_ENABLE);
		//setWhiteBackground();
	        //setPageMode();
	        clearDisplay();
		//setDisplayOn();

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
			clearDisplay();
		}
		if(ar == "letter")
		{
			setCursor(0,0);
			printString("OF ofxGPIO");
		}
		if(ar == "bitmap")
		{
			drawBitmap(Bitmap,0, 0, 16, 8);
		}
		if(ar == "bgblack")
		{
	                setBlackBackground();
		}
		if(ar == "rotate")
		{
			rotateDisplay180();
		}
		if(ar == "number")
		{
			setCursor(0,0);
			printNumber(300234);
		}
	}
	else{
		cout<<"Error: parameter!\n";
	}
	return 0;
}
