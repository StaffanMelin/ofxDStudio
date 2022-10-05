#pragma once

#include "ofMain.h"

#include "dmixer.h"

#include "dsynthsub.h"
#include "dsynthfm.h"
#include "dsynthvar.h"

#include "dfx.h"

#include "dgen.h"

class ofApp : public ofBaseApp {

private:
    DSynthSub dsynthbass;
    DSynthSub dsynthhi;
    DSynthSub dsynthpad;
    DSynthVar dsynthmelody;
    DSynthSub dsyntharp;
    DSynthFm dsynthembellish;
    DSynthSub dsynthfill;

    DFXFlanger dfxflanger;
    DFXFilter dfxfilter;

    DMixer dmixer;

    DGenDrone dgen;

public:
    void setup();

    void update();

    void exit();

    void audioOut(ofSoundBuffer &outBuffer);

    ofSoundStream soundStream;

};
