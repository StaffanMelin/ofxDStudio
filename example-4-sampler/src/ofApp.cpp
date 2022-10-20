#include "ofApp.h"

#include "dstudio.h"
#include "dsampler.h"
#include "dfx.h"



void ofApp::setup()
{

    // soundstream setup
    ofSoundStreamSettings settings;

    // soundStream.printDeviceList();
    // std::vector<ofSoundDevice> devices = soundStream.getDeviceList(ofSoundDevice::Api::ALSA);
    // settings.setOutDevice(devices[0]);

    settings.numOutputChannels = 2;
    settings.sampleRate = DSTUDIO_SAMPLE_RATE;
    settings.bufferSize = DSTUDIO_BUFFER_SIZE;
    settings.numBuffers = DSTUDIO_NUM_BUFFERS;

    // sampler (sampleplayer)
    DSampler::Config dsampler_config;
    dsampler_config.sample_rate = DSTUDIO_SAMPLE_RATE;
    dsampler_config.voices = 2;
    dsampler_config.tune = 0.0f;
    dsampler_config.transpose = 0;
    dsampler_config.filter_type = DSampler::LOW;
    dsampler_config.filter_cutoff = 2000.0f;
    dsampler_config.filter_res = 0.2f;
    dsampler_config.eg_p_level = 0.0f;
    dsampler_config.eg_p_attack = 0.0f;
    dsampler_config.eg_p_decay = 0.01f;
    dsampler_config.eg_p_sustain = 1.0f;
    dsampler_config.eg_p_release = 0.5f;
    dsampler_config.eg_f_level = 1.0f;
    dsampler_config.eg_f_attack = 0.9f;
    dsampler_config.eg_f_decay = 0.01f;
    dsampler_config.eg_f_sustain = 1.0f;
    dsampler_config.eg_f_release = 0.0f;
    dsampler_config.eg_a_attack = 0.4f;
    dsampler_config.eg_a_decay = 0.01f;
    dsampler_config.eg_a_sustain = 0.9f;
    dsampler_config.eg_a_release = 0.2f;
    dsampler_config.lfo_waveform = DSampler::WAVE_TRI;
    dsampler_config.lfo_freq = 1.0f;
    dsampler_config.lfo_amp = 1.0f;
    dsampler_config.lfo_p_level = 0.0f;
    dsampler_config.lfo_f_level = 0.0f;
    dsampler_config.lfo_a_level = 0.0f;
    dsampler_config.portamento = 0.0f;
    dsampler_config.delay_delay = 0.3f;
    dsampler_config.delay_feedback = 0.5f;
    dsampler_config.overdrive_gain = 0.0f;
    dsampler_config.overdrive_drive = 0.0f;
    dsampler_config.loop = true;
    dsampler.Init(dsampler_config);

    dsampler.Load("data/test.wav", true);

    // dsynthvar
    DSynthVar::Config dsynthvar_config;
    dsynthvar_config.sample_rate = DSTUDIO_SAMPLE_RATE;
    dsynthvar_config.voices = 1;
    dsynthvar_config.waveshape = 1.0f;
    dsynthvar_config.pulsewidth = 0.5f;
    dsynthvar_config.sync_enable = true;
    dsynthvar_config.sync_freq = 440.0f;
    dsynthvar_config.osc_level = 0.4f;
    dsynthvar_config.noise_level = 0.0f;
    dsynthvar_config.tune = 0.0f;
    dsynthvar_config.transpose = 0;
    dsynthvar_config.filter_type = DSynthVar::LOW;
    dsynthvar_config.filter_cutoff = 2000.0f;
    dsynthvar_config.filter_res = 0.0f;
    dsynthvar_config.mod_eg_p = DSYNTHVAR_MOD_NONE;
    dsynthvar_config.mod_eg_f = DSYNTHVAR_MOD_NONE;
    dsynthvar_config.mod_eg_a = DSYNTHVAR_MOD_EG1;
    dsynthvar_config.mod_filter_cutoff = DSYNTHVAR_MOD_NONE;
    dsynthvar_config.mod_waveshape = DSYNTHVAR_MOD_NONE;
    dsynthvar_config.mod_pulsewidth = DSYNTHVAR_MOD_LFO1;
    dsynthvar_config.mod_sync_freq = DSYNTHVAR_MOD_NONE; // preferably same as mod_eg_p
    dsynthvar_config.mod_delay = DSYNTHVAR_MOD_NONE;

    dsynthvar_config.eg_0_level = 1.0f;
    dsynthvar_config.eg_0_attack = 0.2f;
    dsynthvar_config.eg_0_decay = 0.01f;
    dsynthvar_config.eg_0_sustain = 1.0f;
    dsynthvar_config.eg_0_release = 0.5f;
    dsynthvar_config.eg_1_level = 1.0f;
    dsynthvar_config.eg_1_attack = 1.51f;
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
    dsynthvar_config.lfo_0_amp = 0.2f;
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
    dsynthvar_config.sm_2_freq = 10.0f;
    dsynthvar_config.sm_2_amp = 0.9f;;
    dsynthvar_config.sm_2_offset = 0.0;
    dsynthvar_config.sm_2_seq_len = 8;
    dsynthvar_config.sm_2_seq_val = {1.0f, 0.0f, 0.8f, 0.2f, 0.7f, 0.3f, 0.6f, 0.4f};
    dsynthvar_config.portamento = 0.0f;
    dsynthvar_config.delay_delay = 0.6f;
    dsynthvar_config.delay_feedback = 0.5f;
    dsynthvar_config.overdrive_gain = 0.0f;
    dsynthvar_config.overdrive_drive = 0.0f;
    dsynthvar.Init(dsynthvar_config);

    // filter on var shape osc (pad) to remove DC offset
    DFXFilter::Config dfxfilter_config;
    dfxfilter_config.sample_rate = DSTUDIO_SAMPLE_RATE;
    dfxfilter_config.level = 1.0f;
    dfxfilter_config.filter_type = DFXFilter::HIGH;
    dfxfilter_config.filter_cutoff = 20.0f;
    dfxfilter_config.filter_res = 0.0f;
    dfxfilter_config.child = &dsynthvar;
    dfxfilter.Init(dfxfilter_config);

    // panner on pad
    DFXPanner::Config dfxpanner_config;
    dfxpanner_config.sample_rate = DSTUDIO_SAMPLE_RATE;
    dfxpanner_config.level = 1.0f;
    dfxpanner_config.child = &dfxfilter;
    dfxpanner_config.type = DFXPanner::LFO; // DFXPanner::RANDOM
    dfxpanner_config.lfo_waveform = DFXPanner::WAVE_TRI;
    dfxpanner_config.freq = 1.0f; // RANDOM: 0.1f
    dfxpanner_config.amp = 0.9f;
    dfxpanner_config.offset = 0.0f; // RANDOM: 0.1f
    dfxpanner.Init(dfxpanner_config);

    // slicer on sampler
    DFXSlicer::Config dfxslicer_config;
    dfxslicer_config.sample_rate = DSTUDIO_SAMPLE_RATE;
    dfxslicer_config.level = 1.0f;
    dfxslicer_config.child = &dsampler;
    dfxslicer_config.record_samples_max = DSTUDIO_SAMPLE_RATE; // 1 sec
    dfxslicer_config.playback_rep_max = 10;
    dfxslicer_config.trig_mode = false;

    dfxslicer.Init(dfxslicer_config);

    // main mixer
    DSound *dmix_synth[MIXER_CHANNELS_MAX];
    float dmix_pan[MIXER_CHANNELS_MAX];
    float dmix_level[MIXER_CHANNELS_MAX];
    float dmix_chorus_level[MIXER_CHANNELS_MAX];
    float dmix_reverb_level[MIXER_CHANNELS_MAX];
    bool dmix_mono[MIXER_CHANNELS_MAX];
    uint8_t dmix_group[MIXER_CHANNELS_MAX];
    DMixer::Config dmix_config;
    dmix_synth[0] = &dfxpanner;
    dmix_synth[1] = &dfxslicer;
    dmix_pan[0] = 0.5f;
    dmix_pan[1] = 0.8f;
    dmix_level[0] = 0.4f;
    dmix_level[1] = 0.6f;
    dmix_chorus_level[0] = 0.0f;
    dmix_chorus_level[1] = 0.2f;
    dmix_reverb_level[0] = 0.8f;
    dmix_reverb_level[1] = 0.8f;
    dmix_mono[0] = false;
    dmix_mono[1] = false;
    dmix_group[0] = 0;
    dmix_group[1] = 1;
    dmix_config.sample_rate = settings.sampleRate;
    dmix_config.channels = 2;
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

    // demo start
    dmixer.SetReverb(0.8f, 8000.f);
    testcount = 8;
    clock.Init(2, settings.sampleRate);

    // soundstream activate
    settings.setOutListener(this);
    soundStream.setup(settings);

}



void ofApp::audioOut(ofSoundBuffer &outBuffer)
{

    float sigL, sigR;

    for(size_t i = 0; i < outBuffer.getNumFrames(); i++) {

        if (clock.Process()) {
            testcount++;
            if (testcount >= 8) {
                testcount = 0;
            }
            switch (testcount)
            {
            case 0:
                testnote1 = rand() % 5 + 56;
                testnote2 = testnote1 + 6;
                dmixer.MidiIn(MIDI_MESSAGE_NOTEON + 0, testnote1, 127);
                dmixer.MidiIn(MIDI_MESSAGE_NOTEON + 1, testnote2, 127);
                dmixer.MidiIn(MIDI_MESSAGE_NOTEON + 1, testnote2 + 7, 127);

                break;

            case 1:
                dmixer.MidiIn(MIDI_MESSAGE_NOTEOFF + 0, testnote1 + 0, 100);
                break;

            case 2:
                dmixer.MidiIn(MIDI_MESSAGE_NOTEON + 0, testnote1 + 5, 100);
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
                dmixer.MidiIn(MIDI_MESSAGE_NOTEOFF + 1, testnote2, 127);
                dmixer.MidiIn(MIDI_MESSAGE_NOTEOFF + 1, testnote2 + 7, 127);

                break;

            case 6:
                break;

            case 7:
                dmixer.MidiIn(MIDI_MESSAGE_NOTEOFF + 0, testnote1 + 5, 100);
                break;

            } // switch
        } // if

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
    ofSoundStreamClose();
}
