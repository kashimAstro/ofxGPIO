#ifndef READWRITE_UTIL
    #define READWRITE_UTIL

#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS
	#include "ofMain.h"
#else
	#include <iostream>
	#include <string>
	#include <vector>
	#include <unistd.h>
	#include <fstream>
	#include <algorithm>
	#include <thread>
	#include <stdint.h> 
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <termios.h>
	#include <stdio.h>
	#include <sys/ioctl.h>
	#include <string.h>
	#include <unistd.h>
#endif

/*

   $GPBOD - Bearing, origin to destination
   $GPBWC - Bearing and distance to waypoint, great circle
   $GPGGA - Global Positioning System Fix Data
   $GPGLL - Geographic position, latitude / longitude
   $GPGSA - GPS DOP and active satellites 
   $GPGSV - GPS Satellites in view
   $GPHDT - Heading, True
   $GPR00 - List of waypoints in currently active route
   $GPRMA - Recommended minimum specific Loran-C data
   $GPRMB - Recommended minimum navigation info
   $GPRMC - Recommended minimum specific GPS/Transit data
   $GPRTE - Routes
   $GPTRF - Transit Fix Data
   $GPSTN - Multiple Data ID
   $GPVBW - Dual Ground / Water Speed
   $GPVTG - Track made good and ground speed
   $GPWPL - Waypoint location
   $GPXTE - Cross-track error, Measured
   $GPZDA - Date & Time

   $GPGGA

   Global Positioning System Fix Data

	Name	Example Data	Description
	Time		170834	17:08:34 Z
	Latitude	4124.8963, N	41d 24.8963' N or 41d 24' 54" N
	Longitude	08151.6838, W	81d 51.6838' W or 81d 51' 41" W
	Fix Quality:
		- 0 = Invalid
		- 1 = GPS fix
		- 2 = DGPS fix	1	Data is from a GPS fix
	Number of Satellites	05	5 Satellites are in view
	Horizontal Dilution of Precision (HDOP)	1.5	Relative accuracy of horizontal position
	Altitude	280.2, M	280.2 meters above mean sea level
	Height of geoid above WGS84 ellipsoid	-34.0, M	-34.0 meters
	Time since last DGPS update	blank	No last update
	DGPS reference station id	blank	No station id
	Checksum	*75	Used by program to check for transmission errors
	
*/

#ifndef COMPILE_WITHOUT_OPENFRAMEWORKS 
class GPSSerial : public ofThread {
	public:
		ofSerial serial;
	        vector<string> token;
		string rawdata;
		float latitude;
		float longitude;
		float altitude;
		float time;
		int sleep;

		double convertDegMinToDecDeg (float degMin) {
		    double min = 0.0;
		    double decDeg = 0.0;
		    min = fmod((double)degMin, 100.0);
		    degMin = (int) ( degMin / 100 );
		    decDeg = degMin + ( min / 60 );
		    return decDeg;
		}

		float getLatitude(){
			return latitude;
		}

		float getLongitude(){
			return longitude;
		}

		float getTime(){
			return longitude;
		}

		float getAltitude(){
			return altitude;
		}

		string getRawData(){
			return rawdata;
		}

		void start(string device, int baund, int _sleep=1000){
			token.push_back("$GPGGA");
		        token.push_back("$GPGSA");
		        token.push_back("$GPRMC");
		        token.push_back("$GPVTG");
		        token.push_back("$GPGLL");

			serial.setup(device,baund);
			startThread(true);
			sleep = _sleep;

		}

		void threadedFunction(){
			while(isThreadRunning()) {
			    if(serial.available()){          
				unsigned char ned[1024];
				memset(ned, 0, 1024);
				serial.readBytes(ned, 1024);
				string Data = (char*) ned;
				rawdata=Data;
                        	std::size_t found = rawdata.find(token[0]);
	                        if (found!=std::string::npos){
        	                    vector<string> data = ofSplitString(rawdata,",");
	                            if(data.size()>0){
        	                            time      = ( (data[1]  != "") ? ofToFloat(data[1]) : 0 );
	                                    latitude  = ( (data[2]  != "") ? convertDegMinToDecDeg(ofToFloat(data[2]))  : 0 );
	                                    longitude = ( (data[4]  != "") ? convertDegMinToDecDeg(ofToFloat(data[4]))  : 0 );
	                                    altitude  = ( (data[10] != "") ? convertDegMinToDecDeg(ofToFloat(data[10])) : 0 );
	                            }
	                        }
			    }
			    ofSleepMillis(sleep);
			}
		}

		void stop(){
			stopThread();
		}
};
#endif

class SerialIO {
	public:
	int baudrate;
	char type;
	char destination[2];
	char *message;
	char *localUsb;
	int fd;

	int iosetup(string serialport, int baud) 
	{
		struct termios toptions;
		fd = open(serialport.c_str(), O_RDWR | O_NOCTTY);
		if (fd == -1) {
			Log("setup: Unable to open port ",FG_RED,BG_GREEN)<<"\n";
			return -1;
		}

		if (tcgetattr(fd, &toptions) < 0) {
			Log("setup: Couldn't get term attributes",FG_RED,BG_GREEN)<<"\n";
			return -1;
		}
		speed_t brate = baud;
		switch (baud) {
		case 4800:
			brate = B4800;
			break;
		case 9600:
			brate = B9600;
			break;
		case 19200:
			brate = B19200;
			break;
		case 38400:
			brate = B38400;
			break;
		case 57600:
			brate = B57600;
			break;
		case 115200:
			brate = B115200;
			break;
		case 460800:
			brate = B460800;
			break;
		}

		cfsetispeed(&toptions, brate);
		cfsetospeed(&toptions, brate);

		toptions.c_cflag &= ~PARENB;
		toptions.c_cflag &= ~CSTOPB;
		toptions.c_cflag &= ~CSIZE;
		toptions.c_cflag |= CS8;

		toptions.c_cflag &= ~CRTSCTS;
		toptions.c_cflag |= CREAD | CLOCAL;
		toptions.c_iflag &= ~(IXON | IXOFF | IXANY);
		toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
		toptions.c_oflag &= ~OPOST;

		toptions.c_cc[VMIN] = 1;
		toptions.c_cc[VTIME] = 10;
		if (tcsetattr(fd, TCSANOW, &toptions) < 0) {
			Log("setup: Couldn't set term attributes",FG_RED,BG_GREEN)<<"\n";
			return -1;
		}
		return fd;
	}

	int iowrite(int fd, const char* str) 
	{
		int len = strlen(str);
		int n = write(fd, str, len);
		if (n != len)
			return -1;
		return n;
	}

	int iowritebyte(int fd, uint8_t b) 
	{
		int n = write(fd, &b, 1);
		if (n != 1)
			return -1;
		return 0;
	}

	int ioread_until(int fd, char buf[10][20], char until) 
	{
		char b[1];
		int i = 0, j = 0;
		do {
			do {
				int n = read(fd, b, 1);
				if (n == -1)
					return -1;
				if (n == 0) {
					usleep(10 * 1000);
					continue;
				}
				buf[j][i] = b[0];
				i++;
				if(b[0] == until)
					break;
			} while (b[0] != ',');
			buf[j][i] = 0;
			i = 0;
			j++;
		} while (b[0] != until);
		return i;
	}

	char ioread(int fd) 
	{
		char b[1];
		int n = read(fd, b, 1);
		if (n == -1){
			Log("error read serial",FG_GREEN,BG_RED)<<"\n";
		}
		return b[0];
	}

	int ioavailable(int fd) 
	{
		int nbytes = 0;
		ioctl(fd, FIONREAD, &nbytes);
		return nbytes;
	}

	void stop()
	{
		close(fd);
	}
	
};

class ReadRawData {
    public:
	vector<string> token;
	string rawdata;
	float latitude,longitude,altitude,time;
	int asleep;
	int baund;
	int fd;
	SerialIO io;

        int setup(string file, int _baundrate, int _sleep)
	{
	    asleep = _sleep;
	    baund  = _baundrate;
	    fd = io.iosetup(file,baund);

	    token.push_back("$GPGGA");
	    token.push_back("$GPGSA");
	    token.push_back("$GPRMC");
	    token.push_back("$GPVTG");
	    token.push_back("$GPGLL");
	    return fd;
        }

	double convertDegMinToDecDeg (float degMin) 
	{
	    double min = 0.0;
	    double decDeg = 0.0;
  	    min = fmod((double)degMin, 100.0);
  	    degMin = (int) ( degMin / 100 );
            decDeg = degMin + ( min / 60 );
            return decDeg;
        }
	
	float getLatitude()
	{
		return latitude;
	}

	float getLongitude()
	{
		return longitude;
	}

	float getTime()
	{
		return longitude;
	}

	float getAltitude()
	{
		return altitude;
	}

	string getRawData()
	{
		return rawdata;
	}

        void update() 
	{
                string res;
		while(1)
        	{
                	char c = 12;
	                char ok= -1;

        	        while(io.ioavailable(fd))
                	{
                        	c = io.ioread(fd);
				if(c != '\n')
				{
					res+=c;
					rawdata+=c;
				}
				else
				{
					std::size_t found = res.find(token[0]);
					if (found!=std::string::npos)
					{
					    vector<string> data = splitstring(res,",");
					    if(data.size()>0)
					    {
		                		    time      = ( (data[1]  != "") ? atof(data[1].c_str()) : 0 );
						    latitude  = ( (data[2]  != "") ? convertDegMinToDecDeg(atof(data[2].c_str()))  : 0 );
						    longitude = ( (data[4]  != "") ? convertDegMinToDecDeg(atof(data[4].c_str()))  : 0 );
						    altitude  = ( (data[10] != "") ? convertDegMinToDecDeg(atof(data[10].c_str())) : 0 );
						    /*Log(time)<<" ";
						    Log(latitude)<<" ";
						    Log(longitude)<<" ";
						    Log(altitude)<<"\n";*/
					    }
					}
					res = "";
					rawdata = "";
				}
        	        }
	        }
		sleep(asleep);
        }

	void start()
	{
		thread t1(&ReadRawData::update, this);
        	t1.join();
	}

        void close()
	{
            io.stop();
        }

	vector <string> splitstring(const string & source, const string & delimiter, bool ignoreEmpty=false) {
		vector<string> result;
		if (delimiter.empty()) {
			result.push_back(source);
			return result;
		}
		string::const_iterator substart = source.begin(), subend;
		while (true) {
			subend = std::search(substart, source.end(), delimiter.begin(), delimiter.end());
			string sub(substart, subend);
			if (!ignoreEmpty || !sub.empty()) {
				result.push_back(sub);
			}
			if (subend == source.end()) {
				break;
			}
			substart = subend + delimiter.size();
		}
		return result;
	}
};
#endif
