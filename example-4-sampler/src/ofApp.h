#pragma once

#include "ofMain.h"

#include "dmixer.h"
#include "dsampler.h"
#include "dsynthvar.h"
#include "dfx.h"

#include "metro.h"

class ofApp : public ofBaseApp{

private:
    DSampler dsampler;
    DSynthVar dsynthvar;

    DFXFilter dfxfilter;
    DFXPanner dfxpanner;
    DFXSlicer dfxslicer;

    DMixer dmixer;

    // test
    uint8_t testcount = 0;
    uint8_t testnote1 = 0;
    uint8_t testnote2 = 0;
    daisysp::Metro clock;

public:
    void setup();
    void update();
    void draw();

    void exit();

    void audioOut(ofSoundBuffer &outBuffer);

    ofSoundStream soundStream;

};
