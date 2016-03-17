#include "ofMain.h"

class GETGoogleImage {
	public:
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

                string request(float latitude, float longitude, int zoom=10,
                               int w=350, int h=350, string type="roadmap", string color = "green") {

			ofBuffer buftmp;
			ofBuffer data;
                        ofHttpResponse response = ofLoadURL(urlStaticMap(latitude,longitude,zoom,w,h,type,color));
                        ofLog()<<response.status;
                        if (response.status == 200) {
                                data = response.data;
				string name = "data.png";
				if( data.size() != buftmp.size()){
	                                if( ofBufferToFile(name, data) )
                                	        ofLog(OF_LOG_NOTICE,"save file");
				}
				return name;
                        } else {
                                ofLog(OF_LOG_FATAL_ERROR, ofToString(response.status));
				return "";
                        }
			buftmp = data;
                }

};
