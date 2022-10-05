#pragma once

#include "dstudio.h"
#include "dsound.h"

#include "adsr.h"
#include "delayline.h"
#include "fm2.h"
#include "oscillator.h"
#include "overdrive.h"
#include "port.h"
#include "svf.h"
#include "whitenoise.h"

// polyphony
#define DSYNTHFM_VOICES_MAX 8
// delay
#define DSYNTHFM_DELAY_MAX_S 2.0f // delay max in seconds
#define DSYNTHFM_DELAY_MAX static_cast<size_t>(DSTUDIO_SAMPLE_RATE * DSYNTHFM_DELAY_MAX_S)

// using namespace daisysp;

class DSynthFm : public DSound
{

	public:

    DSynthFm() {}
    ~DSynthFm() {}

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

    enum Target
    {
    	NONE,
        PITCH,
        FILTER,
        AMP,
        LAST,
    };

	enum FilterType
	{
		BAND,
		HIGH,
		LOW,
		NOTCH,
        PEAK,
        PASSTHROUGH
	};

    struct Config
    {
    	float sample_rate;
    	uint8_t voices;
		float ratio;
		float index;
        float tune;
        int8_t transpose;
        float noise_level;
        FilterType filter_type;
		float filter_res;
		float filter_cutoff;
        float eg_p_level;
        float eg_p_attack;
        float eg_p_decay;
        float eg_p_sustain;
        float eg_p_release;
        float eg_f_level;
        float eg_f_attack;
        float eg_f_decay;
        float eg_f_sustain;
        float eg_f_release;
        float eg_a_attack;
        float eg_a_decay;
        float eg_a_sustain;
        float eg_a_release;
        Waveform lfo_waveform;
		float lfo_freq;
		float lfo_amp;
        float lfo_p_level;
        float lfo_f_level;
        float lfo_a_level;
        float portamento;
        float delay_delay;
        float delay_feedback;
        float overdrive_gain;
        float overdrive_drive;
    };

	void Init(const Config&);
	float Process();
    void Process(float *, float *);
    void MidiIn(uint8_t, uint8_t, uint8_t);
    void NoteOn(uint8_t midi_note, uint8_t midi_velocity = MIDI_VELOCITY_MAX);
	void NoteOff(uint8_t midi_note);

    void Silence();
    void SetRatio(float);
    void SetIndex(float);
    void SetTuning(float);
    void SetTranspose(uint8_t);
    void SetLevel(float);
    void SetFilter(FilterType, float, float);
    void SetEGLevel(Target, float);
    void SetEG(Target, float, float, float, float);
    void SetLFO(Waveform, float, float, float, float, float);
    void SetPortamento(float);
    void SetDelay(float, float);
    void SetOverdrive(float, float);

private:

	float sample_rate_;
   	uint8_t voices_;
	float ratio_;
	float index_;
    float tune_;
    int8_t transpose_;
    float noise_level_;
    FilterType filter_type_;
	float filter_res_;
	float filter_cutoff_;
    float eg_p_level_;
    float eg_p_attack_;
    float eg_p_decay_;
    float eg_p_sustain_;
    float eg_p_release_;
    float eg_f_level_;
    float eg_f_attack_;
    float eg_f_decay_;
    float eg_f_sustain_;
    float eg_f_release_;
    float eg_a_attack_;
	float eg_a_decay_;
	float eg_a_sustain_; // level
	float eg_a_release_;
	Waveform lfo_waveform_;
	float lfo_freq_;
	float lfo_amp_;
    float lfo_p_level_;
    float lfo_f_level_;
    float lfo_a_level_;
    float portamento_;
    float delay_delay_;
    float delay_feedback_;
    float overdrive_gain_;
    float overdrive_drive_;

	uint8_t osc_next_;
    uint8_t note_midi_[DSYNTHFM_VOICES_MAX];
    float note_freq_[DSYNTHFM_VOICES_MAX];
    float note_velocity_[DSYNTHFM_VOICES_MAX];

    daisysp::Fm2 fm2_[DSYNTHFM_VOICES_MAX];
    daisysp::WhiteNoise noise_;
    daisysp::Adsr eg_p_[DSYNTHFM_VOICES_MAX];
    daisysp::Adsr eg_f_[DSYNTHFM_VOICES_MAX];
    daisysp::Adsr eg_a_[DSYNTHFM_VOICES_MAX];
    daisysp::Svf svf_[DSYNTHFM_VOICES_MAX];
    daisysp::Oscillator lfo_;
    daisysp::Port port_[DSYNTHFM_VOICES_MAX];

    daisysp::DelayLine<float, DSYNTHFM_DELAY_MAX> delay_;
    daisysp::Overdrive overdrive_;
};
