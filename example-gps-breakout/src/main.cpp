#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"
#include <fstream>
#include <curl/curl.h>
#include <boost/iostreams/stream.hpp>
#include "XXcurl.h"
//sample map static
//https://maps.googleapis.com/maps/api/staticmap?zoom=5&size=250x250&sensor=false&maptype=roadmap&markers=color:red|39.926586,116.405640

class noWin : public ofBaseApp{
        public:
		GPSSerial gps;
		float time,lati,longi,alti;
		string raw;

		string urlStaticMap(float latitude, float longitude, int zoom=10,
				    int w=350, int h=350, string type="roadmap", string color = "green") {
			stringstream ss;
			ss << "https://maps.googleapis.com/maps/api/staticmap?zoom=";
			ss << ofToString( zoom );
			ss << "&size="+ ofToString(w)+"x"+ofToString(h);
			ss << "&sensor=false&maptype=";
			ss << type;
			ss << "&markers=color:"+color+"|";
			ss << ofToString(latitude)+","+ofToString(longitude);
			return ss.str().c_str();
		}

		void setup(){
			gps.start("/dev/ttyAMA0",9600);
			ofHttpRequest req(urlStaticMap(39.926586,116.405640), "map");
			ofBuffer buf;
			int status=0;
			string error;
			ofHttpResponse res(req,buf,status,error);
			ofLog()<<"status:"<<status;
			ofLog()<<"error:"<<error;
			ofLog()<<"size-buffer:"<<buf.size();
		}
		
		void update(){
			time  = gps.getTime();
			lati  = gps.getLatitude();
	        	longi = gps.getLongitude();
			alti  = gps.getAltitude();
			raw   = gps.getRawData();
		}

		void draw(){
			ofBackground(100);
			ofDrawBitmapStringHighlight("Time:"+ofToString(time),10,10);
			ofDrawBitmapStringHighlight("Latitude:"+ofToString(lati),10,40);
			ofDrawBitmapStringHighlight("Longitude:"+ofToString(longi),10,80);
			ofDrawBitmapStringHighlight("Altitude:"+ofToString(alti),10,120);
			ofDrawBitmapStringHighlight("Raw Data:"+raw,10,160);
		}

		void exit(){
			gps.stop();
		}

};

int main( ){
        //ofAppNoWindow window;
	//ofSetupOpenGL(&window, 0,0, OF_WINDOW);
	ofSetupOpenGL(1024,700, OF_FULLSCREEN);
	ofRunApp( new noWin() );
}
