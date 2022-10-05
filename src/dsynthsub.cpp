#include "dsynthsub.h"



void DSynthSub::Init(const Config& config)
{
	sample_rate_ = config.sample_rate;
	voices_ = config.voices;
	waveform0_ = config.waveform0;
	waveform1_ = config.waveform1;
    tune_ = config.tune;
    detune_ = config.detune;
    transpose_ = config.transpose;
    osc0_level_ = config.osc0_level;
    osc1_level_ = config.osc1_level;
    noise_level_ = config.noise_level;
    filter_type_ = config.filter_type;
	filter_cutoff_ = config.filter_cutoff;
	filter_res_ = config.filter_res;
    eg_p_level_ = config.eg_p_level;
    eg_p_attack_ = config.eg_p_attack;
    eg_p_decay_ = config.eg_p_decay;
    eg_p_sustain_ = config.eg_p_sustain;
    eg_p_release_ = config.eg_p_release;
    eg_f_level_ = config.eg_f_level;
    eg_f_attack_ = config.eg_f_attack;
    eg_f_decay_ = config.eg_f_decay;
    eg_f_sustain_ = config.eg_f_sustain;
    eg_f_release_ = config.eg_f_release;
	eg_a_attack_ = config.eg_a_attack;
	eg_a_decay_ = config.eg_a_decay;
    eg_a_sustain_ = config.eg_a_sustain;
	eg_a_release_ = config.eg_a_release;
	lfo_waveform_ = config.lfo_waveform;
	lfo_freq_ = config.lfo_freq;
	lfo_amp_ = config.lfo_amp;
    lfo_p_level_ = config.lfo_p_level;
    lfo_f_level_ = config.lfo_f_level;
    lfo_a_level_ = config.lfo_a_level;
    portamento_ = config.portamento; // time in s to traverse half distance
    delay_delay_ = config.delay_delay;
    delay_feedback_ = config.delay_feedback;
    overdrive_gain_ = config.overdrive_gain;
    overdrive_drive_ = config.overdrive_drive;

    // noise, shared
    noise_.Init();

	for (uint8_t i = 0; i < voices_; i++)
	{
		// oscillators
	
		osc0_[i].Init(sample_rate_);
		osc0_[i].SetWaveform(waveform0_);
		osc0_[i].SetAmp(0.5f); // default
        osc0_[i].SetFreq(440.0f + tune_); // default

		osc1_[i].Init(sample_rate_);
		osc1_[i].SetWaveform(waveform1_);
		osc1_[i].SetAmp(0.5f); // default
        osc1_[i].SetFreq(440.0f + tune_ + detune_); // default

        // EG - pitch, filter, amplitude

        eg_p_[i].Init(sample_rate_);
        eg_p_[i].SetTime(daisysp::ADSR_SEG_ATTACK, eg_p_attack_);
        eg_p_[i].SetTime(daisysp::ADSR_SEG_DECAY, eg_p_decay_);
        eg_p_[i].SetTime(daisysp::ADSR_SEG_RELEASE, eg_p_release_);
        eg_p_[i].SetSustainLevel(eg_p_sustain_);

        eg_f_[i].Init(sample_rate_);
        eg_f_[i].SetTime(daisysp::ADSR_SEG_ATTACK, eg_f_attack_);
        eg_f_[i].SetTime(daisysp::ADSR_SEG_DECAY, eg_f_decay_);
        eg_f_[i].SetTime(daisysp::ADSR_SEG_RELEASE, eg_f_release_);
        eg_f_[i].SetSustainLevel(eg_f_sustain_);

		eg_a_[i].Init(sample_rate_);
        eg_a_[i].SetTime(daisysp::ADSR_SEG_ATTACK, eg_a_attack_);
        eg_a_[i].SetTime(daisysp::ADSR_SEG_DECAY, eg_a_decay_);
        eg_a_[i].SetTime(daisysp::ADSR_SEG_RELEASE, eg_a_release_);
		eg_a_[i].SetSustainLevel(eg_a_sustain_);

		// filter

		svf_[i].Init(sample_rate_);
		svf_[i].SetFreq(filter_cutoff_);
		svf_[i].SetRes(filter_res_);
		svf_[i].SetDrive(0.0f); // default
	
		// portamento
		
		port_[i].Init(sample_rate_, portamento_);    

        // note data
        note_midi_[i] = 0;
        note_freq_[i] = 0.0f;
        note_velocity_[i] = 0.0f;
    }

	// lfo

	lfo_.Init(sample_rate_);
	lfo_.SetWaveform(lfo_waveform_);
	lfo_.SetFreq(lfo_freq_);
	lfo_.SetAmp(lfo_amp_);

    // delay

    delay_.Init();
    delay_.SetDelay(sample_rate_ * delay_delay_);

    // overdrive

    overdrive_.Init();
    overdrive_.SetDrive(overdrive_drive_);

    // init
    osc_next_ = 0; // circular buffer of midi notes

    SetType(TUNED);
}



float DSynthSub::Process()
{
	float lfo_out;
    float env_p_out;
    float env_f_out;
    float env_a_out;
    float osc_out;
	float filter_out;
    float delay_out;

	bool note_on;
	
	// lfo + apply
	lfo_out = lfo_.Process();
	
	filter_out = 0;
	for (uint8_t i = 0; i < voices_; i++)
	{
		note_on = (note_midi_[i] != 0);

        // amplitude
        // amp can be affected by:
        // lfo, eg (always)

        env_a_out = eg_a_[i].Process(note_on) * (1 - lfo_out * lfo_a_level_);

        osc0_[i].SetAmp(env_a_out);
        osc1_[i].SetAmp(env_a_out);
        noise_.SetAmp(env_a_out);

        // osc - pitch
        // pitch can be affected by:
        // eg, portamento, lfo, tune, detune

        env_p_out = eg_p_[i].Process(note_on) * eg_p_level_;
        float f;
        if (portamento_ > 0)
		{
            f = port_[i].Process(note_freq_[i]) *
                            powf(2.0f,
                                 (tune_ / 1200.0 + lfo_out * lfo_p_level_ + env_p_out));
        } else {
            f = note_freq_[i] *
                powf(2.0f,
                     (tune_ / 1200.0 + lfo_out * lfo_p_level_ + env_p_out));
        }

        osc0_[i].SetFreq(f);
        osc1_[i].SetFreq(f * powf(2, detune_/12.0f));

        // osc

        osc_out = (osc0_[i].Process() * osc0_level_
                   + osc1_[i].Process() * osc1_level_
                   + noise_.Process() * noise_level_)
                * note_velocity_[i]; // * env_a_out;

		// filter
        // cutoff can be affected by:
        // eg, lfo
        env_f_out = eg_f_[i].Process(note_on);

        svf_[i].SetFreq(filter_cutoff_ 
                        * (1 - lfo_out * lfo_f_level_) 
                        * env_f_out * eg_f_level_ 
                        * note_velocity_[i]);

		svf_[i].Process(osc_out);
		switch (filter_type_)
		{
		case BAND:
			filter_out += svf_[i].Band();
			break;
		case HIGH:
			filter_out += svf_[i].High();
			break;
		case LOW:
			filter_out += svf_[i].Low();
			break;
		case NOTCH:
			filter_out += svf_[i].Notch();
			break;
		case PEAK:
			filter_out += svf_[i].Peak();
			break;
		default:
			filter_out += osc_out;
		}
	}
//	filter_out /= voices_;

    // overdrive
    if (overdrive_drive_ > 0.0f) {
        filter_out = overdrive_.Process(filter_out * overdrive_gain_);
    }

    // delay
    if (delay_feedback_ > 0.0f) {
        delay_out = delay_.Read();
        delay_.Write((filter_out + delay_out) * delay_feedback_);
        filter_out += delay_out;
    }
	// return
    return (filter_out);

}



void DSynthSub::Process(float *out_l, float *out_r)
{
    *out_l = Process();
    *out_r = *out_l;
}



void DSynthSub::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
{
    // OMNI - ignore channel
    uint8_t midi_message = midi_status & MIDI_MESSAGE_MASK;
    switch (midi_message)
    {
    case MIDI_MESSAGE_NOTEON:
        if ((midi_data1 & MIDI_DATA_MASK) > 0)
        {
            NoteOn(midi_data0 & MIDI_DATA_MASK, midi_data1 & MIDI_DATA_MASK);
        } else {
            NoteOff(midi_data0 & MIDI_DATA_MASK);
        }
        break;
    case MIDI_MESSAGE_NOTEOFF:
        NoteOff(midi_data0 & MIDI_DATA_MASK);
        break;
    case MIDI_MESSAGE_CC:
        switch (midi_data0 & MIDI_DATA_MASK)
        {
        case MIDI_CC_CUTOFF:
            SetFilter(filter_type_, DSTUDIO_FILTER_BASE * ((midi_data1 & MIDI_DATA_MASK) / (float)MIDI_DATA_MAX), filter_res_);
            break;
        case MIDI_CC_RESONANCE:
            SetFilter(filter_type_, filter_cutoff_, (midi_data1 & MIDI_DATA_MASK) / (float)MIDI_DATA_MAX);
            break;
        }
        break;
    default:
        break;
    }
}



void DSynthSub::NoteOn(uint8_t midi_note, uint8_t midi_velocity)
{
	osc_next_ = (osc_next_ + 1) % voices_;

    note_midi_[osc_next_] = midi_note + transpose_;
//to: osc_frequency = note_frequency * 2 ** (tuning / 1200.0 + lfo_y * lfo_mod_depth)
//    note_freq_[osc_next_] = daisysp::mtof(note_midi_[osc_next_]);
    float f = daisysp::mtof(note_midi_[osc_next_]);
    note_freq_[osc_next_] = f;
    note_velocity_[osc_next_] = (float)midi_velocity / MIDI_VELOCITY_MAX;
    osc0_[osc_next_].SetFreq(note_freq_[osc_next_] + tune_);
    osc1_[osc_next_].SetFreq(note_freq_[osc_next_] + tune_ + detune_);
//    eg_p_[osc_next_].SetSustainLevel((float)midi_velocity / MIDI_VELOCITY_MAX);
//    eg_f_[osc_next_].SetSustainLevel((float)midi_velocity / MIDI_VELOCITY_MAX);
//    eg_a_[osc_next_].SetSustainLevel((float)midi_velocity / MIDI_VELOCITY_MAX);
    if (portamento_ == 0)
    {
        eg_p_[osc_next_].Retrigger(false);
        eg_f_[osc_next_].Retrigger(false);
        eg_a_[osc_next_].Retrigger(false);
    }
}



void DSynthSub::NoteOff(uint8_t midi_note)
{
	for (uint8_t i = 0; i < voices_; i++)
	{
        if (note_midi_[i] == midi_note + transpose_)
		{
			note_midi_[i] = 0;
		}
	}
}	

void DSynthSub::Silence()
{
    for (uint8_t i = 0; i < voices_; i++)
    {
        note_midi_[i] = 0;
        note_velocity_[i] = 0;
    }
}

void DSynthSub::SetWaveform(Waveform waveform0, Waveform waveform1)
{
    waveform0_ = waveform0;
    waveform1_ = waveform1;

    for (uint8_t i = 0; i < voices_; i++)
    {
        osc0_[i].SetWaveform(waveform0_);
        osc1_[i].SetWaveform(waveform1_);
    }
}

void DSynthSub::SetTuning(float tune, float detune)
{
    tune_ = tune;
    detune_ = detune;
}



void DSynthSub::SetTranspose(uint8_t transpose)
{
    transpose_ = transpose;
}



void DSynthSub::SetLevel(float osc0_level, float osc1_level, float noise_level)
{
    osc0_level_ = osc0_level;
    osc1_level_ = osc1_level;
    noise_level_ = noise_level;
}



void DSynthSub::SetFilter(FilterType filter_type, float filter_cutoff, float filter_res)
{
    filter_type_ = filter_type;
    filter_cutoff_ = filter_cutoff;
    filter_res_ = filter_res;

    for (uint8_t i = 0; i < voices_; i++)
    {
        svf_[i].SetFreq(filter_cutoff_);
        svf_[i].SetRes(filter_res_);
    }
}



void DSynthSub::SetEGLevel(Target target, float level)
{
    switch (target)
    {
        case PITCH:
            eg_p_level_ = level;
            break;
        case FILTER:
            eg_f_level_ = level;
            break;
        default:
            break;
    }
}



void DSynthSub::SetEG(Target target, float eg_attack, float eg_decay, float eg_sustain, float eg_release)
{
    switch (target)
    {
        case PITCH:
            eg_p_attack_ = eg_attack;
            eg_p_decay_ = eg_decay;
            eg_p_sustain_ = eg_sustain;
            eg_p_release_ = eg_release;
            for (uint8_t i = 0; i < voices_; i++)
            {
                eg_p_[i].SetTime(daisysp::ADSR_SEG_ATTACK, eg_p_attack_);
                eg_p_[i].SetTime(daisysp::ADSR_SEG_DECAY, eg_p_decay_);
                eg_p_[i].SetTime(daisysp::ADSR_SEG_RELEASE, eg_p_release_);
                eg_p_[i].SetSustainLevel(eg_p_sustain_);
            }
            break;
        case FILTER:
            eg_f_attack_ = eg_attack;
            eg_f_decay_ = eg_decay;
            eg_f_sustain_ = eg_sustain;
            eg_f_release_ = eg_release;
            for (uint8_t i = 0; i < voices_; i++)
            {
                eg_f_[i].SetTime(daisysp::ADSR_SEG_ATTACK, eg_f_attack_);
                eg_f_[i].SetTime(daisysp::ADSR_SEG_DECAY, eg_f_decay_);
                eg_f_[i].SetTime(daisysp::ADSR_SEG_RELEASE, eg_f_release_);
                eg_f_[i].SetSustainLevel(eg_f_sustain_);
            }
            break;
        case AMP:
            eg_a_attack_ = eg_attack;
            eg_a_decay_ = eg_decay;
            eg_a_sustain_ = eg_sustain;
            eg_a_release_ = eg_release;
            for (uint8_t i = 0; i < voices_; i++)
            {
                eg_a_[i].SetTime(daisysp::ADSR_SEG_ATTACK, eg_a_attack_);
//                eg_a_[i].SetAttackTime(eg_a_attack_, 1.0f);
                eg_a_[i].SetTime(daisysp::ADSR_SEG_DECAY, eg_a_decay_);
                eg_a_[i].SetTime(daisysp::ADSR_SEG_RELEASE, eg_a_release_);
                eg_a_[i].SetSustainLevel(eg_a_sustain_);
            }
            break;
        default:
            break;
    }
}



void DSynthSub::SetLFO(Waveform lfo_waveform, float lfo_freq, float lfo_amp, float lfo_p_level, float lfo_f_level, float lfo_a_level)
{
    lfo_waveform_ = lfo_waveform;
    lfo_freq_ = lfo_freq;
    lfo_amp_ = lfo_amp;
    lfo_p_level_ = lfo_p_level;
    lfo_f_level_ = lfo_f_level;
    lfo_a_level_ = lfo_a_level;
    lfo_.SetWaveform(lfo_waveform_);
    lfo_.SetFreq(lfo_freq_);
    lfo_.SetAmp(lfo_amp_);
}



void DSynthSub::SetPortamento(float portamento)
{
    portamento_ = portamento;
    for (uint8_t i = 0; i < voices_; i++)
    {
        port_[i].SetHtime(portamento_);
    }
}



void DSynthSub::SetDelay(float delay_delay, float delay_feedback)
{
    delay_delay_ = delay_delay;
    delay_feedback_ = delay_feedback;
    delay_.SetDelay(sample_rate_ * delay_delay_);
}



void DSynthSub::SetOverdrive(float overdrive_gain, float overdrive_drive)
{
    overdrive_gain_ = overdrive_gain;
    overdrive_drive_ = overdrive_drive;
    overdrive_.SetDrive(overdrive_drive_);
}
