#include "ofApp.h"

#include "dstudio.h"
#include "dsynthsub.h"
#include "dsynthvar.h"
#include "dsynthfm.h"
#include "dsampler.h"

#include "dbass.h"
#include "dsnare.h"
#include "dhihat.h"

#include "dseqperm.h"
#include "dfx.h"



void ofApp::setup(){

    // soundstream setup
    ofSoundStreamSettings settings;

    // soundStream.printDeviceList();
    // std::vector<ofSoundDevice> devices = soundStream.getDeviceList(ofSoundDevice::Api::ALSA);
    // settings.setOutDevice(devices[0]);

    settings.numOutputChannels = 2;
    settings.sampleRate = DSTUDIO_SAMPLE_RATE;
    settings.bufferSize = DSTUDIO_BUFFER_SIZE;
    settings.numBuffers = DSTUDIO_NUM_BUFFERS;

    // synths subtractive
    DSynthSub::Config dsynth_config;

    // synth bass 1
    dsynth_config.sample_rate = settings.sampleRate;
    dsynth_config.voices = 1;
    dsynth_config.waveform0 = DSynthSub::WAVE_SAW;
    dsynth_config.waveform1 = DSynthSub::WAVE_POLYBLEP_SAW;
    dsynth_config.tune = 0.0f;
    dsynth_config.detune = 0.2f;
    dsynth_config.transpose = 0;
    dsynth_config.osc0_level = 0.8f;
    dsynth_config.osc1_level = 0.2f;
    dsynth_config.noise_level = 0.1f;
    dsynth_config.filter_type = DSynthSub::LOW;
    dsynth_config.filter_cutoff = 500.0f;
    dsynth_config.filter_res = 0.2f;
    dsynth_config.eg_p_level = 0.0f;
    dsynth_config.eg_p_attack = 0.0f;
    dsynth_config.eg_p_decay = 0.0f;
    dsynth_config.eg_p_sustain = 0.0f;
    dsynth_config.eg_p_release = 0.0f;
    dsynth_config.eg_f_level = 1.0f;
    dsynth_config.eg_f_attack = 0.1f;
    dsynth_config.eg_f_decay = 0.0f;
    dsynth_config.eg_f_sustain = 1.f;
    dsynth_config.eg_f_release = 0.2f;
    dsynth_config.eg_a_attack = 0.0f;
    dsynth_config.eg_a_decay = 0.1f;
    dsynth_config.eg_a_sustain = 0.0f;
    dsynth_config.eg_a_release = 0.15f;
    dsynth_config.lfo_waveform = DSynthSub::WAVE_TRI;
    dsynth_config.lfo_freq = 0.2f;
    dsynth_config.lfo_amp = 1.0f;
    dsynth_config.lfo_p_level = 0.0f;
    dsynth_config.lfo_f_level = 0.8f;
    dsynth_config.lfo_a_level = 0.0f;
    dsynth_config.portamento = 0.0f;
    dsynth_config.delay_delay = 0.0f;
    dsynth_config.delay_feedback = 0.0f;
    dsynth_config.overdrive_gain = 0.0f;
    dsynth_config.overdrive_drive = 0.0f;
    dsynthbass1.Init(dsynth_config);

    // synth arp1
    dsynth_config.sample_rate = settings.sampleRate;
    dsynth_config.voices = 2;
    dsynth_config.waveform0 = DSynthSub::WAVE_SAW;
    dsynth_config.waveform1 = DSynthSub::WAVE_SAW;
    dsynth_config.tune = 0.0f;
    dsynth_config.detune = 0.1f;
    dsynth_config.transpose = 12;
    dsynth_config.osc0_level = 0.5f;
    dsynth_config.osc1_level = 0.5f;
    dsynth_config.noise_level = 0.0f;
    dsynth_config.filter_type = DSynthSub::LOW;
    dsynth_config.filter_cutoff = 1600.0f;
    dsynth_config.filter_res = 0.0f;
    dsynth_config.eg_p_level = 0.0f;
    dsynth_config.eg_p_attack = 0.0f;
    dsynth_config.eg_p_decay = 0.0f;
    dsynth_config.eg_p_sustain = 0.0f;
    dsynth_config.eg_p_release = 0.0f;
    dsynth_config.eg_f_level = 1.0f;
    dsynth_config.eg_f_attack = 0.0f;
    dsynth_config.eg_f_decay = 0.0f;
    dsynth_config.eg_f_sustain = 1.0f;
    dsynth_config.eg_f_release = 2.0f;
    dsynth_config.eg_a_attack = 0.01f;
    dsynth_config.eg_a_decay = 0.1f;
    dsynth_config.eg_a_sustain = 0.8f;
    dsynth_config.eg_a_release = 0.5f;
    dsynth_config.lfo_waveform = DSynthSub::WAVE_TRI;
    dsynth_config.lfo_freq = 1.0f;
    dsynth_config.lfo_amp = 0.9f;
    dsynth_config.lfo_p_level = 0.0f;
    dsynth_config.lfo_f_level = 0.0f;
    dsynth_config.lfo_a_level = 0.0f;
    dsynth_config.portamento = 0.0f;
    dsynth_config.delay_delay = 0.5f;
    dsynth_config.delay_feedback = 0.5f;
    dsynth_config.overdrive_gain = 0.0f;
    dsynth_config.overdrive_drive = 0.0f;
    dsyntharp1.Init(dsynth_config);

    // synth arp2 (fm)
    DSynthFm::Config dsynthfm_config;
    dsynthfm_config.sample_rate = settings.sampleRate;
    dsynthfm_config.voices = 2;
    dsynthfm_config.ratio = 2.0f;
    dsynthfm_config.index = 1.0f;
    dsynthfm_config.tune = 0.0f;
    dsynthfm_config.transpose = 12;
    dsynthfm_config.noise_level = 0.0f;
    dsynthfm_config.filter_type = DSynthFm::LOW;
    dsynthfm_config.filter_cutoff = 1000.0f;
    dsynthfm_config.filter_res = 0.0f;
    dsynthfm_config.eg_p_level = 0.0f;
    dsynthfm_config.eg_p_attack = 0.0f;
    dsynthfm_config.eg_p_decay = 0.0f;
    dsynthfm_config.eg_p_sustain = 0.0f;
    dsynthfm_config.eg_p_release = 0.0f;
    dsynthfm_config.eg_f_level = 1.0f;
    dsynthfm_config.eg_f_attack = 0.0f;
    dsynthfm_config.eg_f_decay = 0.0f;
    dsynthfm_config.eg_f_sustain = 1.0f;
    dsynthfm_config.eg_f_release = 0.0f;
    dsynthfm_config.eg_a_attack = 0.01f;
    dsynthfm_config.eg_a_decay = 0.01f;
    dsynthfm_config.eg_a_sustain = 1.0f;
    dsynthfm_config.eg_a_release = 0.2f;
    dsynthfm_config.lfo_waveform = DSynthFm::WAVE_TRI;
    dsynthfm_config.lfo_freq = 0.6f;
    dsynthfm_config.lfo_amp = 0.8f;
    dsynthfm_config.lfo_p_level = 0.0f;
    dsynthfm_config.lfo_f_level = 0.0f;
    dsynthfm_config.lfo_a_level = 0.0f;
    dsynthfm_config.portamento = 0.0f;
    dsynthfm_config.delay_delay = 0.3f;
    dsynthfm_config.delay_feedback = 0.6f;
    dsynthfm_config.overdrive_gain = 0.0f;
    dsynthfm_config.overdrive_drive = 0.0f;
    dsyntharp2.Init(dsynthfm_config);

    // synth arp 3 (sub)
    dsynth_config.sample_rate = settings.sampleRate;
    dsynth_config.voices = 1;
    dsynth_config.waveform0 = DSynthSub::WAVE_SAW;
    dsynth_config.waveform1 = DSynthSub::WAVE_POLYBLEP_TRI;
    dsynth_config.tune = 0.0f;
    dsynth_config.detune = 0.1f;
    dsynth_config.transpose = 0;
    dsynth_config.osc0_level = 0.3f;
    dsynth_config.osc1_level = 0.5f;
    dsynth_config.noise_level = 0.0f;
    dsynth_config.filter_type = DSynthSub::BAND;
    dsynth_config.filter_cutoff = 1200.0f;
    dsynth_config.filter_res = 0.1f;
    dsynth_config.eg_p_level = 0.0f;
    dsynth_config.eg_p_attack = 0.0f;
    dsynth_config.eg_p_decay = 0.0f;
    dsynth_config.eg_p_sustain = 0.0f;
    dsynth_config.eg_p_release = 0.0f;
    dsynth_config.eg_f_level = 1.0f;
    dsynth_config.eg_f_attack = 0.0f;
    dsynth_config.eg_f_decay = 0.0f;
    dsynth_config.eg_f_sustain = 1.f;
    dsynth_config.eg_f_release = 1.0f;
    dsynth_config.eg_a_attack = 0.0f;
    dsynth_config.eg_a_decay = 0.2f;
    dsynth_config.eg_a_sustain = 0.0f;
    dsynth_config.eg_a_release = 0.1f;
    dsynth_config.lfo_waveform = DSynthSub::WAVE_TRI;
    dsynth_config.lfo_freq = 10.0f;
    dsynth_config.lfo_amp = 1.0f;
    dsynth_config.lfo_p_level = 0.0f;
    dsynth_config.lfo_f_level = 0.0f;
    dsynth_config.lfo_a_level = 0.0f;
    dsynth_config.portamento = 0.0f;
    dsynth_config.delay_delay = 0.4f;
    dsynth_config.delay_feedback = 0.4f;
    dsynth_config.overdrive_gain = 0.0f;
    dsynth_config.overdrive_drive = 0.0f;
    dsyntharp3.Init(dsynth_config);

    // lead (sub)
    dsynth_config.sample_rate = settings.sampleRate;
    dsynth_config.voices = 1;
    dsynth_config.waveform0 = DSynthSub::WAVE_SAW;
    dsynth_config.waveform1 = DSynthSub::WAVE_TRI;
    dsynth_config.tune = 0.0f;
    dsynth_config.detune = 0.1f;
    dsynth_config.transpose = 24;
    dsynth_config.osc0_level = 0.5f;
    dsynth_config.osc1_level = 0.2f;
    dsynth_config.noise_level = 0.0f;
    dsynth_config.filter_type = DSynthSub::LOW;
    dsynth_config.filter_cutoff = 1000.0f;
    dsynth_config.filter_res = 0.2f;
    dsynth_config.eg_p_level = 0.0f;
    dsynth_config.eg_p_attack = 0.0f;
    dsynth_config.eg_p_decay = 0.0f;
    dsynth_config.eg_p_sustain = 0.0f;
    dsynth_config.eg_p_release = 0.0f;
    dsynth_config.eg_f_level = 1.0f;
    dsynth_config.eg_f_attack = 0.3f;
    dsynth_config.eg_f_decay = 0.0f;
    dsynth_config.eg_f_sustain = 1.f;
    dsynth_config.eg_f_release = 1.0f;
    dsynth_config.eg_a_attack = 0.0f;
    dsynth_config.eg_a_decay = 0.0f;
    dsynth_config.eg_a_sustain = 1.f;
    dsynth_config.eg_a_release = 0.5f;
    dsynth_config.lfo_waveform = DSynthSub::WAVE_TRI;
    dsynth_config.lfo_freq = 0.3f;
    dsynth_config.lfo_amp = 1.0f;
    dsynth_config.lfo_p_level = 0.0f;
    dsynth_config.lfo_f_level = 0.8f;
    dsynth_config.lfo_a_level = 0.0f;
    dsynth_config.portamento = 0.0f;
    dsynth_config.delay_delay = 0.2f;
    dsynth_config.delay_feedback = 0.4f;
    dsynth_config.overdrive_gain = 0.0f;
    dsynth_config.overdrive_drive = 0.0f;
    dsynthlead.Init(dsynth_config);

    // synth pad (var)
    DSynthVar::Config dsynthvar_config;
    dsynthvar_config.sample_rate = settings.sampleRate;
    dsynthvar_config.voices = 5;
    dsynthvar_config.waveshape = 1.0f;
    dsynthvar_config.pulsewidth = 0.5f;
    dsynthvar_config.sync_enable = true;
    dsynthvar_config.sync_freq = 440.0f;
    dsynthvar_config.osc_level = 0.4f;
    dsynthvar_config.noise_level = 0.0f;
    dsynthvar_config.tune = 0.0f;
    dsynthvar_config.transpose = -12;
    dsynthvar_config.filter_type = DSynthVar::LOW;
    dsynthvar_config.filter_cutoff = 800.0f;
    dsynthvar_config.filter_res = 0.0f;
    dsynthvar_config.mod_eg_p = DSYNTHVAR_MOD_NONE;
    dsynthvar_config.mod_eg_f = DSYNTHVAR_MOD_NONE;
    dsynthvar_config.mod_eg_a = DSYNTHVAR_MOD_EG1;
    dsynthvar_config.mod_filter_cutoff = DSYNTHVAR_MOD_SM2;
    dsynthvar_config.mod_waveshape = DSYNTHVAR_MOD_NONE;
    dsynthvar_config.mod_pulsewidth = DSYNTHVAR_MOD_LFO1;
    dsynthvar_config.mod_sync_freq = DSYNTHVAR_MOD_LFO1; // preferably same as mod_eg_p
    dsynthvar_config.mod_delay = DSYNTHVAR_MOD_NONE;
    dsynthvar_config.eg_0_level = 1.0f;
    dsynthvar_config.eg_0_attack = 0.2f;
    dsynthvar_config.eg_0_decay = 0.01f;
    dsynthvar_config.eg_0_sustain = 1.0f;
    dsynthvar_config.eg_0_release = 0.5f;
    dsynthvar_config.eg_1_level = 1.0f;
    dsynthvar_config.eg_1_attack = 1.0f;
    dsynthvar_config.eg_1_decay = 0.01f;
    dsynthvar_config.eg_1_sustain = 1.0f;
    dsynthvar_config.eg_1_release = 0.5f;
    dsynthvar_config.eg_2_level = 0.4f;
    dsynthvar_config.eg_2_attack = 0.01f;
    dsynthvar_config.eg_2_decay = 0.01f;
    dsynthvar_config.eg_2_sustain = 1.0f;
    dsynthvar_config.eg_2_release = 0.5f;
    dsynthvar_config.lfo_0_waveform = DSynthVar::WAVE_TRI;
    dsynthvar_config.lfo_0_freq = 2.0f;
    dsynthvar_config.lfo_0_amp = 1.0f;
    dsynthvar_config.lfo_0_offset = 0.0f;
    dsynthvar_config.lfo_1_waveform = DSynthVar::WAVE_TRI;
    dsynthvar_config.lfo_1_freq = 0.2f;
    dsynthvar_config.lfo_1_amp = 0.6f;
    dsynthvar_config.lfo_1_offset = 0.2f;
    dsynthvar_config.lfo_2_waveform = DSynthVar::WAVE_TRI;
    dsynthvar_config.lfo_2_freq = 0.8f;
    dsynthvar_config.lfo_2_amp = 0.3f;
    dsynthvar_config.lfo_2_offset = 0.0f;
    dsynthvar_config.sm_0_type = DSTUDIO_SM_TYPE_NOISE;
    dsynthvar_config.sm_0_freq = 10.0f;
    dsynthvar_config.sm_0_amp = 1.0f;;
    dsynthvar_config.sm_0_offset = 0.0;
    dsynthvar_config.sm_0_seq_len = 0;
    dsynthvar_config.sm_0_seq_val = {};
    dsynthvar_config.sm_1_type = DSTUDIO_SM_TYPE_CRAWL;
    dsynthvar_config.sm_1_freq = 100.0f;
    dsynthvar_config.sm_1_amp = 0.1f; // how much to change divided by 10
    dsynthvar_config.sm_1_offset = 0.3f; // prob of no change
    dsynthvar_config.sm_1_seq_len = 0;
    dsynthvar_config.sm_1_seq_val = {};
    dsynthvar_config.sm_2_type = DSTUDIO_SM_TYPE_SEQ;
    dsynthvar_config.sm_2_freq = 16.1f;
    dsynthvar_config.sm_2_amp = 0.8f;;
    dsynthvar_config.sm_2_offset = 0.0;
    dsynthvar_config.sm_2_seq_len = 8;
    dsynthvar_config.sm_2_seq_val = {1.0f, 0.0f, 0.8f, 0.2f, 0.7f, 0.3f, 0.6f, 0.4f};
    dsynthvar_config.portamento = 0.0f;
    dsynthvar_config.delay_delay = 0.6f;
    dsynthvar_config.delay_feedback = 0.0f;
    dsynthvar_config.overdrive_gain = 0.0f;
    dsynthvar_config.overdrive_drive = 0.0f;
    dsynthpad.Init(dsynthvar_config);


    // sampler1
    DSampler::Config dsampler_config;
    dsampler_config.sample_rate = settings.sampleRate;
    dsampler_config.voices = 1;
    dsampler_config.tune = 0.0f;
    dsampler_config.transpose = 0;
    dsampler_config.filter_type = DSampler::PASSTHROUGH;
    dsampler_config.filter_cutoff = 2000.0f;
    dsampler_config.filter_res = 0.0f;
    dsampler_config.eg_p_level = 0.0f;
    dsampler_config.eg_p_attack = 0.0f;
    dsampler_config.eg_p_decay = 0.0f;
    dsampler_config.eg_p_sustain = 0.0f;
    dsampler_config.eg_p_release = 0.0f;
    dsampler_config.eg_f_level = 1.0f;
    dsampler_config.eg_f_attack = 0.0f;
    dsampler_config.eg_f_decay = 0.0f;
    dsampler_config.eg_f_sustain = 1.0f;
    dsampler_config.eg_f_release = 0.0f;
    dsampler_config.eg_a_attack = 0.01f;
    dsampler_config.eg_a_decay = 0.01f;
    dsampler_config.eg_a_sustain = 1.0f;
    dsampler_config.eg_a_release = 0.2f;
    dsampler_config.lfo_waveform = DSampler::WAVE_TRI;
    dsampler_config.lfo_freq = 1.0f;
    dsampler_config.lfo_amp = 0.4f;
    dsampler_config.lfo_p_level = 0.0f;
    dsampler_config.lfo_f_level = 0.0f;
    dsampler_config.lfo_a_level = 0.0f;
    dsampler_config.portamento = 0.0f;
    dsampler_config.delay_delay = 0.3f;
    dsampler_config.delay_feedback = 0.3f;
    dsampler_config.overdrive_gain = 0.0f;
    dsampler_config.overdrive_drive = 0.0f;
    dsampler_config.loop = false;

    dsampler1.Init(dsampler_config);
    dsampler1.Load("data/ba.wav", true);

    dsampler2.Init(dsampler_config);
    dsampler2.Load("data/boing.wav", true);

    dsampler3.Init(dsampler_config);
    dsampler3.Load("data/do.wav", true);

    dsampler4.Init(dsampler_config);
    dsampler4.Load("data/tchack.wav", true);

    DSound *dsplit_synth[MIXER_CHANNELS_MAX];
    dsplit_synth[0] = &dsampler1;
    dsplit_synth[1] = &dsampler2;
    dsplit_synth[2] = &dsampler3;
    dsplit_synth[3] = &dsampler4;
    DSplitInfo dsplit_split[MIXER_CHANNELS_MAX];
    dsplit_split[0] = {36, 36, 0}; // end, offset, channel
    dsplit_split[1] = {48, 24, 1}; // end, offset, channel
    dsplit_split[2] = {60, 12, 2}; // end, offset, channel
    dsplit_split[3] = {72, 0, 3}; // end, offset, channel
    DSplit::Config dsplit_config;
    dsplit_config.sample_rate = settings.sampleRate;
    dsplit_config.channels = 4;
    dsplit_config.synth = dsplit_synth;
    dsplit_config.split = dsplit_split;
    dsplit.Init(dsplit_config);

    // filter on var shape osc to remove DC offset
    DFXFilter::Config dfxfilter_config;
    dfxfilter_config.sample_rate = settings.sampleRate;
    dfxfilter_config.level = 1.0f;
    dfxfilter_config.filter_type = DFXFilter::HIGH;
    dfxfilter_config.filter_cutoff = 200.0f;
    dfxfilter_config.filter_res = 0.0f;
    dfxfilter_config.child = &dsynthpad;
    dfxfilter.Init(dfxfilter_config);

    // drum machine

    // drum bass
    DBass::Config dbass_config;
    dbass_config.sample_rate = settings.sampleRate;
    dbass_config.type = DTYPE_SYNTHETIC;
    dbass_config.vol = 1.0f;
    dbass_config.freq = 70.0f;
    dbass_config.tone = 0.8f;
    dbass_config.decay = 0.5f;
    // analog
    dbass_config.fm_attack = 0.8f;
    dbass_config.fm_self = 0.8f;
    // synthetic
    dbass_config.dirtiness = 0.7f;
    dbass_config.fm_env_amount = 0.8f;
    dbass_config.fm_env_decay = 0.5f;
    // opd
    dbass_config.min = 0.5;
    dbass.Init(dbass_config);

    // drums snare
    DSnare::Config dsnare_config;
    dsnare_config.sample_rate = settings.sampleRate;
    dsnare_config.type = DTYPE_OPD;
    dsnare_config.vol = 1.0f;
    // common
    if (dsnare_config.type == DTYPE_OPD)
        dsnare_config.freq = 500.0f;
    else
        dsnare_config.freq = 100.0f;
    dsnare_config.tone = 0.8f;
    dsnare_config.decay = 0.1f;
    // analog
    dsnare_config.snappy = 0.3f;
    // synthetic
    dsnare_config.fm_amount = 0.1f;
    // opd
    dsnare_config.freq_noise = 1000.0f; // highpass
    dsnare_config.amp = 0.5f;
    dsnare_config.res = 0.0f;
    dsnare_config.drive = 0.3f;
    dsnare_config.min = 0.1f;
    dsnare.Init(dsnare_config);

    // drum hihat closed
    DHihat::Config dhihat_config;
    dhihat_config.sample_rate = settings.sampleRate;
    dhihat_config.type = DTYPE_OPD;
    dhihat_config.vol = 1.0f;
    // common
    dhihat_config.freq = 5000.0f;
    dhihat_config.tone = 0.8f;
    dhihat_config.decay = 0.03f;
    // analog
    // synthetic
    dhihat_config.noisiness = 0.5f;
    // opd
    dhihat_config.amp = 0.3f;
    dhihat_config.res = 0.3f;
    dhihat_config.drive = 0.3f;
    dhihatc.Init(dhihat_config);

    // drum hihat open
    dhihat_config.sample_rate = settings.sampleRate;
    dhihat_config.type = DTYPE_OPD;
    dhihat_config.vol = 1.0f;
    // common
    dhihat_config.freq = 5000.0f;
    dhihat_config.tone = 0.8f;
    dhihat_config.decay = 0.2f;
    // analog
    // synthetic
    dhihat_config.noisiness = 0.5f;
    // opd
    dhihat_config.amp = 0.3f;
    dhihat_config.res = 0.3f;
    dhihat_config.drive = 0.3f;
    dhihato.Init(dhihat_config);

    // drum clap
    DClap::Config dclap_config;
    dclap_config.sample_rate = settings.sampleRate;
    dclap_config.vol = 1.0;
    dclap_config.freq = 1200.0f;
    dclap_config.res = 0.5f;
    dclap_config.drive = 0.1f;
    dclap_config.amp = 0.8f;
    dclap_config.decay = 0.15f;
    dclap.Init(dclap_config);

    // drum ride
    DCymbal::Config dcymbal_config;
    dcymbal_config.sample_rate = settings.sampleRate;
    dcymbal_config.vol = 1.0f;
    dcymbal_config.freq = 5000.0f;
    dcymbal_config.res = 0.3f;
    dcymbal_config.drive = 0.3f;
    dcymbal_config.amp = 0.4f;
    dcymbal_config.decay = 0.6f;
    dcymbal_config.min = 0.6f;
    dcymbal_config.mix = 0.1f;
    dride.Init(dcymbal_config);

    // drum crash
    dcymbal_config.sample_rate = settings.sampleRate;
    dcymbal_config.vol = 1.0f;
    dcymbal_config.freq = 1000.0f;
    dcymbal_config.res = 0.3f;
    dcymbal_config.drive = 0.3f;
    dcymbal_config.amp = 0.4f;
    dcymbal_config.decay = 1.2f;
    dcymbal_config.min = 0.3f;
    dcymbal_config.mix = 0.3f;
    dcrash.Init(dcymbal_config);

    // tom hi
    DDrum::Config dtomhi_config;
    dtomhi_config.sample_rate = settings.sampleRate;
    dtomhi_config.vol = 1.0f;
    dtomhi_config.freq = 300.0f;
    dtomhi_config.amp = 0.5f;
    dtomhi_config.decay = 0.4f;
    dtomhi_config.min = 0.1f;
    dtomhi.Init(dtomhi_config);

    // tom lo
    DDrum::Config dtomlo_config;
    dtomlo_config.sample_rate = settings.sampleRate;
    dtomlo_config.vol = 1.0f;
    dtomlo_config.freq = 150.0f;
    dtomlo_config.amp = 0.5f;
    dtomlo_config.decay = 0.4f;
    dtomlo_config.min = 0.1f;
    dtomlo.Init(dtomlo_config);

    // drum submixer = drummachine
    // bass, snare, hh open, hh closed, clap,
    // ride, crash, tomhi, tomlo
    DSound *ddmix_synth[MIXER_CHANNELS_MAX];
    float ddmix_pan[MIXER_CHANNELS_MAX];
    float ddmix_level[MIXER_CHANNELS_MAX];
    float ddmix_chorus_level[MIXER_CHANNELS_MAX];
    float ddmix_reverb_level[MIXER_CHANNELS_MAX];
    bool ddmix_mono[MIXER_CHANNELS_MAX];
    uint8_t ddmix_group[MIXER_CHANNELS_MAX];
    DMixer::Config ddmix_config;
    ddmix_synth[0] = &dbass;
    ddmix_synth[1] = &dsnare;
    ddmix_synth[2] = &dhihatc;
    ddmix_synth[3] = &dhihato;
    ddmix_synth[4] = &dclap;
    ddmix_synth[5] = &dride;
    ddmix_synth[6] = &dcrash;
    ddmix_synth[7] = &dtomhi;
    ddmix_synth[8] = &dtomlo;
    ddmix_pan[0] = 0.5f;
    ddmix_pan[1] = 0.5f;
    ddmix_pan[2] = 0.3f;
    ddmix_pan[3] = 0.3f;
    ddmix_pan[4] = 0.7f;
    ddmix_pan[5] = 0.8f;
    ddmix_pan[6] = 0.4f;
    ddmix_pan[7] = 0.75f;
    ddmix_pan[8] = 0.9f;
    ddmix_level[0] = 0.9;
    ddmix_level[1] = 0.7;
    ddmix_level[2] = 0.15;
    ddmix_level[3] = 0.15;
    ddmix_level[4] = 0.35;
    ddmix_level[5] = 0.2;
    ddmix_level[6] = 0.2;
    ddmix_level[7] = 0.5;
    ddmix_level[8] = 0.6;
    ddmix_chorus_level[0] = 0.0f;
    ddmix_chorus_level[1] = 0.0f;
    ddmix_chorus_level[2] = 0.1f;
    ddmix_chorus_level[3] = 0.0f;
    ddmix_chorus_level[4] = 0.4f;
    ddmix_chorus_level[5] = 0.0f;
    ddmix_chorus_level[6] = 0.0f;
    ddmix_chorus_level[7] = 0.0f;
    ddmix_chorus_level[8] = 0.0f;
    ddmix_reverb_level[0] = 0.1f;
    ddmix_reverb_level[1] = 0.1f;
    ddmix_reverb_level[2] = 0.1f;
    ddmix_reverb_level[3] = 0.5f;
    ddmix_reverb_level[4] = 0.6f;
    ddmix_reverb_level[5] = 0.6f;
    ddmix_reverb_level[6] = 0.6f;
    ddmix_reverb_level[7] = 0.3f;
    ddmix_reverb_level[8] = 0.3f;
    ddmix_mono[0] = true;
    ddmix_mono[1] = true;
    ddmix_mono[2] = true;
    ddmix_mono[3] = true;
    ddmix_mono[4] = true;
    ddmix_mono[5] = true;
    ddmix_mono[6] = true;
    ddmix_mono[7] = true;
    ddmix_mono[8] = true;
    ddmix_group[0] = 0;
    ddmix_group[1] = 1;
    ddmix_group[2] = 2; // hihats share group
    ddmix_group[3] = 2; // as sound is produced with same cymbal
    ddmix_group[4] = 4;
    ddmix_group[5] = 5;
    ddmix_group[6] = 6;
    ddmix_group[7] = 7;
    ddmix_group[8] = 8;
    ddmix_config.sample_rate = settings.sampleRate;
    ddmix_config.channels = 9;
    ddmix_config.amp = 1.0f;
    ddmix_config.synth = ddmix_synth;
    ddmix_config.pan = ddmix_pan;
    ddmix_config.level = ddmix_level;
    ddmix_config.chorus_level = ddmix_chorus_level;
    ddmix_config.reverb_level = ddmix_reverb_level;
    ddmix_config.mono = ddmix_mono;
    ddmix_config.group = ddmix_group;
    ddmix_config.chorus_return = 0.5;
    ddmix_config.reverb_return = 0.5f;
    ddmix_config.mix_dry = 0.5;
    ddmixer.Init(ddmix_config);
    ddmixer.SetType(DSound::MIXER_PERCUSSION);

    // mixer
    DSound *dmix_synth[MIXER_CHANNELS_MAX];
    float dmix_pan[MIXER_CHANNELS_MAX];
    float dmix_level[MIXER_CHANNELS_MAX];
    float dmix_chorus_level[MIXER_CHANNELS_MAX];
    float dmix_reverb_level[MIXER_CHANNELS_MAX];
    bool dmix_mono[MIXER_CHANNELS_MAX];
    uint8_t dmix_group[MIXER_CHANNELS_MAX];
    DMixer::Config dmix_config;

    dmix_synth[0] = &ddmixer;
    dmix_synth[1] = &dsynthbass1;
    dmix_synth[2] = &dsyntharp1;
    dmix_synth[3] = &dsyntharp2;
    dmix_synth[4] = &dsyntharp3;
    dmix_synth[5] = &dsynthlead;
    dmix_synth[6] = &dfxfilter; // &dsynthpad;
    dmix_synth[7] = &dsplit;
    dmix_pan[0] = 0.5f;
    dmix_pan[1] = 0.5f;
    dmix_pan[2] = 0.4f;
    dmix_pan[3] = 0.2f;
    dmix_pan[4] = 0.6f;
    dmix_pan[5] = 0.3f;
    dmix_pan[6] = 0.7f;
    dmix_pan[7] = 0.5f;
    dmix_level[0] = 1.0;
    dmix_level[1] = 0.4;
    dmix_level[2] = 0.2;
    dmix_level[3] = 0.2;
    dmix_level[4] = 0.2;
    dmix_level[5] = 0.2;
    dmix_level[6] = 0.4;
    dmix_level[7] = 0.5;
    dmix_chorus_level[0] = 0.0f;
    dmix_chorus_level[1] = 0.3f;
    dmix_chorus_level[2] = 0.1f;
    dmix_chorus_level[3] = 0.2f;
    dmix_chorus_level[4] = 0.0f;
    dmix_chorus_level[5] = 0.2f;
    dmix_chorus_level[6] = 0.1f;
    dmix_chorus_level[7] = 0.4f;
    dmix_reverb_level[0] = 0.0f;
    dmix_reverb_level[1] = 0.1f;
    dmix_reverb_level[2] = 0.6f;
    dmix_reverb_level[3] = 0.4f;
    dmix_reverb_level[4] = 0.8f;
    dmix_reverb_level[5] = 0.7f;
    dmix_reverb_level[6] = 0.7f;
    dmix_reverb_level[7] = 0.5f;
    dmix_mono[0] = false;
    dmix_mono[1] = true;
    dmix_mono[2] = true;
    dmix_mono[3] = true;
    dmix_mono[4] = true;
    dmix_mono[5] = true;
    dmix_mono[6] = true;
    dmix_mono[7] = false;
    dmix_group[0] = 0;
    dmix_group[1] = 1;
    dmix_group[2] = 2;
    dmix_group[3] = 3;
    dmix_group[4] = 4;
    dmix_group[5] = 5;
    dmix_group[6] = 6;
    dmix_group[7] = 7;
    dmix_config.sample_rate = settings.sampleRate;
    dmix_config.channels = 8;
    dmix_config.amp = 1.2f;
    dmix_config.synth = dmix_synth;
    dmix_config.pan = dmix_pan;
    dmix_config.level = dmix_level;
    dmix_config.chorus_level = dmix_chorus_level;
    dmix_config.reverb_level = dmix_reverb_level;
    dmix_config.mono = dmix_mono;
    dmix_config.group = dmix_group;
    dmix_config.chorus_return = 0.5;
    dmix_config.reverb_return = 0.5f;
    dmix_config.mix_dry = 0.5;
    dmixer.Init(dmix_config);

    // MIDI data
    dmidisong_t dsong
    { // drums        bass1        arp1         arp2         arp3         lead         pad          voice chor
        {{0, DT1*4}, {1, DT1*4},  {2, DT1*4},  {3, DT1*4},  {4, DT1*4},  {5, DT1*4},  {6, DT1*4},  {7, DT1*4}},
    };

    dmidiseqin_t dseq
    {
        { // 0 drums
            {DT1*0, DEN, DEKICK, DV10, DTD},
            {DT1*0+DT16*1, DEN, DEHHC, DV10, DTD},
            {DT1*0+DT16*2, DEN, DEHHO, DV10, DTD},
            {DT1*0+DT16*4, DEN, DESNARE, DV10, DTD},
            {DT1*0+DT16*5, DEN, DEHHC, DV10, DTD},
            {DT1*0+DT16*6, DEN, DEKICK, DV10, DTD},
            {DT1*0+DT16*7, DEN, DEKICK, DV10, DTD},
            {DT1*0+DT16*8, DEN, DEHHO, DV10, DTD},
            {DT1*0+DT16*10, DEN, DEKICK, DV10, DTD},
            {DT1*0+DT16*11, DEN, DEHHO, DV10, DTD},
            {DT1*0+DT16*12, DEN, DESNARE, DV10, DTD},
            {DT1*0+DT16*14, DEN, DEHHC, DV10, DTD},
            {DT1*0+DT16*15, DEN, DEHHC, DV10, DTD},
            {DT1*0+DT16*15, DEN, DEKICK, DV10, DTD},

            {DT1*1, DEN, DEKICK, DV10, DTD},
            {DT1*1+DT16*1, DEN, DEHHC, DV10, DTD},
            {DT1*1+DT16*2, DEN, DEHHO, DV10, DTD},
            {DT1*1+DT16*4, DEN, DESNARE, DV10, DTD},
            {DT1*1+DT16*5, DEN, DEHHC, DV10, DTD},
            {DT1*1+DT16*6, DEN, DEKICK, DV10, DTD},
            {DT1*1+DT16*7, DEN, DEKICK, DV10, DTD},
            {DT1*1+DT16*8, DEN, DEHHO, DV10, DTD},
            {DT1*1+DT16*10, DEN, DEKICK, DV10, DTD},
            {DT1*1+DT16*11, DEN, DEHHO, DV10, DTD},
            {DT1*1+DT16*12, DEN, DESNARE, DV10, DTD},
            {DT1*1+DT16*13, DEN, DEHHC, DV10, DTD},
            {DT1*1+DT16*14, DEN, DEHHC, DV10, DTD},
            {DT1*1+DT16*14, DEN, DESNARE, DV10, DTD},
            {DT1*1+DT16*15, DEN, DEHHC, DV10, DTD},
            {DT1*1+DT16*15, DEN, DESNARE, DV10, DTD},
            {DT1*1+DT16*15, DEN, DEKICK, DV10, DTD},

            {DT1*2, DEN, DEKICK, DV10, DTD},
            {DT1*2+DT16*1, DEN, DEHHC, DV10, DTD},
            {DT1*2+DT16*2, DEN, DEHHO, DV10, DTD},
            {DT1*2+DT16*4, DEN, DESNARE, DV10, DTD},
            {DT1*2+DT16*5, DEN, DEHHC, DV10, DTD},
            {DT1*2+DT16*6, DEN, DEKICK, DV10, DTD},
            {DT1*2+DT16*7, DEN, DEKICK, DV10, DTD},
            {DT1*2+DT16*8, DEN, DEHHO, DV10, DTD},
            {DT1*2+DT16*10, DEN, DEKICK, DV10, DTD},
            {DT1*2+DT16*11, DEN, DEHHO, DV10, DTD},
            {DT1*2+DT16*12, DEN, DESNARE, DV10, DTD},
            {DT1*2+DT16*14, DEN, DEHHC, DV10, DTD},
            {DT1*2+DT16*15, DEN, DEHHC, DV10, DTD},
            {DT1*2+DT16*15, DEN, DEKICK, DV10, DTD},

            {DT1*3, DEN, DEKICK, DV10, DTD},
            {DT1*3+DT16*1, DEN, DEHHC, DV10, DTD},
            {DT1*3+DT16*2, DEN, DEHHO, DV10, DTD},
            {DT1*3+DT16*4, DEN, DESNARE, DV10, DTD},
            {DT1*3+DT16*5, DEN, DEHHC, DV10, DTD},
            {DT1*3+DT16*6, DEN, DEKICK, DV10, DTD},
            {DT1*3+DT16*7, DEN, DEKICK, DV10, DTD},
            {DT1*3+DT16*8, DEN, DEHHO, DV10, DTD},
            {DT1*3+DT16*10, DEN, DEKICK, DV10, DTD},
            {DT1*3+DT16*11, DEN, DEHHO, DV10, DTD},
            {DT1*3+DT16*12, DEN, DESNARE, DV10, DTD},
            {DT1*3+DT16*13, DEN, DEHHC, DV10, DTD},
            {DT1*3+DT16*14, DEN, DEHHC, DV10, DTD},
            {DT1*3+DT16*14, DEN, DESNARE, DV10, DTD},
            {DT1*3+DT16*15, DEN, DEHHC, DV10, DTD},
            {DT1*3+DT16*15, DEN, DESNARE, DV10, DTD},
            {DT1*3+DT16*15, DEN, DEKICK, DV10, DTD},
        }
        ,
        { // 1 bass1 verse
            {DT1*0+DT16*0, DEN, 38, DV10, DT16*1},
            {DT1*0+DT16*3, DEN, 38, DV10, DT16*2},
            {DT1*0+DT16*10, DEN, 38, DV10, DT16*1},
            {DT1*0+DT16*14, DEN, 38, DV10, DT16*1},

            {DT1*1+DT16*0, DEN, 41, DV10, DT16*1},
            {DT1*1+DT16*3, DEN, 41, DV10, DT16*2},
            {DT1*1+DT16*10, DEN, 41, DV10, DT16*1},
            {DT1*1+DT16*14, DEN, 41, DV10, DT16*1},
            {DT1*1+DT16*15, DEN, 48, DV10, DT16*1},

            {DT1*2+DT16*0, DEN, 38, DV10, DT16*1},
            {DT1*2+DT16*3, DEN, 38, DV10, DT16*2},
            {DT1*2+DT16*10, DEN, 38, DV10, DT16*1},
            {DT1*2+DT16*14, DEN, 38, DV10, DT16*1},

            {DT1*3+DT16*0, DEN, 41, DV10, DT16*1},
            {DT1*3+DT16*3, DEN, 41, DV10, DT16*2},
            {DT1*3+DT16*8, DEN, 40, DV10, DT16*1},
            {DT1*3+DT16*9, DEN, 45, DV10, DT16*1},
            {DT1*3+DT16*10, DEN, 41, DV10, DT16*1},
            {DT1*3+DT16*12, DEN, 48, DV10, DT16*1},
            {DT1*3+DT16*13, DEN, 41, DV10, DT16*1},
            {DT1*3+DT16*15, DEN, 49, DV10, DT16*1},

        }
    ,
        { // 2 arp1 verse
            {DT1*0+DT16*0, DEN, 53, DV10, DT16*3},
            {DT1*1+DT16*4, DEN, 53, DV10, DT16*1},
            {DT1*1+DT16*7, DEN, 51, DV10, DT16*1},
            {DT1*1+DT16*8, DEN, 53, DV10, DT16*1},
            {DT1*1+DT16*10, DEN, 50, DV10, DT16*1},
            {DT1*1+DT16*11, DEN, 51, DV10, DT16*1},
            {DT1*1+DT16*13, DEN, 50, DV10, DT16*1},
            {DT1*1+DT16*14, DEN, 51, DV10, DT16*1},
            {DT1*1+DT16*15, DEN, 50, DV10, DT16*3},
            {DT1*2+DT16*14, DEN, 51, DV10, DT16*2},
            {DT1*3+DT16*0, DEN, 50, DV10, DT16*2},
        }
        ,
        { // 3 arp2 verse
            {DT1*0+DT16*0, DEN, 50, DV10, DT16*1},
            {DT1*0+DT16*3, DEN, 50, DV10, DT16*1},
            {DT1*0+DT16*6, DEN, 50, DV10, DT16*1},

            {DT1*0+DT2*1+DT16*0, DEN, 56, DV10, DT16*1},
            {DT1*0+DT2*1+DT16*3, DEN, 56, DV10, DT16*1},
            {DT1*0+DT2*1+DT16*6, DEN, 56, DV10, DT16*1},

            {DT1*0+DT2*2+DT16*0, DEN, 55, DV10, DT16*1},
            {DT1*0+DT2*2+DT16*3, DEN, 55, DV10, DT16*1},
            {DT1*0+DT2*2+DT16*6, DEN, 55, DV10, DT16*1},

            {DT1*0+DT2*3+DT16*0, DEN, 60, DV10, DT16*1},
            {DT1*0+DT2*3+DT16*3, DEN, 60, DV10, DT16*1},
            {DT1*0+DT2*3+DT16*6, DEN, 60, DV10, DT16*1}

        }
        ,
        { // 4 arp3 verse
            {DT1*1+DT16*11, DEN, 57, DV10, DT16*1},
            {DT1*1+DT16*12, DEN, 58, DV10, DT16*1},
            {DT1*1+DT16*13, DEN, 60, DV10, DT16*1},
            {DT1*1+DT16*14, DEN, 61, DV10, DT16*1},
            {DT1*1+DT16*15, DEN, 60, DV10, DT16*1},

            {DT1*3+DT16*11, DEN, 57, DV10, DT16*1},
            {DT1*3+DT16*12, DEN, 58, DV10, DT16*1},
            {DT1*3+DT16*13, DEN, 60, DV10, DT16*1},
            {DT1*3+DT16*14, DEN, 61, DV10, DT16*1},
            {DT1*3+DT16*15, DEN, 60, DV10, DT16*1}

        }
        ,
        { // 5 lead verse
            {DT1*0+DT16*0, DEN, 50, DV10, DT16*1},
            {DT1*1+DT16*4, DEN, 48, DV10, DT16*8},
            {DT1*1+DT16*12, DEN, 46, DV10, DT16*4},
            {DT1*2+DT16*0, DEN, 45, DV10, DT16*12}
        }
        ,
        { // 6 pad verse
            {DT1*0, DEN, 38, DV10, DT16*16},
            {DT1*0, DEN, 50, DV10, DT16*16},
            {DT1*0, DEN, 53, DV10, DT16*16},
            {DT1*0, DEN, 57, DV10, DT16*16},
        }
        ,
        { // 7 voice (chorus) verse
            {DT1*0 + DT2 + DT8, DEN, 36, DV10, DT16*1},
            {DT1*0 + DT2 + DT4, DEN, 48, DV10, DT16*1},
            {DT1*1 + DT2 + DT4, DEN, 48, DV10, DT16*1},
            {DT1*1 + DT4 + DT8, DEN, 36, DV10, DT16*1},
            {DT1*2 + DT2 + DT4, DEN, 58, DV10, DT16*1},
            {DT1*2 + DT2 + DT4+DT16*0, DEN, 64, DV10, DT16*1},
            {DT1*2 + DT2 + DT4+DT16*1, DEN, 64, DV10, DT16*1},
            {DT1*2 + DT2 + DT4+DT16*2, DEN, 64, DV10, DT16*1},
            {DT1*2 + DT2 + DT4+DT16*3, DEN, 64, DV10, DT16*1},
            {DT1*3 + DT2 + DT4, DEN, 40, DV10, DT16*1}
        }

    };

    DSeqPerm::Config dseq_config;
    dseq_config.bpm = 120;
    dseq_config.rep = 999;
    dseq_config.silence = true;
    dseq_config.dmidisong = dsong;
    dseq_config.dmidiseq = dseq;
    dseq_config.channels = dmix_config.channels;
    dseq_config.mixer = &dmixer;
    dseq_config.strength = 0.5; // probability of change
    dseqperm.Init(dseq_config);

    // demo start
	// dmixer.SetReverb(0.9f, 8000.0f);

    // soundstream activate
    settings.setOutListener(this);
    soundStream.setup(settings);

    dseqperm.Start();
    dseqperm.startThread();
}



void ofApp::audioOut(ofSoundBuffer &outBuffer) {

    float sigL, sigR;

//    dseqperm.Process();

    for(size_t i = 0; i < outBuffer.getNumFrames(); i++) {

        dmixer.Process(&sigL, &sigR);

        outBuffer.getSample(i, 0) = sigL;
        outBuffer.getSample(i, 1) = sigR;
    } // for

}



void ofApp::update()
{

}



void ofApp::draw()
{

}



void ofApp::exit()
{
    dseqperm.stopThread();
    ofSoundStreamClose();
}
