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

*/

class ReadRawData : public ofThread {
    public:
        ifstream stream;
	vector<string> token;

        void start(string file){
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

        void threadedFunction() {
            while(isThreadRunning()) {
                string res;
                while (stream >> res) {
			for( int i = 0; i < token.size(); i++ ){
				 std::size_t found = res.find(token[i]);
				 if (found!=std::string::npos){
				    ofLog()<< res;
				 }
			}
                }
            }
        }

        void stop(){
            stream.close();
            stopThread();
        }
};
