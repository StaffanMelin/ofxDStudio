#include "tcymbal.h"

void TCymbal::Init(float aSampleRate)
{
	sample_rate_ = aSampleRate;

	freq_ = 150.0f;
	amp_ = 0.8f;
	decay_ = 0.4f; // seconds
	min_ = 0.3; // fraction of freq_ to reach
	mix_ = 0.5f;
	f0_ = 2.0f * (freq_ / sample_rate_); // < 1.0f
	res_ = 0.3f;
	drive_ = 0.3f;

	// source
	o_whitenoise_.Init();
	o_whitenoise_.SetAmp(amp_);
    o_ringnoise_.Init(sample_rate_);
	o_filter_.Init(sample_rate_);
	o_filter_.SetFreq(freq_);
	o_filter_.SetRes(res_);
	o_filter_.SetDrive(drive_);

	// amp
    env_a_.Init(sample_rate_);
    env_a_.SetTime(daisysp::ADENV_SEG_ATTACK, .01);
    env_a_.SetTime(daisysp::ADENV_SEG_DECAY, decay_);
    env_a_.SetMin(0.0);
    env_a_.SetMax(1.f);
    env_a_.SetCurve(0); // linear

	// filter
    env_f_.Init(sample_rate_);
    env_f_.SetTime(daisysp::ADENV_SEG_ATTACK, 0.3f);
    env_f_.SetTime(daisysp::ADENV_SEG_DECAY, decay_);
    env_f_.SetMin(min_);
    env_f_.SetMax(1.f);
    env_f_.SetCurve(0); // linear

}



float TCymbal::Process(bool aTrig)
{
	if (aTrig)
		Trig();

	o_filter_.SetFreq(freq_ * env_f_.Process());
	o_filter_.Process(o_ringnoise_.Process(f0_) + o_whitenoise_.Process() * mix_);

	return (o_filter_.High() * env_a_.Process());
}



void TCymbal::Trig()
{
	env_a_.Trigger();
	env_f_.Trigger();
}



void TCymbal::SetFreq(float aFreq)
{
	freq_ = aFreq;
	o_filter_.SetFreq(freq_);
}



void TCymbal::SetRes(float aRes)
{
	res_ = aRes;
	o_filter_.SetRes(res_);
}



void TCymbal::SetDrive(float aDrive)
{
	drive_ = aDrive;
	o_filter_.SetDrive(drive_);
}



void TCymbal::SetAmp(float aAmp)
{
	amp_ = aAmp;
	o_whitenoise_.SetAmp(amp_);
}



void TCymbal::SetDecay(float aDecay)
{
	decay_ = aDecay;
    env_a_.SetTime(daisysp::ADENV_SEG_DECAY, decay_);
    env_f_.SetTime(daisysp::ADENV_SEG_DECAY, decay_);
}



void TCymbal::SetMin(float aMin)
{
	min_ = aMin;
    env_f_.SetMin(min_);

}



void TCymbal::SetMix(float aMix)
{
	mix_ = aMix;
}

