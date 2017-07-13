#include "ofMain.h"

/* NOT COMPLETE */


enum TYPEGPIOS{ PIA = 0, PIB = 1, PIBP = 2, PIAP = 3, PI2 = 4, PI3 = 5, PIZERO = 6, H3 = 7 };

class GPIOS
{
	public:
	struct _PIN_
	{
		string name;
		ofColor color;
		string state;
		string value;
		string id;
		string type;
	};

	vector<_PIN_> pin_pi26;
	vector<_PIN_> pin_pi40;

	ofRectangle getBitmapStringBoundingBox(string text) // <- thanks roymacdonald
	{
		vector<string> lines = ofSplitString(text, "\n");
		int maxLineLength = 0;
		for(int i = 0; i < (int)lines.size(); i++) {
			const string & line(lines[i]);
			int currentLineLength = 0;
			for(int j = 0; j < (int)line.size(); j++) {
			    if (line[j] == '\t') {
				currentLineLength += 8 - (currentLineLength % 8);
			    } else {
				currentLineLength++;
			    }
			}
			maxLineLength = MAX(maxLineLength, currentLineLength);
		}

		int padding = 4;
		int fontSize = 8;
		float leading = 1.7;
		int height = lines.size() * fontSize * leading - 1;
		int width = maxLineLength * fontSize;
		return ofRectangle(0,0,width, height);
	}

	void setup()
	{
		/* 26 pin raspberry description */
		_PIN_ p;
		p.name="3.3v";   p.color = ofColor::red;    p.id = "+";  p.type = "VCC";      pin_pi26.push_back(p);
		p.name="GPIO2";  p.color = ofColor::orange; p.id = "2";  p.type = "I2C SDA";  pin_pi26.push_back(p);
		p.name="GPIO3";  p.color = ofColor::orange; p.id = "3";  p.type = "I2C SCL";  pin_pi26.push_back(p);
		p.name="GPIO4";  p.color = ofColor::orange; p.id = "4";  p.type = "IO";       pin_pi26.push_back(p);
		p.name="GND";    p.color = ofColor::black;  p.id = "-";  p.type = "GND";      pin_pi26.push_back(p);
		p.name="GPIO17"; p.color = ofColor::orange; p.id = "17"; p.type = "IO";       pin_pi26.push_back(p);
		p.name="GPIO21"; p.color = ofColor::orange; p.id = "21"; p.type = "IO";	      pin_pi26.push_back(p);
		p.name="GPIO22"; p.color = ofColor::orange; p.id = "22"; p.type = "IO";       pin_pi26.push_back(p);
		p.name="3.3v";   p.color = ofColor::red;    p.id = "+";  p.type = "VCC";      pin_pi26.push_back(p);
		p.name="GPIO10"; p.color = ofColor::orange; p.id = "10"; p.type = "SPI MOSI"; pin_pi26.push_back(p);
		p.name="GPIO9";  p.color = ofColor::orange; p.id = "9";  p.type = "SPI MISO"; pin_pi26.push_back(p);
		p.name="GPIO11"; p.color = ofColor::orange; p.id = "11"; p.type = "SPI CLK";  pin_pi26.push_back(p);
		p.name="GND";    p.color = ofColor::black;  p.id = "-";  p.type = "GND";      pin_pi26.push_back(p);
		//
		p.name="5v";     p.color = ofColor::red;    p.id = "+";  p.type = "VCC";      pin_pi26.push_back(p);
		p.name="5v";     p.color = ofColor::red;    p.id = "+";  p.type = "VCC";      pin_pi26.push_back(p);
		p.name="GND";    p.color = ofColor::black;  p.id = "-";  p.type = "GND";      pin_pi26.push_back(p);
		p.name="GPIO14"; p.color = ofColor::orange; p.id = "14"; p.type = "UART TX";  pin_pi26.push_back(p);
		p.name="GPIO15"; p.color = ofColor::orange; p.id = "15"; p.type = "UART RX";  pin_pi26.push_back(p);
		p.name="GPIO18"; p.color = ofColor::orange; p.id = "18"; p.type = "IO";       pin_pi26.push_back(p);
		p.name="GND";    p.color = ofColor::black;  p.id = "-";  p.type = "GND";      pin_pi26.push_back(p);
		p.name="GPIO23"; p.color = ofColor::orange; p.id = "23"; p.type = "IO";       pin_pi26.push_back(p);
		p.name="GPIO24"; p.color = ofColor::orange; p.id = "24"; p.type = "IO";       pin_pi26.push_back(p);
		p.name="GND";    p.color = ofColor::black;  p.id = "-";  p.type = "GND";      pin_pi26.push_back(p);
		p.name="GPIO25"; p.color = ofColor::orange; p.id = "25"; p.type = "IO";       pin_pi26.push_back(p);
		p.name="GPIO8";  p.color = ofColor::orange; p.id = "8";  p.type = "IO";       pin_pi26.push_back(p);
		p.name="GPIO7";  p.color = ofColor::orange; p.id = "7";  p.type = "IO";       pin_pi26.push_back(p);
		/**/

		/* 40 pin raspberry description */
		p.name="3.3v";   p.color = ofColor::red;    p.id = "+";  p.type = "VCC";      pin_pi40.push_back(p);
		p.name="GPIO2";  p.color = ofColor::orange; p.id = "2";  p.type = "I2C SDA";  pin_pi40.push_back(p);
		p.name="GPIO3";  p.color = ofColor::orange; p.id = "3";  p.type = "I2C SCL";  pin_pi40.push_back(p);
		p.name="GPIO4";  p.color = ofColor::orange; p.id = "4";  p.type = "IO";       pin_pi40.push_back(p);
		p.name="GND";    p.color = ofColor::black;  p.id = "-";  p.type = "GND";      pin_pi40.push_back(p);
		p.name="GPIO17"; p.color = ofColor::orange; p.id = "17"; p.type = "IO";       pin_pi40.push_back(p);
		p.name="GPIO21"; p.color = ofColor::orange; p.id = "21"; p.type = "IO";       pin_pi40.push_back(p);
		p.name="GPIO22"; p.color = ofColor::orange; p.id = "22"; p.type = "IO";       pin_pi40.push_back(p);
		p.name="3.3v";   p.color = ofColor::red;    p.id = "+";  p.type = "VCC";      pin_pi40.push_back(p);
		p.name="GPIO10"; p.color = ofColor::orange; p.id = "10"; p.type = "SPI MOSI"; pin_pi40.push_back(p);
		p.name="GPIO9";  p.color = ofColor::orange; p.id = "9";  p.type = "SPI MISO"; pin_pi40.push_back(p);
		p.name="GPIO11"; p.color = ofColor::orange; p.id = "11"; p.type = "SPI CLK";  pin_pi40.push_back(p);
		p.name="GND";    p.color = ofColor::black;  p.id = "-";  p.type = "GND";      pin_pi40.push_back(p);
		p.name="DNC";    p.color = ofColor::white;  p.id = "/";  p.type = "NC";       pin_pi40.push_back(p);
		p.name="GPIO5";  p.color = ofColor::orange; p.id = "5";  p.type = "IO";       pin_pi40.push_back(p);
		p.name="GPIO6";  p.color = ofColor::orange; p.id = "6";  p.type = "IO";       pin_pi40.push_back(p);
		p.name="GPIO13"; p.color = ofColor::orange; p.id = "13"; p.type = "IO";       pin_pi40.push_back(p);
		p.name="GPIO19"; p.color = ofColor::orange; p.id = "19"; p.type = "IO";       pin_pi40.push_back(p);
		p.name="GPIO26"; p.color = ofColor::orange; p.id = "26"; p.type = "IO";       pin_pi40.push_back(p);
		p.name="GND";    p.color = ofColor::black;  p.id = "-";  p.type = "GND";      pin_pi40.push_back(p);
		//
		p.name="5v";     p.color = ofColor::red;    p.id = "+";  p.type = "VCC";      pin_pi40.push_back(p);
		p.name="5v";     p.color = ofColor::red;    p.id = "+";  p.type = "VCC";      pin_pi40.push_back(p);
		p.name="GND";    p.color = ofColor::black;  p.id = "-";  p.type = "GND";      pin_pi40.push_back(p);
		p.name="GPIO14"; p.color = ofColor::orange; p.id = "14"; p.type = "UART TX";  pin_pi40.push_back(p);
		p.name="GPIO15"; p.color = ofColor::orange; p.id = "15"; p.type = "UART RX";  pin_pi40.push_back(p);
		p.name="GPIO18"; p.color = ofColor::orange; p.id = "18"; p.type = "IO";       pin_pi40.push_back(p);
		p.name="GND";    p.color = ofColor::black;  p.id = "-";  p.type = "GND";      pin_pi40.push_back(p);
		p.name="GPIO23"; p.color = ofColor::orange; p.id = "23"; p.type = "IO";       pin_pi40.push_back(p);
		p.name="GPIO24"; p.color = ofColor::orange; p.id = "24"; p.type = "IO";       pin_pi40.push_back(p);
		p.name="GND";    p.color = ofColor::black;  p.id = "-";  p.type = "GND";      pin_pi40.push_back(p);
		p.name="GPIO25"; p.color = ofColor::orange; p.id = "25"; p.type = "IO";       pin_pi40.push_back(p);
		p.name="GPIO8";  p.color = ofColor::orange; p.id = "8";  p.type = "IO";       pin_pi40.push_back(p);
		p.name="GPIO7";  p.color = ofColor::orange; p.id = "7";  p.type = "IO";       pin_pi40.push_back(p);
		p.name="DNC";    p.color = ofColor::white;  p.id = "/";  p.type = "NC";       pin_pi40.push_back(p);
		p.name="GND";    p.color = ofColor::black;  p.id = "-";  p.type = "GND";      pin_pi40.push_back(p);
		p.name="GPIO12"; p.color = ofColor::orange; p.id = "12"; p.type = "IO";       pin_pi40.push_back(p);
		p.name="GND";    p.color = ofColor::black;  p.id = "-";  p.type = "GND";      pin_pi40.push_back(p);
		p.name="GPIO16"; p.color = ofColor::orange; p.id = "16"; p.type = "IO";       pin_pi40.push_back(p);
		p.name="GPIO20"; p.color = ofColor::orange; p.id = "20"; p.type = "IO";       pin_pi40.push_back(p);
		p.name="GPIO21"; p.color = ofColor::orange; p.id = "21"; p.type = "IO";       pin_pi40.push_back(p);
		/**/
	}

	void gpio( TYPEGPIOS t, int _x = 10, int _y = 10 )
	{

		if( t == PIA || t == PIB )
		{
			ofPushMatrix();
			for( int i = 0, l = 0; i < pin_pi26.size(); i++ )
			{
				int padd = 1;
				int couter = i;
				ofRectangle rect;
				if(i>=pin_pi26.size()/2)
				{
					padd = 150;
					couter = l;
					l++;
				}
				int x = padd+_x;
				int y = (5+(couter*20))+_y;
				rect.set(x+80,y-8,15,15);
				if(i>=pin_pi26.size()/2)
					rect.set(x-50,y-8,15,15);

				ofDrawBitmapStringHighlight( pin_pi26[i].name, x, y, pin_pi26[i].color );
				ofPushStyle();
				if(rect.inside(ofGetMouseX(),ofGetMouseY()))
				{
					ofSetColor(pin_pi26[i].color);
					string str = "Name: "+pin_pi26[i].name+", Type: "+pin_pi26[i].type+", Pin: "+pin_pi26[i].id;
					ofDrawBitmapStringHighlight(str,1+_x,280+_y);
				}
				else
					ofSetColor(ofColor::white);
				ofDrawRectangle(rect);
				ofPopStyle();
			}
			ofPopMatrix();
		}
		else if( t == PIBP || t == PIAP || t == PI2 || t == PI3 || t == PIZERO )
		{
			ofPushMatrix();
			for( int i = 0, l = 0; i < pin_pi40.size(); i++ )
			{
				int padd = 1;
				int couter = i;
				ofRectangle rect;
				if(i>=pin_pi40.size()/2)
				{
					padd = 150;
					couter = l;
					l++;
				}
				int x = padd+_x;
				int y = (5+(couter*20))+_y;
				ofDrawBitmapStringHighlight( pin_pi40[i].name, x, y, pin_pi40[i].color );
				ofPushStyle();
				rect.set(x+80,y-8,15,15);
				if(i>=pin_pi40.size()/2)
					rect.set(x-50,y-8,15,15);
				if(rect.inside(ofGetMouseX(),ofGetMouseY()))
				{
					ofSetColor(pin_pi40[i].color);
					string str = "Name: "+pin_pi40[i].name+", Type: "+pin_pi40[i].type+", Pin: "+pin_pi40[i].id;
					ofDrawBitmapStringHighlight(str,1+_x,420+_y);
				}
				else
					ofSetColor(ofColor::white);
				ofDrawRectangle(rect);
				ofPopStyle();
			}
			ofPopMatrix();
		}
		else if( t == H3 )
		{

		}
	}
};
