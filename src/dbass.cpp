#include "dstudio.h"
#include "dbass.h"

void DBass::Init(const Config& config)
{
    sample_rate_ = config.sample_rate;
    type_ = config.type;
	
	// default values
	
    vol_ = config.vol;
	
	// common
    freq_ = config.freq;
    tone_ = config.tone;
    decay_ = config.decay;
	
	// analog
    fm_attack_ = config.fm_attack;
    fm_self_ = config.fm_self;
	
	// synthetic
    dirtiness_ = config.dirtiness;
    fm_env_amount_ = config.fm_env_amount;
    fm_env_decay_ = config.fm_env_decay;
	
	// opd
    min_ = config.min;
		
	// analog
    o_bass_analog_.Init(sample_rate_);
	
	// synthetic
    o_bass_synthetic_.Init(sample_rate_);
	
	// opd
    o_tdrum_.Init(sample_rate_);

    Setup();

    SetType(PERCUSSION);
}

void DBass::Setup()
{
    o_bass_analog_.SetFreq(freq_);
    o_bass_analog_.SetTone(tone_);
    o_bass_analog_.SetDecay(decay_);
    o_bass_analog_.SetAttackFmAmount(fm_attack_);
    o_bass_analog_.SetSelfFmAmount(fm_self_);
	
	// synthetic
    o_bass_synthetic_.SetFreq(freq_);
    o_bass_synthetic_.SetTone(tone_);
//	o_bass_synthetic_.SetAccent(0.8f);
    o_bass_synthetic_.SetDecay(decay_);
    o_bass_synthetic_.SetDirtiness(dirtiness_);
    o_bass_synthetic_.SetFmEnvelopeAmount(fm_env_amount_);
    o_bass_synthetic_.SetFmEnvelopeDecay(fm_env_decay_);
	
	// opd
    o_tdrum_.SetFreq(freq_);
	//o_tdrum_.SetAmp(amp_);
    o_tdrum_.SetDecay(decay_);
    o_tdrum_.SetMin(min_);
}



void DBass::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
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
        }
        break;
    default:
        break;
    }
}



void DBass::NoteOn(uint8_t midi_velocity)
{
    vol_ = (float)midi_velocity / MIDI_VELOCITY_MAX;

    switch (type_)
	{
	case DTYPE_ANALOG:
		o_bass_analog_.Trig();
		break;
	case DTYPE_SYNTHETIC:
		o_bass_synthetic_.Trig();
		break;
	case DTYPE_OPD:
		o_tdrum_.Trig();
		break;
	}		
}



void DBass::Silence()
{
    vol_ = 0;
}



float DBass::Process()
{
	float voice_out;

    switch (type_)
	{
	case DTYPE_ANALOG:
		voice_out = o_bass_analog_.Process(false);
		break;
	case DTYPE_SYNTHETIC:
		voice_out = o_bass_synthetic_.Process(false);
		break;
	case DTYPE_OPD:
		voice_out = o_tdrum_.Process(false);
		break;
	default:
		voice_out = 0.0f;
	}		

	// out

    return (voice_out * vol_);
}



void DBass::Process(float *out_l, float *out_r)
{
    *out_l = Process();
    *out_r = *out_l;
}



void DBass::SetDType(uint8_t type)
{
    type_ = type;
}



void DBass::SetFreq(float freq)
{
    freq_ = freq;

    o_bass_analog_.SetFreq(freq_);
    o_bass_synthetic_.SetFreq(freq_);
    o_tdrum_.SetFreq(freq_);
}

void DBass::SetTone(float tone)
{
    tone_ = tone;

    o_bass_analog_.SetTone(tone_);
    o_bass_synthetic_.SetTone(tone_);
}

void DBass::SetDecay(float decay)
{
    decay_ = decay;

    o_bass_analog_.SetDecay(decay_);
    o_bass_synthetic_.SetDecay(decay_);
    o_tdrum_.SetDecay(decay_);
}

void DBass::SetFMAttack(float fm_attack)
{
    fm_attack_ = fm_attack;

    o_bass_analog_.SetAttackFmAmount(fm_attack_);
}

void DBass::SetFMSelf(float fm_self)
{
    fm_self_ = fm_self;

    o_bass_analog_.SetSelfFmAmount(fm_self_);
}

void DBass::SetDirtiness(float dirtiness)
{
    dirtiness_ = dirtiness;

    o_bass_synthetic_.SetDirtiness(dirtiness_);
}

void DBass::SetFMEnv(float fm_env_amount)
{
    fm_env_amount_ = fm_env_amount;

    o_bass_synthetic_.SetFmEnvelopeAmount(fm_env_amount_);
}

void DBass::SetFMEnvDecay(float fm_env_decay)
{
    fm_env_decay_ = fm_env_decay;

    o_bass_synthetic_.SetFmEnvelopeDecay(fm_env_decay_);
}

void DBass::SetMin(float min)
{
    min_ = min;

    o_tdrum_.SetMin(min_);
}
