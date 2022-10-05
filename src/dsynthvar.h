#pragma once

#include "dstudio.h"
#include "dsound.h"
#include "dsm.h"

#include "oscillator.h"
#include "variableshapeosc.h"
#include "adsr.h"
#include "delayline.h"
#include "overdrive.h"
#include "port.h"
#include "svf.h"
#include "whitenoise.h"

// polyphony
#define DSYNTHVAR_VOICES_MAX 8
// delay
#define DSYNTHVAR_DELAY_MAX_S 2.0f // delay max in seconds
#define DSYNTHVAR_DELAY_MAX static_cast<size_t>(DSTUDIO_SAMPLE_RATE * DSYNTHVAR_DELAY_MAX_S)
// mod
#define DSYNTHVAR_EG_MAX 3
#define DSYNTHVAR_LFO_MAX 3
#define DSYNTHVAR_SM_MAX 3
#define DSYNTHVAR_MOD_NONE 0
#define DSYNTHVAR_MOD_EG0 1
#define DSYNTHVAR_MOD_EG1 2
#define DSYNTHVAR_MOD_EG2 3
#define DSYNTHVAR_MOD_LFO0 4
#define DSYNTHVAR_MOD_LFO1 5
#define DSYNTHVAR_MOD_LFO2 6
#define DSYNTHVAR_MOD_SM0 7
#define DSYNTHVAR_MOD_SM1 8
#define DSYNTHVAR_MOD_SM2 9

class DSynthVar : public DSound
{

	public:

    DSynthVar() {}
    ~DSynthVar() {}

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
        float waveshape; // 0 is saw/ramp/tri, 1 is square
        float pulsewidth; // PW when shape is square. Saw, ramp, tri otherwise
        bool sync_enable; // Whether or not to sync to the sync oscillator
        float sync_freq; // sync oscillator freq in Hz
        float tune;
        int8_t transpose;
        float osc_level;
        float noise_level;

        FilterType filter_type;
		float filter_res;
		float filter_cutoff;

        uint8_t mod_eg_p;
        uint8_t mod_eg_f;
        uint8_t mod_eg_a;
        uint8_t mod_filter_cutoff;
        uint8_t mod_waveshape;
        uint8_t mod_pulsewidth;
        uint8_t mod_sync_freq;
        uint8_t mod_delay;

        float eg_0_level;
        float eg_0_attack;
        float eg_0_decay;
        float eg_0_sustain;
        float eg_0_release;
        float eg_1_level;
        float eg_1_attack;
        float eg_1_decay;
        float eg_1_sustain;
        float eg_1_release;
        float eg_2_level;
        float eg_2_attack;
        float eg_2_decay;
        float eg_2_sustain;
        float eg_2_release;

        Waveform lfo_0_waveform;
        float lfo_0_freq;
        float lfo_0_amp;
        float lfo_0_offset;
        Waveform lfo_1_waveform;
        float lfo_1_freq;
        float lfo_1_amp;
        float lfo_1_offset;
        Waveform lfo_2_waveform;
        float lfo_2_freq;
        float lfo_2_amp;
        float lfo_2_offset;

        uint8_t sm_0_type;
        float sm_0_freq;
        float sm_0_amp;
        float sm_0_offset;
        uint8_t sm_0_seq_len;
        std::vector<float> sm_0_seq_val;
        uint8_t sm_1_type;
        float sm_1_freq;
        float sm_1_amp;
        float sm_1_offset;
        uint8_t sm_1_seq_len;
        std::vector<float> sm_1_seq_val;
        uint8_t sm_2_type;
        float sm_2_freq;
        float sm_2_amp;
        float sm_2_offset;
        uint8_t sm_2_seq_len;
        std::vector<float> sm_2_seq_val;

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
    void SetWaveshape(float);
    void SetPulsewidth(float);
    void SetSync(bool);
    void SetSyncFreq(float);
    void SetTuning(float, float);
    void SetTranspose(uint8_t);
    void SetLevel(float, float);
    void SetFilter(FilterType, float, float);
    void SetMod(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
    void SetEGLevel(uint8_t, float);
    void SetEG(uint8_t, float, float, float, float);
    void SetLFO(uint8_t, Waveform, float, float, float);
    void SetSM(uint8_t, uint8_t, float, float, float);
    void SetSMSeq(uint8_t, uint8_t, std::vector<float>&);
    void SetSMSeqStep(uint8_t, uint8_t, float);
    void SetPortamento(float);
    void SetDelay(float, float);
    void SetOverdrive(float, float);

private:

	float sample_rate_;
   	uint8_t voices_;
    float waveshape_;
    float pulsewidth_;
    bool sync_enable_;
    float sync_freq_;
    float osc_level_;
    float tune_;
    int8_t transpose_;

    float noise_level_;
    FilterType filter_type_;
	float filter_res_;
	float filter_cutoff_;

    uint8_t mod_eg_p_;
    uint8_t mod_eg_f_;
    uint8_t mod_eg_a_;
    uint8_t mod_filter_cutoff_;
    uint8_t mod_waveshape_;
    uint8_t mod_pulsewidth_;
    uint8_t mod_sync_freq_;
    uint8_t mod_delay_;

    float eg_0_level_;
    float eg_0_attack_;
    float eg_0_decay_;
    float eg_0_sustain_;
    float eg_0_release_;
    float eg_1_level_;
    float eg_1_attack_;
    float eg_1_decay_;
    float eg_1_sustain_;
    float eg_1_release_;
    float eg_2_level_;
    float eg_2_attack_;
    float eg_2_decay_;
    float eg_2_sustain_;
    float eg_2_release_;

    Waveform lfo_0_waveform_;
    float lfo_0_freq_;
    float lfo_0_amp_;
    float lfo_0_offset_;
    Waveform lfo_1_waveform_;
    float lfo_1_freq_;
    float lfo_1_amp_;
    float lfo_1_offset_;
    Waveform lfo_2_waveform_;
    float lfo_2_freq_;
    float lfo_2_amp_;
    float lfo_2_offset_;

    uint8_t sm_0_type_;
    float sm_0_freq_;
    float sm_0_amp_;
    float sm_0_offset_;
    uint8_t sm_0_seq_len_;
    std::vector<float> sm_0_seq_val_;
    uint8_t sm_1_type_;
    float sm_1_freq_;
    float sm_1_amp_;
    float sm_1_offset_;
    uint8_t sm_1_seq_len_;
    std::vector<float> sm_1_seq_val_;
    uint8_t sm_2_type_;
    float sm_2_freq_;
    float sm_2_amp_;
    float sm_2_offset_;
    uint8_t sm_2_seq_len_;
    std::vector<float> sm_2_seq_val_;

	float portamento_;
    float delay_delay_;
    float delay_feedback_;
    float overdrive_gain_;
    float overdrive_drive_;

	uint8_t osc_next_;
    uint8_t note_midi_[DSYNTHVAR_VOICES_MAX];
    float note_freq_[DSYNTHVAR_VOICES_MAX];
    float note_velocity_[DSYNTHVAR_VOICES_MAX];
    daisysp::VariableShapeOscillator osc_[DSYNTHVAR_VOICES_MAX];
    daisysp::WhiteNoise noise_;
    daisysp::Adsr eg_[DSYNTHVAR_VOICES_MAX][DSYNTHVAR_EG_MAX];
    daisysp::Svf svf_[DSYNTHVAR_VOICES_MAX];
    daisysp::Oscillator lfo_[DSYNTHVAR_LFO_MAX];
    daisysp::Port port_[DSYNTHVAR_VOICES_MAX];
    DSM sm_[DSYNTHVAR_SM_MAX];
    daisysp::DelayLine<float, DSYNTHVAR_DELAY_MAX> delay_;
    daisysp::Overdrive overdrive_;

    float mod_value_[1 + DSYNTHVAR_EG_MAX + DSYNTHVAR_LFO_MAX + DSYNTHVAR_SM_MAX];
};
