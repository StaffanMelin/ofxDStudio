#include "dsynthvar.h"



void DSynthVar::Init(const Config& config)
{
	sample_rate_ = config.sample_rate;
	voices_ = config.voices;
    waveshape_ = config.waveshape;
    pulsewidth_ = config.pulsewidth;
    sync_enable_ = config.sync_enable;
    sync_freq_ =  config.sync_freq;
    osc_level_ = config.osc_level;
    tune_ = config.tune;
    transpose_ = config.transpose;
    noise_level_ = config.noise_level;
    filter_type_ = config.filter_type;
	filter_cutoff_ = config.filter_cutoff;
	filter_res_ = config.filter_res;
    mod_eg_p_ = config.mod_eg_p;
    mod_eg_f_ = config.mod_eg_f;
    mod_eg_a_ = config.mod_eg_a;
    mod_filter_cutoff_ = config.mod_filter_cutoff;
    mod_waveshape_ = config.mod_waveshape;
    mod_pulsewidth_ = config.mod_pulsewidth;
    mod_sync_freq_ = config.mod_sync_freq;
    mod_delay_ = config.mod_delay;

    eg_0_level_ = config.eg_0_level;
    eg_0_attack_ = config.eg_0_attack;
    eg_0_decay_ = config.eg_0_decay;
    eg_0_sustain_ = config.eg_0_sustain;
    eg_0_release_ = config.eg_0_release;
    eg_1_level_ = config.eg_1_level;
    eg_1_attack_ = config.eg_1_attack;
    eg_1_decay_ = config.eg_1_decay;
    eg_1_sustain_ = config.eg_1_sustain;
    eg_1_release_ = config.eg_1_release;
    eg_2_level_ = config.eg_2_level;
    eg_2_attack_ = config.eg_2_attack;
    eg_2_decay_ = config.eg_2_decay;
    eg_2_sustain_ = config.eg_2_sustain;
    eg_2_release_ = config.eg_2_release;

    lfo_0_waveform_ = config.lfo_0_waveform;
    lfo_0_freq_ = config.lfo_0_freq;
    lfo_0_amp_ = config.lfo_0_amp;
    lfo_0_offset_ = config.lfo_0_offset;
    lfo_1_waveform_ = config.lfo_1_waveform;
    lfo_1_freq_ = config.lfo_1_freq;
    lfo_1_amp_ = config.lfo_1_amp;
    lfo_1_offset_ = config.lfo_1_offset;
    lfo_2_waveform_ = config.lfo_2_waveform;
    lfo_2_freq_ = config.lfo_2_freq;
    lfo_2_amp_ = config.lfo_2_amp;
    lfo_2_offset_ = config.lfo_2_offset;

    sm_0_type_ = config.sm_0_type;
    sm_0_freq_ = config.sm_0_freq;
    sm_0_amp_ = config.sm_0_amp;
    sm_0_offset_ = config.sm_0_offset;
    sm_0_seq_len_ = config.sm_0_seq_len;
    sm_0_seq_val_ = config.sm_0_seq_val;
    sm_1_type_ = config.sm_1_type;
    sm_1_freq_ = config.sm_1_freq;
    sm_1_amp_ = config.sm_1_amp;
    sm_1_offset_ = config.sm_1_offset;
    sm_1_seq_len_ = config.sm_1_seq_len;
    sm_1_seq_val_ = config.sm_1_seq_val;
    sm_2_type_ = config.sm_2_type;
    sm_2_freq_ = config.sm_2_freq;
    sm_2_amp_ = config.sm_2_amp;
    sm_2_offset_ = config.sm_2_offset;
    sm_2_seq_len_ = config.sm_2_seq_len;
    sm_2_seq_val_ = config.sm_2_seq_val;

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
	
        osc_[i].Init(sample_rate_);
        osc_[i].SetSync(sync_enable_);
        osc_[i].SetSyncFreq(sync_freq_);
        osc_[i].SetPW(pulsewidth_);
        osc_[i].SetWaveshape(waveshape_);
        osc_[i].SetFreq(440.0f + tune_);

        // EG

        eg_[i][0].Init(sample_rate_);
        eg_[i][0].SetTime(daisysp::ADSR_SEG_ATTACK, eg_0_attack_);
        eg_[i][0].SetTime(daisysp::ADSR_SEG_DECAY, eg_0_decay_);
        eg_[i][0].SetTime(daisysp::ADSR_SEG_RELEASE, eg_0_release_);
        eg_[i][0].SetSustainLevel(eg_0_sustain_);

        eg_[i][1].Init(sample_rate_);
        eg_[i][1].SetTime(daisysp::ADSR_SEG_ATTACK, eg_1_attack_);
        eg_[i][1].SetTime(daisysp::ADSR_SEG_DECAY, eg_1_decay_);
        eg_[i][1].SetTime(daisysp::ADSR_SEG_RELEASE, eg_1_release_);
        eg_[i][1].SetSustainLevel(eg_1_sustain_);

        eg_[i][2].Init(sample_rate_);
        eg_[i][2].SetTime(daisysp::ADSR_SEG_ATTACK, eg_2_attack_);
        eg_[i][2].SetTime(daisysp::ADSR_SEG_DECAY, eg_2_decay_);
        eg_[i][2].SetTime(daisysp::ADSR_SEG_RELEASE, eg_2_release_);
        eg_[i][2].SetSustainLevel(eg_2_sustain_);

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

    lfo_[0].Init(sample_rate_);
    lfo_[0].SetWaveform(lfo_0_waveform_);
    lfo_[0].SetFreq(lfo_0_freq_);
    lfo_[0].SetAmp(lfo_0_amp_);

    lfo_[1].Init(sample_rate_);
    lfo_[1].SetWaveform(lfo_1_waveform_);
    lfo_[1].SetFreq(lfo_1_freq_);
    lfo_[1].SetAmp(lfo_1_amp_);

    lfo_[2].Init(sample_rate_);
    lfo_[2].SetWaveform(lfo_2_waveform_);
    lfo_[2].SetFreq(lfo_2_freq_);
    lfo_[2].SetAmp(lfo_2_amp_);

    // sm
    DSM::Config dsm_config;
    dsm_config.sample_rate = sample_rate_;
    dsm_config.type = sm_0_type_;
    dsm_config.freq = sm_0_freq_;
    dsm_config.amp = sm_0_amp_;
    dsm_config.offset = sm_0_offset_;
    dsm_config.seq_len = sm_0_seq_len_;
    dsm_config.seq_val = sm_0_seq_val_;
    sm_[0].Init(dsm_config);

    dsm_config.type = sm_1_type_;
    dsm_config.freq = sm_1_freq_;
    dsm_config.amp = sm_1_amp_;
    dsm_config.offset = sm_1_offset_;
    dsm_config.seq_len = sm_1_seq_len_;
    dsm_config.seq_val = sm_1_seq_val_;
    sm_[1].Init(dsm_config);

    dsm_config.type = sm_2_type_;
    dsm_config.freq = sm_2_freq_;
    dsm_config.amp = sm_2_amp_;
    dsm_config.offset = sm_2_offset_;
    dsm_config.seq_len = sm_2_seq_len_;
    dsm_config.seq_val = sm_2_seq_val_;
    sm_[2].Init(dsm_config);

    // delay

    delay_.Init();
    delay_.SetDelay(sample_rate_ * delay_delay_);

    // overdrive

    overdrive_.Init();
    overdrive_.SetDrive(overdrive_drive_);

    // init
    osc_next_ = 0; // circular buffer of midi notes
    mod_value_[DSYNTHVAR_MOD_NONE] = 1.0f;

    SetType(TUNED);
}



float DSynthVar::Process()
{
    float env_a_out, env_p_out, env_f_out;
	float osc_out;
    float filter_out;
    float delay_out;

	bool note_on;
	
    // update mods: LFO
    mod_value_[DSYNTHVAR_MOD_LFO0] = lfo_[0].Process() + lfo_0_offset_;
    mod_value_[DSYNTHVAR_MOD_LFO1] = lfo_[1].Process() + lfo_1_offset_;
    mod_value_[DSYNTHVAR_MOD_LFO2] = lfo_[2].Process() + lfo_2_offset_;
    // update mods: SM
    mod_value_[DSYNTHVAR_MOD_SM0] = sm_[0].Process();
    mod_value_[DSYNTHVAR_MOD_SM1] = sm_[1].Process();
    mod_value_[DSYNTHVAR_MOD_SM2] = sm_[2].Process();

	filter_out = 0;
	for (uint8_t i = 0; i < voices_; i++)
	{
        note_on = (note_midi_[i] != 0);

        // update mods: EG
        mod_value_[DSYNTHVAR_MOD_EG0] = eg_[i][0].Process(note_on) * eg_0_level_;
        mod_value_[DSYNTHVAR_MOD_EG1] = eg_[i][1].Process(note_on) * eg_1_level_;
        mod_value_[DSYNTHVAR_MOD_EG2] = eg_[i][2].Process(note_on) * eg_2_level_;

        // amplitude
        env_a_out = mod_value_[mod_eg_a_] * note_velocity_[i];

        noise_.SetAmp(env_a_out);

        // osc - pitch
        // pitch can be affected by:
        // eg, portamento, lfo, tune, detune
        env_p_out = mod_value_[mod_eg_p_];

        // osc

        float f;
        if (portamento_ > 0)
        {
            f = port_[i].Process(note_freq_[i]) *
                            powf(2.0f,
                                 (tune_ / 1200.0 + env_p_out));
        } else {
            f = note_freq_[i]
                * powf(2.0f,
                     (tune_ / 1200.0 + env_p_out));
        }

        osc_[i].SetFreq(f);

        // mods
        if (mod_sync_freq_ != DSYNTHVAR_MOD_NONE)
        {
//            osc_[i].SetSyncFreq(sync_freq_ * (1.0f + mod_value_[mod_sync_freq_]));
            osc_[i].SetSyncFreq(sync_freq_ *
                powf(2.0f,
                     (mod_value_[mod_sync_freq_])));
        }
        if (mod_pulsewidth_ != DSYNTHVAR_MOD_NONE)
        {
            osc_[i].SetPW(pulsewidth_ * mod_value_[mod_pulsewidth_]);
        }
        if (mod_waveshape_ != DSYNTHVAR_MOD_NONE)
        {
            osc_[i].SetWaveshape(waveshape_ * mod_value_[mod_waveshape_]);
        }

        osc_out = (osc_[i].Process() * osc_level_ * env_a_out +
                noise_.Process() * noise_level_);

		// filter
        // cutoff can be affected by:
        // eg, lfo, sm
        env_f_out = mod_value_[mod_eg_f_];
        svf_[i].SetFreq(filter_cutoff_
                        * env_f_out
                        * mod_value_[mod_filter_cutoff_]);

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
        if (mod_delay_ != DSYNTHVAR_MOD_NONE)
        {
            delay_.SetDelay(sample_rate_ * delay_delay_ * mod_value_[mod_delay_]);
        }
        delay_out = delay_.Read();
        delay_.Write((filter_out + delay_out) * delay_feedback_);
        filter_out += delay_out;
    }

	// return
    return (filter_out);

}



void DSynthVar::Process(float *out_l, float *out_r)
{
    *out_l = Process();
    *out_r = *out_l;
}



void DSynthVar::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
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



void DSynthVar::NoteOn(uint8_t midi_note, uint8_t midi_velocity)
{
	osc_next_ = (osc_next_ + 1) % voices_;

    note_midi_[osc_next_] = midi_note + transpose_;
    note_freq_[osc_next_] = daisysp::mtof(note_midi_[osc_next_]);
    note_velocity_[osc_next_] = (float)midi_velocity / MIDI_VELOCITY_MAX;
    osc_[osc_next_].SetFreq(note_freq_[osc_next_] + tune_);

    if (portamento_ == 0)
    {
        eg_[osc_next_][0].Retrigger(false);
        eg_[osc_next_][1].Retrigger(false);
        eg_[osc_next_][2].Retrigger(false);
    }
}



void DSynthVar::NoteOff(uint8_t midi_note)
{
	for (uint8_t i = 0; i < voices_; i++)
	{
        if (note_midi_[i] == midi_note + transpose_)
		{
			note_midi_[i] = 0;
		}
	}
}	

void DSynthVar::Silence()
{
    for (uint8_t i = 0; i < voices_; i++)
    {
        note_midi_[i] = 0;
        note_velocity_[i] = 0;
    }
}

void DSynthVar::SetWaveshape(float waveshape)
{
    waveshape_ = waveshape;

    for (uint8_t i = 0; i < voices_; i++)
    {
        osc_[i].SetWaveshape(waveshape_);
    }
}



void DSynthVar::SetPulsewidth(float pulsewidth)
{
    pulsewidth_ = pulsewidth;
    for (uint8_t i = 0; i < voices_; i++)
    {
    osc_[i].SetPW(pulsewidth_);
    }
}



void DSynthVar::SetSync(bool sync_enable)
{
    sync_enable_ = sync_enable;

    for (uint8_t i = 0; i < voices_; i++)
    {
        osc_[i].SetSync(sync_enable_);
    }
}



void DSynthVar::SetSyncFreq(float sync_freq)
{
    sync_freq_ = sync_freq;

    for (uint8_t i = 0; i < voices_; i++)
    {
        osc_[i].SetSyncFreq(sync_freq_);
    }
}



void DSynthVar::SetTuning(float tune, float detune)
{
    tune_ = tune;
//    detune_ = detune;
}



void DSynthVar::SetTranspose(uint8_t transpose)
{
    transpose_ = transpose;
}



void DSynthVar::SetLevel(float osc_level, float noise_level)
{
    osc_level_ = osc_level;
    noise_level_ = noise_level;
}



void DSynthVar::SetFilter(FilterType filter_type, float filter_cutoff, float filter_res)
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



void DSynthVar::SetMod(uint8_t mod_eg_p, uint8_t mod_eg_f, uint8_t mod_eg_a, uint8_t mod_filter_cutoff, uint8_t mod_waveshape, uint8_t mod_pulsewidth, uint8_t mod_sync_freq, uint8_t mod_delay)
{
    mod_eg_p_ = mod_eg_p;
    mod_eg_f_ = mod_eg_f;
    mod_eg_a_ = mod_eg_a;
    mod_filter_cutoff_ = mod_filter_cutoff;
    mod_waveshape_ = mod_waveshape;
    mod_pulsewidth_ = mod_pulsewidth;
    mod_sync_freq_ = mod_sync_freq;
    mod_delay_ = mod_delay;

}



void DSynthVar::SetEGLevel(uint8_t index, float eg_level)
{
    switch (index)
    {
        case 0:
            eg_0_level_ = eg_level;
            break;
        case 1:
            eg_1_level_ = eg_level;
            break;
        case 2:
            eg_2_level_ = eg_level;
            break;
        default:
            break;
    }
}



void DSynthVar::SetEG(uint8_t index, float eg_attack, float eg_decay, float eg_sustain, float eg_release)
{
    switch (index)
    {
        case 0:
            eg_0_attack_ = eg_attack;
            eg_0_decay_ = eg_decay;
            eg_0_sustain_ = eg_sustain;
            eg_0_release_ = eg_release;
            for (uint8_t i = 0; i < voices_; i++)
            {
                eg_[i][0].SetTime(daisysp::ADSR_SEG_ATTACK, eg_0_attack_);
                eg_[i][0].SetTime(daisysp::ADSR_SEG_DECAY, eg_0_decay_);
                eg_[i][0].SetTime(daisysp::ADSR_SEG_RELEASE, eg_0_release_);
                eg_[i][0].SetSustainLevel(eg_0_sustain_);
            }
            break;
        case 1:
            eg_1_attack_ = eg_attack;
            eg_1_decay_ = eg_decay;
            eg_1_sustain_ = eg_sustain;
            eg_1_release_ = eg_release;
            for (uint8_t i = 0; i < voices_; i++)
            {
                eg_[i][1].SetTime(daisysp::ADSR_SEG_ATTACK, eg_1_attack_);
                eg_[i][1].SetTime(daisysp::ADSR_SEG_DECAY, eg_1_decay_);
                eg_[i][1].SetTime(daisysp::ADSR_SEG_RELEASE, eg_1_release_);
                eg_[i][1].SetSustainLevel(eg_1_sustain_);
            }
            break;
        case 2:
            eg_2_attack_ = eg_attack;
            eg_2_decay_ = eg_decay;
            eg_2_sustain_ = eg_sustain;
            eg_2_release_ = eg_release;
            for (uint8_t i = 0; i < voices_; i++)
            {
                eg_[i][2].SetTime(daisysp::ADSR_SEG_ATTACK, eg_2_attack_);
                eg_[i][2].SetTime(daisysp::ADSR_SEG_DECAY, eg_2_decay_);
                eg_[i][2].SetTime(daisysp::ADSR_SEG_RELEASE, eg_2_release_);
                eg_[i][2].SetSustainLevel(eg_2_sustain_);
            }
            break;
        default:
            break;
    }
}



void DSynthVar::SetLFO(uint8_t index, Waveform lfo_waveform, float lfo_freq, float lfo_amp, float lfo_offset)
{
    switch (index)
    {
    case 0:
        lfo_0_waveform_ = lfo_waveform;
        lfo_0_freq_ = lfo_freq;
        lfo_0_amp_ = lfo_amp;
        lfo_0_offset_ = lfo_offset;
        lfo_[0].SetWaveform(lfo_0_waveform_);
        lfo_[0].SetFreq(lfo_0_freq_);
        lfo_[0].SetAmp(lfo_0_amp_);
        break;
    case 1:
        lfo_1_waveform_ = lfo_waveform;
        lfo_1_freq_ = lfo_freq;
        lfo_1_amp_ = lfo_amp;
        lfo_1_offset_ = lfo_offset;
        lfo_[1].SetWaveform(lfo_1_waveform_);
        lfo_[1].SetFreq(lfo_1_freq_);
        lfo_[1].SetAmp(lfo_1_amp_);
        break;
    case 2:
        lfo_2_waveform_ = lfo_waveform;
        lfo_2_freq_ = lfo_freq;
        lfo_2_amp_ = lfo_amp;
        lfo_2_offset_ = lfo_offset;
        lfo_[2].SetWaveform(lfo_2_waveform_);
        lfo_[2].SetFreq(lfo_2_freq_);
        lfo_[2].SetAmp(lfo_2_amp_);
        break;
    default:
        break;
    }
}



void DSynthVar::SetSM(uint8_t index, uint8_t sm_type, float sm_freq, float sm_amp, float sm_offset)
{
    switch (index)
    {
    case 0:
        sm_0_type_ = sm_type;
        sm_0_freq_ = sm_freq;
        sm_0_amp_ = sm_amp;
        sm_0_offset_ = sm_offset;
        sm_[index].SetType(sm_0_type_);
        sm_[index].SetFreq(sm_0_freq_);
        sm_[index].SetAmp(sm_0_amp_);
        sm_[index].SetAmp(sm_0_offset_);
        break;
    case 1:
        sm_1_type_ = sm_type;
        sm_1_freq_ = sm_freq;
        sm_1_amp_ = sm_amp;
        sm_1_offset_ = sm_offset;
        sm_[index].SetType(sm_1_type_);
        sm_[index].SetFreq(sm_1_freq_);
        sm_[index].SetAmp(sm_1_amp_);
        sm_[index].SetAmp(sm_1_offset_);
        break;
    case 2:
        sm_2_type_ = sm_type;
        sm_2_freq_ = sm_freq;
        sm_2_amp_ = sm_amp;
        sm_2_offset_ = sm_offset;
        sm_[index].SetType(sm_2_type_);
        sm_[index].SetFreq(sm_2_freq_);
        sm_[index].SetAmp(sm_2_amp_);
        sm_[index].SetAmp(sm_2_offset_);
        break;
    default:
        break;
    }
}



void DSynthVar::SetSMSeq(uint8_t index, uint8_t seq_len, std::vector<float>& seq_val)
{
    switch (index)
    {
    case 0:
        sm_0_seq_len_ = seq_len;
        sm_0_seq_val_ = seq_val;
        sm_[0].SetSeq(sm_0_seq_len_, sm_0_seq_val_);
        break;
    case 1:
        sm_1_seq_len_ = seq_len;
        sm_1_seq_val_ = seq_val;
        sm_[1].SetSeq(sm_1_seq_len_, sm_1_seq_val_);        break;
    case 2:
        sm_2_seq_len_ = seq_len;
        sm_2_seq_val_ = seq_val;
        sm_[2].SetSeq(sm_2_seq_len_, sm_2_seq_val_);
        break;
    default:
        break;
    }
}


void DSynthVar::SetSMSeqStep(uint8_t index, uint8_t step, float val)
{
    switch (index)
    {
    case 0:
        sm_0_seq_val_[step] = val;
        sm_[0].SetSeqStep(step, val);
        break;
    case 1:
        sm_1_seq_val_[step] = val;
        sm_[1].SetSeqStep(step, val);
        break;
    case 2:
        sm_2_seq_val_[step] = val;
        sm_[2].SetSeqStep(step, val);
        break;
    default:
        break;
    }
}


void DSynthVar::SetPortamento(float portamento)
{
    portamento_ = portamento;
    for (uint8_t i = 0; i < voices_; i++)
    {
        port_[i].SetHtime(portamento_);
    }
}



void DSynthVar::SetDelay(float delay_delay, float delay_feedback)
{
    delay_delay_ = delay_delay;
    delay_feedback_ = delay_feedback;
    delay_.SetDelay(sample_rate_ * delay_delay_);
}



void DSynthVar::SetOverdrive(float overdrive_gain, float overdrive_drive)
{
    overdrive_gain_ = overdrive_gain;
    overdrive_drive_ = overdrive_drive;
    overdrive_.SetDrive(overdrive_drive_);
}
