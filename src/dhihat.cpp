#include "dstudio.h"
#include "dsnare.h"
#include "tdrum.h"
#include "dhihat.h"

void DHihat::Init(const Config& config)
{
	sample_rate_ = config.sample_rate;
	type_ = config.type;
	vol_ = config.vol;
	
	// common
    freq_ = config.freq;
    tone_ = config.tone;
	decay_ = config.decay;

	// analog
	// synthetic
	noisiness_ = config.noisiness;
	
	// opd
	amp_ = config.amp;
	res_ = config.res;
	drive_ = config.drive;
	
	// analog (squarenoise)
	o_hihat_analog_.Init(sample_rate_);
	
	// synthetic (ringmodnoise)
	o_hihat_synthetic_.Init(sample_rate_);
	
	// opd
	o_whitenoise_.Init();
	o_filter_.Init(sample_rate_);
    o_env_a_.Init(sample_rate_);


	Setup();

    SetType(PERCUSSION);
}

void DHihat::Setup()
{
	o_hihat_analog_.SetFreq(freq_);
	o_hihat_analog_.SetTone(tone_);
	o_hihat_analog_.SetDecay(decay_);
	o_hihat_analog_.SetNoisiness(noisiness_);
	
	// synthetic (ringmodnoise)
	o_hihat_synthetic_.SetFreq(freq_);
	o_hihat_synthetic_.SetTone(tone_);
	o_hihat_synthetic_.SetDecay(decay_);
	o_hihat_synthetic_.SetNoisiness(noisiness_);
	
	// opd
	o_whitenoise_.SetAmp(amp_);

	o_filter_.SetFreq(freq_);
	o_filter_.SetRes(res_);
	o_filter_.SetDrive(drive_);

    o_env_a_.SetTime(daisysp::ADENV_SEG_ATTACK, .01f);
    o_env_a_.SetTime(daisysp::ADENV_SEG_DECAY, decay_);
    o_env_a_.SetMin(0.0f);
    o_env_a_.SetMax(1.f);
    o_env_a_.SetCurve(0); // linear

    switch (type_)
    {
    case DTYPE_ANALOG:
        o_hihat_analog_.SetDecay(decay_);
        break;
    case DTYPE_SYNTHETIC:
        o_hihat_analog_.SetDecay(decay_);
        break;
    case DTYPE_OPD:
        o_env_a_.SetTime(daisysp::ADENV_SEG_DECAY, decay_);
        break;
    }


}



void DHihat::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
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
        case MIDI_CC_CUTOFF:
            SetTone((midi_data1 & MIDI_DATA_MASK) / (float)MIDI_DATA_MAX);
            break;
        case MIDI_CC_RESONANCE:
            SetRes((midi_data1 & MIDI_DATA_MASK) / (float)MIDI_DATA_MAX);
            break;
        }
        break;
    default:
        break;
    }
}



void DHihat::NoteOn(uint8_t midi_velocity)
{
    vol_ = (float)midi_velocity / MIDI_VELOCITY_MAX;

	switch (type_)
	{
	case DTYPE_ANALOG:
		o_hihat_analog_.Trig();
		break;
	case DTYPE_SYNTHETIC:
		o_hihat_synthetic_.Trig();
		break;
	case DTYPE_OPD:
		o_env_a_.Trigger();
		break;
    }
}



void DHihat::Silence()
{
    vol_ = 0;
}



float DHihat::Process()
{
	float voice_out;

	switch (type_)
	{
	case DTYPE_ANALOG:
		voice_out = o_hihat_analog_.Process(false);
		break;
	case DTYPE_SYNTHETIC:
		voice_out = o_hihat_synthetic_.Process(false);
		break;
	case DTYPE_OPD:
		o_filter_.Process(o_whitenoise_.Process());
		voice_out = o_filter_.High() * o_env_a_.Process();
		break;
	default:
		voice_out = 0.0f;
	}		

	return (voice_out * vol_);
}



void DHihat::Process(float *out_l, float *out_r)
{
    *out_l = Process();
    *out_r = *out_l;
}

void DHihat::SetDType(uint8_t type)
{
    type_ = type;
}

void DHihat::SetFreq(float freq)
{
	freq_ = freq;
	
	o_hihat_analog_.SetFreq(freq_);
	o_hihat_synthetic_.SetFreq(freq_);
	o_filter_.SetFreq(freq_);
}

void DHihat::SetTone(float tone)
{
	tone_ = tone;
	
	o_hihat_analog_.SetTone(tone_);
	o_hihat_synthetic_.SetTone(tone_);
}

void DHihat::SetDecay(float decay)
{
	decay_ = decay;
	
	o_hihat_analog_.SetDecay(decay_);
	o_hihat_synthetic_.SetDecay(decay_);
    o_env_a_.SetTime(daisysp::ADENV_SEG_DECAY, decay_);
}

void DHihat::SetNoisiness(float noisiness)
{
	noisiness_ = noisiness;
	
	o_hihat_analog_.SetNoisiness(noisiness_);
	o_hihat_synthetic_.SetNoisiness(noisiness_);
}

void DHihat::SetRes(float res)
{
	res_ = res;
	
	o_filter_.SetRes(res_);
}

void DHihat::SetAmp(float amp)
{
	amp_ = amp;
	
	o_whitenoise_.SetAmp(amp_);
}

void DHihat::SetDrive(float drive)
{
	drive_ = drive;
	
	o_filter_.SetDrive(drive_);
}
