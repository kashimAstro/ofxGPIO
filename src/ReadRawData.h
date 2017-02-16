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

class ReadRawData {
    public:
        ifstream stream;
	vector<string> token;
	string rawdata;
	float latitude,longitude,altitude,time;
	int xsleep;

        void start(string file, int _sleep){
	    xsleep = _sleep;
            stream.open(file);
            if(!stream.is_open()){
                LogHighLight::Log("Error open file: "+file)<<"\n";
            }
	    token.push_back("$GPGGA");
	    token.push_back("$GPGSA");
	    token.push_back("$GPRMC");
	    token.push_back("$GPVTG");
	    token.push_back("$GPGLL");
        }

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

        void update() {
                string res;
		LogHighLight::Log("***************",LogHighLight::FG_WHITE,LogHighLight::BG_BLACK)<<"\n";
                while (stream >> res) {
			rawdata=res;
                        LogHighLight::Log(res,LogHighLight::FG_GREEN,LogHighLight::BG_BLUE)<<"\n";

			std::size_t found = res.find(token[0]);
			if (found!=std::string::npos){
			    vector<string> data = splitstring(res,",");
			    if(data.size()>0){
		                    time      = ( (data[1]  != "") ? atof(data[1].c_str()) : 0 );
				    latitude  = ( (data[2]  != "") ? convertDegMinToDecDeg(atof(data[2].c_str()))  : 0 );
				    longitude = ( (data[4]  != "") ? convertDegMinToDecDeg(atof(data[4].c_str()))  : 0 );
				    altitude  = ( (data[10] != "") ? convertDegMinToDecDeg(atof(data[10].c_str())) : 0 );
			    }
			}
                }
		sleep(xsleep);
        }

        void stop(){
            stream.close();
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
