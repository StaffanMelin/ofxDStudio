#include "tclap.h"

void TClap::Init(float aSampleRate)
{
	sample_rate_ = aSampleRate;

	freq_ = 1000.0f;
	amp_ = 0.8f;
	decay_ = 0.6f; // seconds
	res_ = 0.3f;
	drive_ = 0.1f;

	// source
	o_whitenoise_.Init();
	o_whitenoise_.SetAmp(amp_);
	o_filter_.Init(sample_rate_);
	o_filter_.SetFreq(freq_);
	o_filter_.SetRes(res_);
	o_filter_.SetDrive(drive_);

	// amp
    env_a_.Init(sample_rate_);
    env_a_.SetTime(daisysp::ADENV_SEG_ATTACK, 0.01f);
    env_a_.SetTime(daisysp::ADENV_SEG_DECAY, decay_);
    env_a_.SetMin(0.0);
    env_a_.SetMax(1.f);
    env_a_.SetCurve(0); // linear
}



float TClap::Process(bool aTrig)
{
	if (aTrig)
		Trig();

	o_filter_.Process(o_whitenoise_.Process());

	return (o_filter_.Band() * env_a_.Process());
}


void TClap::Trig()
{
	env_a_.Trigger();
}



void TClap::SetFreq(float aFreq)
{
	freq_ = aFreq;
	o_filter_.SetFreq(freq_);
}



void TClap::SetAmp(float aAmp)
{
	amp_ = aAmp;
	o_whitenoise_.SetAmp(amp_);
}



void TClap::SetDecay(float aDecay)
{
	decay_ = aDecay;
    env_a_.SetTime(daisysp::ADENV_SEG_DECAY, decay_);
}



void TClap::SetRes(float aRes)
{
	res_ = aRes;
	o_filter_.SetRes(res_);
}



void TClap::SetDrive(float aDrive)
{
	drive_ = aDrive;
	o_filter_.SetDrive(drive_);
}
