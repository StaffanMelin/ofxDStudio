#pragma once

#include "ofMain.h"

#include "dmixer.h"
#include "dsynthsub.h"
#include "dsynthfm.h"
#include "dsampler.h"
#include "dsynthvar.h"

#include "ofxMidi.h"

class ofApp : public ofBaseApp, public ofxMidiListener {

private:
    DSynthSub dsyntharp;
    DSynthSub dsynthpad;
    DSynthVar dsynthlead;
    DSynthFm dsynthfm;
    DSampler dsampler;
    DMixer dmixer;

public:
    void setup();
    void update();
    void draw();

    void exit();

    void audioOut(ofSoundBuffer &outBuffer);

    ofSoundStream soundStream;

    void newMidiMessage(ofxMidiMessage& eventArgs);

    ofxMidiIn midiIn;
};
