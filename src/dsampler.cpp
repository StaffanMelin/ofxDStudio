#include <string>

#include "dsampler.h"

void DSampler::Init(const Config& config)
{

    sample_rate_ = config.sample_rate;
    voices_ = config.voices;
    tune_ = config.tune;
    transpose_ = config.transpose;
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
    loop_ = config.loop;
    sample_file_name_ = config.sample_file_name;
    sample_phase_start_ = config.sample_phase_start;
    sample_phase_loop_start_ = config.sample_phase_loop_start;
    sample_phase_loop_end_ = config.sample_phase_loop_end;
    sample_phase_end_ = config.sample_phase_end;
    sample_length_ = config.sample_length; // length of sample, < BUFFER_MAX
    sample_channels_ = config.sample_channels;

    for (uint8_t i = 0; i < voices_; i++)
    {
        // oscillators
        // samples
        sample_index_[i] = 0.0f;
        sample_index_factor_[0] = 1.0f;
        note_midi_[i] = 0;
        note_freq_[i] = 0;

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

        svf_l_[i].Init(sample_rate_);
        svf_l_[i].SetFreq(filter_cutoff_);
        svf_l_[i].SetRes(filter_res_);
        svf_l_[i].SetDrive(0.0f); // default
        svf_r_[i].Init(sample_rate_);
        svf_r_[i].SetFreq(filter_cutoff_);
        svf_r_[i].SetRes(filter_res_);
        svf_r_[i].SetDrive(0.0f); // default

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

    delay_l_.Init();
    delay_l_.SetDelay(sample_rate_ * delay_delay_);
    delay_r_.Init();
    delay_r_.SetDelay(sample_rate_ * delay_delay_);

    // overdrive

    overdrive_.Init();
    overdrive_.SetDrive(overdrive_drive_);

    // init
    osc_next_ = 0; // circular buffer of midi notes

    SetType(TUNED);
}



float DSampler::Process()
{
    float out_l, out_r;

    Process(&out_l, &out_r);
    return (out_l);
}



void DSampler::Process(float *out_l, float *out_r)
{
    float lfo_out;
    float env_p_out, env_f_out, env_a_out;
    float filter_out_l, filter_out_r;
    float delay_out_l, delay_out_r;

    bool note_on;

    float a, b;
    float osc_out_l;
    float osc_out_r;

    // lfo + apply
    lfo_out = lfo_.Process();

    filter_out_l = 0.0f;
    filter_out_r = 0.0f;
    for (uint8_t i = 0; i < voices_; i++)
    {
        note_on = (note_midi_[i] != 0);

        // amplitude
        // amp can be affected by:
        // lfo, eg (always), velocity

        env_a_out = eg_a_[i].Process(note_on) * (1 - lfo_out * lfo_a_level_);

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

        SetFreq(f);

        // osc

        if (sample_index_[i] < sample_phase_end_)
        {
            // pos in buffer
            uint32_t sample_index_int_ = static_cast<int32_t>(sample_index_[i]);
            // how much did we miss?
            float sample_index_fraction_ = sample_index_[i] - sample_index_int_;
            uint32_t index = sample_index_int_ * sample_channels_;
            // get samples and interpolate
            switch (sample_channels_)
            {
            case 1:
                a = sample_buffer_[index];
                b = sample_buffer_[index + 1];
                osc_out_l = (a + (b - a) * sample_index_fraction_);// * env_a_out;
                osc_out_r = osc_out_l;
                break;
            case 2:
                a = sample_buffer_[index];
                b = sample_buffer_[index + 2];
                osc_out_l = (a + (b - a) * sample_index_fraction_);// * env_a_out;
                a = sample_buffer_[index + sample_channels_];
                b = sample_buffer_[index + sample_channels_ + 2];
                osc_out_r = (a + (b - a) * sample_index_fraction_);// * env_a_out;
                break;
            default:
                osc_out_l = 0.0f;
                osc_out_r = 0.0f;
                break;
            }

            sample_index_[i] += sample_index_factor_[i];

            // loop?
            if ((sample_index_[i] >= sample_phase_loop_end_) && loop_)
            {
                sample_index_[i] = sample_phase_loop_start_;
            }

        } else {
            osc_out_l = 0.f;
            osc_out_r = 0.f;
        }

        osc_out_l = osc_out_l * env_a_out * note_velocity_[i];
        osc_out_r = osc_out_r * env_a_out * note_velocity_[i];

        // filter
        // cutoff can be affected by:
        // eg, lfo

        env_f_out = eg_f_[i].Process(note_on);

        f = filter_cutoff_
                * (1 - lfo_out * lfo_f_level_)
                * env_f_out *  eg_f_level_
                * note_velocity_[i]
                ;

        svf_l_[i].SetFreq(f);
        svf_r_[i].SetFreq(f);

        svf_l_[i].Process(osc_out_l);
        svf_r_[i].Process(osc_out_r);
        switch (filter_type_)
        {
        case BAND:
            filter_out_l += svf_l_[i].Band();
            filter_out_r += svf_r_[i].Band();
            break;
        case HIGH:
            filter_out_l += svf_l_[i].High();
            filter_out_r += svf_r_[i].High();
            break;
        case LOW:
            filter_out_l += svf_l_[i].Low();
            filter_out_r += svf_r_[i].Low();
            break;
        case NOTCH:
            filter_out_l += svf_l_[i].Notch();
            filter_out_r += svf_r_[i].Notch();
            break;
        case PEAK:
            filter_out_l += svf_l_[i].Peak();
            filter_out_r += svf_r_[i].Peak();
            break;
        default:
            filter_out_l += osc_out_l;
            filter_out_r += osc_out_r;
        }

    } // for voices_

//    filter_out_l /= voices_;
//    filter_out_r /= voices_;

    // overdrive
    // no state in overdrive fx so we can use it on both channels
    if (overdrive_drive_ > 0.0f) {
        filter_out_l = overdrive_.Process(filter_out_l * overdrive_gain_);
        filter_out_r = overdrive_.Process(filter_out_r * overdrive_gain_);
    }

    // delay
    if (delay_feedback_ > 0.0f) {
        delay_out_l = delay_l_.Read();
        delay_out_r = delay_r_.Read();
        delay_l_.Write((filter_out_l + delay_out_l) * delay_feedback_);
        delay_r_.Write((filter_out_r + delay_out_r) * delay_feedback_);
        filter_out_l += delay_out_l;
        filter_out_r += delay_out_r;
    }

    *out_l = filter_out_l;
    *out_r = filter_out_r;

}



void DSampler::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
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



void DSampler::NoteOn(uint8_t midi_note, uint8_t midi_velocity)
{
    osc_next_ = (osc_next_ + 1) % voices_;

    note_midi_[osc_next_] = midi_note + transpose_;
    note_freq_[osc_next_] = daisysp::mtof(note_midi_[osc_next_] + tune_);
    note_velocity_[osc_next_] = (float)midi_velocity / MIDI_VELOCITY_MAX;

    sample_index_[osc_next_] = sample_phase_start_;
    sample_index_factor_[osc_next_] = (note_freq_[osc_next_] / DSAMPLER_BASE_FREQ);// * (fxSettings.oscDetune / 100.0f);

    if (portamento_ == 0)
    {
        eg_p_[osc_next_].Retrigger(false);
        eg_f_[osc_next_].Retrigger(false);
        eg_a_[osc_next_].Retrigger(false);
    }
}



void DSampler::NoteOff(uint8_t midi_note)
{
    for (uint8_t i = 0; i < voices_; i++)
    {
        if (note_midi_[i] == midi_note + transpose_)
        {
            note_midi_[i] = 0;
        }
    }
}



void DSampler::Silence()
{
    for (uint8_t i = 0; i < voices_; i++)
    {
        note_midi_[i] = 0;
        note_velocity_[i] = 0;
    }
}



void DSampler::SetFreq(float freq)
{
    for (uint8_t i = 0; i < voices_; i++)
    {
        sample_index_factor_[i] = (freq / DSAMPLER_BASE_FREQ);
    }
}



void DSampler::SetTuning(float tune)
{
    tune_ = tune;
}



void DSampler::SetTranspose(uint8_t transpose)
{
    transpose_ = transpose;
}



void DSampler::SetFilter(FilterType filter_type, float filter_cutoff, float filter_res)
{
    filter_type_ = filter_type;
    filter_cutoff_ = filter_cutoff;
    filter_res_ = filter_res;

    for (uint8_t i = 0; i < voices_; i++)
    {
        svf_l_[i].SetFreq(filter_cutoff_);
        svf_l_[i].SetRes(filter_res_);
        svf_r_[i].SetFreq(filter_cutoff_);
        svf_r_[i].SetRes(filter_res_);
    }
}



void DSampler::SetEGLevel(Target target, float level)
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



void DSampler::SetEG(Target target, float eg_attack, float eg_decay, float eg_sustain, float eg_release)
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
                eg_a_[i].SetTime(daisysp::ADSR_SEG_DECAY, eg_a_decay_);
                eg_a_[i].SetTime(daisysp::ADSR_SEG_RELEASE, eg_a_release_);
                eg_a_[i].SetSustainLevel(eg_a_sustain_);
            }
            break;
        default:
            break;
    }
}


void DSampler::SetLFO(Waveform lfo_waveform, float lfo_freq, float lfo_amp, float lfo_p_level, float lfo_f_level, float lfo_a_level)
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



void DSampler::SetPortamento(float portamento)
{
    portamento_ = portamento;
}



void DSampler::SetDelay(float delay_delay, float delay_feedback)
{
    delay_delay_ = delay_delay;
    delay_feedback_ = delay_feedback;
    delay_l_.SetDelay(sample_rate_ * delay_delay_);
    delay_r_.SetDelay(sample_rate_ * delay_delay_);
}



void DSampler::SetOverdrive(float overdrive_gain, float overdrive_drive)
{
    overdrive_gain_ = overdrive_gain;
    overdrive_drive_ = overdrive_drive;
    overdrive_.SetDrive(overdrive_drive_);
}



bool DSampler::Load(const std::string sample_file_name, bool reset)
{
    SNDFILE *sample_file;
    SF_INFO sample_file_info;
    bool retval = false;

    sample_file_info.format = 0;
    const char *c_file_name = sample_file_name.c_str();
    sample_file = sf_open(c_file_name, SFM_READ, &sample_file_info);

    // handle mono/stereo
    uint8_t frame_size;

    switch (sample_file_info.channels)
    {
    case 1: // mono
        frame_size = 1;
        break;
    case 2: // stereo
        frame_size = 2;
        break;
    default:
        // we don't handle anything else
        frame_size = 0;
        break;
    }

    // we are assumeing that a frame is interleaved channels

    sf_count_t	frame_count = sample_file_info.frames;

    if (frame_count < SAMPLE_BUFFER_MAX)
    {
        // read sample data
        frame_count = sf_readf_float(sample_file, sample_buffer_, sample_file_info.frames);

        if (reset)
        {
            sample_length_ = frame_count;
            sample_phase_start_ = 0;
            sample_phase_loop_start_ = 0;
            //if (sample_phase_loop_end_ == 0)
                sample_phase_loop_end_ = frame_count - 1;
            //if (sample_phase_end_ == 0)
                sample_phase_end_ = frame_count - 1;
            sample_file_name_ = sample_file_name;
        }
        // always set from sample data
        sample_channels_ = frame_size;
    } else {
        // failed to load so always reset values
        sample_length_ = 0;
        sample_phase_start_ = 0;
        sample_phase_loop_start_ = 0;
        sample_phase_loop_end_ = 0;
        sample_phase_end_ = 0;
        sample_channels_ = frame_size;
    }

    sf_close(sample_file);

    for (uint8_t i = 0; i < voices_; i++)
    {
        sample_index_[i] = sample_phase_start_;
        sample_index_factor_[i] = 1.0f;
    }

    return (retval);
}



void DSampler::SetLoop(bool loop)
{
    loop_ = loop;
}



void DSampler::GetPhase(uint32_t *sample_phase_start,
                             uint32_t *sample_phase_loop_start,
                             uint32_t *sample_phase_loop_end,
                             uint32_t *sample_phase_end)
{
        *sample_phase_start = sample_phase_start_;
        *sample_phase_loop_start = sample_phase_loop_start_;
        *sample_phase_loop_end = sample_phase_loop_end_;
        *sample_phase_end = sample_phase_end_;
}



void DSampler::SetPhase(uint32_t sample_phase_start,
                             uint32_t sample_phase_loop_start,
                             uint32_t sample_phase_loop_end,
                             uint32_t sample_phase_end)
{
    if (sample_phase_start < sample_length_ - 1)
    {
        sample_phase_start_ = sample_phase_start;
    }
    if (sample_phase_loop_start_ < sample_length_ - 1)
    {
        sample_phase_loop_start_ = sample_phase_loop_start;
    }
    if (sample_phase_loop_end < sample_length_ - 1)
    {
        sample_phase_loop_end_ = sample_phase_loop_end;
    }
    if (sample_phase_end < sample_length_ - 1)
    {
        sample_phase_end_ = sample_phase_end;
    }

    // reset
    for (uint8_t i = 0; i < voices_; i++)
    {
        sample_index_[i] = sample_phase_start_;
        sample_index_factor_[i] = 1.0f;
    }
}



uint32_t DSampler::GetLength()
{
    return (sample_length_);
}
