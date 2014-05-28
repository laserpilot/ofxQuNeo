
#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofSetVerticalSync(true);
	ofBackground(255, 255, 255);
	ofSetLogLevel(OF_LOG_VERBOSE);
	
    quNeo.setup();

}

//--------------------------------------------------------------
void testApp::update() {
    
}
//--------------------------------------------------------------
void testApp::draw() {
    quNeo.drawDebug();
    quNeo.drawInterface(20, 300);
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
