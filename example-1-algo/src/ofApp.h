#pragma once

#include "ofMain.h"

#include "dmixer.h"
#include "dsynthsub.h"
#include "dsynthfm.h"
#include "dbass.h"
#include "dhihat.h"
#include "dsnare.h"
#include "dclap.h"
#include "dcymbal.h"
#include "ddrum.h"

#include "metro.h"

class ofApp : public ofBaseApp{

private:
    DSynthSub dsynth0; // chord
    DSynthSub dsynth1; // chord
    DSynthSub dsynth2; // solo portamento
    DSynthSub dsynthb; // bass
    DSynthFm dsynthfm;

    DBass dbass;
    DSnare dsnare;
    DHihat dhihatc;
    DHihat dhihato;
    DClap dclap;
    DCymbal dcrash;
    DCymbal dride;
    DDrum dtomhi;
    DDrum dtomlo;

    DMixer dmixer;
    DMixer ddmixer;

    // test
    uint8_t testcount = 0;
    uint8_t testnote1 = 0;
    uint8_t testnote2 = 0;
    uint8_t testnote3 = 0;
    daisysp::Metro clock;

public:
    void setup();

    void update();
    void draw();

    void exit();

    void audioOut(ofSoundBuffer &outBuffer);

    ofSoundStream soundStream;

};
