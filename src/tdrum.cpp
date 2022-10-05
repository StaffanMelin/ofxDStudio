#include "tdrum.h"

#include "adenv.h"

void TDrum::Init(float aSampleRate)
{
	sample_rate_ = aSampleRate;

	freq_ = 150.0f;
	amp_ = 0.8f;
	decay_ = 0.4f; // seconds
	min_ = 0.3; // fraction of freq_ to reach

	// osc
    osc_.Init(sample_rate_);
    osc_.SetWaveform(osc_.WAVE_SIN);
    osc_.SetAmp(amp_);
    osc_.SetFreq(freq_);

	// amp
    env_a_.Init(sample_rate_);
    env_a_.SetTime(daisysp::ADENV_SEG_ATTACK, .01);
    env_a_.SetTime(daisysp::ADENV_SEG_DECAY, decay_);
    env_a_.SetMin(0.0);
    env_a_.SetMax(1.f);
    env_a_.SetCurve(0); // linear

	// pitch
    env_p_.Init(sample_rate_);
    env_p_.SetTime(daisysp::ADENV_SEG_ATTACK, 0.01f);
    env_p_.SetTime(daisysp::ADENV_SEG_DECAY, decay_);
    env_p_.SetMin(min_);
    env_p_.SetMax(1.f);
    env_p_.SetCurve(0); // linear

}


float TDrum::Process(bool aTrig)
{
	if (aTrig)
		Trig();

	osc_.SetFreq(freq_ * env_p_.Process());
	
	return (osc_.Process() * env_a_.Process());
}


void TDrum::Trig()
{
	env_a_.Trigger();
	env_p_.Trigger();
}



void TDrum::SetFreq(float aFreq)
{
	freq_ = aFreq;
    osc_.SetFreq(freq_);

}

void TDrum::SetAmp(float aAmp)
{
	amp_ = aAmp;
    osc_.SetAmp(amp_);
}

void TDrum::SetDecay(float aDecay)
{
	decay_ = aDecay;
    env_a_.SetTime(daisysp::ADENV_SEG_DECAY, decay_);
    env_p_.SetTime(daisysp::ADENV_SEG_DECAY, decay_);
}

void TDrum::SetMin(float aMin)
{
	min_ = aMin;
    env_p_.SetMin(min_);
}
