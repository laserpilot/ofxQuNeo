#include "ofxQuNeo.h"
int pressNum[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}; //pressure input control values
int xNum[16] = {17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47}; //x control num
int yNum[16] = {18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48}; //Y control num

ofxQuNeo::ofxQuNeo(){
    
}

ofxQuNeo::~ofxQuNeo(){
    
}

void ofxQuNeo::setup(){
    quNeo.openPort("QUNEO");
    quNeo.addListener(this);
    controlVals.assign(90, 0);
    velocityVals.assign(90, 0);
    
    sender.setup("localhost", 1234);
}

void ofxQuNeo::update(){
    
}

void ofxQuNeo::drawInterface(int x, int y){
    
    int numCols = 4;
    int numRows = 4;
    int padWidth = 50;
    int padHeight = 50;
    
    ofPushMatrix();
    ofTranslate(x,y);
    int countpos = 1;
    for(int k = 4; k>0;k--){
        for(int j = 0; j<4;j++){
            ofPushMatrix();
            ofTranslate((j*100)+50, (k*100)-50);
            
            ofSetColor(0, 0, 0);
            ofNoFill();
            ofRect(0,0,padWidth, padHeight);
            

            float xScale, yScale, pressureScale;
            pressureScale = ofMap(controlVals[pressNum[countpos-1]], 0, 127, 0, padWidth);
            xScale = ofMap(controlVals[xNum[countpos-1]], 0, 127, 0, padWidth);
            yScale = ofMap(controlVals[yNum[countpos-1]], 127, 0, 0, padHeight);
            
            
            ofSetColor(100, 100, 255);
            ofFill();
            ofRect(0,0,pressureScale, padHeight);
            
            ofFill();
            ofSetColor(0, 0, 255);
            ofRect(xScale, yScale, 5, 5);
            
            ofSetColor(0);
            ofDrawBitmapString(ofToString(countpos), 20,20);
            ofPopMatrix();
            countpos++;
        }
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofxQuNeo::newMidiMessage(ofxMidiMessage& msg){
	// make a copy of the latest message
	quNeoMessage = msg;
    
    for (int i=0; i<90; i++) {
        if (i==quNeoMessage.control) {
            controlVals[i] = quNeoMessage.value; //just make a vector of all the control vals...
            
            for (int j=0; j<16; j++){
                if (i==pressNum[j]) {
                    ofxOscMessage m;
                    m.setAddress("/quP/"+ofToString(pressNum[j]));
                    m.addIntArg(controlVals[i]);
                    sender.sendMessage(m);
                }
                if (i==xNum[j]) {
                    ofxOscMessage m;
                    m.setAddress("/quX/"+ofToString(j+1));
                    m.addIntArg(controlVals[i]);
                    sender.sendMessage(m);
                }
                if (i==yNum[j]) {
                    ofxOscMessage m;
                    m.setAddress("/quY/"+ofToString(j+1));
                    m.addIntArg(controlVals[i]);
                    sender.sendMessage(m);
                }
            }
        }
    }
    
    for (int i=0; i<90; i++) {
        if (i==quNeoMessage.pitch) {
            velocityVals[i] = quNeoMessage.velocity; //just make a vector of all the velocity vals...
        }
    }
    
    
    
    

}

void ofxQuNeo::drawDebug(){
    
    ofSetColor(0);
	
	// draw the last recieved message contents to the screen
	text << "Received: " << ofxMidiMessage::getStatusString(quNeoMessage.status);
	ofDrawBitmapString(text.str(), 20, 20);
	text.str(""); // clear
	
	text << "channel: " << quNeoMessage.channel;
	ofDrawBitmapString(text.str(), 20, 34);
	text.str(""); // clear
	
	text << "pitch: " << quNeoMessage.pitch;
	ofDrawBitmapString(text.str(), 20, 48);
	text.str(""); // clear
	ofRect(20, 58, ofMap(quNeoMessage.pitch, 0, 127, 0, ofGetWidth()-40), 20);
	
	text << "velocity: " << quNeoMessage.velocity;
	ofDrawBitmapString(text.str(), 20, 96);
	text.str(""); // clear
	ofRect(20, 105, ofMap(quNeoMessage.velocity, 0, 127, 0, ofGetWidth()-40), 20);
	
	text << "control: " << quNeoMessage.control;
	ofDrawBitmapString(text.str(), 20, 144);
	text.str(""); // clear
	ofRect(20, 154, ofMap(quNeoMessage.control, 0, 127, 0, ofGetWidth()-40), 20);
	
	text << "value: " << quNeoMessage.value;
	ofDrawBitmapString(text.str(), 20, 192);
	text.str(""); // clear

	if(quNeoMessage.status == MIDI_PITCH_BEND) {
		ofRect(20, 202, ofMap(quNeoMessage.value, 0, MIDI_MAX_BEND, 0, ofGetWidth()-40), 20);
	}
	else {
		ofRect(20, 202, ofMap(quNeoMessage.value, 0, 127, 0, ofGetWidth()-40), 20);
	}
	
	text << "delta: " << quNeoMessage.deltatime;
	ofDrawBitmapString(text.str(), 20, 240);
	text.str(""); // clear
}

void ofxQuNeo::exit(){
    quNeo.closePort();
	quNeo.removeListener(this);
}