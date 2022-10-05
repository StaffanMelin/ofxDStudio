#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxMidi.h"

#include "dsound.h"
#include "dsynthsub.h"
#include "dsynthfm.h"
#include "dsynthvar.h"
#include "dsampler.h"
#include "dbass.h"
#include "dhihat.h"
#include "dsnare.h"
#include "dclap.h"
#include "dcymbal.h"
#include "ddrum.h"

#include "dsettings.h"

#define GUI_DEFAULT_WIDTH 1150
#define GUI_VOICES_MAX 16
#define GUI_SEQ_MAX 3
#define GUI_SEQ_STEP_MAX 16
#define GUI_SEQ_STEP_HEIGHT 20
#define GUI_NOTE_MAX 8
#define GUI_NOTE_MAP_MAX 13
#define GUI_NOTE_MIDI_BASE 48
#define GUI_SYNTH_VELOCITY 70
#define GUI_DRUM_NOTE 60
#define GUI_DRUM_VELOCITY 70

class ofApp : public ofBaseApp, public ofxMidiListener
{

private:
    DSynthSub dsynthsub; // a subtractive synthesizer
    DSynthVar dsynthvar;
    DSynthFm dsynthfm;
    DSampler dsampler;

    DBass dbass;
    DSnare dsnare;
    DHihat dhihat;
    DClap dclap;
    DCymbal dcymbal;
    DDrum ddrum;

    DSynthSub::Config dsynthsub_config;
    DSynthVar::Config dsynthvar_config;
    DSynthFm::Config dsynthfm_config;
    DSampler::Config dsampler_config;

    DBass::Config dbass_config;
    DSnare::Config dsnare_config;
    DHihat::Config dhihat_config;
    DClap::Config dclap_config;
    DCymbal::Config dcymbal_config;
    DDrum::Config ddrum_config;

    uint8_t note_play[GUI_NOTE_MAX];
    // maps ASCII code to relative note value
    uint8_t note_map[GUI_NOTE_MAP_MAX][2] =
        {
        {122, 0}, // z - C
        {115, 1}, // s
        {120, 2}, // x
        {100, 3}, // d
        {99, 4}, // c
        {118, 5}, // v
        {103, 6}, // g
        {98, 7}, // b
        {104, 8}, // h
        {110, 9}, // n
        {106, 10}, // j
        {109, 11}, // m
        {44, 12} // ,
        };

    enum SynthEngine
    {
        SUB,
        FM,
        VAR,
        VAR_SEQ,
        SAMPLER,
        DRUM,
    };

    SynthEngine synth_engine = SUB;

    ofxPanel gui_sub, gui_fm, gui_var, gui_sampler;

    ofParameter<void> gui_save, gui_load;
    ofParameter<int> gui_synth_engine{"Synth SFVqSD", (int)synth_engine, 0, 5};

    // dsynthsub

    ofParameterGroup gui_sub_group_osc;
    ofParameter<int> gui_sub_voices{"Voices", 1, 1, GUI_VOICES_MAX};
    ofParameter<int> gui_sub_waveform0{"Waveform0", 0, 0, 7};
    ofParameter<int> gui_sub_waveform1{"Waveform1", 0, 0, 7};
    ofParameter<float> gui_sub_tune{"Tune", 0, -50, 50};
    ofParameter<float> gui_sub_detune{"Detune", 0, -10, 10};
    ofParameter<int> gui_sub_transpose{"Transpose", 0, -24, 24};
    ofParameter<float> gui_sub_osc0_level{"Osc0 level", 0, 0, 1};
    ofParameter<float> gui_sub_osc1_level{"Osc1 level", 0, 0, 1};
    ofParameter<float> gui_sub_noise_level{"Noise level", 0, 0, 1};

    ofParameterGroup gui_sub_group_filter;
    ofParameter<int> gui_sub_filter_type{"Type (Band, High, Low, Notch, Peak, Pass)", 0, 0, 5};
    ofParameter<float> gui_sub_filter_cutoff{"Cutoff", 0, 0, DSTUDIO_FILTER_BASE};
    ofParameter<float> gui_sub_filter_res{"Res", 0, 0, 1};

    ofParameterGroup gui_sub_group_eg_p;
    ofParameter<float> gui_sub_eg_p_level{"Level", 0, 0, 1};
    ofParameter<float> gui_sub_eg_p_attack{"A", 0, 0, 10};
    ofParameter<float> gui_sub_eg_p_decay{"D", 0, 0, 10};
    ofParameter<float> gui_sub_eg_p_sustain{"S", 0, 0, 1};
    ofParameter<float> gui_sub_eg_p_release{"R", 0, 0, 10};

    ofParameterGroup gui_sub_group_eg_f;
    ofParameter<float> gui_sub_eg_f_level{"Level", 0, 0, 1};
    ofParameter<float> gui_sub_eg_f_attack{"A", 0, 0, 10};
    ofParameter<float> gui_sub_eg_f_decay{"D", 0, 0, 10};
    ofParameter<float> gui_sub_eg_f_sustain{"S", 0, 0, 1};
    ofParameter<float> gui_sub_eg_f_release{"R", 0, 0, 10};

    ofParameterGroup gui_sub_group_eg_a;
    ofParameter<float> gui_sub_eg_a_attack{"A", 0, 0, 100};
    ofParameter<float> gui_sub_eg_a_decay{"D", 0, 0, 10};
    ofParameter<float> gui_sub_eg_a_sustain{"S", 0, 0, 1};
    ofParameter<float> gui_sub_eg_a_release{"R", 0, 0, 10};

    ofParameterGroup gui_sub_group_lfo;
    ofParameter<int> gui_sub_lfo_waveform{"Waveform", 0, 0, 7};
    ofParameter<float> gui_sub_lfo_freq{"Freq", 0, 0, 1000};
    ofParameter<float> gui_sub_lfo_amp{"Amp", 0, 0, 1};
    ofParameter<float> gui_sub_lfo_p_level{"P level", 0, 0, 1};
    ofParameter<float> gui_sub_lfo_f_level{"F level", 0, 0, 1};
    ofParameter<float> gui_sub_lfo_a_level{"A level", 0, 0, 1};

    ofParameterGroup gui_sub_group_fx;
    ofParameter<float> gui_sub_portamento{"Portamento", 0, 0, 10};
    ofParameter<float> gui_sub_delay_delay{"Delay time", 0, 0, DSYNTHSUB_DELAY_MAX_S};
    ofParameter<float> gui_sub_delay_feedback{"Delay fb", 0, 0, 1};
    ofParameter<float> gui_sub_overdrive_gain{"OD gain", 0, 0, 1};
    ofParameter<float> gui_sub_overdrive_drive{"OD drive", 0, 0, 1};

    // synthfm

    ofParameterGroup gui_fm_group_osc;
    ofParameter<int> gui_fm_voices{"Voices", 1, 1, GUI_VOICES_MAX};
    ofParameter<float> gui_fm_ratio{"Ratio", 0, 0, 2};
    ofParameter<float> gui_fm_index{"Index", 0, 0, 2};
    ofParameter<float> gui_fm_tune{"Tune", 0, -50, 50};
    ofParameter<int> gui_fm_transpose{"Transpose", 0, -24, 24};
    ofParameter<float> gui_fm_noise_level{"Noise level", 0, 0, 1};

    ofParameterGroup gui_fm_group_filter;
    ofParameter<int> gui_fm_filter_type{"Type (Band, High, Low, Notch, Peak, Pass)", 0, 0, 5};
    ofParameter<float> gui_fm_filter_cutoff{"Cutoff", 0, 0, DSTUDIO_FILTER_BASE};
    ofParameter<float> gui_fm_filter_res{"Res", 0, 0, 1};

    ofParameterGroup gui_fm_group_eg_p;
    ofParameter<float> gui_fm_eg_p_level{"Level", 0, 0, 1};
    ofParameter<float> gui_fm_eg_p_attack{"A", 0, 0, 10};
    ofParameter<float> gui_fm_eg_p_decay{"D", 0, 0, 10};
    ofParameter<float> gui_fm_eg_p_sustain{"S", 0, 0, 1};
    ofParameter<float> gui_fm_eg_p_release{"R", 0, 0, 10};

    ofParameterGroup gui_fm_group_eg_f;
    ofParameter<float> gui_fm_eg_f_level{"Level", 0, 0, 1};
    ofParameter<float> gui_fm_eg_f_attack{"A", 0, 0, 10};
    ofParameter<float> gui_fm_eg_f_decay{"D", 0, 0, 10};
    ofParameter<float> gui_fm_eg_f_sustain{"S", 0, 0, 1};
    ofParameter<float> gui_fm_eg_f_release{"R", 0, 0, 10};

    ofParameterGroup gui_fm_group_eg_a;
    ofParameter<float> gui_fm_eg_a_attack{"A", 0, 0, 10};
    ofParameter<float> gui_fm_eg_a_decay{"D", 0, 0, 10};
    ofParameter<float> gui_fm_eg_a_sustain{"S", 0, 0, 1};
    ofParameter<float> gui_fm_eg_a_release{"R", 0, 0, 10};

    ofParameterGroup gui_fm_group_lfo;
    ofParameter<int> gui_fm_lfo_waveform{"Waveform", 0, 0, 7};
    ofParameter<float> gui_fm_lfo_freq{"Freq", 0, 0, 1000};
    ofParameter<float> gui_fm_lfo_amp{"Amp", 0, 0, 1};
    ofParameter<float> gui_fm_lfo_p_level{"P level", 0, 0, 1};
    ofParameter<float> gui_fm_lfo_f_level{"F level", 0, 0, 1};
    ofParameter<float> gui_fm_lfo_a_level{"A level", 0, 0, 1};

    ofParameterGroup gui_fm_group_fx;
    ofParameter<float> gui_fm_portamento{"Portamento", 0, 0, 10};
    ofParameter<float> gui_fm_delay_delay{"Delay time", 0, 0, DSYNTHFM_DELAY_MAX_S};
    ofParameter<float> gui_fm_delay_feedback{"Delay fb", 0, 0, 1};
    ofParameter<float> gui_fm_overdrive_gain{"OD gain", 0, 0, 1};
    ofParameter<float> gui_fm_overdrive_drive{"OD drive", 0, 0, 1};

    // dsynthvar

    ofParameterGroup gui_var_group_osc;
    ofParameter<int> gui_var_voices{"Voices", 1, 1, GUI_VOICES_MAX};
    ofParameter<float> gui_var_waveshape{"Waveshape", 0, 0, 1};
    ofParameter<float> gui_var_pulsewidth{"Pulsewidth", 0, 0, 1};
    ofParameter<bool> gui_var_sync_enable{"Sync enable", 1, 0, 1};
    ofParameter<float> gui_var_sync_freq{"Sync freq", 0, 0, DSTUDIO_FILTER_BASE};
    ofParameter<float> gui_var_tune{"Tune", 0, -50, 50};
    ofParameter<int> gui_var_transpose{"Transpose", 0, -24, 24};
    ofParameter<float> gui_var_osc_level{"Osc level", 0, 0, 1};
    ofParameter<float> gui_var_noise_level{"Noise level", 0, 0, 1};

    ofParameterGroup gui_var_group_filter;
    ofParameter<int> gui_var_filter_type{"Type (Band, High, Low, Notch, Peak, Pass)", 0, 0, 5};
    ofParameter<float> gui_var_filter_cutoff{"Cutoff", 0, 0, DSTUDIO_FILTER_BASE};
    ofParameter<float> gui_var_filter_res{"Res", 0, 0, 1};

    ofParameterGroup gui_var_group_mod;
    ofParameter<int> gui_var_mod_eg_p{"EG pitch", 0, 0, 9};
    ofParameter<int> gui_var_mod_eg_f{"EG filter", 0, 0, 9};
    ofParameter<int> gui_var_mod_eg_a{"EG amp", 0, 0, 9};
    ofParameter<int> gui_var_mod_filter_cutoff{"Filter cutoff", 0, 0, 9};
    ofParameter<int> gui_var_mod_waveshape{"Waveshape", 0, 0, 9};
    ofParameter<int> gui_var_mod_pulsewidth{"Pulsewidth", 0, 0, 9};
    ofParameter<int> gui_var_mod_sync_freq{"Sync freq", 0, 0, 9};
    ofParameter<int> gui_var_mod_delay{"Delay delay", 0, 0, 9};

    ofParameterGroup gui_var_group_eg_0;
    ofParameter<float> gui_var_eg_0_level{"Level", 0, 0, 1};
    ofParameter<float> gui_var_eg_0_attack{"A", 0, 0, 10};
    ofParameter<float> gui_var_eg_0_decay{"D", 0, 0, 10};
    ofParameter<float> gui_var_eg_0_sustain{"S", 0, 0, 1};
    ofParameter<float> gui_var_eg_0_release{"R", 0, 0, 10};

    ofParameterGroup gui_var_group_eg_1;
    ofParameter<float> gui_var_eg_1_level{"Level", 0, 0, 1};
    ofParameter<float> gui_var_eg_1_attack{"A", 0, 0, 10};
    ofParameter<float> gui_var_eg_1_decay{"D", 0, 0, 10};
    ofParameter<float> gui_var_eg_1_sustain{"S", 0, 0, 1};
    ofParameter<float> gui_var_eg_1_release{"R", 0, 0, 10};

    ofParameterGroup gui_var_group_eg_2;
    ofParameter<float> gui_var_eg_2_level{"Level", 0, 0, 1};
    ofParameter<float> gui_var_eg_2_attack{"A", 0, 0, 10};
    ofParameter<float> gui_var_eg_2_decay{"D", 0, 0, 10};
    ofParameter<float> gui_var_eg_2_sustain{"S", 0, 0, 1};
    ofParameter<float> gui_var_eg_2_release{"R", 0, 0, 10};

    ofParameterGroup gui_var_group_lfo_0;
    ofParameter<int> gui_var_lfo_0_waveform{"Waveform", 0, 0, 7};
    ofParameter<float> gui_var_lfo_0_freq{"Freq", 0, 0, 1000};
    ofParameter<float> gui_var_lfo_0_amp{"Amp", 0, 0, 1};
    ofParameter<float> gui_var_lfo_0_offset{"Offset", 0, 0, 1};

    ofParameterGroup gui_var_group_lfo_1;
    ofParameter<int> gui_var_lfo_1_waveform{"Waveform", 0, 0, 7};
    ofParameter<float> gui_var_lfo_1_freq{"Freq", 0, 0, 1000};
    ofParameter<float> gui_var_lfo_1_amp{"Amp", 0, 0, 1};
    ofParameter<float> gui_var_lfo_1_offset{"Offset", 0, 0, 1};

    ofParameterGroup gui_var_group_lfo_2;
    ofParameter<int> gui_var_lfo_2_waveform{"Waveform", 0, 0, 7};
    ofParameter<float> gui_var_lfo_2_freq{"Freq", 0, 0, 1000};
    ofParameter<float> gui_var_lfo_2_amp{"Amp", 0, 0, 1};
    ofParameter<float> gui_var_lfo_2_offset{"Offset", 0, 0, 1};

    ofParameterGroup gui_var_group_sm_0;
    ofParameter<int> gui_var_sm_0_type{"Type (Noise, Crawl, interval, Chaos, Seq)", 0, 0, DSTUDIO_SM_TYPE_MAX - 1};
    ofParameter<float> gui_var_sm_0_freq{"Freq", 0, 0, 1000};
    ofParameter<float> gui_var_sm_0_amp{"Amp", 0, 0, 1};
    ofParameter<float> gui_var_sm_0_offset{"Offset", 0, 0, 1};

    ofParameterGroup gui_var_group_sm_1;
    ofParameter<int> gui_var_sm_1_type{"Type (Noise, Crawl, interval, Chaos, Seq)", 0, 0, DSTUDIO_SM_TYPE_MAX - 1};
    ofParameter<float> gui_var_sm_1_freq{"Freq", 0, 0, 1000};
    ofParameter<float> gui_var_sm_1_amp{"Amp", 0, 0, 1};
    ofParameter<float> gui_var_sm_1_offset{"Offset", 0, 0, 1};

    ofParameterGroup gui_var_group_sm_2;
    ofParameter<int> gui_var_sm_2_type{"Type (Noise, Crawl, interval, Chaos, Seq)", 0, 0, DSTUDIO_SM_TYPE_MAX - 1};
    ofParameter<float> gui_var_sm_2_freq{"Freq", 0, 0, 1000};
    ofParameter<float> gui_var_sm_2_amp{"Amp", 0, 0, 1};
    ofParameter<float> gui_var_sm_2_offset{"Offset", 0, 0, 1};

    ofParameterGroup gui_var_group_fx;
    ofParameter<float> gui_var_portamento{"Portamento", 0, 0, 10};
    ofParameter<float> gui_var_delay_delay{"Delay time", 0, 0, DSYNTHVAR_DELAY_MAX_S};
    ofParameter<float> gui_var_delay_feedback{"Delay fb", 0, 0, 1};
    ofParameter<float> gui_var_overdrive_gain{"OD gain", 0, 0, 1};
    ofParameter<float> gui_var_overdrive_drive{"OD drive", 0, 0, 1};

    // dsampler

    ofParameterGroup gui_sampler_group_osc;
    ofParameter<int> gui_sampler_voices{"Voices", 1, 1, GUI_VOICES_MAX};
    ofParameter<void> gui_sampler_sample;
    ofParameter<string> gui_sampler_file_name{"File"};
    ofParameter<int> gui_sampler_phase_start{"Start", 0, 0, 1};
    ofParameter<int> gui_sampler_phase_loop_start{"Loop start", 0, 0, 1};
    ofParameter<int> gui_sampler_phase_loop_end{"Loop end", 0, 0, 1};
    ofParameter<int> gui_sampler_phase_end{"End", 0, 0, 1};
    ofParameter<bool> gui_sampler_loop{"Loop", 0};
    ofParameter<float> gui_sampler_tune{"Tune", 0, -50, 50};
    ofParameter<int> gui_sampler_transpose{"Transpose", 0, -24, 24};

    ofParameterGroup gui_sampler_group_filter;
    ofParameter<int> gui_sampler_filter_type{"Type (Band, High, Low, Notch, Peak, Pass)", 0, 0, 5};
    ofParameter<float> gui_sampler_filter_cutoff{"Cutoff", 0, 0, DSTUDIO_FILTER_BASE};
    ofParameter<float> gui_sampler_filter_res{"Res", 0, 0, 1};

    ofParameterGroup gui_sampler_group_eg_p;
    ofParameter<float> gui_sampler_eg_p_level{"Level", 0, 0, 1};
    ofParameter<float> gui_sampler_eg_p_attack{"A", 0, 0, 10};
    ofParameter<float> gui_sampler_eg_p_decay{"D", 0, 0, 10};
    ofParameter<float> gui_sampler_eg_p_sustain{"S", 0, 0, 1};
    ofParameter<float> gui_sampler_eg_p_release{"R", 0, 0, 10};

    ofParameterGroup gui_sampler_group_eg_f;
    ofParameter<float> gui_sampler_eg_f_level{"Level", 0, 0, 1};
    ofParameter<float> gui_sampler_eg_f_attack{"A", 0, 0, 10};
    ofParameter<float> gui_sampler_eg_f_decay{"D", 0, 0, 10};
    ofParameter<float> gui_sampler_eg_f_sustain{"S", 0, 0, 1};
    ofParameter<float> gui_sampler_eg_f_release{"R", 0, 0, 10};

    ofParameterGroup gui_sampler_group_eg_a;
    ofParameter<float> gui_sampler_eg_a_attack{"A", 0, 0, 10};
    ofParameter<float> gui_sampler_eg_a_decay{"D", 0, 0, 10};
    ofParameter<float> gui_sampler_eg_a_sustain{"S", 0, 0, 1};
    ofParameter<float> gui_sampler_eg_a_release{"R", 0, 0, 10};

    ofParameterGroup gui_sampler_group_lfo;
    ofParameter<int> gui_sampler_lfo_waveform{"Waveform", 0, 0, 7};
    ofParameter<float> gui_sampler_lfo_freq{"Freq", 0, 0, 1000};
    ofParameter<float> gui_sampler_lfo_amp{"Amp", 0, 0, 1};
    ofParameter<float> gui_sampler_lfo_p_level{"P level", 0, 0, 1};
    ofParameter<float> gui_sampler_lfo_f_level{"F level", 0, 0, 1};
    ofParameter<float> gui_sampler_lfo_a_level{"A level", 0, 0, 1};

    ofParameterGroup gui_sampler_group_fx;
    ofParameter<float> gui_sampler_portamento{"Portamento", 0, 0, 10};
    ofParameter<float> gui_sampler_delay_delay{"Delay time", 0, 0, DSAMPLER_DELAY_MAX_S};
    ofParameter<float> gui_sampler_delay_feedback{"Delay fb", 0, 0, 1};
    ofParameter<float> gui_sampler_overdrive_gain{"OD gain", 0, 0, 1};
    ofParameter<float> gui_sampler_overdrive_drive{"OD drive", 0, 0, 1};

    // dsynthvar - seq

    ofxPanel gui_seq;
    ofParameterGroup gui_seq_0_group, gui_seq_1_group, gui_seq_2_group;
    ofParameter<int> gui_seq_0_step_max{"Steps 0", 0, 0, GUI_SEQ_STEP_MAX};
    ofParameter<int> gui_seq_1_step_max{"Steps 1", 0, 0, GUI_SEQ_STEP_MAX};
    ofParameter<int> gui_seq_2_step_max{"Steps 2", 0, 0, GUI_SEQ_STEP_MAX};
    ofParameter<float> gui_seq_0_step[GUI_SEQ_STEP_MAX];
    ofParameter<float> gui_seq_1_step[GUI_SEQ_STEP_MAX];
    ofParameter<float> gui_seq_2_step[GUI_SEQ_STEP_MAX];

    // drum

    ofxPanel gui_d;

    // bass
    ofParameterGroup gui_d_bass;
    // common
    ofParameter<int> gui_d_bass_type{"Type ASO", 1, 1, 3};
    ofParameter<float> gui_d_bass_freq{"Freq", 0, 0, 999};
    ofParameter<float> gui_d_bass_tone{"Tone", 0, 0, 1};
    ofParameter<float> gui_d_bass_decay{"Decay", 0, 0, 1};
    // analog
    ofParameter<float> gui_d_bass_fm_attack{"Analog Attack", 0, 0, 1};
    ofParameter<float> gui_d_bass_fm_self{"Analog Self", 0, 0, 1};
    // synthetic
    ofParameter<float> gui_d_bass_dirtiness{"Synth Dirtiness", 0, 0, 1};
    ofParameter<float> gui_d_bass_fm_env_amount{"Synth FM env", 0, 0, 1};
    ofParameter<float> gui_d_bass_fm_env_decay{"Synth FM decay", 0, 0, 1};
    // opd
    ofParameter<float> gui_d_bass_min{"OPD Min", 0, 0, 1};

    // snare
    ofParameterGroup gui_d_snare;
    // common
    ofParameter<int> gui_d_snare_type{"Type ASO", 1, 1, 3};
    ofParameter<float> gui_d_snare_freq{"Freq", 0, 0, 999};
    ofParameter<float> gui_d_snare_tone{"Tone", 0, 0, 1};
    ofParameter<float> gui_d_snare_decay{"Decay", 0, 0, 1};
    // analog
    ofParameter<float> gui_d_snare_snappy{"Analog Snappy", 0, 0, 1};
    // synthetic
    ofParameter<float> gui_d_snare_fm_amount{"Synth FM amount", 0, 0, 1};
    // opd
    ofParameter<float> gui_d_snare_freq_noise{"OPD Freq noise", 0, 0, DSTUDIO_FILTER_BASE};
    ofParameter<float> gui_d_snare_amp{"OPD Amp", 0, 0, 1};
    ofParameter<float> gui_d_snare_res{"OPD Res", 0, 0, 1};
    ofParameter<float> gui_d_snare_drive{"OPD Drive", 0, 0, 1};
    ofParameter<float> gui_d_snare_min{"OPD Min", 0, 0, 1};

    // hihat
    ofParameterGroup gui_d_hihat;
    // common
    ofParameter<int> gui_d_hihat_type{"Type ASO", 1, 1, 3};
    ofParameter<float> gui_d_hihat_freq{"Freq", 0, 0, DSTUDIO_FILTER_BASE};
    ofParameter<float> gui_d_hihat_tone{"Tone", 0, 0, 1};
    ofParameter<float> gui_d_hihat_decay{"Decay", 0, 0, 1};
    // analog
    // synthetic
    ofParameter<float> gui_d_hihat_noisiness{"Synth/Analog Noisiness", 0, 0, 1};
    // opd
    ofParameter<float> gui_d_hihat_amp{"OPD Amp", 0, 0, 1};
    ofParameter<float> gui_d_hihat_res{"OPD Res", 0, 0, 1};
    ofParameter<float> gui_d_hihat_drive{"OPD Drive", 0, 0, 1};

    // clap
    ofParameterGroup gui_d_clap;
    ofParameter<float> gui_d_clap_freq{"Freq", 0, 0, DSTUDIO_FILTER_BASE};
    ofParameter<float> gui_d_clap_res{"Res", 0, 0, 1};
    ofParameter<float> gui_d_clap_drive{"Drive", 0, 0, 1};
    ofParameter<float> gui_d_clap_amp{"Amp", 0, 0, 1};
    ofParameter<float> gui_d_clap_decay{"Decay", 0, 0, 1};

    // cymbal
    ofParameterGroup gui_d_cymbal;
    ofParameter<float> gui_d_cymbal_freq{"Freq", 0, 0, DSTUDIO_FILTER_BASE};
    ofParameter<float> gui_d_cymbal_res{"Res", 0, 0, 1};
    ofParameter<float> gui_d_cymbal_drive{"Drive", 0, 0, 1};
    ofParameter<float> gui_d_cymbal_amp{"Amp", 0, 0, 1};
    ofParameter<float> gui_d_cymbal_decay{"Decay", 0, 0, 1};
    ofParameter<float> gui_d_cymbal_min{"Min", 0, 0, 1};
    ofParameter<float> gui_d_cymbal_mix{"Mix", 0, 0, 1};

    // tom
    ofParameterGroup gui_d_drum;
    ofParameter<float> gui_d_drum_freq{"Freq", 0, 0, DSTUDIO_FILTER_BASE};
    ofParameter<float> gui_d_drum_amp{"Amp", 0, 0, 1};
    ofParameter<float> gui_d_drum_decay{"Decay", 0, 0, 1};
    ofParameter<float> gui_d_drum_min{"Min", 0, 0, 1};

    void GuiSetupSub();
    void GuiSetupFm();
    void GuiSetupVar();
    void GuiSetupSampler();
    void GuiSetupSeq();
    void GuiSetupD();

    void GuiSetSub();
    void GuiSetFm();
    void GuiSetVar();
    void GuiSetSampler();
    void GuiSetSeq();
    void GuiSetD();

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void exit();

    void audioOut(ofSoundBuffer &outBuffer);
    ofSoundStream soundStream;

    void newMidiMessage(ofxMidiMessage& eventArgs);
    ofxMidiIn midiIn;

    uint8_t noteMap(int);
    void saveButtonPressed();
    void loadButtonPressed();
    void sampleButtonPressed();

};
