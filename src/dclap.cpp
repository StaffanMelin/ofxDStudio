#include "dstudio.h"
#include "dsound.h"

#include "dclap.h"
#include "whitenoise.h"

void DClap::Init(const Config& config)
{
	sample_rate_ = config.sample_rate;
	vol_ = config.vol;
		
	// common
	freq_ = config.freq;
	res_ = config.res;
	drive_ = config.drive;
	amp_ = config.amp;
	decay_ = config.decay;
	
	// OPD
	o_tclap_.Init(sample_rate_);

	Setup();

    SetType(PERCUSSION);
}



void DClap::Setup()
{	o_tclap_.SetFreq(freq_);
	o_tclap_.SetRes(res_);
	o_tclap_.SetDrive(drive_);
	o_tclap_.SetAmp(amp_);
	o_tclap_.SetDecay(decay_);
}



void DClap::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
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



void DClap::NoteOn(uint8_t midi_velocity)
{
    vol_ = (float)midi_velocity / MIDI_VELOCITY_MAX;

	o_tclap_.Trig();
}



void DClap::Silence()
{
    vol_ = 0;
}



float DClap::Process()
{
	float voice_out;

	voice_out = o_tclap_.Process(false);

	return (voice_out * vol_);
}



void DClap::Process(float *out_l, float *out_r)
{
    *out_l = Process();
    *out_r = *out_l;
}



void DClap::SetFreq(float freq)
{
    freq_ = freq;

    o_tclap_.SetFreq(freq_);
}

void DClap::SetDecay(float decay)
{
    decay_ = decay;

    o_tclap_.SetDecay(decay_);
}

void DClap::SetRes(float res)
{
    res_ = res;

    o_tclap_.SetRes(res_);
}

void DClap::SetDrive(float drive)
{
    drive_ = drive;

    o_tclap_.SetDrive(drive_);
}

void DClap::SetAmp(float amp)
{
    amp_ = amp;

    o_tclap_.SetAmp(amp_);
}
