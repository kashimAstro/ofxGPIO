#include <iostream>
#include <thread>
#include "ofxGPIO.h"

using namespace UIGpio;

UI* ui;

void event()
{
	while(1)
	{
                _DescEvent desc = ui->getEvent();
                if(desc.type != "")
                {
                        if(desc.type == "Toggle" && desc.name == "GPIO (toggle) 1")
                        {
                                static bool toggle = false;
                                toggle =! toggle;
                                cout << "Push Toggle: " << toggle << endl;

                        }
                        if(desc.type == "Button" && desc.name == "LED Color")
                        {
                                cout << "Push Color Picker" << endl;
                                //ui->addColorPalett("palett"); // bug
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
	vector<string> list = { "GPIO1", "GPIO2", "GPIO3" };
        vector<string> list1 = { "XXXGPIO1", "XXXGPIO2", "XXXGPIO3" };
        vector<string> list2 = { "FFFGPIO1", "FFFGPIO2", "FFFGPIO3" };

        ui = new UI();
        ui->setup("ofxGPIO UI Interface", 5, 5);
        thread ev(event);

        ui->addButton("LED Color",       0, 0);
        ui->addButton("GPIO 2",          0, 1);
        ui->addButton("GPIO 3",          0, 2);
        ui->addButton("GPIO 4",          0, 3);

        ui->addToggle("GPIO (toggle) 1", 1, 0);
        ui->addToggle("GPIO (toggle) 2", 1, 1);
        ui->addCheck("GPIO (check) 1",   1, 2);
        ui->addCheck("GPIO (check) 2",   1, 3);

        ui->addSlider("LED (slider) 1",  2, 0, 0,100,1);
        ui->addSlider("LED (slider) 2",  2, 1, 0,100,1);
        ui->addInput("Input 1",          2, 2);
        ui->addInput("Input 2",          2, 3);

        ui->addList("List 1", list,      3, 0);
        ui->addImage("sample.jpg",       3, 1);
        ui->addButtonImage("Image","button.jpg",3,2);
        ui->addButtonImage("Image","sample.jpg",3,3);

        ui->addInput("Input in 1",       0, 4);
        ui->addInput("Input in 2",       1, 4);
        ui->addInput("Input in 3",       2, 4);
        ui->addList("List 2", list1,     3, 4);

        ui->addSlider("MOTOR 1",         4, 0, 0,100,1);
        ui->addSlider("MOTOR 2",         4, 1, 0,200,1);
        ui->addSlider("MOTOR 1",         4, 2, 0,300,1);
        ui->addSlider("MOTOR 2",         4, 3, 0,400,1);
        ui->addList("List 3", list2,     4, 4);

        ui->show();
        ev.join();

	return 0;
}
