#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	a2d.setup("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
}

//--------------------------------------------------------------
void ofApp::update(){
         data[0] = 1;
         data[1] = 0b10000000 |( ((a2dChannel & 7) << 4));
         data[2] = 0;
         a2d.readWrite(data);//sizeof(data) );
         a2dVal = 0;
         a2dVal = (data[1]<< 8) & 0b1100000000;
         a2dVal |=  (data[2] & 0xff);
         cout << "The Result is: " << a2dVal << endl;
         usleep(5000);
}

void ofApp::exit(){
	a2d.quit();
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
