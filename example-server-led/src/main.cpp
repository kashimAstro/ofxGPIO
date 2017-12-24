#include <iostream>
#include <thread>
#include "ofxGPIO.h"

GPIO gp;
TCPServer tcp;

void * loop(void * m)
{
        pthread_detach(pthread_self());
	while(1)
	{
		string str = tcp.getMessage();
		if( str == "LEDON" )
		{
			cout << "led on" << endl;
			gp.setval_gpio(HIGH);
			tcp.Send("led on");
			tcp.clean();
		}
		if( str == "LEDOFF" )
		{
			cout << "led off" << endl;
			gp.setval_gpio(LOW);
			tcp.Send("led off");
			tcp.clean();
		}

		usleep(1000);
	}
	tcp.detach();
}

int main(int arcg, char ** argv)
{
	gp.setup(GPIO17,OUT,LOW);
	pthread_t msg;
	tcp.setup(11999);
	if( pthread_create(&msg, NULL, loop, (void *)0) == 0)
	{
		tcp.receive();
	}
	return 0;
}
