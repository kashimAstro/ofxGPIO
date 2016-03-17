#include "ofMain.h"

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

class ReadRawData : public ofThread {
    public:
        ifstream stream;
	vector<string> token;
	string rawdata;
	float latitude,longitude,altitude,time;
	int sleep;

        void start(string file, int _sleep){
	    sleep = _sleep;
            stream.open(file);
            if(!stream.is_open()){
                ofLog()<<"Error open file: "+file;
            }
	    token.push_back("$GPGGA");
	    token.push_back("$GPGSA");
	    token.push_back("$GPRMC");
	    token.push_back("$GPVTG");
	    token.push_back("$GPGLL");
            startThread(true, false);
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

        void threadedFunction() {
            while(isThreadRunning()) {
                string res;
                while (stream >> res) {
			rawdata=res;
			std::size_t found = res.find(token[0]);
			if (found!=std::string::npos){
			    ofLog()<<res;
			    vector<string> data = ofSplitString(res,",");
	                    time = ofToFloat(data[1]);
			    latitude = convertDegMinToDecDeg(ofToFloat(data[2]));
			    longitude = convertDegMinToDecDeg(ofToFloat(data[4]));
			    altitude = convertDegMinToDecDeg(ofToFloat(data[10]));
			}
                }
		ofSleepMillis(sleep);
            }
        }

        void stop(){
            stream.close();
            stopThread();
        }
};
