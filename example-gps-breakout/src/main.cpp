#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxGPIO.h"
#include <fstream>
//sample map static
//https://maps.googleapis.com/maps/api/staticmap?zoom=5&size=250x250&sensor=false&maptype=roadmap&markers=color:red|39.926586,116.405640

class ofApp : public ofBaseApp{
        public:
		GPSSerial gps;
		GETGoogleImage maps;
		float time,lati,longi,alti;
		float tmplati,tmplongi;
		string raw;
		ofImage image;

		void setup(){
			gps.start("/dev/ttyAMA0",9600);
		}
		
		void update(){
			time  = gps.getTime();
			lati  = gps.getLatitude();
	        	longi = gps.getLongitude();
			alti  = gps.getAltitude();
			raw   = gps.getRawData();
			if( lati == tmplati && longi == tmplongi ) {
				string s = maps.request(lati,longi,10,700,700,"roadmap","orange");
				if(s!="") image.load(s);
			}
			tmplati = lati;
			tmplongi = longi;
		}

		void draw(){
			ofBackground(100);
			image.draw(100,100);
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
	ofRunApp( new ofApp() );
}
