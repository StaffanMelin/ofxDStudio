#include "ofApp.h"

#include "dstudio.h"
#include "dsynthsub.h"
#include "dsynthfm.h"
#include "dbass.h"
#include "dsnare.h"
#include "dseqmidi.h"
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

    // synth bass > pad
    dsynth_config.sample_rate = settings.sampleRate;
    dsynth_config.voices = 6;
    dsynth_config.waveform0 = DSynthSub::WAVE_SAW;
    dsynth_config.waveform1 = DSynthSub::WAVE_TRI;
    dsynth_config.tune = 0.0f;
    dsynth_config.detune = 12.1f;
    dsynth_config.transpose = 24;
    dsynth_config.osc0_level = 0.5f;
    dsynth_config.osc1_level = 0.5f;
    dsynth_config.noise_level = 0.3f;
    dsynth_config.filter_type = DSynthSub::LOW;
    dsynth_config.filter_cutoff = 1200.0f;
    dsynth_config.filter_res = 0.1f;
    dsynth_config.eg_p_level = 0.0f;
    dsynth_config.eg_p_attack = 0.0f;
    dsynth_config.eg_p_decay = 0.0f;
    dsynth_config.eg_p_sustain = 0.0f;
    dsynth_config.eg_p_release = 0.0f;
    dsynth_config.eg_f_level = 1.0f;
    dsynth_config.eg_f_attack = 0.5f;
    dsynth_config.eg_f_decay = 0.0f;
    dsynth_config.eg_f_sustain = 1.f;
    dsynth_config.eg_f_release = 1.0f;
    dsynth_config.eg_a_attack = 2.0f;
    dsynth_config.eg_a_decay = 0.0f;
    dsynth_config.eg_a_sustain = 1.f;
    dsynth_config.eg_a_release = 1.0f;
    dsynth_config.lfo_waveform = DSynthSub::WAVE_TRI;
    dsynth_config.lfo_freq = 10.0f;
    dsynth_config.lfo_amp = 1.0f;
    dsynth_config.lfo_p_level = 0.0f;
    dsynth_config.lfo_f_level = 0.0f;
    dsynth_config.lfo_a_level = 0.0f;
    dsynth_config.portamento = 0.0f;
    dsynth_config.delay_delay = 0.8f;
    dsynth_config.delay_feedback = 0.3f;
    dsynth_config.overdrive_gain = 0.0f;
    dsynth_config.overdrive_drive = 0.0f;
    dsynthbass.Init(dsynth_config);

    // synth arp
    dsynth_config.sample_rate = settings.sampleRate;
    dsynth_config.voices = 3;
    dsynth_config.waveform0 = DSynthSub::WAVE_POLYBLEP_SQUARE;
    dsynth_config.waveform1 = DSynthSub::WAVE_TRI;
    dsynth_config.tune = 0.0f;
    dsynth_config.detune = 6.0f;
    dsynth_config.transpose = 12;
    dsynth_config.osc0_level = 0.5f;
    dsynth_config.osc1_level = 0.5f;
    dsynth_config.noise_level = 0.0f;
    dsynth_config.filter_type = DSynthSub::LOW;
    dsynth_config.filter_cutoff = 700.0f;
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
    dsynth_config.eg_f_release = 0.0f;
    dsynth_config.eg_a_attack = 0.01f;
    dsynth_config.eg_a_decay = 0.05f;
    dsynth_config.eg_a_sustain = 0.0f;
    dsynth_config.eg_a_release = 0.00f;
    dsynth_config.lfo_waveform = DSynthSub::WAVE_TRI;
    dsynth_config.lfo_freq = 1.0f;
    dsynth_config.lfo_amp = 0.9f;
    dsynth_config.lfo_p_level = 0.0f;
    dsynth_config.lfo_f_level = 0.0f;
    dsynth_config.lfo_a_level = 0.0f;
    dsynth_config.portamento = 0.0f;
    dsynth_config.delay_delay = 0.5f;
    dsynth_config.delay_feedback = 0.1f;
    dsynth_config.overdrive_gain = 0.0f;
    dsynth_config.overdrive_drive = 0.0f;
    dsyntharp.Init(dsynth_config);

    // synth fm
    DSynthFm::Config dsynthfm_config;
    dsynthfm_config.sample_rate = settings.sampleRate;
    dsynthfm_config.voices = 2;
    dsynthfm_config.ratio = 2.0f;
    dsynthfm_config.index = 1.0f;
    dsynthfm_config.tune = 0.0f;
    dsynthfm_config.transpose = 0;
    dsynthfm_config.noise_level = 0.0f;
    dsynthfm_config.filter_type = DSynthFm::PASSTHROUGH;
    dsynthfm_config.filter_cutoff = 700.0f;
    dsynthfm_config.filter_res = 0.1f;
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
    dsynthfm_config.eg_a_sustain = 0.3f;
    dsynthfm_config.eg_a_release = 0.2f;
    dsynthfm_config.lfo_waveform = DSynthFm::WAVE_TRI;
    dsynthfm_config.lfo_freq = 0.6f;
    dsynthfm_config.lfo_amp = 0.8f;
    dsynthfm_config.lfo_p_level = 0.0f;
    dsynthfm_config.lfo_f_level = 0.0f;
    dsynthfm_config.lfo_a_level = 0.0f;
    dsynthfm_config.portamento = 0.0f;
    dsynthfm_config.delay_delay = 0.8f;
    dsynthfm_config.delay_feedback = 0.3f;
    dsynthfm_config.overdrive_gain = 0.0f;
    dsynthfm_config.overdrive_drive = 0.0f;
    dsynthsolo.Init(dsynthfm_config);
    // lead
    dsynth_config.sample_rate = settings.sampleRate;
    dsynth_config.voices = 1;
    dsynth_config.waveform0 = DSynthSub::WAVE_SAW;
    dsynth_config.waveform1 = DSynthSub::WAVE_TRI;
    dsynth_config.tune = 0.0f;
    dsynth_config.detune = 2.0f;
    dsynth_config.transpose = 12;
    dsynth_config.osc0_level = 0.5f;
    dsynth_config.osc1_level = 0.5f;
    dsynth_config.noise_level = 0.1f;
    dsynth_config.filter_type = DSynthSub::LOW;
    dsynth_config.filter_cutoff = 800.0f;
    dsynth_config.filter_res = 0.1f;
    dsynth_config.eg_p_level = 0.0f;
    dsynth_config.eg_p_attack = 0.0f;
    dsynth_config.eg_p_decay = 0.0f;
    dsynth_config.eg_p_sustain = 0.0f;
    dsynth_config.eg_p_release = 0.0f;
    dsynth_config.eg_f_level = 0.0f;
    dsynth_config.eg_f_attack = 0.5f;
    dsynth_config.eg_f_decay = 0.0f;
    dsynth_config.eg_f_sustain = 1.f;
    dsynth_config.eg_f_release = 1.0f;
    dsynth_config.eg_a_attack = 2.0f;
    dsynth_config.eg_a_decay = 0.0f;
    dsynth_config.eg_a_sustain = 1.f;
    dsynth_config.eg_a_release = 1.0f;
    dsynth_config.lfo_waveform = DSynthSub::WAVE_TRI;
    dsynth_config.lfo_freq = 10.0f;
    dsynth_config.lfo_amp = 1.0f;
    dsynth_config.lfo_p_level = 0.0f;
    dsynth_config.lfo_f_level = 0.0f;
    dsynth_config.lfo_a_level = 0.0f;
    dsynth_config.portamento = 0.3f;
    dsynth_config.delay_delay = 0.8f;
    dsynth_config.delay_feedback = 0.0f;
    dsynth_config.overdrive_gain = 0.0f;
    dsynth_config.overdrive_drive = 0.0f;
    dsynthlead.Init(dsynth_config);

    // drum bass
    DBass::Config dbass_config;
    dbass_config.sample_rate = settings.sampleRate;
    dbass_config.type = DTYPE_SYNTHETIC;
    dbass_config.vol = 1.0f;
    dbass_config.freq = 70.0f;
    dbass_config.tone = 0.4f;
    dbass_config.decay = 0.8f;
    // analog
    dbass_config.fm_attack = 0.8f;
    dbass_config.fm_self = 0.8f;
    // synthetic
    dbass_config.dirtiness = 0.5f;
    dbass_config.fm_env_amount = 0.5f;
    dbass_config.fm_env_decay = 0.5f;
    // opd
    dbass_config.min = 0.5;
    dbass.Init(dbass_config);

    // drums snare
    DSnare::Config dsnare_config;
    dsnare_config.sample_rate = settings.sampleRate;
    dsnare_config.type = DTYPE_SYNTHETIC;
    dsnare_config.vol = 1.0f;
    // common
    if (dsnare_config.type == DTYPE_OPD)
        dsnare_config.freq = 200.0f;
    else
        dsnare_config.freq = 60.0f;
    dsnare_config.tone = 0.5f;
    dsnare_config.decay = 0.8f;
    // analog
    dsnare_config.snappy = 0.3f;
    // synthetic
    dsnare_config.fm_amount = 0.5f;
    // opd
    dsnare_config.freq_noise = 1000.0f; // highpass
    dsnare_config.amp = 0.5f;
    dsnare_config.res = 0.3f;
    dsnare_config.drive = 0.3f;
    dsnare_config.min = 0.3f;
    dsnare.Init(dsnare_config);

    // fx
    // flanger on bass pad
    DFXFlanger::Config dfxflanger_config;
    dfxflanger_config.sample_rate = settings.sampleRate;
    dfxflanger_config.level = 0.8f;
    dfxflanger_config.feedback = 0.7f;
    dfxflanger_config.lfo_depth = 0.8f;
    dfxflanger_config.lfo_freq = 0.3f;
    dfxflanger_config.delay = 0.8f;
    dfxflanger_config.child = &dsynthbass;
    dfxflanger.Init(dfxflanger_config);
    // delay on snare
    DFXDelay::Config dfxdelay_config;
    dfxdelay_config.sample_rate = settings.sampleRate;
    dfxdelay_config.level = 1.0f;
    dfxdelay_config.delay_delay_l = 0.7f;
    dfxdelay_config.delay_feedback_l = 0.5f;
    dfxdelay_config.delay_delay_r = 0.6f;
    dfxdelay_config.delay_feedback_r = 0.5f;
    dfxdelay_config.child = &dsnare;
    dfxdelay.Init(dfxdelay_config);
    // decimator on dsynthsolo
    DFXDecimator::Config dfxdecimator_config;
    dfxdecimator_config.sample_rate = settings.sampleRate;
    dfxdecimator_config.level = 1.0f;
    dfxdecimator_config.downsample_factor = 0.5f;
    dfxdecimator_config.bitcrush_factor = 0.8f;
    dfxdecimator_config.bits_to_crush = 6;
    dfxdecimator_config.child = &dsyntharp;
    dfxdecimator.Init(dfxdecimator_config);
    // filter on bass drum
    DFXFilter::Config dfxfilter_config;
    dfxfilter_config.sample_rate = settings.sampleRate;
    dfxfilter_config.level = 1.0f;
    dfxfilter_config.filter_type = DFXFilter::BAND;
    dfxfilter_config.filter_cutoff = 100.0f;
    dfxfilter_config.filter_res = 0.8f;
    dfxfilter_config.child = &dbass;
    dfxfilter.Init(dfxfilter_config);

    // mixer
    DSound *dmix_synth[MIXER_CHANNELS_MAX];
    float dmix_pan[MIXER_CHANNELS_MAX];
    float dmix_level[MIXER_CHANNELS_MAX];
    float dmix_chorus_level[MIXER_CHANNELS_MAX];
    float dmix_reverb_level[MIXER_CHANNELS_MAX];
    bool dmix_mono[MIXER_CHANNELS_MAX];
    uint8_t dmix_group[MIXER_CHANNELS_MAX];
    DMixer::Config dmix_config;

    dmix_synth[0] = &dfxflanger;
    dmix_synth[1] = &dfxdecimator;
    dmix_synth[2] = &dsynthsolo;
    dmix_synth[3] = &dfxfilter;
    dmix_synth[4] = &dfxdelay;
    dmix_synth[5] = &dsynthlead;
    dmix_pan[0] = 0.4f;
    dmix_pan[1] = 0.8f;
    dmix_pan[2] = 0.3f;
    dmix_pan[3] = 0.5f;
    dmix_pan[4] = 0.6f;
    dmix_pan[5] = 0.5f;
    dmix_level[0] = 0.4;
    dmix_level[1] = 0.5;
    dmix_level[2] = 0.2;
    dmix_level[3] = 0.6;
    dmix_level[4] = 0.8;
    dmix_level[5] = 0.1;
    dmix_chorus_level[0] = 0.5f;
    dmix_chorus_level[1] = 0.2f;
    dmix_chorus_level[2] = 0.1f;
    dmix_chorus_level[3] = 0.0f;
    dmix_chorus_level[4] = 0.0f;
    dmix_chorus_level[5] = 0.2f;
    dmix_reverb_level[0] = 0.7f;
    dmix_reverb_level[1] = 0.7f;
    dmix_reverb_level[2] = 0.6f;
    dmix_reverb_level[3] = 0.5f;
    dmix_reverb_level[4] = 0.7f;
    dmix_reverb_level[5] = 0.6f;
    dmix_mono[0] = false;
    dmix_mono[1] = false;
    dmix_mono[2] = true;
    dmix_mono[3] = false;
    dmix_mono[4] = false;
    dmix_mono[5] = true;
    dmix_group[0] = 0;
    dmix_group[1] = 1;
    dmix_group[2] = 2;
    dmix_group[3] = 3;
    dmix_group[4] = 4;
    dmix_group[5] = 5;
    dmix_config.sample_rate = settings.sampleRate;
    dmix_config.channels = 6;
    dmix_config.amp = 1.0f;
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

    // seq
    dmidisong_t dsong
    {
        {{0, DT1 * 8}, {5, DT1}, {5, DT1 * 8}, {3, DT1}, {5, DT1}, {6, DT1 * 2}},
        {{0, DT1 * 8}, {1, DT1}, {5, DT1 * 8}, {3, DT1}, {5, DT1}, {6, DT1 * 2}},
        {{0, DT1 * 8}, {1, DT1}, {2, DT1 * 8}, {3, DT1}, {4, DT1}, {6, DT1 * 2}},
        {{5, DT1 * 8}, {5, DT1}, {2, DT1 * 8}, {3, DT1}, {5, DT1}, {6, DT1 * 2}}
    };
    dmidiseq_t dseq
    {
        {
            {0, DEN, 31, DV7}, {0, DEN, 38, DV7}, {0, DEN, 43, DV7},
            {DT1*4, DEN, 38, DVOFF}, {DT1*4, DEN, 39, DV7}, {DT1*4, DEN, 36, DV7},
            {DT1*5, DEN, 39, DVOFF}, {DT1*5, DEN, 41, DV7},
            {DT1*6, DEN, 31, DVOFF}, {DT1*6, DEN, 43, DVOFF}, {DT1*6, DEN, 38, DVOFF}, {DT1*6, DEN, 39, DV7}, {DT1*6, DEN, 34, DV7},
            {DT1*7, DEN, 39, DVOFF}, {DT1*7, DEN, 34, DVOFF}, {DT1*7, DEN, 38, DV7}, {DT1*7, DEN, 33, DV7},
            {DT1*8-1, DEN, 38, DVOFF}, {DT1*8-1, DEN, 33, DVOFF}, {DT1*8-1, DEN, 41, DVOFF}
        }
        ,
        {
            {0, DEN, 62, DV7}, {DT16, DEN, 62, DVOFF},
            {DT16, DEN, 63, DV7}, {DT16*2, DEN, 63, DVOFF},
            {DT16*2, DEN, 67, DV7}, {DT16*3, DEN, 67, DVOFF},
            {DT4, DEN, 62, DV7}, {DT4+DT16, DEN, 62, DVOFF},
            {DT4+DT16, DEN, 63, DV7}, {DT4+DT16*2, DEN, 63, DVOFF},
            {DT4+DT16*2, DEN, 67, DV7}, {DT4+DT16*3, DEN, 67, DVOFF},
            {DT2, DEN, 62, DV7}, {DT2+DT16, DEN, 62, DVOFF},
            {DT2+DT16, DEN, 63, DV7}, {DT2+DT16*2, DEN, 63, DVOFF},
            {DT2+DT16*2, DEN, 67, DV7}, {DT2+DT16*3, DEN, 67, DVOFF},
            {DT4+DT2, DEN, 62, DV7}, {DT4+DT2+DT16, DEN, 62, DVOFF},
            {DT4+DT2+DT16, DEN, 63, DV7}, {DT4+DT2+DT16*2, DEN, 63, DVOFF},
            {DT4+DT2+DT16*2, DEN, 67, DV7}, {DT4+DT2+DT16*3, DEN, 67, DVOFF},
        }
        ,
        {
            {0, DEN, 62, DV7}, {DT16, DEN, 62, DVOFF},
            {DT4, DEN, 62, DV7}, {DT4+DT16, DEN, 62, DVOFF},
            {DT4+DT8, DEN, 67, DV7}, {DT4+DT8, DEN, 67, DVOFF},
            {DT2, DEN, 70, DV7}, {DT2+DT16, DEN, 70, DVOFF},
            {DT2+DT4, DEN, 70, DV7}, {DT2+DT4+DT16, DEN, 70, DVOFF},
            {DT1, DEN, 70, DV7}, {DT1+DT16, DEN, 70, DVOFF},
            {DT1+DT8, DEN, 69, DV7}, {DT1+DT8+DT16, DEN, 69, DVOFF},
            {DT1+DT4, DEN, 70, DV7}, {DT1+DT4+DT16, DEN, 70, DVOFF},
            {DT1+DT4+DT8, DEN, 69, DV7}, {DT1+DT4+DT8+DT16, DEN, 69, DVOFF},
            {DT1+DT2, DEN, 70, DV7}, {DT1+DT2+DT16, DEN, 70, DVOFF},
            {DT1+DT2+DT4, DEN, 69, DV7}, {DT1+DT2+DT4+DT16, DEN, 69, DVOFF},

            {DT1*2+0, DEN, 62, DV7}, {DT1*2+DT16, DEN, 62, DVOFF},
            {DT1*2+DT4, DEN, 62, DV7}, {DT1*2+DT4+DT16, DEN, 62, DVOFF},
            {DT1*2+DT4+DT8, DEN, 67, DV7}, {DT1*2+DT4+DT8, DEN, 67, DVOFF},
            {DT1*2+DT2, DEN, 70, DV7}, {DT1*2+DT2+DT16, DEN, 70, DVOFF},
            {DT1*2+DT2+DT4, DEN, 70, DV7}, {DT1*2+DT2+DT4+DT16, DEN, 70, DVOFF},
            {DT1*2+DT1, DEN, 70, DV7}, {DT1*2+DT1+DT16, DEN, 70, DVOFF},
            {DT1*2+DT1+DT8, DEN, 69, DV7}, {DT1*2+DT1+DT8+DT16, DEN, 69, DVOFF},
            {DT1*2+DT1+DT4, DEN, 70, DV7}, {DT1*2+DT1+DT4+DT16, DEN, 70, DVOFF},
            {DT1*2+DT1+DT4+DT8, DEN, 69, DV7}, {DT1*2+DT1+DT4+DT8+DT16, DEN, 69, DVOFF},
            {DT1*2+DT1+DT2, DEN, 70, DV7}, {DT1*2+DT1+DT2+DT16, DEN, 70, DVOFF},
            {DT1*2+DT1+DT2+DT4, DEN, 69, DV7}, {DT1*2+DT1+DT2+DT4+DT16, DEN, 69, DVOFF},

            {DT1*4+0, DEN, 60, DV7}, {DT1*4+DT16, DEN, 60, DVOFF},
            {DT1*4+DT4, DEN, 60, DV7}, {DT1*4+DT4+DT16, DEN, 60, DVOFF},
            {DT1*4+DT4+DT8, DEN, 67, DV7}, {DT1*4+DT4+DT8, DEN, 67, DVOFF},
            {DT1*4+DT2, DEN, 70, DV7}, {DT1*4+DT2+DT16, DEN, 70, DVOFF},
            {DT1*4+DT2+DT4, DEN, 70, DV7}, {DT1*4+DT2+DT4+DT16, DEN, 70, DVOFF},
            {DT1*4+DT1, DEN, 70, DV7}, {DT1*4+DT1+DT16, DEN, 70, DVOFF},
            {DT1*4+DT1+DT8, DEN, 69, DV7}, {DT1*4+DT1+DT8+DT16, DEN, 69, DVOFF},
            {DT1*4+DT1+DT4, DEN, 70, DV7}, {DT1*4+DT1+DT4+DT16, DEN, 70, DVOFF},
            {DT1*4+DT1+DT4+DT8, DEN, 69, DV7}, {DT1*4+DT1+DT4+DT8+DT16, DEN, 69, DVOFF},
            {DT1*4+DT1+DT2, DEN, 70, DV7}, {DT1*4+DT1+DT2+DT16, DEN, 70, DVOFF},
            {DT1*4+DT1+DT2+DT4, DEN, 69, DV7}, {DT1*4+DT1+DT2+DT4+DT16, DEN, 69, DVOFF},

            {DT1*6+0, DEN, 58, DV7}, {DT1*6+DT16, DEN, 58, DVOFF},
            {DT1*6+DT4, DEN, 58, DV7}, {DT1*6+DT4+DT16, DEN, 58, DVOFF},
            {DT1*6+DT4+DT8, DEN, 67, DV7}, {DT1*6+DT4+DT8, DEN, 67, DVOFF},
            {DT1*6+DT2, DEN, 70, DV7}, {DT1*6+DT2+DT16, DEN, 70, DVOFF},
            {DT1*6+DT2+DT4, DEN, 70, DV7}, {DT1*6+DT2+DT4+DT16, DEN, 70, DVOFF},

            {DT1*7+0, DEN, 57, DV7}, {DT1*7+DT16, DEN, 57, DVOFF},
            {DT1*7+DT4, DEN, 57, DV7}, {DT1*7+DT4+DT16, DEN, 57, DVOFF},
            {DT1*7+DT4+DT8, DEN, 67, DV7}, {DT1*7+DT4+DT8, DEN, 67, DVOFF},
            {DT1*7+DT2, DEN, 70, DV7}, {DT1*7+DT2+DT16, DEN, 70, DVOFF},
            {DT1*7+DT2+DT4, DEN, 70, DV7}, {DT1*7+DT2+DT4+DT16, DEN, 70, DVOFF},


        }
        ,
        // dbass
        {
            {0, DEN, 0, DV10},
            {DT4, DEN, 0, DV10}
        }
        ,
        // dsnare
        {
            {DT2, DEN, 0, DV10},
            {DT2+DT4+DT8, DEN, 0, DV10}
        }
        ,
        // empty bar
        {
            // {0, DEN, 0, DVOFF}
        },
        // dsynthsolo
        {
            {0, DEN, 62, DV10},
            {DT2+DT4, DEN, 74, DV10}
        }
    };
    DSeqMidi::Config dmidiseq_config;
    dmidiseq_config.bpm = 120;
    dmidiseq_config.rep = 1;
    dmidiseq_config.silence = true;
    dmidiseq_config.dmidisong = dsong;
    dmidiseq_config.dmidiseq = dseq;
    dmidiseq_config.channels = dmix_config.channels;
    dmidiseq_config.mixer = &dmixer;
    dseqmidi.Init(dmidiseq_config);

    // demo start
    dmixer.SetReverb(0.8f, 8000.0f);

    // soundstream activate
    settings.setOutListener(this);
    soundStream.setup(settings);

    dseqmidi.Start();
    dseqmidi.startThread();
}



void ofApp::audioOut(ofSoundBuffer &outBuffer) {

    float sigL, sigR;

    for(size_t i = 0; i < outBuffer.getNumFrames(); i++) {

        dmixer.Process(&sigL, &sigR);

        outBuffer.getSample(i, 0) = sigL;
        outBuffer.getSample(i, 1) = sigR;
    } // for

}



void ofApp::update(){

}



void ofApp::draw(){

}



void ofApp::exit()
{
    dseqmidi.stopThread();
    ofSoundStreamClose();
}
