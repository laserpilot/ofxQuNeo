#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxOsc.h"

class ofxQuNeo : public ofBaseApp, public ofxMidiListener {
    
    public:
    
    ofxQuNeo();
    ~ofxQuNeo();
    
    void setup();
    void update();
    void drawInterface(int x, int y);
    void drawDebug();
    void drawPad(ofPoint loc, int x, int y, int pressure);
    void drawSlider(ofPoint loc, int value, int pressure);
    void sendOsc();
    void exit();

    void newMidiMessage(ofxMidiMessage& msg);
    
    stringstream text;
    
    ofxMidiIn quNeo;
    ofxMidiMessage quNeoMessage;
    
    ofxOscSender sender;
    
    vector<int> controlVals;
        vector<int> velocityVals;
    
};