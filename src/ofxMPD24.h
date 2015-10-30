#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxOsc.h"

class ofxMPD24 : public ofBaseApp, public ofxMidiListener {
    
    public:
    
    ofxMPD24();
    ~ofxMPD24();
    
    void setup();

    void drawInterface(int x, int y);
    void drawDebug(int x, int y);
    void exit();
    
    vector<int> getControlVals();
    vector<int> getAfterTouchVals();
    vector<int> getVelocityVals();
    void setSendOsc(bool _send);
    
    ofEvent< vector<int> > mpdControlValEvent;
    ofEvent< vector<int> > mpdAfterTouchEvent;
    ofEvent< vector<int> > mpdVelocityEvent;

    void newMidiMessage(ofxMidiMessage& msg);
    
private:
    
    stringstream text;
    
    ofxMidiIn mpd24;
    ofxMidiMessage mpd24Message;
    ofxMidiMessage prevMessage;
    
    ofxOscSender sender;
    
    bool sendOsc;
    
    vector<int> controlVals;
    vector<int> prevControlVals;
    vector<int> afterTouchVals;
    vector<int> prevAfterTouchVals;
    vector<int> velocityVals;
    
    float prevSendTime;
    
    vector<int> prevVelocity;
        vector<int> prevVelocity2;
    vector <string>  oscPaths;
    
    const int mpdPressNum[32] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32}; //pressure input aftertouch
    
    const int mpdSliderLocNum[12] = {1,2,3,4,5,6}; //slider
    const int knobNum[8] = {7,8,9,10,11,12,13,14}; //knobs
    const int buttonNum[8] = {115,116,117,118,119}; //button
};