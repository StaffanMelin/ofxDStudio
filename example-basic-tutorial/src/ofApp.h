#pragma once

#include "ofMain.h"

#include "dsound.h"
#include "dsynthsub.h"

class ofApp : public ofBaseApp{

private:
    DSynthSub dsynthsub; // a subtractive synthesizer
    uint8_t note;

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);

    void exit();

    void audioOut(ofSoundBuffer &outBuffer);

    ofSoundStream soundStream;
};
