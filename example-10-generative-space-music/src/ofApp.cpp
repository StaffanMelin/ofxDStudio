#include "ofApp.h"

#include "dstudio.h"
#include "dsynthsub.h"
#include "dsynthvar.h"
#include "dsynthfm.h"

#include "dfx.h"
#include "dgen.h"

#include "dsettings.h"

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

    // synth bass
    DSettings::LoadSetting(DSettings::DSYNTHSUB, DSettings::NONE, "data/sub_bass.xml", &dsynth_config);
    dsynthbass.Init(dsynth_config);

    // synth hi
    DSettings::LoadSetting(DSettings::DSYNTHSUB, DSettings::NONE, "data/sub_hi.xml", &dsynth_config);
    dsynthhi.Init(dsynth_config);

    // synth pad (dsynthsub)
    DSettings::LoadSetting(DSettings::DSYNTHSUB, DSettings::NONE, "data/sub_pad.xml", &dsynth_config);
    dsynthpad.Init(dsynth_config);

    // synth filler (dsynthsub)
    DSettings::LoadSetting(DSettings::DSYNTHSUB, DSettings::NONE, "data/sub_filler.xml", &dsynth_config);
    dsynthfill.Init(dsynth_config);

    // synth melody (dsynthvar)
    DSynthVar::Config dsynthvar_config;
    DSettings::LoadSetting(DSettings::DSYNTHVAR, DSettings::NONE, "data/var_melody.xml", &dsynthvar_config);
    dsynthmelody.Init(dsynthvar_config);

    // synth arp
    dsynth_config.sample_rate = settings.sampleRate;
    DSettings::LoadSetting(DSettings::DSYNTHSUB, DSettings::NONE, "data/sub_arp.xml", &dsynth_config);
    dsyntharp.Init(dsynth_config);

    // synth embellish
    DSynthFm::Config dsynthfm_config;
    DSettings::LoadSetting(DSettings::DSYNTHFM, DSettings::NONE, "data/fm_embellish.xml", &dsynthfm_config);
    dsynthembellish.Init(dsynthfm_config);

    // filter on var shape osc to remove DC offset
    DFXFilter::Config dfxfilter_config;
    dfxfilter_config.sample_rate = settings.sampleRate;
    dfxfilter_config.level = 1.0f;
    dfxfilter_config.filter_type = DFXFilter::HIGH;
    dfxfilter_config.filter_cutoff = 200.0f;
    dfxfilter_config.filter_res = 0.0f;
    dfxfilter_config.child = &dsynthmelody;
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

    dmix_synth[0] = &dsynthbass;
    dmix_synth[1] = &dsynthhi;
    dmix_synth[2] = &dsynthpad;
    dmix_synth[3] = &dfxfilter; // dsynthmelody
    dmix_synth[4] = &dsyntharp;
    dmix_synth[5] = &dsynthembellish;
    dmix_synth[6] = &dsynthfill;
    dmix_pan[0] = 0.5f;
    dmix_pan[1] = 0.2f;
    dmix_pan[2] = 0.8f;
    dmix_pan[3] = 0.4f;
    dmix_pan[4] = 0.6f;
    dmix_pan[5] = 0.3f;
    dmix_pan[6] = 0.7f;
    dmix_level[0] = 0.4;//.4
    dmix_level[1] = 0.4;//.4
    dmix_level[2] = 0.2;//.2
    dmix_level[3] = 0.3;//.3
    dmix_level[4] = 0.6;//.5
    dmix_level[5] = 0.3;//.3
    dmix_level[6] = 0.35;//.35
    dmix_chorus_level[0] = 0.0f;
    dmix_chorus_level[1] = 0.3f;
    dmix_chorus_level[2] = 0.5f;
    dmix_chorus_level[3] = 0.2f;
    dmix_chorus_level[4] = 0.0f;
    dmix_chorus_level[5] = 0.3f;
    dmix_chorus_level[6] = 0.7f;
    dmix_reverb_level[0] = 0.5f;
    dmix_reverb_level[1] = 0.5f;
    dmix_reverb_level[2] = 0.5f;
    dmix_reverb_level[3] = 0.7f;
    dmix_reverb_level[4] = 0.5f;
    dmix_reverb_level[5] = 0.2f;
    dmix_reverb_level[6] = 0.7f;
    dmix_mono[0] = true;
    dmix_mono[1] = true;
    dmix_mono[2] = true;
    dmix_mono[3] = false;
    dmix_mono[4] = true;
    dmix_mono[5] = true;
    dmix_mono[6] = true;
    dmix_group[0] = 0;
    dmix_group[1] = 1;
    dmix_group[2] = 2;
    dmix_group[3] = 3;
    dmix_group[4] = 4;
    dmix_group[5] = 5;
    dmix_group[6] = 6;
    dmix_config.sample_rate = settings.sampleRate;
    dmix_config.channels = 7;
    dmix_config.amp = 1.0f;
    dmix_config.synth = dmix_synth;
    dmix_config.pan = dmix_pan;
    dmix_config.level = dmix_level;
    dmix_config.chorus_level = dmix_chorus_level;
    dmix_config.reverb_level = dmix_reverb_level;
    dmix_config.mono = dmix_mono;
    dmix_config.group = dmix_group;
    dmix_config.chorus_return = 0.5;
    dmix_config.reverb_return = 0.8f;
    dmix_config.mix_dry = 0.2;
    dmixer.Init(dmix_config);

    // demo start
    dmixer.SetReverb(0.9f, 2000.0f);

    // soundstream activate
    settings.setOutListener(this);
    soundStream.setup(settings);

    // gen note creation

    DGenDrone::ChannelType dgen_channel_type[MIXER_CHANNELS_MAX];
    dgen_channel_type[0] = DGenDrone::BASS;
    dgen_channel_type[1] = DGenDrone::TREBLE;
    dgen_channel_type[2] = DGenDrone::PAD;
    dgen_channel_type[3] = DGenDrone::MELODY;
    dgen_channel_type[4] = DGenDrone::ARPEGGIO;
    dgen_channel_type[5] = DGenDrone::EMBELLISH;
    dgen_channel_type[6] = DGenDrone::BASS;
    float dgen_drama_fade[MIXER_CHANNELS_MAX];
    dgen_drama_fade[0] = 0.1f;
    dgen_drama_fade[1] = 0.0f;
    dgen_drama_fade[2] = 0.1f;
    dgen_drama_fade[3] = 0.0f;
    dgen_drama_fade[4] = 0.1f;
    dgen_drama_fade[5] = 0.0f;
    dgen_drama_fade[6] = 0.2f;

    dgen_note_t dgen_note_base = {24, 70, 48, 48, 70, 82, 36}; // base MIDI note of each channel; same length as number of channels
    dgen_note_t dgen_note_pad = {0, 4, 7, 10}; // relative to base note
    dgen_note_t dgen_note_arp = {0, 7, 7, 2}; // relative to base note
    dgen_note_t dgen_note_melody = {0, 2, 4, 2, 5, 4, 7, 4}; // relative to base note

    DGenDrone::Config dgen_config;
    dgen_config.bpm = 60;
    dgen_config.channels = 7;
    dgen_config.child = &dmixer;
    dgen_config.channel_type = dgen_channel_type;
    dgen_config.drama_fade = dgen_drama_fade;
    dgen_config.level = dmix_level;
    dgen_config.note_base = dgen_note_base;
    dgen_config.note_pad = dgen_note_pad;
    dgen_config.note_arp = dgen_note_arp;
    dgen_config.note_melody = dgen_note_melody;
    dgen.Init(dgen_config);

    dgen.Start();
    dgen.startThread();

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



void ofApp::update()
{

}



void ofApp::exit()
{
    // stop the thread
    dgen.Stop();
    dgen.stopThread();
    ofSoundStreamClose();
}
