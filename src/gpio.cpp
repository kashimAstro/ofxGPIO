#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "gpio.h"

using namespace std;

GPIO::GPIO()
{
    this->gpionum = "4";
}

GPIO::GPIO(string gnum)
{
    this->gpionum = gnum;
}

void GPIO::setup(string gnum)
{
    this->gpionum = gnum;
}

int GPIO::export_gpio()
{
    string export_str = "/sys/class/gpio/export";
    ofstream exportgpio(export_str.c_str()); 
    if (!exportgpio.is_open()) {
        cout << " OPERATION FAILED: Unable to export GPIO"<< this->gpionum <<" ."<< endl;
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
        cout << " OPERATION FAILED: Unable to unexport GPIO"<< this->gpionum <<" ."<< endl;
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
            cout << " OPERATION FAILED: Unable to set direction of GPIO"<< this->gpionum <<" ."<< endl;
            return -1;
    }
    setdirgpio << dir;
    setdirgpio.close();
    return 0;
}

int GPIO::setval_gpio(string val)
{

    string setval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
    ofstream setvalgpio(setval_str.c_str()); 
    if (!setvalgpio.is_open()){
            cout << " OPERATION FAILED: Unable to set the value of GPIO"<< this->gpionum <<" ."<< endl;
            return -1;
    }
    setvalgpio << val ;
    setvalgpio.close();
    return 0;
}

int GPIO::getval_gpio(string& val){

    string getval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
    ifstream getvalgpio(getval_str.c_str());
    if (!getvalgpio.is_open()){
        cout << " OPERATION FAILED: Unable to get value of GPIO"<< this->gpionum <<" ."<< endl;
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

string GPIO::get_gpionum(){

return this->gpionum;

}

