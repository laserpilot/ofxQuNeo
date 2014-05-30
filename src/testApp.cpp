
#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofSetVerticalSync(true);
	ofBackground(255, 255, 255);
	ofSetLogLevel(OF_LOG_VERBOSE);
	
    quNeo.setup();
    mpd24.setup();

}

//--------------------------------------------------------------
void testApp::update() {

}
//--------------------------------------------------------------
void testApp::draw() {
    ofBackgroundGradient(ofColor::white, ofColor::gray);
    //quNeo.drawDebug();
    quNeo.drawInterface(20, 80);
    mpd24.drawInterface(300, 80);
}
//--------------------------------------------------------------
void testApp::exit() {
	
}
//--------------------------------------------------------------
void testApp::keyPressed(int key) {

}
//--------------------------------------------------------------
void testApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mouseReleased() {
}
