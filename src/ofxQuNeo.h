#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxOsc.h"

class ofxQuNeo : public ofBaseApp, public ofxMidiListener {
    
    public:
    
        ofxQuNeo();
        ~ofxQuNeo();
        
        void setup(string name, int port);
        void setup();

        void drawInterface(int x, int y);
        void drawDebug(int x, int y);
        void setSendOsc(bool send);
        void exit();
        vector<int> getControlVals();
        vector<int> getVelocityVals();
    
        ofEvent< vector<int> > quControlValEvent;
        ofEvent< vector<int> > quVelocityEvent;

        void newMidiMessage(ofxMidiMessage& msg);
    
    private:
        bool sendOsc;
        stringstream text;
        
        ofxMidiIn quNeo;
        ofxMidiMessage quNeoMessage;
        ofxMidiMessage prevMessage;
        
        ofxOscSender sender;
        
        vector<int> controlVals;
        vector<int> prevControlVals;
        vector<int> velocityVals;
        
        float prevSendTime;
        
        vector<int> prevVelocity;

        
        //change these values if you have a different set of control/velocity numbers - this just translates your code between the two
        const int pressNum[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}; //pressure input control values
        const int xNum[16] = {17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47}; //x control num
        const int yNum[16] = {18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48}; //Y control num
        const int sliderPressNum[12] = {49,50,51,52,53,54,55,56,57,58,69}; //pressure on slider num
        const int sliderLocNum[12] = {59,60,61,62,63,64,65,66,67,68,70}; //pressure on slider num
        const int arrowPressNum[15] = {71,72,73,74,75,76,77,78,79,80,81,82,83,84,85}; //pressure on slider num
};