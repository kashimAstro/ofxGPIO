#include "ofMain.h"
#include "GPIOSlider.h"
#include "gpio.h"

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
		int index;
	};

	vector<_PIN_> pin_pi26;
	vector<_PIN_> pin_pi40;
	vector<_PIN_> desc;
	vector<GPIO> gpio;
        vector<GPIOSlider> sliderGroup;
	TYPEGPIOS type;
	bool menu;
	int _x, _y, pin;
	int key_code;
	int key_return,key_return_tmp;

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

		//int padding = 4;
		int fontSize = 8;
		float leading = 1.7;
		int height = lines.size() * fontSize * leading - 1;
		int width = maxLineLength * fontSize;
		return ofRectangle(0,0,width, height);
	}

	void setup( TYPEGPIOS _t, int __x, int __y)
	{
		type = _t;
		_x   = __x;
		_y   = __y;

		menu = true;
		pin  = -1;
		key_code = -1;
		key_return = -1;
		key_return_tmp = -1;
                ofAddListener(ofEvents().keyPressed, this, &GPIOS::mykeyPressed);
                ofAddListener(ofEvents().keyReleased, this, &GPIOS::mykeyReleased);

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
		if( type == PIA || type == PIB ) {
			for(unsigned int i = 0; i < pin_pi26.size(); i++)
			{
				size_t found = pin_pi26[i].name.find("GPIO");
				if (found!=string::npos) 
				{
					pin_pi26[i].index = i;
					GPIO gg;
					gg.setup(atoi(pin_pi26[i].id.c_str()),OUT,LOW);
					gpio.push_back(gg);
					cout << "******" << endl;
				}
				else{
					pin_pi26[i].index = i;
					GPIO gg;
					gpio.push_back(gg);
				}
			}
			desc = pin_pi26;
		}
		else if( type == PIBP || type == PIAP || type == PI2 || type == PI3 || type == PIZERO ) {
			for(unsigned int i = 0; i < pin_pi40.size(); i++)
			{
				size_t found = pin_pi40[i].name.find("GPIO");
				if (found!=string::npos)
				{
					pin_pi40[i].index = i;
					GPIO gg;
					gg.setup(atoi(pin_pi40[i].id.c_str()),OUT,LOW);
					gpio.push_back(gg);
					cout << "******" << endl;
				}
				else{
					pin_pi40[i].index = i;
					GPIO gg;
					gpio.push_back(gg);
				}
			}
			desc = pin_pi40;
		}
	}

	void draw_gpio(vector<_PIN_> _desc, int label_y)
	{
		ofPushMatrix();
		for(unsigned int i = 0, l = 0; i < _desc.size(); i++ )
		{
			int padd = 1;
			int couter = i;
			ofRectangle rect;
			if(i>=_desc.size()/2)
			{
				padd = 150;
				couter = l;
				l++;
			}
			int x = padd+_x;
			int y = (5+(couter*20))+_y;
			rect.set(x+80,y-8,15,15);
			if(i>=_desc.size()/2)
				rect.set(x-50,y-8,15,15);

			ofDrawBitmapStringHighlight( _desc[i].name, x, y, _desc[i].color );
			ofPushStyle();

			if(rect.inside(ofGetMouseX(),ofGetMouseY()) || key_code == i)
			{
				ofSetColor(_desc[i].color);
				string str = "Name: "+_desc[i].name+", Type: "+_desc[i].type+", Pin: "+_desc[i].id;
				size_t found = _desc[i].name.find("GPIO");
				if( (ofGetMousePressed(0)) && menu && found!=string::npos ) {
					menu = false;
					gpio[i].setval_gpio(HIGH);
					cout << "MOUSE HIGH: " << gpio[i].get_gpionum() << endl;
					pin = i;
				}
				else if( (!ofGetMousePressed(0) && key_return == -1) && !menu && found!=string::npos )  {
					menu = true;
					gpio[i].setval_gpio(LOW);
					cout << "MOUSE LOW: " << gpio[i].get_gpionum() << endl;
					pin  = -1;
				}
				key_return_tmp = key_return;
				ofDrawBitmapStringHighlight(str,1+_x,label_y+_y);
			}
			else
			{
				ofSetColor(ofColor::white);
			}
			ofDrawRectangle(rect);
			ofPopStyle();
			if(!menu && pin != -1) {
				//ofPushStyle();
				//sliderGroup[pin].draw();
				//ofPopStyle();
			}
		}
		ofPopMatrix();
	}

	void draw()
	{
		if( type == PIA || type == PIB )
		{
			draw_gpio(desc,280);
		}
		else if( type == PIBP || type == PIAP || type == PI2 || type == PI3 || type == PIZERO )
		{
			draw_gpio(desc,420);
		}
		else if( type == H3 )
		{

		}
	}

        void mykeyReleased(ofKeyEventArgs& eventArgs)
	{ 
		if( eventArgs.key == OF_KEY_RETURN ){
			key_return = -1;
			/*if(key_code != -1)
			{
				size_t found = desc[key_code].name.find("GPIO");
				if( menu && found!=string::npos ) {
					menu = false;
					gpio[key_code].setval_gpio(LOW);
					cout << "KEY LOW: " << gpio[key_code].get_gpionum() << endl;
					pin = key_code;
				}
			}*/
		}
	}

        void mykeyPressed(ofKeyEventArgs& eventArgs)
	{
		if( eventArgs.key == OF_KEY_DOWN ) {
			key_code++;
			if( type == PIA || type == PIB ) {
				if(key_code>=pin_pi26.size()) key_code = -1;
			}else if( type == PIBP || type == PIAP || type == PI2 || type == PI3 || type == PIZERO ) {
				if(key_code>=pin_pi40.size()) key_code = -1;
			}
		}
		if( eventArgs.key == OF_KEY_UP ) {
			key_code--;
			if( type == PIA || type == PIB ) {
				if(key_code<=0) key_code = -1;
			}else if( type == PIBP || type == PIAP || type == PI2 || type == PI3 || type == PIZERO ) {
				if(key_code<=0) key_code = -1;
			}
		}

		if( eventArgs.key == OF_KEY_RETURN ){
			key_return = 1;
			if(key_code != -1)
			{
				size_t found = desc[key_code].name.find("GPIO");
				if( menu && found!=string::npos ) {
					menu = false;
					gpio[key_code].setval_gpio(HIGH);
					cout << "KEY HIGH: " << gpio[key_code].get_gpionum() << endl;
					pin = key_code;
				}
			}
		}
	}

	void exit(){
                ofRemoveListener(ofEvents().keyPressed, this, &GPIOS::mykeyPressed);
                ofRemoveListener(ofEvents().keyReleased, this, &GPIOS::mykeyReleased);

		for(unsigned int i = 0; i < pin_pi26.size(); i++)
		{
			size_t found = pin_pi40[i].name.find("GPIO");
			if (found!=string::npos) 
			{
				gpio[i].unexport_gpio();
			}
		}
		for(unsigned int i = 0; i < pin_pi40.size(); i++)
		{
			size_t found = pin_pi40[i].name.find("GPIO");
			if (found!=string::npos) 
			{
				gpio[i].unexport_gpio();
			}
		}
	}
};
