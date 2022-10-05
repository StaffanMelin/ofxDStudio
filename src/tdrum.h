#pragma once

#include "adenv.h"
#include "oscillator.h"

class TDrum
{

public:
	void Init(float);
	float Process(bool);
	void Trig(void);
	void SetFreq(float);
	void SetAmp(float);
	void SetDecay(float);
	void SetMin(float);

private:
	float sample_rate_;

	float freq_;
	float amp_;
	float decay_;
	float min_;

    daisysp::Oscillator osc_;
    daisysp::AdEnv env_p_;
    daisysp::AdEnv env_a_;

};

