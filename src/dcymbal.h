#pragma once

#include "dstudio.h"
#include "dsound.h"
#include "tcymbal.h"


class DCymbal : public DSound
{
	public:

    DCymbal() {}
    ~DCymbal() {}

    struct Config
    {
        float sample_rate;
        float vol;

        // common
        float freq;
        float res;
        float drive;
        float amp;
        float decay;
        float min;
        float mix;
    };

    void Init(const Config&);
    void Setup();
	float Process();
    void Process(float *, float *);
    void MidiIn(uint8_t, uint8_t, uint8_t);
    void NoteOn(uint8_t);
    void Silence();

    void SetFreq(float);
    void SetDecay(float);
    void SetRes(float);
    void SetDrive(float);
    void SetAmp(float);
    void SetMin(float);
    void SetMix(float);

private:

	// config
    float sample_rate_;
    uint8_t type_;
    float vol_;

    // common
    float freq_;
    float res_;
    float drive_;
    float amp_;
    float decay_;
    float min_;
    float mix_;

	// objects
	TCymbal o_tcymbal_;
	
};
