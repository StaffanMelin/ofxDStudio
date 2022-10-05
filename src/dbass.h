#pragma once

#include "dstudio.h"
#include "dsound.h"

#include "analogbassdrum.h"
#include "synthbassdrum.h"

#include "tdrum.h"

class DBass : public DSound
{

	public:

    DBass() {}
    ~DBass() {}

	struct Config
	{
		float sample_rate;
		uint8_t type;
		float vol;

		// common
		float freq;
		float tone;
		float decay;
		
		// analog
		float fm_attack;
		float fm_self;
		
		// synthetic
		float dirtiness;
		float fm_env_amount;
		float fm_env_decay;
		
		// opd
		float min;
	};

    void Init(const Config&);
	void Setup();
    float Process();
    void Process(float *, float *);
    void MidiIn(uint8_t, uint8_t, uint8_t);
    void NoteOn(uint8_t);
    void Silence();

    void SetDType(uint8_t);
    void SetFreq(float);
    void SetTone(float);
    void SetDecay(float);
    void SetFMAttack(float);
    void SetFMSelf(float);
    void SetDirtiness(float);
    void SetFMEnv(float);
    void SetFMEnvDecay(float);
    void SetMin(float);

private:

	// config
    float sample_rate_;
    uint8_t type_;
    float vol_;

    // common
    float freq_;
    float tone_;
    float decay_;

    // analog
    float fm_attack_;
    float fm_self_;

    // synthetic
    float dirtiness_;
    float fm_env_amount_;
    float fm_env_decay_;

    // opd
    float min_;

	// objects
    daisysp::AnalogBassDrum o_bass_analog_;
    daisysp::SyntheticBassDrum o_bass_synthetic_;
	TDrum o_tdrum_;
	
    // runtime

};
