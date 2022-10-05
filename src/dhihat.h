#pragma once

#include "dstudio.h"
#include "dsound.h"
#include "tdrum.h"

#include "hihat.h"
#include "whitenoise.h"


class DHihat : public DSound
{

	public:

    DHihat() {}
    ~DHihat() {}
    
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
		// synthetic
		float noisiness;
		
		// opd
		float amp;
		float res; // tone?
		float drive; // noisiness_?

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
	void SetNoisiness(float);
	void SetRes(float);
	void SetAmp(float);
	void SetDrive(float);

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
	// synthetic
	float noisiness_;
	
	// opd
	float amp_;
	float res_; // tone?
	float drive_; // noisiness_?

    // objects
    daisysp::HiHat<daisysp::SquareNoise> o_hihat_analog_;
    daisysp::HiHat<daisysp::RingModNoise> o_hihat_synthetic_;
    daisysp::WhiteNoise o_whitenoise_;
    daisysp::Svf o_filter_;
    daisysp::AdEnv o_env_a_;

	// runtime	
};
