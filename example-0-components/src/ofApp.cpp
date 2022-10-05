#include "ofApp.h"

#include "dstudio.h"

#include "dsynthsub.h"
#include "dsynthvar.h"
#include "dsynthfm.h"
#include "dsampler.h"

#include "dfx.h"

#include "dbass.h"
#include "dsnare.h"
#include "dhihat.h"

#include "dseqperm.h"



void ofApp::setup(){

    // soundstream setup
    ofSoundStreamSettings settings;

    // soundStream.printDeviceList();
    std::vector<ofSoundDevice> devices = soundStream.getDeviceList(ofSoundDevice::Api::ALSA);
    settings.setOutDevice(devices[0]);

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
    dsynth_config.detune = 12.2f;
    dsynth_config.transpose = 0;
    dsynth_config.osc0_level = 0.8f;
    dsynth_config.osc1_level = 0.2f;
    dsynth_config.noise_level = 0.1f;
    dsynth_config.filter_type = DSynthSub::LOW;
    dsynth_config.filter_cutoff = 800.0f;
    dsynth_config.filter_res = 0.5f;
    dsynth_config.eg_p_level = 0.0f;
    dsynth_config.eg_p_attack = 0.0f;
    dsynth_config.eg_p_decay = 0.0f;
    dsynth_config.eg_p_sustain = 0.0f;
    dsynth_config.eg_p_release = 0.0f;
    dsynth_config.eg_f_level = 1.0f;
    dsynth_config.eg_f_attack = 0.0f;
    dsynth_config.eg_f_decay = 0.0f;
    dsynth_config.eg_f_sustain = 1.f;
    dsynth_config.eg_f_release = 0.5f;
    dsynth_config.eg_a_attack = 0.5f;
    dsynth_config.eg_a_decay = 0.0f;
    dsynth_config.eg_a_sustain = 1.0f;
    dsynth_config.eg_a_release = 0.5f;
    dsynth_config.lfo_waveform = DSynthSub::WAVE_TRI;
    dsynth_config.lfo_freq = 0.2f;
    dsynth_config.lfo_amp = 1.0f;
    dsynth_config.lfo_p_level = 0.0f;
    dsynth_config.lfo_f_level = 0.0f;
    dsynth_config.lfo_a_level = 0.0f;
    dsynth_config.portamento = 0.0f;
    dsynth_config.delay_delay = 0.0f;
    dsynth_config.delay_feedback = 0.0f;
    dsynth_config.overdrive_gain = 0.0f;
    dsynth_config.overdrive_drive = 0.0f;
    dsynthsub.Init(dsynth_config);

    // sampler1
    DSampler::Config dsampler_config;
    dsampler_config.sample_rate = settings.sampleRate;
    dsampler_config.voices = 2;
    dsampler_config.tune = 0.2f;
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
    dsampler_config.delay_feedback = 0.5f;
    dsampler_config.overdrive_gain = 0.0f;
    dsampler_config.overdrive_drive = 0.0f;
    dsampler_config.loop = true;

    dsampler.Init(dsampler_config);
    dsampler.Load("data/aah_mono.wav");
    uint32_t sstart, slstart, slend, send;
    dsampler.GetPhase(&sstart, &slstart, &slend, &send);
    dsampler.SetPhase(sstart, (send - sstart) * 0.1f, send * 0.9f, send);

    dsampler_config.loop = false;
    dsampler2.Init(dsampler_config);
    dsampler2.Load("data/dsound_mono.wav");

    DSound *dsplit_synth[MIXER_CHANNELS_MAX];
    dsplit_synth[0] = &dsampler;
    dsplit_synth[1] = &dsampler2;
    DSplitInfo dsplit_split[MIXER_CHANNELS_MAX];
    dsplit_split[0] = {72, 0, 0}; // end, offset, channel
    dsplit_split[1] = {127, -48, 1}; // end, offset, channel
    DSplit::Config dsplit_config;
    dsplit_config.sample_rate = settings.sampleRate;
    dsplit_config.channels = 2;
    dsplit_config.synth = dsplit_synth;
    dsplit_config.split = dsplit_split;
    dsplit.Init(dsplit_config);

    // drum machine

    // drum bass
    DBass::Config dbass_config;
    dbass_config.sample_rate = settings.sampleRate;
    dbass_config.type = DTYPE_SYNTHETIC;
    dbass_config.vol = 1.0f;
    dbass_config.freq = 50.0f;
    dbass_config.tone = 0.5f;
    dbass_config.decay = 0.8f;
    // analog
    dbass_config.fm_attack = 0.8f;
    dbass_config.fm_self = 0.8f;
    // synthetic
    dbass_config.dirtiness = 0.7f;
    dbass_config.fm_env_amount = 0.8f;
    dbass_config.fm_env_decay = 0.8f;
    // opd
    dbass_config.min = 0.5;
    dbass.Init(dbass_config);

    // drums snare
    DSnare::Config dsnare_config;
    dsnare_config.sample_rate = settings.sampleRate;
    dsnare_config.type = DTYPE_ANALOG;
    dsnare_config.vol = 1.0f;
    // common
    if (dsnare_config.type == DTYPE_OPD)
        dsnare_config.freq = 500.0f;
    else
        dsnare_config.freq = 80.0f;
    dsnare_config.tone = 0.4f;
    dsnare_config.decay = 0.8f;
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
    ddmix_pan[0] = 0.5f;
    ddmix_pan[1] = 0.5f;
    ddmix_level[0] = 0.9;
    ddmix_level[1] = 0.7;
    ddmix_chorus_level[0] = 0.0f;
    ddmix_chorus_level[1] = 0.0f;
    ddmix_reverb_level[0] = 0.6f;
    ddmix_reverb_level[1] = 0.8f;
    ddmix_mono[0] = true;
    ddmix_mono[1] = true;
    ddmix_group[0] = 0;
    ddmix_group[1] = 1;
    ddmix_config.sample_rate = settings.sampleRate;
    ddmix_config.channels = 2;
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

    // fx tremolo test
    DFXTremolo::Config dfxtremolo_config;
    dfxtremolo_config.sample_rate = settings.sampleRate;
    dfxtremolo_config.level = 0.5f;
    dfxtremolo_config.freq = 3.0f;
    dfxtremolo_config.waveform = DFXTremolo::WAVE_SAW;
    dfxtremolo_config.depth = 0.9f;
    dfxtremolo_config.child = &dsynthsub;
    dfxtremolo.Init(dfxtremolo_config);

    // mixer
    DSound *dmix_synth[MIXER_CHANNELS_MAX];
    float dmix_pan[MIXER_CHANNELS_MAX];
    float dmix_level[MIXER_CHANNELS_MAX];
    float dmix_chorus_level[MIXER_CHANNELS_MAX];
    float dmix_reverb_level[MIXER_CHANNELS_MAX];
    bool dmix_mono[MIXER_CHANNELS_MAX];
    uint8_t dmix_group[MIXER_CHANNELS_MAX];
    DMixer::Config dmix_config;

    dmix_synth[0] = &dfxtremolo; //&dsynthsub;
    dmix_synth[1] = &dsplit; //&dsampler;
    dmix_synth[2] = &ddmixer;
    dmix_pan[0] = 0.3f;//0.3f;
    dmix_pan[1] = 0.7f;//0.7f;
    dmix_pan[2] = 0.5f;
    dmix_level[0] = 0.3f;//0.1;
    dmix_level[1] = 0.3f;//0.3;
    dmix_level[2] = 1.0f;//1.0;
    dmix_chorus_level[0] = 0.2f;//0.2f;
    dmix_chorus_level[1] = 0.3f;//0.3f;
    dmix_chorus_level[2] = 0.0f;
    dmix_reverb_level[0] = 0.4f;//0.4f;
    dmix_reverb_level[1] = 0.8f;//0.4f;
    dmix_reverb_level[2] = 0.0f;
    dmix_mono[0] = true;
    dmix_mono[1] = false; // true;
    dmix_mono[2] = false;
    dmix_group[0] = 0;
    dmix_group[1] = 1;
    dmix_group[2] = 2;
    dmix_config.sample_rate = settings.sampleRate;
    dmix_config.channels = 3;
    dmix_config.amp = 1.3f;
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
    { // synthsub     sampler      drums
        {{0, DT1}, {1, DT1 * 4},  {2, DT1}}
    };

    dmidiseqin_t dseq
    {
        { // 0 synthsub
            {DT1*0, DEN, 37, DV10, DT4*2}
        }
        ,
        { // 1 sampler
            {DT1*0, DEN, 112, DV10, DT16*12}, // dsampler2
            {DT1*0+DT4, DEN, 67, DV10, DT16*12},
            {DT1*0+DT4, DEN, 62, DV10, DT16*12},
            {DT1*1+DT4, DEN, 70, DV10, DT16*12},
            {DT1*1+DT4, DEN, 62, DV10, DT16*12},
            {DT1*2+DT4, DEN, 69, DV10, DT16*12},
            {DT1*2+DT4, DEN, 62, DV10, DT16*12},
            {DT1*2+DT2, DEN, 120, DV10, DT16*12}, // dsampler2
            {DT1*3+DT4, DEN, 68, DV10, DT16*12},
            {DT1*3+DT4, DEN, 62, DV10, DT16*12},
        }
       ,
        { // 2 drums
            {DT1*0, DEN, DEKICK, DV10, DTD},
            {DT1*0+DT16*4, DEN, DESNARE, DV10, DTD},
            {DT1*0+DT16*6, DEN, DEKICK, DV10, DTD},
            {DT1*0+DT16*7, DEN, DEKICK, DV10, DTD},
            {DT1*0+DT16*10, DEN, DEKICK, DV10, DTD},
            {DT1*0+DT16*12, DEN, DESNARE, DV10, DTD},
            {DT1*0+DT16*15, DEN, DEKICK, DV10, DTD}
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
    dseq_config.strength = 0.9; // probability of change
    dseqperm.Init(dseq_config);

    // demo start
    dseqperm.Start();

    // soundstream activate
    settings.setOutListener(this);
    soundStream.setup(settings);

    dseqperm.startThread();
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



void ofApp::keyPressed(int key)
{

}



void ofApp::keyReleased(int key)
{

}



void ofApp::exit()
{
    dseqperm.stopThread();
    ofSoundStreamClose();
}
