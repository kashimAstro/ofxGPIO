#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"

class I2CScanner : public ofBaseApp 
{
	public:
		I2c * i2c;
		string path;

		void setup()
		{
			path = "/dev/i2c-1";
                        i2c = new I2c(path.c_str());
		}

		void update()
		{
			int address;
			int result;
			string str;
			Log("Scanning i2c Device...",FG_RED,BG_WHITE)<<"\n";
			Log("   #   #   #   #   #   #   #   #   #   #   #   #   #   #   #   #",FG_MAGENTA,BG_BLACK)<<"\n";
			Log("   0   1   2   3   4   5   6   7   8   9   a   b   c   d   e   f",FG_WHITE,BG_GREEN)<<"\n";
			for(address = 1; address < 127; address++ )
			{
			 	i2c->addressSet(address);
				result = i2c->readByte(address);
				if(result == 0||result == 255)
				{
					stringstream stream;
					stream<<std::hex<<address;
					str +="  "+stream.str();
				}
				else{
					str +="   *";
				}
				if(address % 16 == 0)
					str +="\n";
			}
			Log(str,FG_GREEN,BG_RED)<<"\n";
			Log("Done.",FG_RED,BG_WHITE)<<"\n";
			ofExit(0);
		}
};

int main(int argc, char *argv[])
{
	ofAppNoWindow window;
        ofSetupOpenGL(&window, 0,0, OF_WINDOW);
        ofRunApp( new I2CScanner() );
}
