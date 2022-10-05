#pragma once

#include "adenv.h"
#include "hihat.h"
#include "svf.h"
#include "whitenoise.h"

class TCymbal
{

private:
	float sample_rate_;

	float freq_;
	float amp_;
	float decay_;
	float min_;
	float mix_;
	float res_;
	float drive_;


    daisysp::WhiteNoise o_whitenoise_;
    daisysp::RingModNoise o_ringnoise_;
    daisysp::Svf o_filter_;
    daisysp::AdEnv env_f_;
    daisysp::AdEnv env_a_;

	float f0_;


public:
	void Init(float);
	float Process(bool);
	void Trig(void);
	void SetFreq(float);
	void SetRes(float);
	void SetDrive(float);
	void SetAmp(float);
	void SetDecay(float);
	void SetMin(float);
	void SetMix(float);
};
