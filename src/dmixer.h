#pragma once

#include "dstudio.h"
#include "dsound.h"

#include "chorus.h"
#include "reverbsc.h"

class DMixer : public DSound
{
	public:

    DMixer() {}
    ~DMixer() {}

    struct Config
    {
    	float sample_rate;
        float amp; // amplification of out signal (1.0 neutral)
        uint8_t channels; // number of channels
        DSound **synth; // array of pointers to DSound objects
        float *pan; // array of pan values; 0 = fully left, 0.5 = center, 1.0 fully right
		float *level; // array of channel levels, 0-1.0
        float *chorus_level; // array of chorus send levels, 0-1.0
        float *reverb_level; // array of reverb send levels, 0-1.0
        bool *mono; // array for booleans telling whether the channel is mono (true) or stereo (false)
        uint8_t *group; // array of group number, use for drum sounds that are exclusive like hihat open/closed which you put in the same groups
        float chorus_return; // how much of sent chorus should be added to mix (0.0 - 1.0)
        float reverb_return; // how much of sent reverb should be added to mix (0.0 - 1.0)
        float mix_dry; // how much of dry mix signal should be kept (0.0 - 1.0)
    };

	void Init(const Config&);
	void Process(float *out_l, float *out_r);
    void MidiIn(uint8_t, uint8_t, uint8_t);
    void Silence(uint8_t);
    void Silence();
    void SetPan(uint8_t, float);
    void SetLevel(uint8_t, float);
    void SetChorus(float, float, float, float, float);
    void SetChorusLevel(uint8_t, float);
    void SetReverb(float, float);
    void SetReverbLevel(uint8_t, float);
    uint8_t GetChannels();
    void SetChorusReturn(float);
    void SetReverbReturn(float);
    void SetMixDry(float);

private:

	float sample_rate_;
	uint8_t channels_;

    float amp_;
    DSound *synth_[MIXER_CHANNELS_MAX];
    float pan_[MIXER_CHANNELS_MAX];
	float level_[MIXER_CHANNELS_MAX];
    float chorus_level_[MIXER_CHANNELS_MAX];
    float reverb_level_[MIXER_CHANNELS_MAX];
    float mono_[MIXER_CHANNELS_MAX];
    uint8_t group_[MIXER_CHANNELS_MAX];
    float chorus_return_;
    float reverb_return_;
    float mix_dry_;

    daisysp::Chorus chorus_;
    float chorus_delay_;
    float chorus_feedback_;
    float chorus_lfo_depth_;
    float chorus_lfo_freq_;
    float chorus_pan_;
//    float chorus_dry_;

    daisysp::ReverbSc reverb_;
	float reverb_feedback_;
	float reverb_lpffreq_;
//	float reverb_dry_;

};
