#include "ofMain.h"

class GPIOSlider 
{
	public:
        float   x;
        float   y;
        float   width;
        float   height;
        ofRectangle box;
        int     numberDisplayPrecision;
        bool    bVertical;
        bool    bDrawNumber;
        bool    bHasFocus;
        float   lowValue;
        float   highValue;
        float   percent;
        string  labelString;
        bool    bWasSetup;

	GPIOSlider(){  bWasSetup = false; 	}
	~GPIOSlider(){ clear(); }

	void setup(float inx, float iny, float inw, float inh, float loVal, float hiVal, float initialValue, bool bVert, bool bDrawNum){
		x = inx;
		y = iny; 
		width = inw; 
		height = inh;
		box.set(x,y, width, height); 
		numberDisplayPrecision = 2;
		
		bVertical = bVert;
		bDrawNumber = bDrawNum;
		bHasFocus = false;

		lowValue = loVal;
		highValue = hiVal;
		percent = ofMap(initialValue, lowValue,highValue, 0,1); 
		percent = ofClamp(percent, 0,1);
		
		labelString = ""; 
		
		if(!bWasSetup){
			//ofAddListener(ofEvents().draw, this, &GPIOSlider::draw);
			ofAddListener(ofEvents().mouseMoved, this, &GPIOSlider::mouseMoved);
			ofAddListener(ofEvents().mousePressed, this, &GPIOSlider::mousePressed);
			ofAddListener(ofEvents().mouseReleased, this, &GPIOSlider::mouseReleased);
			ofAddListener(ofEvents().mouseDragged, this, &GPIOSlider::mouseDragged);
			bWasSetup = true;
		}
	}

	void clear(){
		if(bWasSetup){
			//ofRemoveListener(ofEvents().draw, this, &ofxSimpleSlider::draw);
			ofRemoveListener(ofEvents().mouseMoved, this, &GPIOSlider::mouseMoved);
			ofRemoveListener(ofEvents().mousePressed, this, &GPIOSlider::mousePressed);
			ofRemoveListener(ofEvents().mouseReleased, this, &GPIOSlider::mouseReleased);
			ofRemoveListener(ofEvents().mouseDragged, this, &GPIOSlider::mouseDragged);
		}
		bWasSetup = false;
	}

	//----------------------------------------------------
	void setLabelString (string str){
		labelString = str;
	}


	//----------------------------------------------------
	void draw(){
		
		ofEnableAlphaBlending();
		ofDisableSmoothing();
		ofPushMatrix();
		ofTranslate(x,y,0);
		
		ofFill();
		ofSetColor(ofColor::white);
		ofDrawRectangle(-width, -height, width*3,height*3); 

		// Use different alphas if we're actively maniupulating me. 
		float sliderAlpha = (bHasFocus) ? 128:64;
		float spineAlpha  = (bHasFocus) ? 192:128;
		float thumbAlpha  = (bHasFocus) ? 255:160;
		
		// draw box outline
		ofNoFill();
		ofSetLineWidth(1.0);
		ofSetColor(64,64,64, sliderAlpha); 
		ofDrawRectangle(0,0, width,height); 
		
		// draw spine
		ofSetLineWidth(1.0);
		ofSetColor(0,0,0, spineAlpha); 
		if (bVertical){
			ofDrawLine(width/2,0, width/2,height); 
		} else {
			ofDrawLine(0,height/2, width,height/2); 
		}
		
		// draw thumb
		ofSetLineWidth(5.0);
		ofSetColor(0,0,0, thumbAlpha);
		if (bVertical){
			float thumbY = ofMap(percent, 0,1, height,0, true);
			ofDrawLine(0,thumbY, width,thumbY); 
		} else {
			float thumbX = ofMap(percent, 0,1, 0,width, true);
			ofDrawLine(thumbX,0, thumbX,height); 
		}
		
		
		
		// draw numeric value 
		if (bHasFocus){
			ofSetColor(0); 
		} else {
			ofSetColor(128); 
		}
		if (bVertical){
			ofDrawBitmapString( ofToString(getValue(),numberDisplayPrecision), width+5,height);
		} else {
			ofDrawBitmapString( ofToString(getValue(),numberDisplayPrecision), width+5,height/2 + 4);
			
			float labelStringWidth = labelString.size();
			ofDrawBitmapString( labelString, 0-labelStringWidth*8-5, height/2 + 4); 
		}	

		
		ofPopMatrix();
		ofSetLineWidth(1.0);
		ofDisableAlphaBlending();
	}

	//----------------------------------------------------
	float getValue(){
		// THIS IS THE MAIN WAY YOU GET THE VALUE FROM THE SLIDER!
		float out = ofMap(percent, 0,1, lowValue,highValue, true); 
		return out;
	}


	//----------------------------------------------------
	// Probably not used very much. 
	float getLowValue(){
		return lowValue;
	}
	float getHighValue(){
		return highValue;
	}
	float getPercent(){
		return percent;
	}

	//----------------------------------------------------
	// Probably not used very much. 
	void setLowValue(float lv){
		lowValue = lv;
	}
	void setHighValue(float hv){
		highValue = hv; 
	}
	void setPercent (float p){
		// Set the slider's percentage from the outside. 
		p = ofClamp(p, 0,1);
		percent	= p;
	}
	void setNumberDisplayPrecision(int prec){
		numberDisplayPrecision = prec;
	}
			
	//----------------------------------------------------
	void mouseMoved(ofMouseEventArgs& event){
		bHasFocus = false;
	}
	void mouseDragged(ofMouseEventArgs& event){
		if (bHasFocus){
			updatePercentFromMouse (event.x, event.y); 
		}
	}
	void mousePressed(ofMouseEventArgs& event){
		bHasFocus = false;
		if (box.inside(event.x, event.y)){
			bHasFocus = true;
			updatePercentFromMouse (event.x, event.y); 
		}
	}
	void mouseReleased(ofMouseEventArgs& event){
		if (bHasFocus){
			if (box.inside(event.x, event.y)){
				updatePercentFromMouse (event.x, event.y); 
			}
		}
		bHasFocus = false;
	}

	//----------------------------------------------------
	void updatePercentFromMouse (int mx, int my){
		// Given the mouse value, compute the percentage.
		if (bVertical){
			percent = ofMap(my, y, y+height, 1,0, true);
		} else {
			percent = ofMap(mx, x, x+width,  0,1, true);
		}
	}
};
