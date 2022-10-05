#pragma once

#include "dstudio.h"
#include "dsound.h"
#include "tdrum.h"

class DDrum : public DSound
{

	public:

    DDrum() {}
    ~DDrum() {}

    struct Config
    {
        float sample_rate;
        float vol;

        // common
        float freq;
        float amp;
        float decay;
        float min;
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
    void SetAmp(float);
    void SetMin(float);

private:

	// config
    float sample_rate_;
    uint8_t type_;
    float vol_;

    // common
    float freq_;
    float amp_;
    float decay_;
    float min_;

	// objects
	TDrum o_tdrum_;	

};
