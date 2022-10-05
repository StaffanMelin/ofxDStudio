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
    // std::vector<ofSoundDevice> devices = soundStream.getDeviceList(ofSoundDevice::Api::PULSE);
    // settings.setOutDevice(devices[0]);

    settings.numOutputChannels = 2;
    settings.sampleRate = DSTUDIO_SAMPLE_RATE;
    settings.bufferSize = DSTUDIO_BUFFER_SIZE;
    settings.numBuffers = DSTUDIO_NUM_BUFFERS;

    // synths subtractive
    DSynthSub::Config dsynth_config;

    // synth 0
    dsynth_config.sample_rate = settings.sampleRate;
    dsynth_config.voices = 8;
    dsynth_config.waveform0 = DSynthSub::WAVE_SAW;
    dsynth_config.waveform1 = DSynthSub::WAVE_TRI;
    dsynth_config.tune = 0.0f;
    dsynth_config.detune = 5.0f;
    dsynth_config.transpose = 0;
    dsynth_config.osc0_level = 0.4f;
    dsynth_config.osc1_level = 0.5f;
    dsynth_config.noise_level = 0.0f;
    dsynth_config.filter_type = DSynthSub::LOW;
    dsynth_config.filter_cutoff = 1000.0f;
    dsynth_config.filter_res = 0.2f;
    dsynth_config.eg_p_level = 0.0f;
    dsynth_config.eg_p_attack = 0.2f;
    dsynth_config.eg_p_decay = 0.2f;
    dsynth_config.eg_p_sustain = 0.0f;
    dsynth_config.eg_p_release = 0.0f;
    dsynth_config.eg_f_level = 1.0f;
    dsynth_config.eg_f_attack = 0.5f;
    dsynth_config.eg_f_decay = 0.5f;
    dsynth_config.eg_f_sustain = 0.3f;
    dsynth_config.eg_f_release = 0.2f;
    dsynth_config.eg_a_attack = 0.5f;
    dsynth_config.eg_a_decay = 0.01f;
    dsynth_config.eg_a_sustain = 0.6f;
    dsynth_config.eg_a_release = 0.4f;
    dsynth_config.lfo_waveform = DSynthSub::WAVE_TRI;
    dsynth_config.lfo_freq = 1.0f;
    dsynth_config.lfo_amp = 0.4f;
    dsynth_config.lfo_p_level = 0.0f;
    dsynth_config.lfo_f_level = 0.0f;
    dsynth_config.lfo_a_level = 0.0f;
    dsynth_config.portamento = 0.0f;
    dsynth_config.delay_delay = 0.3f;
    dsynth_config.delay_feedback = 0.3f;
    dsynth_config.overdrive_gain = 0.0f;
    dsynth_config.overdrive_drive = 0.0f;
    dsynth.Init(dsynth_config);

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
    dsynthfm_config.eg_f_attack = 0.5f;
    dsynthfm_config.eg_f_decay = 0.0f;
    dsynthfm_config.eg_f_sustain = 1.0f;
    dsynthfm_config.eg_f_release = 0.8f;
    dsynthfm_config.eg_a_attack = 0.3f;
    dsynthfm_config.eg_a_decay = 0.01f;
    dsynthfm_config.eg_a_sustain = 0.3f;
    dsynthfm_config.eg_a_release = 0.2f;
    dsynthfm_config.lfo_waveform = DSynthFm::WAVE_TRI;
    dsynthfm_config.lfo_freq = 0.6f;
    dsynthfm_config.lfo_amp = 0.8f;
    dsynthfm_config.lfo_p_level = 0.0f;
    dsynthfm_config.lfo_f_level = 0.0f;
    dsynthfm_config.lfo_a_level = 0.0f;
    dsynthfm_config.portamento = 0.5f;
    dsynthfm_config.delay_delay = 0.5f;
    dsynthfm_config.delay_feedback = 0.3f;
    dsynthfm_config.overdrive_gain = 0.0f;
    dsynthfm_config.overdrive_drive = 0.0f;
    dsynthfm.Init(dsynthfm_config);

    // sampler (sampleplayer)
    DSampler::Config dsampler_config;
    dsampler_config.sample_rate = settings.sampleRate;
    dsampler_config.voices = 8;
    dsampler_config.tune = 0.0f;
    dsampler_config.transpose = 0;
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
    dsampler_config.eg_a_attack = 0.8f;
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
    dmix_synth[2] = &dsynth;
    dmix_synth[1] = &dsynthfm;
    dmix_synth[0] = &dsampler;
    dmix_pan[0] = 0.5f;
    dmix_pan[1] = 0.5f;
    dmix_pan[2] = 0.5f;
    dmix_level[0] = 0.8;
    dmix_level[1] = 0.8;
    dmix_level[2] = 0.8;
    dmix_chorus_level[0] = 0.1f;
    dmix_chorus_level[1] = 0.2f;
    dmix_chorus_level[2] = 0.4f;
    dmix_reverb_level[0] = 0.8f;
    dmix_reverb_level[1] = 0.3f;
    dmix_reverb_level[2] = 0.6f;
    dmix_mono[0] = true;
    dmix_mono[0] = true;
    dmix_mono[0] = false;
    dmix_group[0] = 0;
    dmix_group[1] = 1;
    dmix_group[2] = 2;
    dmix_config.sample_rate = settings.sampleRate;
    dmix_config.channels = 3;
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
