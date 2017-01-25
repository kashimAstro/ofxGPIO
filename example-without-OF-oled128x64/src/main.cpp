#include <iostream>
#include "ofxGPIO.h"
#include "bitmap.h"

int main(int argc, char *argv[])
{
	if(argc > 1)
	{
		OLED oled;
		oled.setup(OLEDBG::BLACK);
		string ar = argv[1];

		if(ar == "clear")
		{
			oled.clearDisplay();
		}
		if(ar == "letter")
		{
			oled.setCursor(4,5);
			oled.printString("OF ofxGPIO");
		}

		if(ar == "bitmap")
		{
			oled.drawBitmap(Bitmap,0, 0, 16, 8);
		}
		if(ar == "bgblack")
		{
	                oled.setBlackBackground();
			oled.drawBitmap(Bitmap,0, 0, 16, 8);
		}
		if(ar == "rotate")
		{
			oled.rotateDisplay180();
		}
		if(ar == "number")
		{
			oled.setCursor(0,0);
			oled.printNumber(300234);
		}
	}
	else{
		cout<<"Error: parameter!\n";
	}
	return 0;
}
