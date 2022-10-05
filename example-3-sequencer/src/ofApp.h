#pragma once

#include "ofMain.h"

#include "dmixer.h"
#include "dsynthsub.h"
#include "dsynthfm.h"
#include "dbass.h"
#include "dsnare.h"
#include "dseqmidi.h"
#include "dfx.h"

class ofApp : public ofBaseApp{

private:
    DSynthSub dsynthbass;
    DSynthSub dsyntharp;
    DSynthFm dsynthsolo;
    DSynthSub dsynthlead;
    DBass dbass;
    DSnare dsnare;

    DFXFlanger dfxflanger;
    DFXDelay dfxdelay;
    DFXDecimator dfxdecimator;
    DFXFilter dfxfilter;

    DMixer dmixer;
    DSeqMidi dseqmidi;

public:
    void setup();

    void update();
    void draw();

    void exit();

    void audioOut(ofSoundBuffer &outBuffer);

    ofSoundStream soundStream;
};
