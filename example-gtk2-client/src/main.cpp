#include <iostream>
#include <thread>
#include "ofxGPIO.h"

using namespace UIGpio;

UI* ui;
TCPClient tcp;
bool toggle1 = false;

void event()
{
	while(1)
	{
		_DescEvent desc = ui->getEvent();
		if(desc.type != "") 
		{
			if(desc.type == "Button" && desc.name == "ON")
			{
				tcp.Send("LEDON");
				string rec = tcp.receive();
				if( rec != "" )
				{
					cout << "Server Response:" << rec << endl;
				}
			}
			if(desc.type == "Button" && desc.name == "OFF")
			{
				tcp.Send("LEDOFF");
				string rec = tcp.receive();
				if( rec != "" )
				{
					cout << "Server Response:" << rec << endl;
				}
			}

			ui->buffer = {};
		};
		usleep(25000);
	}
}

int main(int arcg, char ** argv)
{
	tcp.setup("127.0.0.1",11999);
	thread ev(event);

	ui = new UI();
	ui->setWindowSize(300,300);
	ui->setup("LED", 2, 1);
	ui->addButton("ON",  0, 0);
	ui->addButton("OFF", 0, 1);
	ui->show();
	ev.join();

	return 0;
}
