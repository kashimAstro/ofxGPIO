#ifndef GPIO_H
#define GPIO_H

#include <string>
using namespace std;
class GPIO
{
	public:
	    GPIO();
	    GPIO(string x);
	    int export_gpio();
	    int unexport_gpio();
	    int setdir_gpio(string dir);
	    int setval_gpio(string val);
	    int getval_gpio(string& val);
	    string get_gpionum();
	private:
	    string gpionum;
};
#endif

