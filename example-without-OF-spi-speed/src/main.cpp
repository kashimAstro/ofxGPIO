#include "ofxGPIO.h"

/*
	ofxGPIO
	speed test SPI 
*/


int main(int argc, char ** argv)
{
	if(argc < 2)
	{
		cout << "Param: device-spi" << endl;
		exit(0);
	}

	MCP a2d;
	int i,a2dVal = 0;
        unsigned char data[3];
	struct timespec start, end;
	double fq,sec,nsec,msec;

	a2d.setup(argv[1], SPI_MODE_0, 1000000, 8);

	while(i<500) {
		unsigned static int a2dChannel = 0;

	        data[0] = 1;
        	data[1] = 0b10000000 |( ((a2dChannel & 7) << 4));
	        data[2] = 0;

    		clock_gettime(CLOCK_REALTIME, &start);
        	a2d.readWrite(data);
	        a2dVal = 0;
        	a2dVal = (data[1]<< 8) & 0b1100000000;
	        a2dVal |=  (data[2] & 0xff);
        	cout << "Result channel["<< a2dChannel <<"]: " << a2dVal << "; "; 
		clock_gettime(CLOCK_REALTIME, &end);

		sec  = ((double)end.tv_sec) - ((double)start.tv_sec);
		nsec = ((double)end.tv_nsec) - ((double)start.tv_nsec);
		msec = round(nsec / 1000);
		fq   = (1.0e9 / nsec);

		cout << "Time s[ " << sec << " ] ms[ " <<  msec << " ] ns[ " << nsec << " ]; Freq Hz[ " <<  fq << " ]" << endl;

		a2dChannel++;
		if(a2dChannel >= 8) a2dChannel = 0;
		i++;
	}
	a2d.quit();

	return 0;
}
