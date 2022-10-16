#pragma once

#include <string>

#include "dstudio.h"
#include "dsound.h"

#include "oscillator.h"
#include "adsr.h"
#include "delayline.h"
#include "overdrive.h"
#include "port.h"
#include "svf.h"

#include <sndfile.h>

// base freq
#define DSAMPLER_BASE_FREQ 440.0f
// max sample time in seconds
#define SAMPLE_TIME_MAX 30
#define SAMPLE_BUFFER_MAX (DSTUDIO_SAMPLE_RATE * SAMPLE_TIME_MAX * 2) // 60 secs; 48k * 2 * 4 = 384k/s
// polyphony
#define DSAMPLER_VOICES_MAX 8
// delay
#define DSAMPLER_DELAY_MAX_S 2.0f // delay max in seconds
#define DSAMPLER_DELAY_MAX static_cast<size_t>(DSTUDIO_SAMPLE_RATE * DSAMPLER_DELAY_MAX_S)

class DSampler : public DSound
{

public:

    DSampler()
    {
        sample_buffer_ = new (std::nothrow) float[SAMPLE_BUFFER_MAX * 2];
    }

    ~DSampler()
    {
        delete sample_buffer_;
    }

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
        float tune;
        uint8_t transpose;
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
        bool loop;
        std::string sample_file_name;
        uint32_t sample_phase_start;
        uint32_t sample_phase_loop_start;
        uint32_t sample_phase_loop_end;
        uint32_t sample_phase_end;
        uint32_t sample_length;
        uint8_t sample_channels;
    };

    void Init(const Config&);
    float Process();
    void Process(float *, float *);
    void MidiIn(uint8_t, uint8_t, uint8_t);
    void NoteOn(uint8_t midi_note, uint8_t midi_velocity = MIDI_VELOCITY_MAX);
    void NoteOff(uint8_t midi_note);

    void Silence();
    void SetFreq(float);
    void SetTuning(float);
    void SetTranspose(uint8_t);
    void SetFilter(FilterType, float, float);
    void SetEGLevel(Target, float);
    void SetEG(Target, float, float, float, float);
    void SetLFO(Waveform, float, float, float, float, float);
    void SetPortamento(float);
    void SetDelay(float, float);
    void SetOverdrive(float, float);
    void SetLoop(bool);
    bool Load(std::string, bool reset = true);
    void GetPhase(uint32_t *, uint32_t *, uint32_t *, uint32_t *);
    void SetPhase(uint32_t, uint32_t, uint32_t, uint32_t);
    uint32_t GetLength();

private:

    float sample_rate_;
    uint8_t voices_;
    float tune_;
    uint8_t transpose_;
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
    bool loop_;
    std::string sample_file_name_;
    uint32_t sample_phase_start_;
    uint32_t sample_phase_loop_start_;
    uint32_t sample_phase_loop_end_; // if 0, set to sample_length_ - 1 when loading sample
    uint32_t sample_phase_end_; // if 0, set to sample_length_ - 1 when loading sample
    uint32_t sample_length_; // set when loading sample; length of sample, < BUFFER_MAX
    uint8_t sample_channels_; // set when loading sample

    // MIDI
    uint8_t osc_next_;
    uint8_t note_midi_[DSAMPLER_VOICES_MAX];
    float note_freq_[DSAMPLER_VOICES_MAX];
    float note_velocity_[DSAMPLER_VOICES_MAX];

    // sampler
    float *sample_buffer_ = NULL;

    // sample info
    // sssssssssssssssssssss
    // start lstart lend end
    // gate--<--------->
    // sample - runtime
    float sample_index_[DSAMPLER_VOICES_MAX]; // index into buffer
    float sample_index_factor_[DSAMPLER_VOICES_MAX]; // how much to advance index for a new sample

    // objects
    daisysp::Adsr eg_p_[DSAMPLER_VOICES_MAX];
    daisysp::Adsr eg_f_[DSAMPLER_VOICES_MAX];
    daisysp::Adsr eg_a_[DSAMPLER_VOICES_MAX];
    daisysp::Svf svf_l_[DSAMPLER_VOICES_MAX];
    daisysp::Svf svf_r_[DSAMPLER_VOICES_MAX];
    daisysp::Oscillator lfo_;
    daisysp::Port port_[DSAMPLER_VOICES_MAX];

    daisysp::DelayLine<float, DSAMPLER_DELAY_MAX> delay_l_;
    daisysp::DelayLine<float, DSAMPLER_DELAY_MAX> delay_r_;
    daisysp::Overdrive overdrive_;
};
