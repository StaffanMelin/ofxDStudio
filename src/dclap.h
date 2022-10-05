#pragma once

#include "dstudio.h"
#include "dsound.h"

#include "tclap.h"
#include "tdrum.h"
#include "tclap.h"

#include "whitenoise.h"

class DClap : public DSound
{

	public:

    DClap() {}
    ~DClap() {}

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

private:

	// config
	float sample_rate_;
	float vol_;

	// common
	float freq_;
	float res_;
	float drive_;
	float amp_;
	float decay_;	

	// objects
	TClap o_tclap_;

};

