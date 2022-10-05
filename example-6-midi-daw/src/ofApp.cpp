#include "ofApp.h"

#include "dstudio.h"
#include "dsynthsub.h"

// Use MIDI addon: https://github.com/danomatika/ofxMidi



void ofApp::setup()
{

    ofSetLogLevel(OF_LOG_VERBOSE);

    // print input ports to console
    midiIn.listInPorts();

    // open port by number (you may need to change this)
    midiIn.openPort(1);
    //midiIn.openPort("IAC Pure Data In");	// by name
    //midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port

    // don't ignore sysex, timing, & active sense messages,
    // these are ignored by default
    midiIn.ignoreTypes(false, false, false);

    // add ofApp as a listener
    midiIn.addListener(this);

    // print received messages to the console
    midiIn.setVerbose(true);

    // soundstream
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

    // synth 0
    dsynth_config.sample_rate = settings.sampleRate;
    dsynth_config.voices = 4;
    dsynth_config.waveform0 = DSynthSub::WAVE_SAW;
    dsynth_config.waveform1 = DSynthSub::WAVE_TRI;
    dsynth_config.tune = 0.0f;
    dsynth_config.detune = 0.0f;
    dsynth_config.transpose = 0;
    dsynth_config.osc0_level = 0.4f;
    dsynth_config.osc1_level = 0.5f;
    dsynth_config.noise_level = 0.0f;
    dsynth_config.filter_type = DSynthSub::HIGH;
    dsynth_config.filter_cutoff = 1000.0f;
    dsynth_config.filter_res = 0.2f;
    dsynth_config.eg_p_level = 0.0f;
    dsynth_config.eg_p_attack = 0.2f;
    dsynth_config.eg_p_decay = 0.2f;
    dsynth_config.eg_p_sustain = 0.0f;
    dsynth_config.eg_p_release = 0.0f;
    dsynth_config.eg_f_level = 1.0f;
    dsynth_config.eg_f_attack = 0.0f;
    dsynth_config.eg_f_decay = 0.0f;
    dsynth_config.eg_f_sustain = 1.0f;
    dsynth_config.eg_f_release = 0.2f;
    dsynth_config.eg_a_attack = 0.0f;
    dsynth_config.eg_a_decay = 0.01f;
    dsynth_config.eg_a_sustain = 1.0f;
    dsynth_config.eg_a_release = 0.1f;
    dsynth_config.lfo_waveform = DSynthSub::WAVE_TRI;
    dsynth_config.lfo_freq = 0.4f;
    dsynth_config.lfo_amp = 0.4f;
    dsynth_config.lfo_p_level = 0.0f;
    dsynth_config.lfo_f_level = 1.0f;
    dsynth_config.lfo_a_level = 0.0f;
    dsynth_config.portamento = 0.0f;
    dsynth_config.delay_delay = 0.3f;
    dsynth_config.delay_feedback = 0.3f;
    dsynth_config.overdrive_gain = 0.0f;
    dsynth_config.overdrive_drive = 0.0f;
    dsyntharp.Init(dsynth_config);

    // synth pad
    dsynth_config.sample_rate = settings.sampleRate;
    dsynth_config.voices = 8;
    dsynth_config.waveform0 = DSynthSub::WAVE_SAW;
    dsynth_config.waveform1 = DSynthSub::WAVE_TRI;
    dsynth_config.tune = 0.0f;
    dsynth_config.detune = 12.1f;
    dsynth_config.transpose = 0;
    dsynth_config.osc0_level = 0.4f;
    dsynth_config.osc1_level = 0.5f;
    dsynth_config.noise_level = 0.1f;
    dsynth_config.filter_type = DSynthSub::BAND;
    dsynth_config.filter_cutoff = 1000.0f;
    dsynth_config.filter_res = 0.0f;
    dsynth_config.eg_p_level = 0.0f;
    dsynth_config.eg_p_attack = 0.2f;
    dsynth_config.eg_p_decay = 0.2f;
    dsynth_config.eg_p_sustain = 0.0f;
    dsynth_config.eg_p_release = 0.0f;
    dsynth_config.eg_f_level = 1.0f;
    dsynth_config.eg_f_attack = 0.0f;
    dsynth_config.eg_f_decay = 0.0f;
    dsynth_config.eg_f_sustain = 1.0f;
    dsynth_config.eg_f_release = 0.2f;
    dsynth_config.eg_a_attack = 0.5f;
    dsynth_config.eg_a_decay = 0.01f;
    dsynth_config.eg_a_sustain = 1.0f;
    dsynth_config.eg_a_release = 0.5f;
    dsynth_config.lfo_waveform = DSynthSub::WAVE_TRI;
    dsynth_config.lfo_freq = 0.2f;
    dsynth_config.lfo_amp = 0.4f;
    dsynth_config.lfo_p_level = 0.0f;
    dsynth_config.lfo_f_level = 0.8f;
    dsynth_config.lfo_a_level = 0.0f;
    dsynth_config.portamento = 0.0f;
    dsynth_config.delay_delay = 0.3f;
    dsynth_config.delay_feedback = 0.3f;
    dsynth_config.overdrive_gain = 0.0f;
    dsynth_config.overdrive_drive = 0.0f;
    dsynthpad.Init(dsynth_config);

    // synth solo
    DSynthVar::Config dsynthvar_config;
    dsynthvar_config.sample_rate = settings.sampleRate;
    dsynthvar_config.voices = 1;
    dsynthvar_config.waveshape = 1.0f;
    dsynthvar_config.pulsewidth = 0.5f;
    dsynthvar_config.sync_enable = true;
    dsynthvar_config.sync_freq = 440.0f;
    dsynthvar_config.osc_level = 0.4f;
    dsynthvar_config.noise_level = 0.0f;
    dsynthvar_config.tune = 0.0f;
    dsynthvar_config.transpose = 0;
    dsynthvar_config.filter_type = DSynthVar::BAND;
    dsynthvar_config.filter_cutoff = 2000.0f;
    dsynthvar_config.filter_res = 0.5f;
    dsynthvar_config.mod_eg_p = DSYNTHVAR_MOD_NONE;
    dsynthvar_config.mod_eg_f = DSYNTHVAR_MOD_NONE;
    dsynthvar_config.mod_eg_a = DSYNTHVAR_MOD_EG1;
    dsynthvar_config.mod_filter_cutoff = DSYNTHVAR_MOD_NONE;
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
    dsynthvar_config.portamento = 0.3f;
    dsynthvar_config.delay_delay = 0.6f;
    dsynthvar_config.delay_feedback = 0.5f;
    dsynthvar_config.overdrive_gain = 0.0f;
    dsynthvar_config.overdrive_drive = 0.0f;
    dsynthlead.Init(dsynthvar_config);

    // synth fm
    DSynthFm::Config dsynthfm_config;
    dsynthfm_config.sample_rate = settings.sampleRate;
    dsynthfm_config.voices = 1;
    dsynthfm_config.ratio = 2.0f;
    dsynthfm_config.index = 1.0f;
    dsynthfm_config.tune = 0.0f;
    dsynthfm_config.transpose = 0;
    dsynthfm_config.noise_level = 0.0f;
    dsynthfm_config.filter_type = DSynthFm::LOW;
    dsynthfm_config.filter_cutoff = 700.0f;
    dsynthfm_config.filter_res = 0.0f;
    dsynthfm_config.eg_p_level = 0.0f;
    dsynthfm_config.eg_p_attack = 0.2f;
    dsynthfm_config.eg_p_decay = 0.0f;
    dsynthfm_config.eg_p_sustain = 0.0f;
    dsynthfm_config.eg_p_release = 0.0f;
    dsynthfm_config.eg_f_level = 1.0f;
    dsynthfm_config.eg_f_attack = 0.0f;
    dsynthfm_config.eg_f_decay = 0.0f;
    dsynthfm_config.eg_f_sustain = 1.0f;
    dsynthfm_config.eg_f_release = 0.8f;
    dsynthfm_config.eg_a_attack = 0.0f;
    dsynthfm_config.eg_a_decay = 0.01f;
    dsynthfm_config.eg_a_sustain = 1.0f;
    dsynthfm_config.eg_a_release = 0.5f;
    dsynthfm_config.lfo_waveform = DSynthFm::WAVE_TRI;
    dsynthfm_config.lfo_freq = 0.6f;
    dsynthfm_config.lfo_amp = 0.8f;
    dsynthfm_config.lfo_p_level = 0.0f;
    dsynthfm_config.lfo_f_level = 0.0f;
    dsynthfm_config.lfo_a_level = 0.0f;
    dsynthfm_config.portamento = 0.0f;
    dsynthfm_config.delay_delay = 0.94f;
    dsynthfm_config.delay_feedback = 0.7f;
    dsynthfm_config.overdrive_gain = 0.0f;
    dsynthfm_config.overdrive_drive = 0.0f;
    dsynthfm.Init(dsynthfm_config);

    // sampler (sampleplayer)
    DSampler::Config dsampler_config;
    dsampler_config.sample_rate = settings.sampleRate;
    dsampler_config.voices = 4;
    dsampler_config.tune = 0.0f;
    dsampler_config.transpose = 12;
    dsampler_config.filter_type = DSampler::LOW;
    dsampler_config.filter_cutoff = 2000.0f;
    dsampler_config.filter_res = 0.0f;
    dsampler_config.eg_p_level = 0.0f;
    dsampler_config.eg_p_attack = 0.0f;
    dsampler_config.eg_p_decay = 0.5f;
    dsampler_config.eg_p_sustain = 0.5f;
    dsampler_config.eg_p_release = 0.5f;
    dsampler_config.eg_f_level = 1.0f;
    dsampler_config.eg_f_attack = 0.5f;
    dsampler_config.eg_f_decay = 0.01f;
    dsampler_config.eg_f_sustain = 1.0f;
    dsampler_config.eg_f_release = 0.2f;
    dsampler_config.eg_a_attack = 0.01f;
    dsampler_config.eg_a_decay = 0.01f;
    dsampler_config.eg_a_sustain = 0.9f;
    dsampler_config.eg_a_release = 0.2f;
    dsampler_config.lfo_waveform = DSampler::WAVE_TRI;
    dsampler_config.lfo_freq = 1.0f;
    dsampler_config.lfo_amp = 0.4f;
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

    dsampler.Load("data/test.wav");

    // main mixer
    DSound *dmix_synth[MIXER_CHANNELS_MAX];
    float dmix_pan[MIXER_CHANNELS_MAX];
    float dmix_level[MIXER_CHANNELS_MAX];
    float dmix_chorus_level[MIXER_CHANNELS_MAX];
    float dmix_reverb_level[MIXER_CHANNELS_MAX];
    bool dmix_mono[MIXER_CHANNELS_MAX];
    uint8_t dmix_group[MIXER_CHANNELS_MAX];
    DMixer::Config dmix_config;
    dmix_synth[0] = &dsyntharp;
    dmix_synth[1] = &dsynthpad;
    dmix_synth[2] = &dsynthlead;
    dmix_synth[3] = &dsynthfm;
    dmix_synth[4] = &dsampler;
    dmix_pan[0] = 0.2f;
    dmix_pan[1] = 0.7f;
    dmix_pan[2] = 0.5f;
    dmix_pan[3] = 0.3f;
    dmix_pan[4] = 0.4f;
    dmix_level[0] = 0.12;
    dmix_level[1] = 0.20;
    dmix_level[2] = 0.16;
    dmix_level[3] = 0.9;
    dmix_level[4] = 0.5;
    dmix_chorus_level[0] = 0.2f;
    dmix_chorus_level[1] = 0.4f;
    dmix_chorus_level[2] = 0.2f;
    dmix_chorus_level[3] = 0.1f;
    dmix_chorus_level[4] = 0.5f;
    dmix_reverb_level[0] = 0.4f;
    dmix_reverb_level[1] = 0.9f;
    dmix_reverb_level[2] = 0.8f;
    dmix_reverb_level[3] = 0.4f;
    dmix_reverb_level[4] = 0.7f;
    dmix_mono[0] = true;
    dmix_mono[1] = true;
    dmix_mono[2] = true;
    dmix_mono[3] = true;
    dmix_mono[4] = false;
    dmix_group[0] = 0;
    dmix_group[1] = 1;
    dmix_group[2] = 2;
    dmix_group[3] = 3;
    dmix_group[4] = 4;
    dmix_config.sample_rate = settings.sampleRate;
    dmix_config.channels = 5;
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

    // soundstream activate
    settings.setOutListener(this);
    soundStream.setup(settings);
}



void ofApp::audioOut(ofSoundBuffer &outBuffer)
{

    float sigL, sigR;

    for(size_t i = 0; i < outBuffer.getNumFrames(); i++) {

        dmixer.Process(&sigL, &sigR);

        outBuffer.getSample(i, 0) = sigL;
        outBuffer.getSample(i, 1) = sigR;
    } // for

}



void ofApp::newMidiMessage(ofxMidiMessage& msg)
{

    uint8_t midi_message = msg.status & MIDI_MESSAGE_MASK;
    uint8_t midi_channel = msg.channel;

    // ofxMidi: channel 1-16
    midi_channel--;

    if (midi_channel < dmixer.GetChannels())
    {
        switch (midi_message)
        {
        case MIDI_MESSAGE_NOTEON:
        case MIDI_MESSAGE_NOTEOFF:
            // mixer will send note on/off to synth on channel 0
            dmixer.MidiIn(midi_message + midi_channel, msg.pitch, msg.velocity);
            break;
        case MIDI_MESSAGE_CC:
            // mixer willl handle pan and level
            // and send cutoff and res to synth on channel 0
            dmixer.MidiIn(midi_message + midi_channel, msg.control, msg.value);
            break;
        default:
            break;
        }
    }

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
