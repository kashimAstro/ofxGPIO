#include <iostream>
#include <thread>
#include "ofxGPIO.h"

using namespace UIGpio;

UI* ui;
GPIO gp;
bool toggle1 = false;

void event()
{
	while(1)
	{
		_DescEvent desc = ui->getEvent();
		if(desc.type != "") 
		{
			if(desc.type == "Toggle" && desc.name == "GPIO17")
			{
				toggle1 =! toggle1;
				gp.setval_gpio((toggle1)?HIGH:LOW);
			}
			ui->buffer = {};
		};
		usleep(25000);
	}
}

int main(int arcg, char ** argv)
{
	gp.setup(GPIO17,OUT,LOW);
	thread ev(event);

	ui = new UI();
	ui->setup("LED", 2, 1);
	ui->addToggle("GPIO17", 0, 0);
	ui->addImage("sample.jpg", 0, 1);

	ui->show();
	ev.join();

	return 0;
}
