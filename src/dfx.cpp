#include "dstudio.h"
#include "dfx.h"


/*

DFXOverdrive

*/

void DFXOverdrive::Init(const Config& config)
{
    sample_rate_ = config.sample_rate;
	level_ = config.level;
    gain_ = config.gain;
    drive_ = config.drive;
    child_ = config.child;

    overdrive_.Init();
    overdrive_.SetDrive(drive_);

    SetType(FX);
}



void DFXOverdrive::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
{
    child_->MidiIn(midi_status, midi_data0, midi_data1);
}



void DFXOverdrive::NoteOn(uint8_t midi_note, uint8_t midi_velocity)
{
    child_->NoteOn(midi_note, midi_velocity);
}



void DFXOverdrive::NoteOff(uint8_t midi_note)
{
    child_->NoteOff(midi_note);
}



void DFXOverdrive::Silence()
{
    child_->Silence();
}



float DFXOverdrive::Process()
{
    float child_l, child_r;
    float fx_in;

    child_->Process(&child_l, &child_r);
    fx_in = (child_l + child_r) / 2;

    return (overdrive_.Process(fx_in * gain_) * level_);
}



void DFXOverdrive::Process(float *out_l, float *out_r)
{
    float child_l, child_r;

    child_->Process(&child_l, &child_r);
    *out_l = overdrive_.Process(child_l * gain_) * level_;
    *out_r = overdrive_.Process(child_r * gain_) * level_;
}



void DFXOverdrive::SetGain(float gain)
{
    gain_ = gain;
}



void DFXOverdrive::SetDrive(float drive)
{
    drive_ = drive;

    overdrive_.SetDrive(drive_);
}



/*

DFXTremolo

*/

void DFXTremolo::Init(const Config& config)
{
    sample_rate_ = config.sample_rate;
    level_ = config.level;
    freq_ = config.freq;
    waveform_ = config.waveform;
    depth_ = config.depth;
    child_ = config.child;

    tremolo_l_.Init(sample_rate_);
    tremolo_l_.SetFreq(freq_);
    tremolo_l_.SetWaveform(waveform_);
    tremolo_l_.SetDepth(depth_);

    tremolo_r_.Init(sample_rate_);
    tremolo_r_.SetFreq(freq_);
    tremolo_r_.SetWaveform(waveform_);
    tremolo_r_.SetDepth(depth_);

    SetType(FX);
}



void DFXTremolo::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
{
    child_->MidiIn(midi_status, midi_data0, midi_data1);
}



void DFXTremolo::NoteOn(uint8_t midi_note, uint8_t midi_velocity)
{
    child_->NoteOn(midi_note, midi_velocity);
}



void DFXTremolo::NoteOff(uint8_t midi_note)
{
    child_->NoteOff(midi_note);
}



void DFXTremolo::Silence()
{
    child_->Silence();
}



float DFXTremolo::Process()
{
    float child_l, child_r;
    float fx_in;

    child_->Process(&child_l, &child_r);
    fx_in = (child_l + child_r) / 2;

    return(tremolo_l_.Process(fx_in) * level_);
}



void DFXTremolo::Process(float *out_l, float *out_r)
{
    float child_l, child_r;

    child_->Process(&child_l, &child_r);
    *out_l = tremolo_l_.Process(child_l) * level_;
    *out_r = tremolo_r_.Process(child_r) * level_;
}



void DFXTremolo::SetFreq(float freq)
{
    freq_ = freq;

    tremolo_l_.SetFreq(freq_);
    tremolo_r_.SetFreq(freq_);
}



void DFXTremolo::SetWaveform(int waveform)
{
    waveform_ = waveform;

    tremolo_l_.SetWaveform(waveform_);
    tremolo_r_.SetWaveform(waveform_);
}



void DFXTremolo::SetDepth(float depth)
{
    depth_ = depth;

    tremolo_l_.SetDepth(depth_);
    tremolo_r_.SetDepth(depth_);
}



/*

DFXDelay

*/

void DFXDelay::Init(const Config& config)
{
    sample_rate_ = config.sample_rate;
    level_ = config.level;
    delay_delay_l_ = config.delay_delay_l;
    delay_feedback_l_ = config.delay_feedback_l;
    delay_delay_r_ = config.delay_delay_r;
    delay_feedback_r_ = config.delay_feedback_r;
    child_ = config.child;

    delay_l_.Init();
    delay_l_.SetDelay(sample_rate_ * delay_delay_l_);
    delay_r_.Init();
    delay_r_.SetDelay(sample_rate_ * delay_delay_r_);

    SetType(FX);
}



void DFXDelay::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
{
    child_->MidiIn(midi_status, midi_data0, midi_data1);
}



void DFXDelay::NoteOn(uint8_t midi_note, uint8_t midi_velocity)
{
    child_->NoteOn(midi_note, midi_velocity);
}



void DFXDelay::NoteOff(uint8_t midi_note)
{
    child_->NoteOff(midi_note);
}



void DFXDelay::Silence()
{
    child_->Silence();
}



float DFXDelay::Process()
{
    float child_l, child_r;
    float fx_out_l, fx_out_r;

    child_->Process(&child_l, &child_r);

    fx_out_l = delay_l_.Read();
    delay_l_.Write((child_l + fx_out_l) * delay_feedback_l_);
    fx_out_r = delay_r_.Read();
    delay_r_.Write((child_r + fx_out_r) * delay_feedback_r_);

    return (((child_l + fx_out_l + child_r + fx_out_r) / 2) * level_);
}



void DFXDelay::Process(float *out_l, float *out_r)
{
    float child_l, child_r;
    float fx_out_l, fx_out_r;

    child_->Process(&child_l, &child_r);

    fx_out_l = delay_l_.Read();
    delay_l_.Write((child_l + fx_out_l) * delay_feedback_l_);
    fx_out_r = delay_r_.Read();
    delay_r_.Write((child_r + fx_out_r) * delay_feedback_r_);

    *out_l = (child_l + fx_out_l) * level_;
    *out_r = (child_r + fx_out_r) * level_;
}



void DFXDelay::SetDelay(float delay_delay_l, float delay_feedback_l, float delay_delay_r, float delay_feedback_r)
{
    delay_delay_l_ = delay_delay_l;
    delay_feedback_l_ = delay_feedback_l;
    delay_delay_r_ = delay_delay_r;
    delay_feedback_r_ = delay_feedback_r;

    delay_l_.SetDelay(sample_rate_ * delay_delay_l_);
    delay_r_.SetDelay(sample_rate_ * delay_delay_r_);
}



/*

DFXFlanger

*/

void DFXFlanger::Init(const Config& config)
{
    sample_rate_ = config.sample_rate;
    level_ = config.level;
    feedback_ = config.feedback;
    lfo_depth_ = config.lfo_depth;
    lfo_freq_ = config.lfo_freq;
    delay_ = config.delay; // 0.0 - 1.0, maps to .1 to 7 ms
    child_ = config.child;

    flanger_l_.Init(sample_rate_);
    flanger_l_.SetFeedback(feedback_);
    flanger_l_.SetLfoDepth(lfo_depth_);
    flanger_l_.SetLfoFreq(lfo_freq_);
    flanger_l_.SetDelay(delay_);

    flanger_r_.Init(sample_rate_);
    flanger_r_.SetFeedback(feedback_);
    flanger_r_.SetLfoDepth(lfo_depth_);
    flanger_r_.SetLfoFreq(lfo_freq_);
    flanger_r_.SetDelay(delay_);

    SetType(FX);
}



void DFXFlanger::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
{
    child_->MidiIn(midi_status, midi_data0, midi_data1);
}



void DFXFlanger::NoteOn(uint8_t midi_note, uint8_t midi_velocity)
{
    child_->NoteOn(midi_note, midi_velocity);
}



void DFXFlanger::NoteOff(uint8_t midi_note)
{
    child_->NoteOff(midi_note);
}



void DFXFlanger::Silence()
{
    child_->Silence();
}



float DFXFlanger::Process()
{
    float child_l, child_r;

    child_->Process(&child_l, &child_r);

    return (((flanger_l_.Process(child_l)
              + flanger_r_.Process(child_r)) / 2)
            * level_);
}



void DFXFlanger::Process(float *out_l, float *out_r)
{
    float child_l, child_r;

    child_->Process(&child_l, &child_r);

    *out_l = flanger_l_.Process(child_l) * level_;
    *out_r = flanger_r_.Process(child_r) * level_;
}



void DFXFlanger::SetFeedback(float feedback)
{
    feedback_ = feedback;

    flanger_l_.SetFeedback(feedback_);
    flanger_r_.SetFeedback(feedback_);
}



void DFXFlanger::SetLFODepth(float lfo_depth)
{
    lfo_depth_ = lfo_depth;

    flanger_l_.SetLfoDepth(lfo_depth_);
    flanger_r_.SetLfoDepth(lfo_depth_);
}



void DFXFlanger::SetLFOFreq(float lfo_freq)
{
    lfo_freq_ = lfo_freq;

    flanger_l_.SetLfoFreq(lfo_freq_);
    flanger_r_.SetLfoFreq(lfo_freq_);
}



void DFXFlanger::SetDelay(float delay)
{
    delay_ = delay;

    flanger_l_.SetDelay(delay_);
    flanger_r_.SetDelay(delay_);
}



/*

DFXDecimator

*/

void DFXDecimator::Init(const Config& config)
{
    sample_rate_ = config.sample_rate;
    level_ = config.level;
    downsample_factor_ = config.downsample_factor;
    bitcrush_factor_ = config.bitcrush_factor;
    bits_to_crush_ = config.bits_to_crush;
    child_ = config.child;

    decimator_l_.Init();
    decimator_l_.SetDownsampleFactor(downsample_factor_);
    decimator_l_.SetBitcrushFactor(bitcrush_factor_);
    decimator_l_.SetBitsToCrush(bits_to_crush_);

    decimator_r_.Init();
    decimator_r_.SetDownsampleFactor(downsample_factor_);
    decimator_r_.SetBitcrushFactor(bitcrush_factor_);
    decimator_r_.SetBitsToCrush(bits_to_crush_);

    SetType(FX);
}



void DFXDecimator::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
{
    child_->MidiIn(midi_status, midi_data0, midi_data1);
}



void DFXDecimator::NoteOn(uint8_t midi_note, uint8_t midi_velocity)
{
    child_->NoteOn(midi_note, midi_velocity);
}



void DFXDecimator::NoteOff(uint8_t midi_note)
{
    child_->NoteOff(midi_note);
}



void DFXDecimator::Silence()
{
    child_->Silence();
}



float DFXDecimator::Process()
{
    float child_l, child_r;

    child_->Process(&child_l, &child_r);

    return (((decimator_l_.Process(child_l)
              + decimator_r_.Process(child_r)) / 2)
            * level_);
}



void DFXDecimator::Process(float *out_l, float *out_r)
{
    float child_l, child_r;

    child_->Process(&child_l, &child_r);

    *out_l = decimator_l_.Process(child_l) * level_;
    *out_r = decimator_r_.Process(child_r) * level_;
}



void DFXDecimator::SetDownsampleFactor(float downsample_factor)
{
    downsample_factor_ = downsample_factor;

    decimator_l_.SetDownsampleFactor(downsample_factor_);
    decimator_r_.SetDownsampleFactor(downsample_factor_);
}



void DFXDecimator::SetBitcrushFactor(float bitcrush_factor)
{
    bitcrush_factor_ = bitcrush_factor;

    decimator_l_.SetBitcrushFactor(bitcrush_factor_);
    decimator_r_.SetBitcrushFactor(bitcrush_factor_);
}



void DFXDecimator::SetBitsToCrush(uint8_t bits_to_crush)
{
    bits_to_crush_ = bits_to_crush;

    decimator_l_.SetBitsToCrush(bits_to_crush_);
    decimator_r_.SetBitsToCrush(bits_to_crush_);
}



/*

DFXFilter

*/

void DFXFilter::Init(const Config& config)
{
    sample_rate_ = config.sample_rate;
    level_ = config.level;
    filter_type_ = config.filter_type;
    filter_res_ = config.filter_res;
    filter_cutoff_ = config.filter_cutoff;
    child_ = config.child;

    svf_l_.Init(sample_rate_);
    svf_l_.SetFreq(filter_cutoff_);
    svf_l_.SetRes(filter_res_);
    svf_l_.SetDrive(0.0f);

    svf_r_.Init(sample_rate_);
    svf_r_.SetFreq(filter_cutoff_);
    svf_r_.SetRes(filter_res_);
    svf_r_.SetDrive(0.0f);

    SetType(FX);
}



void DFXFilter::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
{
    child_->MidiIn(midi_status, midi_data0, midi_data1);
}



void DFXFilter::NoteOn(uint8_t midi_note, uint8_t midi_velocity)
{
    child_->NoteOn(midi_note, midi_velocity);
}



void DFXFilter::NoteOff(uint8_t midi_note)
{
    child_->NoteOff(midi_note);
}



void DFXFilter::Silence()
{
    child_->Silence();
}



float DFXFilter::Process()
{
    float child_l, child_r;

    Process(&child_l, &child_r);

    return ((child_l + child_r) / 2);
}



void DFXFilter::Process(float *out_l, float *out_r)
{
    float child_l, child_r;

    child_->Process(&child_l, &child_r);

    svf_l_.Process(child_l);
    svf_r_.Process(child_r);
    switch (filter_type_)
    {
    case BAND:
        *out_l = svf_l_.Band();
        *out_r = svf_r_.Band();
        break;
    case HIGH:
        *out_l = svf_l_.High();
        *out_r = svf_r_.High();
        break;
    case LOW:
        *out_l = svf_l_.Low();
        *out_r = svf_r_.Low();
        break;
    case NOTCH:
        *out_l = svf_l_.Notch();
        *out_r = svf_r_.Notch();
        break;
    case PEAK:
        *out_l = svf_l_.Peak();
        *out_r = svf_r_.Peak();
        break;
    default:
        *out_l = child_l;
        *out_r = child_r;
    }

    *out_l = *out_l * level_;
    *out_r = *out_r * level_;
}



void DFXFilter::SetFilter(FilterType filter_type, float filter_cutoff, float filter_res)
{
    filter_type_ = filter_type;
    filter_cutoff_ = filter_cutoff;
    filter_res_ = filter_res;

    svf_l_.SetFreq(filter_cutoff_);
    svf_r_.SetFreq(filter_cutoff_);
    svf_l_.SetRes(filter_res_);
    svf_r_.SetRes(filter_res_);
}

void DFXFilter::SetFreq(float filter_cutoff)
{
    filter_cutoff_ = filter_cutoff;

    svf_l_.SetFreq(filter_cutoff_);
}


void DFXFilter::SetRes(float filter_res)
{
    filter_res_ = filter_res;

    svf_r_.SetRes(filter_res_);
}



/*

DFXSlicer

Records a random amount of time and plays it back a random amount of times. Can also be triggered.

*/

void DFXSlicer::Init(const Config& config)
{
    sample_rate_ = config.sample_rate;
    level_ = config.level;
    child_ = config.child;
    record_samples_max_ = config.record_samples_max;
    playback_rep_max_ = config.playback_rep_max;
    trig_mode_ = config.trig_mode;

    record_ = true;
    record_pos_ = 0;
    record_samples_ = 1 + ((float)rand() / (float)RAND_MAX) * (float)record_samples_max_;

    playback_pos_ = 0;
    playback_end_ = 1;
    playback_rep_ = 0;
    playback_rep_nr_ = 1 + ((float)rand() / (float)RAND_MAX) * (float)playback_rep_max_;

    SetType(FX);
}



void DFXSlicer::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
{
    child_->MidiIn(midi_status, midi_data0, midi_data1);
}



void DFXSlicer::NoteOn(uint8_t midi_note, uint8_t midi_velocity)
{
    child_->NoteOn(midi_note, midi_velocity);
}



void DFXSlicer::NoteOff(uint8_t midi_note)
{
    child_->NoteOff(midi_note);
}



void DFXSlicer::Silence()
{
    child_->Silence();
}



float DFXSlicer::Process()
{
    float child_l;

    child_l = child_->Process();

    if (record_)
    {
        buffer_l_[record_pos_] = child_l;
        record_pos_++;

        if (record_pos_ >= record_samples_ || record_pos_ >= DFXSLICER_MAX)
        {
            record_ = false;
            playback_end_ = record_pos_ - 1;
            playback_pos_ = 0;
            if (!trig_mode_)
            {
                playback_rep_nr_ = 1 + ((float)rand() / (float)RAND_MAX) * (float)playback_rep_max_;
                playback_rep_ = 0;
            }
        }
    }

    float return_value = buffer_l_[playback_pos_];

    playback_pos_++;

    if (playback_pos_ > playback_end_ && !record_)
    {
        playback_pos_ = 0;
        if (!record_ && !trig_mode_)
        {
            playback_rep_++;
            if (playback_rep_ >= playback_rep_nr_)
            {
                playback_rep_nr_ = 1 + ((float)rand() / (float)RAND_MAX) * (float)playback_rep_max_;
                playback_rep_ = 0;
                record_samples_ = 1 + ((float)rand() / (float)RAND_MAX) * (float)record_samples_max_;
                record_pos_ = 0;
                record_ = true;
            }
        }
    }

    return (return_value);
}



void DFXSlicer::Process(float *out_l, float *out_r)
{
    float child_l, child_r;

    child_->Process(&child_l, &child_r);

    if (record_)
    {
        buffer_l_[record_pos_] = child_l;
        buffer_r_[record_pos_] = child_r;
        record_pos_++;

        if (record_pos_ >= record_samples_ || record_pos_ >= DFXSLICER_MAX)
        {
            record_ = false;
            playback_end_ = record_pos_ - 1;
            playback_pos_ = 0;
            if (!trig_mode_)
            {
                playback_rep_nr_ = 1 + ((float)rand() / (float)RAND_MAX) * (float)playback_rep_max_;
                playback_rep_ = 0;
            }
        }
    }

    *out_l = buffer_l_[playback_pos_] * level_;
    *out_r = buffer_r_[playback_pos_] * level_;

    playback_pos_++;

    if (playback_pos_ > playback_end_ && !record_)
    {
        playback_pos_ = 0;
        if (!record_ && !trig_mode_)
        {
            playback_rep_++;
            if (playback_rep_ >= playback_rep_nr_)
            {
                playback_rep_nr_ = 1 + ((float)rand() / (float)RAND_MAX) * (float)playback_rep_max_;
                playback_rep_ = 0;
                record_samples_ = 1 + ((float)rand() / (float)RAND_MAX) * (float)record_samples_max_;
                record_pos_ = 0;
                record_ = true;
            }
        }
    }

}



void DFXSlicer::SetRecordMax(size_t val)
{
    if (val <= DFXSLICER_MAX)
        record_samples_max_ = val;
    else
        record_samples_max_ = DFXSLICER_MAX;
}



void DFXSlicer::SetPlaybackMax(size_t val)
{
    playback_rep_max_ = val;
}



void DFXSlicer::SetTrigMode(bool mode)
{
    trig_mode_ = mode;
}



void DFXSlicer::Trig(bool on)
{
    if (trig_mode_)
    {
        if (on)
        {
            // start recording
            record_samples_ = DFXSLICER_MAX;
            record_pos_ = 0;
            record_ = true;
            playback_pos_ = 0;
        } else {
            // start repeat
            record_ = false;
            playback_end_ = record_pos_ - 1;
            playback_pos_ = 0;

        }
    }
}



/*

DFXPanner

*/

void DFXPanner::Init(const Config& config)
{
    sample_rate_ = config.sample_rate;
    level_ = config.level;
    child_ = config.child;
    type_ = config.type;
    lfo_waveform_ = config.lfo_waveform;
    freq_ = config.freq;
    amp_ = config.amp;
    offset_ = config.offset;

    lfo_.Init(sample_rate_);
    lfo_.SetWaveform(lfo_waveform_);
    lfo_.SetFreq(freq_);
    lfo_.SetAmp(amp_);

    prev_sig_ = 0.0f;
    random_sig_ = ((float)rand() / (float)RAND_MAX);

    SetType(FX);
}



void DFXPanner::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
{
    child_->MidiIn(midi_status, midi_data0, midi_data1);
}



void DFXPanner::NoteOn(uint8_t midi_note, uint8_t midi_velocity)
{
    child_->NoteOn(midi_note, midi_velocity);
}



void DFXPanner::NoteOff(uint8_t midi_note)
{
    child_->NoteOff(midi_note);
}



void DFXPanner::Silence()
{
    child_->Silence();
}



float DFXPanner::Process()
{
    float child_sig;

    child_sig = child_->Process();

    // cannot pan if we return mono signal

    return (child_sig);
}



void DFXPanner::Process(float *out_l, float *out_r)
{
    float child_sig;
    float lfo_sig;

    child_sig = child_->Process() * level_;

    switch(type_)
    {
    case STATIC:
        *out_l = child_sig * (1.0f - offset_);
        *out_r = child_sig * (offset_);
        break;
    case LFO:
        lfo_sig = (lfo_.Process() + 1.0f) / 2.0f + offset_;
        *out_l = child_sig * (1.0f - lfo_sig);
        *out_r = child_sig * (lfo_sig);
        break;
    case RANDOM:
        lfo_sig = (lfo_.Process() + 1.0f) / 2.0f;
        if (abs(lfo_sig - prev_sig_) > offset_)
        {
            random_sig_ = ((float)rand() / (float)RAND_MAX) * amp_;
            *out_l = child_sig * (1.0f - random_sig_);
            *out_r = child_sig * (random_sig_);
            prev_sig_ = lfo_sig;
        } else {
            *out_l = child_sig * (1.0f - random_sig_);
            *out_r = child_sig * (random_sig_);
        }
        break;
    }
}
