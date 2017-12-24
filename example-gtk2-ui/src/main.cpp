#include <iostream>
#include <thread>
#include "ofxGPIO.h"

using namespace UIGpio;

UI* ui;
GPIO gp;
bool toggle;

void event()
{
	while(1)
	{
		_DescEvent desc = ui->getEvent();
		if(desc.type != "") 
		{
			if(desc.type == "Toggle" && desc.name == "GPIO (toggle) 17")
			{
				toggle =! toggle;
				gp.setval_gpio((toggle)?HIGH:LOW);
			}
			cout << "Name:  " << desc.name  << endl;
			cout << "Type:  " << desc.type  << endl;
			cout << "Value: " << desc.value << endl;
		};
		ui->buffer = {}; // fundamental clear event
		usleep(25000);
	}
}

int main(int arcg, char ** argv)
{
	toggle = false;
	ui = new UI();
	//ui->setWindowSize(200,200);
	ui->setup("ofxGPIO UI Interface", 4, 4);
	gp.setup(GPIO17,OUT,LOW);

	thread ev(event);

	ui->addButton("GPIO 1", 0, 0);
	ui->addButton("GPIO 2", 0, 1);
	ui->addButton("GPIO 3", 0, 2);
	ui->addButton("GPIO 4", 0, 3);

	ui->addToggle("GPIO (toggle) 17", 1, 0);
	ui->addToggle("GPIO (toggle) 2", 1, 1);
	ui->addCheck("GPIO (check) 1",   1, 2);
	ui->addCheck("GPIO (check) 2",   1, 3);

	ui->addSlider("LED (slider) 1", 2, 0, 0,100,1);
	ui->addSlider("LED (slider) 2", 2, 1, 0,100,1);
	ui->addInput("Input 1",         2, 2);
	ui->addInput("Input 2",         2, 3);

	vector<string> list = { "GPIO1", "GPIO2", "GPIO3" };
	ui->addList("List 1", list, 3, 0);
	ui->addImage("sample.jpg",3, 1);

	ui->show();
	ev.join();

	return 0;
}
