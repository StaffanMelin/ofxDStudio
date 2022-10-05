#pragma once

#include "dstudio.h"
#include "dsound.h"


struct DSplitInfo
{
    uint8_t split_end;
    int8_t split_offset;
    uint8_t split_channel;
};

class DSplit : public DSound
{
	public:

    DSplit() {}
    ~DSplit() {}

    struct Config
    {
    	float sample_rate;
		uint8_t channels;
        DSound **synth;
		DSplitInfo *split;
    };

	void Init(const Config&);
	void Process(float *out_l, float *out_r);
    void MidiIn(uint8_t, uint8_t, uint8_t);
    void Silence(uint8_t);
    void Silence();
    uint8_t GetChannels();

private:

	float sample_rate_;
	uint8_t channels_;
    DSound *synth_[MIXER_CHANNELS_MAX];
	DSplitInfo split_[MIXER_CHANNELS_MAX];

};
