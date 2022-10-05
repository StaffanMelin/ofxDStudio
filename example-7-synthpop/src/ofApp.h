#pragma once

#include "ofMain.h"

#include "dmixer.h"

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

#include "dseqmidi.h"

class ofApp : public ofBaseApp {

private:
    DSynthSub dsynthbass1, dsynthbass2;
    DSynthVar dsynthpad;
    DSynthFm dsyntharp;
    DSynthSub dsynthlead;
    DSynthSub dsynthpiano;
    DSampler dsampler_verse, dsampler_chorus;

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

    DSeqMidi dseqmidi;


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
