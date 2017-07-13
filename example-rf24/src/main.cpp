#include "ofMain.h"
#include "ofxGPIO.h"
#include "rf24.h"

#define ARR_LEN 100

class ofApp : public ofBaseApp 
{
	public:
	RF24Scanner sc;
	vector<int> arr;
        int index = 0;
	ofPolyline eline;
	int w,h;

	void setup() 
	{
		sc.setup();
		arr.resize(ARR_LEN);
		w = ofGetWidth();
		h = ofGetHeight();
	}

	void draw()
	{
		ofBackground(30);
		eline.clear();
		eline.addVertex(ofVec3f(0,h/2,0));
		int k = 0;
		for( auto & d : sc.getDataChannel())
		{
			eline.addVertex(ofVec3f(k*24,(h/2)+d,0));
	                insert(d);
			k++;
		}
		eline.addVertex(ofVec3f(w,h/2,0));
		ofDrawBitmapStringHighlight("CHANNEL:",5,30,ofColor::red,ofColor::white);
                for(int j = 1; j < 15; j++)
                        ofDrawBitmapStringHighlight(ofToString(j), (j*70), 30,ofColor::red,ofColor::white);

                if(arr.size()>=ARR_LEN)
                {
                        for(int i = 0; i < arr.size(); i++)
                        {
                                ofNoFill();
                                ofSetColor(ofColor::red);
                                ofDrawRectangle(10+(i*10),160,10,arr[i]);
                                ofFill();
                                ofSetColor(arr[i] % 255,25,arr[i] % 255);
                                ofDrawRectangle(10+(i*10),160,10,arr[i]);
                        }
                }
		ofPushStyle();
                ofSetColor(ofColor::blue);
		eline.draw();
		ofPopStyle();
	}

	void insert(int value)
        {
                arr.at(index) = value;
                if (index == ARR_LEN - 1)
                        index = 0;
                else
                        index++;
        }

	void keyPressed(int key)
	{
		if(key == ' ')
			ofSaveScreen(ofToString(ofGetFrameNum())+"screen.png");
	}

	void exit()
	{
		sc.exit();
	}
};

int main()
{
        ofSetupOpenGL(1024,320, OF_WINDOW);
        ofRunApp( new ofApp());
}
