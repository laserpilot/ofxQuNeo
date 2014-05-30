#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxOsc.h"

class ofxMPD24 : public ofBaseApp, public ofxMidiListener {
    
    public:
    
    ofxMPD24();
    ~ofxMPD24();
    
    void setup();
    void update();
    void drawInterface(int x, int y);
    void drawDebug(int x, int y);
    void drawPad(ofPoint loc, int x, int y, int pressure);
    void drawSlider(ofPoint loc, int value, int pressure);
    void sendOsc();
    void exit();

    void newMidiMessage(ofxMidiMessage& msg);
    
    stringstream text;
    
    ofxMidiIn mpd24;
    ofxMidiMessage mpd24Message;
    ofxMidiMessage prevMessage;
    
    ofxOscSender sender;
    
    vector<int> controlVals;
    vector<int> prevControlVals;
    vector<int> afterTouchVals;
    vector<int> prevAfterTouchVals;
    vector<int> velocityVals;
    
    float prevSendTime;
    
    vector<int> prevVelocity;
    
    int zeroCount;
};