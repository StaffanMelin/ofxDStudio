#include "ofApp.h"

#include "dstudio.h"
#include "dsynthsub.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // configure soundstream
    ofSoundStreamSettings settings;

    // soundStream.printDeviceList();
    std::vector<ofSoundDevice> devices = soundStream.getDeviceList(ofSoundDevice::Api::ALSA);
    settings.setOutDevice(devices[0]);

    settings.numOutputChannels = 2;
    settings.sampleRate = DSTUDIO_SAMPLE_RATE;
    settings.bufferSize = DSTUDIO_BUFFER_SIZE;
    settings.numBuffers = DSTUDIO_NUM_BUFFERS;

    // configure subtractive synthesizer
    DSynthSub::Config dsynth_config;
    dsynth_config.sample_rate = settings.sampleRate;
    dsynth_config.voices = 1;
    dsynth_config.waveform0 = DSynthSub::WAVE_POLYBLEP_SAW;
    dsynth_config.waveform1 = DSynthSub::WAVE_POLYBLEP_TRI;
    dsynth_config.tune = 0.0f;
    dsynth_config.detune = 0.0f;
    dsynth_config.transpose = 0;
    dsynth_config.osc0_level = 0.3f;
    dsynth_config.osc1_level = 0.3f;
    dsynth_config.noise_level = 0.0f;
    dsynth_config.filter_type = DSynthSub::LOW;
    dsynth_config.filter_cutoff = 800.0f;
    dsynth_config.filter_res = 0.2f;
    dsynth_config.eg_p_level = 0.0f;
    dsynth_config.eg_p_attack = 0.0f;
    dsynth_config.eg_p_decay = 0.0f;
    dsynth_config.eg_p_sustain = 0.0f;
    dsynth_config.eg_p_release = 0.0f;
    dsynth_config.eg_f_level = 1.0f;
    dsynth_config.eg_f_attack = 0.3f;
    dsynth_config.eg_f_decay = 0.01f;
    dsynth_config.eg_f_sustain = 1.0f;
    dsynth_config.eg_f_release = 0.2f;
    dsynth_config.eg_a_attack = 0.1f;
    dsynth_config.eg_a_decay = 0.01f;
    dsynth_config.eg_a_sustain = 1.0f;
    dsynth_config.eg_a_release = 0.7f;
    dsynth_config.lfo_waveform = DSynthSub::WAVE_TRI;
    dsynth_config.lfo_freq = 0.5f;
    dsynth_config.lfo_amp = 0.7f;
    dsynth_config.lfo_p_level = 0.0f;
    dsynth_config.lfo_f_level = 0.5f;
    dsynth_config.lfo_a_level = 0.0f;
    dsynth_config.portamento = 0.0f;
    dsynth_config.delay_delay = 0.3f;
    dsynth_config.delay_feedback = 0.3f;
    dsynth_config.overdrive_gain = 0.0f;
    dsynth_config.overdrive_drive = 0.0f;
    dsynthsub.Init(dsynth_config);

    // init
    note = 0;

    // start soundstream
    settings.setOutListener(this);
    soundStream.setup(settings);
}

void ofApp::audioOut(ofSoundBuffer &outBuffer)
{
    float sigL, sigR;

    for (size_t i = 0; i < outBuffer.getNumFrames(); i++) {

        dsynthsub.Process(&sigL, &sigR);

        outBuffer.getSample(i, 0) = sigL;
        outBuffer.getSample(i, 1) = sigR;
    }
}


void ofApp::update()
{
}

void ofApp::draw()
{
}

void ofApp::keyPressed(int key)
{
    if ((key > 30) && (key < 130))
    {
        note = key - 30;
        dsynthsub.MidiIn(MIDI_MESSAGE_NOTEON, note, 70);
    }
}

void ofApp::keyReleased(int key)
{
    dsynthsub.MidiIn(MIDI_MESSAGE_NOTEOFF, note, 0);
}

void ofApp::exit()
{
    ofSoundStreamClose();
}
