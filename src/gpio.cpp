#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "LogHighLight.h"
#include "gpio.h"

using namespace std;

GPIO::GPIO()
{
    this->gpionum = "";
}

GPIO::GPIO(string gnum)
{
    this->gpionum = gnum;
}

GPIO::GPIO(int gnum)
{
    this->gpionum = to_string(gnum);
}

GPIO::GPIO(string gnum, string dir, string val)
{
    this->gpionum = gnum;
    this->export_gpio();
    this->setdir_gpio(dir);
    this->setval_gpio(val);
}

GPIO::GPIO(int gnum, int dir, int val)
{
    this->gpionum = to_string(gnum);
    this->export_gpio();
    string _dir = "out";
    if(dir == 1) _dir = "in";
    this->setdir_gpio(_dir);
    this->setval_gpio(to_string(val));
}

void GPIO::setup(string gnum)
{
    this->gpionum = gnum;
}

void GPIO::setup(int gnum)
{
    this->gpionum = to_string(gnum);
}

void GPIO::setup(string gnum, string dir, string val)
{
    this->gpionum = gnum;
    this->export_gpio();
    this->setdir_gpio(dir);
    this->setval_gpio(val);
}

void GPIO::setup(int gnum, int dir, int val)
{
    this->gpionum = to_string(gnum);
    this->export_gpio();
    string _dir = "out";
    if(dir == 1) _dir = "in";
    this->setdir_gpio(_dir);
    this->setval_gpio(to_string(val));
}

int GPIO::export_gpio()
{
    string export_str = "/sys/class/gpio/export";
    ofstream exportgpio(export_str.c_str()); 
    if (!exportgpio.is_open()) {
        LogHighLight::Log("OPERATION FAILED:",LogHighLight::FG_RED,LogHighLight::BG_WHITE) << " ";
	LogHighLight::Log("Unable to export GPIO",LogHighLight::FG_YELLOW,LogHighLight::BG_BLACK) << this->gpionum;
	cout << endl;
        return -1;
    }

    exportgpio << this->gpionum ;
    exportgpio.close();
    return 0;
}

int GPIO::unexport_gpio()
{
    string unexport_str = "/sys/class/gpio/unexport";
    ofstream unexportgpio(unexport_str.c_str());
    if (!unexportgpio.is_open()) {
        LogHighLight::Log("OPERATION FAILED:",LogHighLight::FG_RED,LogHighLight::BG_WHITE) << " ";
	LogHighLight::Log("Unable to unexport GPIO",LogHighLight::FG_YELLOW,LogHighLight::BG_BLACK) << this->gpionum;
	cout << endl;
        return -1;
    }

    unexportgpio << this->gpionum ;
    unexportgpio.close(); 
    return 0;
}

int GPIO::setdir_gpio(string dir)
{
    string setdir_str ="/sys/class/gpio/gpio" + this->gpionum + "/direction";
    ofstream setdirgpio(setdir_str.c_str());
    if (!setdirgpio.is_open()) {
        LogHighLight::Log("OPERATION FAILED:",LogHighLight::FG_RED,LogHighLight::BG_WHITE) << " ";
	LogHighLight::Log("Unable to set direction of GPIO",LogHighLight::FG_YELLOW,LogHighLight::BG_BLACK) << this->gpionum;
	cout << endl;
        return -1;
    }
    setdirgpio << dir;
    setdirgpio.close();
    return 0;
}

int GPIO::setdir_gpio(int dir)
{
    string setdir_str ="/sys/class/gpio/gpio" + this->gpionum + "/direction";
    ofstream setdirgpio(setdir_str.c_str());
    if (!setdirgpio.is_open()) {
	LogHighLight::Log("OPERATION FAILED:",LogHighLight::FG_RED,LogHighLight::BG_WHITE) << " ";
	LogHighLight::Log("Unable to set direction of GPIO",LogHighLight::FG_YELLOW,LogHighLight::BG_BLACK) << this->gpionum;
	cout << endl;
        return -1;
    }
    string _dir = "out";
    if(dir == 1) _dir = "in";
    setdirgpio << _dir;
    setdirgpio.close();
    return 0;
}

int GPIO::setval_gpio(string val)
{
    string setval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
    ofstream setvalgpio(setval_str.c_str()); 
    if (!setvalgpio.is_open()){
 	LogHighLight::Log("OPERATION FAILED:",LogHighLight::FG_RED,LogHighLight::BG_WHITE) << " ";
	LogHighLight::Log("Unable to set value of GPIO",LogHighLight::FG_YELLOW,LogHighLight::BG_BLACK) << this->gpionum;
	cout << endl;
        return -1;
    }
    setvalgpio << val ;
    setvalgpio.close();
    return 0;
}

int GPIO::setval_gpio(int val)
{
    string setval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
    ofstream setvalgpio(setval_str.c_str()); 
    if (!setvalgpio.is_open()){
	LogHighLight::Log("OPERATION FAILED:",LogHighLight::FG_RED,LogHighLight::BG_WHITE) << " ";
	LogHighLight::Log("Unable to set value of GPIO",LogHighLight::FG_YELLOW,LogHighLight::BG_BLACK) << this->gpionum;
	cout << endl;
        return -1;
    }
    setvalgpio << to_string(val);
    setvalgpio.close();
    return 0;
}

int GPIO::getval_gpio(string& val)
{
    string getval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
    ifstream getvalgpio(getval_str.c_str());
    if (!getvalgpio.is_open()){
	LogHighLight::Log("OPERATION FAILED:",LogHighLight::FG_RED,LogHighLight::BG_WHITE) << " ";
	LogHighLight::Log("Unable to get value of GPIO",LogHighLight::FG_YELLOW,LogHighLight::BG_BLACK) << this->gpionum;
	cout << endl;
        return -1;
    }
    getvalgpio >> val ;

    if(val != "0")
        val = "1";
    else
        val = "0";

    getvalgpio.close();
    return 0;
}

int GPIO::getval_gpio(int& val)
{
    string getval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
    ifstream getvalgpio(getval_str.c_str());
    if (!getvalgpio.is_open()){
	LogHighLight::Log("OPERATION FAILED:",LogHighLight::FG_RED,LogHighLight::BG_WHITE) << " ";
	LogHighLight::Log("Unable to get value of GPIO",LogHighLight::FG_YELLOW,LogHighLight::BG_BLACK) << this->gpionum;
	cout << endl;
        return -1;
    }
    string get_val;
    getvalgpio >> get_val;

    if(get_val != "0")
        val = 1;
    else
        val = 0;

    getvalgpio.close();
    return 0;
}

string GPIO::get_gpionum()
{
    return this->gpionum;
}

int GPIO::get_igpionum()
{
    return atoi(this->gpionum.c_str());
}
