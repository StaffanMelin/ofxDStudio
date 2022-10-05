#pragma once

#include "dstudio.h"

#include "adenv.h"
#include "svf.h"
#include "whitenoise.h"

class TClap {

public:
    void Init(float);
    float Process(bool);
    void Trig(void);
    void SetFreq(float);
    void SetRes(float);
    void SetDrive(float);
    void SetAmp(float);
    void SetDecay(float);

private:
    float sample_rate_;
    float freq_;
    float amp_;
    float decay_;
    float res_;
    float drive_;


    daisysp::WhiteNoise o_whitenoise_;
    daisysp::Svf o_filter_;
    daisysp::AdEnv env_a_;

};
