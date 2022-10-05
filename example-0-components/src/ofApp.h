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

//#include "dseqmidi.h"
#include "dseqperm.h"

class ofApp : public ofBaseApp {

private:
    DSynthSub dsynthsub;
    DSampler dsampler;
    DSampler dsampler2;

    DSplit dsplit;

    DFXTremolo dfxtremolo;

    DBass dbass;
    DSnare dsnare;

    DMixer dmixer;
    DMixer ddmixer;

    DSeqPerm dseqperm;


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
