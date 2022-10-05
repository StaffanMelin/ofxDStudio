#pragma once

#include "dstudio.h"
#include "dsound.h"

#include "tdrum.h"

#include "analogsnaredrum.h"
#include "synthsnaredrum.h"
#include "whitenoise.h"

class DSnare : public DSound
{

    public:

    DSnare() {}
    ~DSnare() {}

	struct Config
	{
		float sample_rate;
		uint8_t type;
		float vol;
		
		// common
		float freq;
		float decay;
		float snappy;

		// analog
		float tone;

		// synthetic
		float fm_amount;
		
		// opd
		float amp;
		float min;
		float res;
		float drive;
		float freq_noise;
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
    void SetSnappy(float);
    void SetFM(float);
    void SetFreqNoise(float);
    void SetRes(float);
    void SetAmp(float);
    void SetDrive(float);
    void SetMin(float);

private:

	// config

	float sample_rate_;
	uint8_t type_;
	float vol_;
	
	// common
	float freq_;
	float decay_;
	float snappy_;

	// analog
	float tone_;

	// synthetic
	float fm_amount_;
	
	// opd
	float amp_;
	float min_;
	float res_;
	float drive_;
	float freq_noise_;

	// objects
    daisysp::AnalogSnareDrum o_snare_analog_;
    daisysp::SyntheticSnareDrum o_snare_synthetic_;

    daisysp::WhiteNoise o_whitenoise_;
    daisysp::Svf o_filter_;
    daisysp::AdEnv o_env_a_;
    TDrum o_tdrum_;
	
};

