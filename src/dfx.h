#pragma once

#include "dstudio.h"
#include "dsound.h"

/*

DFXOverdrive

*/

#include "overdrive.h"

class DFXOverdrive : public DSound
{

	public:

    DFXOverdrive() {}
    ~DFXOverdrive() {}

	struct Config
	{
		float sample_rate;
		float level;
		float gain;
		float drive;
        DSound *child;
	};

    void Init(const Config&);
    float Process();
    void Process(float *, float *);
    void MidiIn(uint8_t, uint8_t, uint8_t);
    void NoteOn(uint8_t midi_note, uint8_t midi_velocity = MIDI_VELOCITY_MAX);
    void NoteOff(uint8_t midi_note);
    void Silence();

    void SetGain(float);
    void SetDrive(float);

private:

	// config
    float sample_rate_;
    float level_;
    float gain_;
    float drive_;
    DSound *child_;

	// objects
    daisysp::Overdrive overdrive_;

    // runtime

};



/*

DFXTremolo

*/

#include "tremolo.h"

class DFXTremolo : public DSound
{

    public:

    enum Waveform
    {
        WAVE_SIN,
        WAVE_TRI,
        WAVE_SAW,
        WAVE_RAMP,
        WAVE_SQUARE,
        WAVE_POLYBLEP_TRI,
        WAVE_POLYBLEP_SAW,
        WAVE_POLYBLEP_SQUARE,
        WAVE_LAST,
    };

    DFXTremolo() {}
    ~DFXTremolo() {}

    struct Config
    {
        float sample_rate;
        float level;
        float freq;
        uint8_t waveform;
        float depth;
        DSound *child;
    };

    void Init(const Config&);
    float Process();
    void Process(float *, float *);
    void MidiIn(uint8_t, uint8_t, uint8_t);
    void NoteOn(uint8_t midi_note, uint8_t midi_velocity = MIDI_VELOCITY_MAX);
    void NoteOff(uint8_t midi_note);
    void Silence();

    void SetFreq(float freq);
    void SetWaveform(int waveform);
    void SetDepth(float depth);

private:

    // config
    float sample_rate_;
    float level_;
    float freq_;
    uint8_t waveform_;
    float depth_;
    DSound *child_;

    // objects
    daisysp::Tremolo tremolo_l_, tremolo_r_;

    // runtime

};



/*

DFXDelay

*/

#include "delayline.h"

#define DFXDELAY_DELAY_MAX_S 2.0f // delay max in seconds
#define DFXDELAY_DELAY_MAX static_cast<size_t>(DSTUDIO_SAMPLE_RATE * DFXDELAY_DELAY_MAX_S)

class DFXDelay : public DSound
{

    public:

    DFXDelay() {}
    ~DFXDelay() {}

    struct Config
    {
        float sample_rate;
        float level;
        float delay_delay_l;
        float delay_feedback_l;
        float delay_delay_r;
        float delay_feedback_r;
        DSound *child;
    };

    void Init(const Config&);
    float Process();
    void Process(float *, float *);
    void MidiIn(uint8_t, uint8_t, uint8_t);
    void NoteOn(uint8_t midi_note, uint8_t midi_velocity = MIDI_VELOCITY_MAX);
    void NoteOff(uint8_t midi_note);
    void Silence();

    void SetDelay(float, float, float, float);

private:

    // config
    float sample_rate_;
    float level_;
    float delay_delay_l_;
    float delay_feedback_l_;
    float delay_delay_r_;
    float delay_feedback_r_;
    DSound *child_;

    // objects
    daisysp::DelayLine<float, DFXDELAY_DELAY_MAX> delay_l_;
    daisysp::DelayLine<float, DFXDELAY_DELAY_MAX> delay_r_;

    // runtime

};



/*

DFXFlanger

*/

#include "flanger.h"

class DFXFlanger : public DSound
{

    public:

    DFXFlanger() {}
    ~DFXFlanger() {}

    struct Config
    {
        float sample_rate;
        float level;
        float feedback;
        float lfo_depth;
        float lfo_freq;
        float delay; // 0.0 - 1.0, maps to .1 to 7 ms
        DSound *child;
    };

    void Init(const Config&);
    float Process();
    void Process(float *, float *);
    void MidiIn(uint8_t, uint8_t, uint8_t);
    void NoteOn(uint8_t midi_note, uint8_t midi_velocity = MIDI_VELOCITY_MAX);
    void NoteOff(uint8_t midi_note);
    void Silence();

    void SetFeedback(float);
    void SetLFODepth(float);
    void SetLFOFreq(float);
    void SetDelay(float);

private:

    // config
    float sample_rate_;
    float level_;
    float feedback_;
    float lfo_depth_;
    float lfo_freq_;
    float delay_; // 0.0 - 1.0, maps to .1 to 7 ms
    DSound *child_;

    // objects
    daisysp::Flanger flanger_l_, flanger_r_;

    // runtime

};


/*

DFXDecimator

*/

#include "decimator.h"

class DFXDecimator : public DSound
{

    public:

    DFXDecimator() {}
    ~DFXDecimator() {}

    struct Config
    {
        float sample_rate;
        float level;
        float downsample_factor;
        float bitcrush_factor;
        uint8_t bits_to_crush;
        DSound *child;
    };

    void Init(const Config&);
    float Process();
    void Process(float *, float *);
    void MidiIn(uint8_t, uint8_t, uint8_t);
    void NoteOn(uint8_t midi_note, uint8_t midi_velocity = MIDI_VELOCITY_MAX);
    void NoteOff(uint8_t midi_note);
    void Silence();

    void SetDownsampleFactor(float);
    void SetBitcrushFactor(float);
    void SetBitsToCrush(uint8_t);

private:

    // config
    float sample_rate_;
    float level_;
    float downsample_factor_;
    float bitcrush_factor_;
    uint8_t bits_to_crush_;
    DSound *child_;

    // objects
    daisysp::Decimator decimator_l_, decimator_r_;

    // runtime

};



/*

DFXFilter

*/

#include "svf.h"

class DFXFilter : public DSound
{

public:

    enum FilterType
    {
        BAND,
        HIGH,
        LOW,
        NOTCH,
        PEAK,
        PASSTHROUGH
    };

    DFXFilter() {}
    ~DFXFilter() {}

    struct Config
    {
        float sample_rate;
        float level;
        FilterType filter_type;
        float filter_res;
        float filter_cutoff;
        DSound *child;
    };

    void Init(const Config&);
    float Process();
    void Process(float *, float *);
    void MidiIn(uint8_t, uint8_t, uint8_t);
    void NoteOn(uint8_t midi_note, uint8_t midi_velocity = MIDI_VELOCITY_MAX);
    void NoteOff(uint8_t midi_note);
    void Silence();

    void SetFilter(FilterType, float, float);
    void SetFreq(float);
    void SetRes(float);

private:

    // config
    float sample_rate_;
    float level_;
    FilterType filter_type_;
    float filter_res_;
    float filter_cutoff_;
    DSound *child_;

    // objects
    daisysp::Svf svf_l_, svf_r_;

    // runtime

};



/*

DFXSlicer

*/

// set max slice to 10 seconds
#define DFXSLICER_MAX (DSTUDIO_SAMPLE_RATE * 10)

class DFXSlicer : public DSound
{

public:
    DFXSlicer() {}
    ~DFXSlicer() {}

    struct Config
    {
        float sample_rate;
        float level;
        DSound *child;
        size_t record_samples_max; // < max_size
        size_t playback_rep_max;
        bool trig_mode; // if true, record mode and playback mode is started with Trig()
    };

    void Init(const Config& config);
    float Process();
    void Process(float *, float *);
    void MidiIn(uint8_t, uint8_t, uint8_t);
    void NoteOn(uint8_t, uint8_t);
    void NoteOff(uint8_t);
    void Silence();

    void SetRecordMax(size_t);
    void SetPlaybackMax(size_t);
    void SetTrigMode(bool);
    void Trig(bool);

private:
    float sample_rate_;
    float level_;
    DSound *child_;
    size_t record_samples_max_; // < max_size
    size_t playback_rep_max_;
    bool trig_mode_; // if true, record mode and playback mode is started with Trig()

    size_t record_;

    size_t record_pos_;
    size_t record_samples_;

    size_t playback_pos_;
    size_t playback_end_;

    size_t playback_rep_;
    size_t playback_rep_nr_;

    float buffer_l_[DFXSLICER_MAX];
    float buffer_r_[DFXSLICER_MAX];

};



/*

DFXPanner

*/

class DFXPanner : public DSound
{

public:

    enum PannerType
    {
        STATIC,
        LFO,
        RANDOM
    };

    enum Waveform
    {
        WAVE_SIN,
        WAVE_TRI,
        WAVE_SAW,
        WAVE_RAMP,
        WAVE_SQUARE,
        WAVE_POLYBLEP_TRI,
        WAVE_POLYBLEP_SAW,
        WAVE_POLYBLEP_SQUARE,
        WAVE_LAST,
    };

    DFXPanner() {}
    ~DFXPanner() {}

    struct Config
    {
        float sample_rate;
        float level;
        DSound *child;
        PannerType type;
        Waveform lfo_waveform;
        float freq;
        float amp;
        float offset;

    };

    void Init(const Config& config);
    float Process();
    void Process(float *, float *);
    void MidiIn(uint8_t, uint8_t, uint8_t);
    void NoteOn(uint8_t, uint8_t);
    void NoteOff(uint8_t);
    void Silence();

private:
    float sample_rate_;
    float level_;
    DSound *child_;
    PannerType type_;
    Waveform lfo_waveform_;
    float freq_;
    float amp_;
    float offset_;

    daisysp::Oscillator lfo_;
    float prev_sig_;
    float random_sig_;

};
