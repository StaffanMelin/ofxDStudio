#pragma once

#include "ofMain.h"

#include "dmixer.h"
#include "dsplit.h"

#include "dsynthsub.h"
#include "dsynthfm.h"
#include "dsynthvar.h"
#include "dsampler.h"

#include "dfx.h"

#include "dbass.h"
#include "dhihat.h"
#include "dsnare.h"
#include "dclap.h"
#include "dcymbal.h"
#include "ddrum.h"

#include "dseqperm.h"

#include "dgfx.h"

class ofApp : public ofBaseApp {

private:
    DSynthSub dsynthbass1;
    DSynthSub dsyntharp1;
    DSynthFm dsyntharp2;
    DSynthSub dsyntharp3;
    DSynthSub dsynthlead;
    DSynthVar dsynthpad;

    DSampler dsampler1, dsampler2, dsampler3, dsampler4;
    DSplit dsplit;

    DFXFlanger dfxflanger;
    DFXDelay dfxdelay;
    DFXDecimator dfxdecimator;
    DFXFilter dfxfilter;

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

    DSeqPerm dseqperm;

    DGFXBase dgfxbase;

public:
    void setup();

    void update();
    void draw();

    void exit();

    void audioOut(ofSoundBuffer &outBuffer);

    ofSoundStream soundStream;

};
