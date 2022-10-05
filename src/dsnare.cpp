#include "dstudio.h"

#include "dsnare.h"
#include "tdrum.h"

void DSnare::Init(const Config& config)
{
	sample_rate_ = config.sample_rate;
	type_ = config.type;
	vol_ = config.vol;
	
	// common
	freq_ = config.freq;
	tone_ = config.tone;
	decay_ = config.decay;

	// analog
	snappy_ = config.snappy;
	
	// synthetic
    fm_amount_ = config.fm_amount;
	
	// opd
	freq_noise_ = config.freq_noise; // highpass
	amp_ = config.amp;
	res_ = config.res;
	drive_ = config.drive;
	min_ = config.min;

	// analog
	o_snare_analog_.Init(sample_rate_);
	
	// synthetic
	o_snare_synthetic_.Init(sample_rate_);
	
	// opd
	o_whitenoise_.Init();
	o_filter_.Init(sample_rate_);
    o_env_a_.Init(sample_rate_);
	o_tdrum_.Init(sample_rate_);
	
	Setup();

    SetType(PERCUSSION);
}



void DSnare::Setup()
{
	// analog
	o_snare_analog_.SetFreq(freq_);
	o_snare_analog_.SetTone(tone_);
	o_snare_analog_.SetDecay(decay_);
	o_snare_analog_.SetSnappy(snappy_);
	
	// synthetic
	o_snare_synthetic_.SetFreq(freq_);
	o_snare_synthetic_.SetDecay(decay_);
	o_snare_synthetic_.SetSnappy(snappy_);
	o_snare_synthetic_.SetFmAmount(fm_amount_);
	
	// opd
	o_whitenoise_.SetAmp(amp_);
	
	o_filter_.SetFreq(freq_noise_);
	o_filter_.SetRes(res_);
	o_filter_.SetDrive(drive_);
	
    o_env_a_.SetTime(daisysp::ADENV_SEG_ATTACK, .01);
    o_env_a_.SetTime(daisysp::ADENV_SEG_DECAY, decay_);
    o_env_a_.SetMin(0.0);
    o_env_a_.SetMax(1.f);
    o_env_a_.SetCurve(0); // linear

	o_tdrum_.SetFreq(freq_);
	o_tdrum_.SetAmp(amp_);
	o_tdrum_.SetDecay(decay_);
	o_tdrum_.SetMin(min_);
}



void DSnare::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
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



void DSnare::NoteOn(uint8_t midi_velocity)
{
    vol_ = (float)midi_velocity / MIDI_VELOCITY_MAX;

	switch (type_)
	{
	case DTYPE_ANALOG:
		o_snare_analog_.Trig();
		break;
	case DTYPE_SYNTHETIC:
		o_snare_synthetic_.Trig();
		break;
	case DTYPE_OPD:
		o_tdrum_.Trig();
		o_env_a_.Trigger();
		break;
	}		

}



void DSnare::Silence()
{
    vol_ = 0;
}



float DSnare::Process()
{
	float voice_out;

	switch (type_)
	{
	case DTYPE_ANALOG:
		voice_out = o_snare_analog_.Process(false);
		break;
	case DTYPE_SYNTHETIC:
		voice_out = o_snare_synthetic_.Process(false);
		break;
	case DTYPE_OPD:
		o_filter_.Process(o_whitenoise_.Process());
		voice_out = o_filter_.High() * o_env_a_.Process() * snappy_;
		voice_out += o_tdrum_.Process(false) * (1.0f - snappy_);
		//voice_out /= 2;
		break;
	default:
		voice_out = 0.0f;
	}		

	return (voice_out * vol_);
}



void DSnare::Process(float *out_l, float *out_r)
{
    *out_l = Process();
    *out_r = *out_l;
}



void DSnare::SetDType(uint8_t type)
{
    type_ = type;
}



void DSnare::SetFreq(float freq)
{
	freq_ = freq;
	
	o_snare_analog_.SetFreq(freq_);
	o_snare_synthetic_.SetFreq(freq_);
	o_tdrum_.SetFreq(freq_);
}

void DSnare::SetTone(float tone)
{
	tone_ = tone;
	
	o_snare_analog_.SetTone(tone_);
}

void DSnare::SetDecay(float decay)
{
	decay_ = decay;
	
	o_snare_analog_.SetDecay(decay_);
	o_snare_synthetic_.SetDecay(decay_);
    o_env_a_.SetTime(daisysp::ADENV_SEG_DECAY, decay_);
	o_tdrum_.SetDecay(decay_);
}

void DSnare::SetSnappy(float snappy)
{
	snappy_ = snappy;
	
	o_snare_analog_.SetSnappy(snappy_);
	o_snare_synthetic_.SetSnappy(snappy_);
}

void DSnare::SetFM(float fm_amount)
{
	fm_amount_ = fm_amount;
	
	o_snare_synthetic_.SetFmAmount(fm_amount_);
}

void DSnare::SetFreqNoise(float freq_noise)
{
	freq_noise_ = freq_noise;
	
	o_filter_.SetFreq(freq_noise_);
}

void DSnare::SetRes(float res)
{
	res_ = res;
	
	o_filter_.SetRes(res_);
}

void DSnare::SetAmp(float amp)
{
	amp_ = amp;
	
	o_tdrum_.SetAmp(amp_);
}

void DSnare::SetDrive(float drive)
{
	drive_ = drive;
	
	o_filter_.SetDrive(drive_);
}

void DSnare::SetMin(float min)
{
	min_ = min;
	
	o_tdrum_.SetMin(min_);
}
