#ifndef GPIO_H
#define GPIO_H

#include <string>

using namespace std;

enum GPIO_MAP_PIN {
	GPIO2  = 2,       GPIO14 = 14,
	GPIO3  = 3,       GPIO15 = 15,
	GPIO4  = 4,	  GPIO18 = 18,
	GPIO17 = 17,      GPIO23 = 23,
	GPIO27 = 27,      GPIO24 = 24,
	GPIO22 = 22,      GPIO25 = 25,
	GPIO10 = 10,      GPIO8  = 8,
	GPIO9  = 9,       GPIO7  = 7,
	GPIO11 = 11,      GPIO12 = 12,
	GPIO5  = 5,       GPIO16 = 16,
	GPIO6  = 6,       GPIO20 = 20,
	GPIO13 = 13,      GPIO21 = 21,
	GPIO19 = 19,
	GPIO26 = 26,
};

enum INTERNAL_STATE {
	LOW  = 0,
	HIGH = 1,
	OUT  = 0,
	IN   = 1	
};

class GPIO {
	public:
	    GPIO();
	    GPIO(string x);
	    GPIO(int x);
	    GPIO(string x, string dir, string val);
	    GPIO(int x, int dir, int val);
		
	    void setup(string x);
	    void setup(int x);
	    void setup(string x, string dir, string val);
	    void setup(int x, int dir, int val);

	    int export_gpio();
	    int unexport_gpio();
	    int setdir_gpio(string dir);
	    int setdir_gpio(int dir);

	    int setval_gpio(string val);
	    int setval_gpio(int val);

	    int getval_gpio(string& val);
	    int getval_gpio(int& val);

	    string get_gpionum();
	    int get_igpionum();

	private:
	    string gpionum;
};
#endif

