#include "dstudio.h"

#include "ddrum.h"
#include "tdrum.h"

void DDrum::Init(const Config& config)
{
    sample_rate_ = config.sample_rate;
	
	// common
    vol_ = config.vol;
    freq_ = config.freq;
    amp_ = config.amp;
    decay_ = config.decay;
    min_ = config.min;
	
	// analog
    o_tdrum_.Init(sample_rate_);

	Setup();

    SetType(PERCUSSION);
}



void DDrum::Setup()
{
    o_tdrum_.SetFreq(freq_);
    o_tdrum_.SetAmp(amp_);
    o_tdrum_.SetDecay(decay_);
    o_tdrum_.SetMin(min_);
}



void DDrum::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
{
    // OMNI - ignore channel
    uint8_t midi_message = midi_status & MIDI_MESSAGE_MASK;
    switch (midi_message)
    {
    case MIDI_MESSAGE_NOTEON:
        NoteOn(midi_data1 & MIDI_DATA_MASK);
        break;
    case MIDI_MESSAGE_CC:
        switch (midi_data0 & MIDI_DATA_MASK)
        {
        default:
            break;
        }
        break;
    default:
        break;
    }
}



void DDrum::NoteOn(uint8_t midi_velocity)
{
    vol_ = (float)midi_velocity / MIDI_VELOCITY_MAX;

	o_tdrum_.Trig();
}



void DDrum::Silence()
{
    vol_ = 0;
}



float DDrum::Process()
{
	float voice_out;

	voice_out = o_tdrum_.Process(false);

    return (voice_out * vol_);
}



void DDrum::Process(float *out_l, float *out_r)
{
    *out_l = Process();
    *out_r = *out_l;
}



void DDrum::SetFreq(float freq)
{
    freq_ = freq;

    o_tdrum_.SetFreq(freq_);
}

void DDrum::SetDecay(float decay)
{
    decay_ = decay;

    o_tdrum_.SetDecay(decay_);
}

void DDrum::SetAmp(float amp)
{
    amp_ = amp;

    o_tdrum_.SetAmp(amp_);
}

void DDrum::SetMin(float min)
{
    min_ = min;

    o_tdrum_.SetMin(min_);
}
