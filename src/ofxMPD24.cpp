#include "ofxMPD24.h"


ofxMPD24::ofxMPD24(){
    
}

ofxMPD24::~ofxMPD24(){
    
}

void ofxMPD24::setup(){
    mpd24.openPort("Akai MPD24");
    mpd24.addListener(this);
    controlVals.assign(127, 0);
    prevControlVals.assign(127, 0);
    velocityVals.assign(127, 0);
    prevVelocity.assign(127, 0);
    afterTouchVals.assign(127,0);
    prevAfterTouchVals.assign(127,0);
    
    sender.setup("localhost", 1273);
    
    prevSendTime = 0;
    
    sendOsc = true;
}


void ofxMPD24::drawInterface(int x, int y){
    
    int numCols = 4;
    int numRows = 4;
    int padWidth = 50;
    int padHeight = 50;
    
    ofPushStyle();


        //Draw Pads Area 1-----------------------
        ofPushMatrix();
        ofTranslate(x,y);
        int countpos = 1;
        for(int k = 4; k>0;k--){ //start in bottom left
            for(int j = 0; j<4;j++){
                ofPushMatrix();
                ofTranslate((j*55)+50, (k*55));
                
                ofSetRectMode(OF_RECTMODE_CORNER);
                ofSetColor(0, 0, 0);
                ofNoFill();
                ofRect(0,0,padWidth, padHeight);
                
                
                float xScale, yScale, pressureScale;
                pressureScale = ofMap(afterTouchVals[(countpos)], 0, 127, 0, padWidth);
                
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofSetColor(100, 100, 255);
                ofFill();
                ofRect(padWidth/2,(padWidth/2),pressureScale, pressureScale);
                
                //name of pad
                ofSetColor(0);
                ofDrawBitmapString(ofToString(countpos), 20,20);
                ofPopMatrix();
                
                countpos++;
            }
        }
      ofPopMatrix();
    
    // Draw pads area 2
    ofPushMatrix();
    ofTranslate(x+55*4+50+5, y);
        int countpos2 = 17;
        for(int k = 4; k>0;k--){ //start in bottom left
            for(int j = 0; j<4;j++){
                ofPushMatrix();
                ofTranslate((j*55)+50, (k*55));
                
                ofSetRectMode(OF_RECTMODE_CORNER);
                ofSetColor(0, 0, 0);
                ofNoFill();
                ofRect(0,0,padWidth, padHeight);
                

                float xScale, yScale, pressureScale;
                pressureScale = ofMap(afterTouchVals[(countpos2)], 0, 127, 0, padWidth);
                
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofSetColor(100, 100, 255);
                ofFill();
                ofRect(padWidth/2,(padWidth/2),pressureScale, pressureScale);
                
                ofSetRectMode(OF_RECTMODE_CORNER);
                //name of pad
                ofSetColor(0);
                ofDrawBitmapString(ofToString(countpos2), 20,20);
                ofPopMatrix();
                
                countpos2++;
            }
        }
    ofPopMatrix();

        //Draw Sliders Buttons----------------------
        ofPushMatrix();
            ofTranslate(x+50, y);
            ofDrawBitmapString("Sliders", 0,40);
            for (int i=0; i<6; i++){
                ofPushMatrix();
                ofTranslate(i*20,0);
                    ofSetRectMode(OF_RECTMODE_CENTER);
                
                    int locScale = ofMap(controlVals[mpdSliderLocNum[i]], 127, 0, 0, padHeight);
                    
                    ofNoFill();
                    ofSetColor(0, 0, 0);
                    ofRect(0,0,10, padHeight);
                ofFill();
                    ofSetColor(0, 0, 0);
                    ofRect(0, locScale-padHeight/2, 10, 3);
                ofPopMatrix();
            }
        ofPopMatrix();
    
        //Draw Knobs----------------------
        ofPushMatrix();
            ofTranslate(x+50, y+320);
            ofDrawBitmapString("Knob", 0,40);
            for (int i=0; i<8; i++){
                ofPushMatrix();
                ofTranslate(i*20,0);
                ofSetRectMode(OF_RECTMODE_CENTER);
                
                int locScale = ofMap(controlVals[knobNum[i]], 127, 0, 0, padHeight);
                
                ofNoFill();
                ofSetColor(0, 0, 0);
                ofRect(0,0,10, padHeight);
                
                ofFill();
                ofSetColor(0, 0, 0);
                ofRect(0, locScale-padHeight/2, 10, 3);
                ofPopMatrix();
            }
        ofPopMatrix();
    
        //Draw Buttons----------------------
    //These dont update because they just send 127 continuously and never get a 0 message like a velocity change
        ofPushMatrix();
        ofTranslate(x+240, y+320);
        ofDrawBitmapString("Buttons", 0,40);
        for (int i=0; i<5; i++){
            ofPushMatrix();
            ofTranslate(i*20,0);
            ofSetRectMode(OF_RECTMODE_CENTER);
            
            int locScale = ofMap(controlVals[buttonNum[i]], 127, 0, 0, padHeight);
            
            ofNoFill();
            ofSetColor(0, 0, 0);
            ofRect(0,0,10, padHeight);
            
            ofFill();
            ofSetColor(0, 0, 0);
            ofRect(0, locScale-padHeight/2, 10, 3);
            ofPopMatrix();
        }
        ofPopMatrix();
        
  
    
    ofPopStyle();
}

//--------------------------------------------------------------
void ofxMPD24::newMidiMessage(ofxMidiMessage& msg){
	// make a copy of the latest message

    mpd24Message = msg;

    
    //send velocity values
    for (int i=0; i<127; i++) { //this could be optimized...
        if (i==mpd24Message.pitch && prevVelocity[i] != mpd24Message.velocity ) {
            velocityVals[i] = mpd24Message.velocity;
            ofxOscMessage m;
            m.setAddress("/mpdVel/"+ofToString(i));
            m.addIntArg(velocityVals[i]);
            sender.sendMessage(m);
            
            prevVelocity[i] = velocityVals [i]; //we need to ignore messages with values of 0, which get sent with all the other control data, ut we need to keep at least one of them for their note-off data
        }
        
        //Todo: send all the velocity data for all of the other notes but segment them better

    }
    

    if(mpd24Message.bytes.size()>0){
        if (mpd24Message.bytes[0]==162 && mpd24Message.bytes.size()>1) { //if the first byte indicates it is aftertouch...
            //second byte is the aftertouch channel, and 3rd byte is the value
            int aTChannel, aTVal;
            aTChannel = mpd24Message.bytes[1];
            aTVal = mpd24Message.bytes[2];
            afterTouchVals[aTChannel]=aTVal;
  
            if (aTChannel==mpdPressNum[aTChannel-1] && sendOsc && prevAfterTouchVals[aTChannel] != afterTouchVals[aTChannel] ) {
                ofxOscMessage m;
                m.setAddress("/mpdP/"+ofToString(aTChannel));
                m.addIntArg(afterTouchVals[aTChannel]);
                sender.sendMessage(m);
            }
        }
    }
    
    prevAfterTouchVals = afterTouchVals;

    for (int i=0; i<127; i++) {
    
        
        if (i==mpd24Message.control) {
            controlVals[i] = mpd24Message.value; //just make a vector of all the control vals...
            
            if (prevSendTime+0.002 < ofGetElapsedTimef() && controlVals[i]!=prevControlVals[i] && sendOsc) { //need to rate limit incoming data before sending over osc - but we need to keep values that are equal to 0
                
                //Send Pad info over OSC
                for (int j=0; j<16; j++){
                    if (i==mpdPressNum[j]) {
                        ofxOscMessage m;
                        m.setAddress("/mpdP/"+ofToString(j+1));
                        m.addIntArg(controlVals[i]);
                        sender.sendMessage(m);
                    }
                }
                
                //send sliders
                for (int j=0; j<6; j++){
                    if(i==mpdSliderLocNum[j]){
                        ofxOscMessage m;
                        m.setAddress("/mpdSlide/"+ofToString(j+1));
                        m.addIntArg(controlVals[i]);
                        sender.sendMessage(m);
                    }
                }
                
                //send arrow pressure data
                for (int j=0; j<8; j++){
                    if (i==knobNum[j]) {
                        ofxOscMessage m;
                        m.setAddress("/mpdKnob/"+ofToString(j+1));
                        m.addIntArg(controlVals[i]);
                        sender.sendMessage(m);
                    }
                }
                prevControlVals = controlVals;
                prevSendTime = ofGetElapsedTimef();
            
            }
        }
    }
    
    //sends events out with a vector of values
    //To decode you would just look for the specified control value 0-127,and stored in that position in the array would be the value for that control channel
    //ie button pad 1 is control channel 1. you would do changingVal = controlVal[1]
    //these could be integrated better to disable false positives, but this works for now
    ofNotifyEvent(mpdControlValEvent, controlVals, this);
    ofNotifyEvent(mpdVelocityEvent, velocityVals, this);
    ofNotifyEvent(mpdAfterTouchEvent, afterTouchVals, this);
    

}

void ofxMPD24::drawDebug(int x, int y){
    
    ofPushMatrix();
    ofTranslate(x, y);
    
    ofSetColor(0);
	
	// draw the last recieved message contents to the screen
	text << "Received: " << ofxMidiMessage::getStatusString(mpd24Message.status);
	ofDrawBitmapString(text.str(), 20, 20);
	text.str(""); // clear
	
	text << "channel: " << mpd24Message.channel;
	ofDrawBitmapString(text.str(), 20, 34);
	text.str(""); // clear
	
	text << "pitch: " << mpd24Message.pitch;
	ofDrawBitmapString(text.str(), 20, 48);
	text.str(""); // clear
	ofRect(20, 58, ofMap(mpd24Message.pitch, 0, 127, 0, ofGetWidth()-40), 20);
	
	text << "velocity: " << mpd24Message.velocity;
	ofDrawBitmapString(text.str(), 20, 96);
	text.str(""); // clear
	ofRect(20, 105, ofMap(mpd24Message.velocity, 0, 127, 0, ofGetWidth()-40), 20);
	
	text << "control: " << mpd24Message.control;
	ofDrawBitmapString(text.str(), 20, 144);
	text.str(""); // clear
	ofRect(20, 154, ofMap(mpd24Message.control, 0, 127, 0, ofGetWidth()-40), 20);
	
	text << "value: " << mpd24Message.value;
	ofDrawBitmapString(text.str(), 20, 192);
	text.str(""); // clear

	text << "delta: " << mpd24Message.deltatime;
	ofDrawBitmapString(text.str(), 20, 240);
	text.str(""); // clear
    
    ofPopMatrix();
}

vector <int> ofxMPD24::getControlVals(){
    return controlVals;
}
vector <int> ofxMPD24::getVelocityVals(){
    return velocityVals;
}
vector <int> ofxMPD24::getAfterTouchVals(){
    return afterTouchVals;
}

void ofxMPD24::setSendOsc(bool _send){
    sendOsc = _send;
}

void ofxMPD24::exit(){
    mpd24.closePort();
	mpd24.removeListener(this);
}