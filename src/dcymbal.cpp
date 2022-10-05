#include "dstudio.h"
#include "tcymbal.h"
#include "dcymbal.h"

void DCymbal::Init(const Config& config)
{
    sample_rate_ = config.sample_rate;
    vol_ = config.vol;
		
	// common
    freq_ = config.freq;
    res_ = config.res;
    drive_ = config.drive;
    amp_ = config.amp;
    decay_ = config.decay;
    min_ = config.min;
    mix_ = config.mix;
	
	// analog
    o_tcymbal_.Init(sample_rate_);

	Setup();

    SetType(PERCUSSION);
}



void DCymbal::Setup()
{
    o_tcymbal_.SetFreq(freq_);
    o_tcymbal_.SetRes(res_);
    o_tcymbal_.SetDrive(drive_);
    o_tcymbal_.SetAmp(amp_);
    o_tcymbal_.SetDecay(decay_);
    o_tcymbal_.SetMin(min_);
    o_tcymbal_.SetMix(mix_);
}



void DCymbal::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
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
        case MIDI_CC_RESONANCE:
            SetRes((midi_data1 & MIDI_DATA_MASK) / (float)MIDI_DATA_MAX);
            break;
        }
        break;
    default:
        break;
    }
}



void DCymbal::NoteOn(uint8_t midi_velocity)
{
    vol_ = (float)midi_velocity / MIDI_VELOCITY_MAX;
	
	o_tcymbal_.Trig();
}



void DCymbal::Silence()
{
    vol_ = 0;
}



float DCymbal::Process()
{
	float voice_out;

	voice_out = o_tcymbal_.Process(false);

    return (voice_out * vol_);
}



void DCymbal::Process(float *out_l, float *out_r)
{
    *out_l = Process();
    *out_r = *out_l;
}



void DCymbal::SetFreq(float freq)
{
    freq_ = freq;

    o_tcymbal_.SetFreq(freq_);
}



void DCymbal::SetDecay(float decay)
{
    decay_ = decay;

    o_tcymbal_.SetDecay(decay_);
}



void DCymbal::SetRes(float res)
{
    res_ = res;

    o_tcymbal_.SetRes(res_);
}



void DCymbal::SetDrive(float drive)
{
    drive_ = drive;

    o_tcymbal_.SetDrive(drive_);
}



void DCymbal::SetAmp(float amp)
{
    amp_ = amp;

    o_tcymbal_.SetAmp(amp_);
}



void DCymbal::SetMin(float min)
{
    min_ = min;

    o_tcymbal_.SetMin(min_);
}



void DCymbal::SetMix(float mix)
{
    mix_ = mix;

    o_tcymbal_.SetMix(mix_);
}
