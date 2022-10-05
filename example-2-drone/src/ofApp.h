#pragma once

#include "ofMain.h"

#include "dmixer.h"
#include "dsynthsub.h"
#include "dsynthfm.h"

#define DRONES 5

class ofApp : public ofBaseApp{

private:
    DSynthSub ddrone[DRONES];

    DMixer dmixer;

    float tune[DRONES];
    float detune[DRONES];
    float cutoff[DRONES];

public:
    void setup();

    void update();
    void draw();

    void exit();

    void audioOut(ofSoundBuffer &outBuffer);

    ofSoundStream soundStream;
};
