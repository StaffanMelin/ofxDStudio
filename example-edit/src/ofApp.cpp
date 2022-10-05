#include "ofApp.h"

#include "dstudio.h"
#include "dsynthsub.h"
#include "dsettings.h"



void ofApp::setup()
{

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
    dsynthsub_config.sample_rate = settings.sampleRate;
    dsynthsub_config.voices = 1;
    dsynthsub_config.waveform0 = DSynthSub::WAVE_POLYBLEP_SAW;
    dsynthsub_config.waveform1 = DSynthSub::WAVE_POLYBLEP_TRI;
    dsynthsub_config.tune = 0.0f;
    dsynthsub_config.detune = 0.0f;
    dsynthsub_config.transpose = 0;
    dsynthsub_config.osc0_level = 0.3f;
    dsynthsub_config.osc1_level = 0.3f;
    dsynthsub_config.noise_level = 0.0f;
    dsynthsub_config.filter_type = DSynthSub::LOW;
    dsynthsub_config.filter_cutoff = 800.0f;
    dsynthsub_config.filter_res = 0.2f;
    dsynthsub_config.eg_p_level = 0.0f;
    dsynthsub_config.eg_p_attack = 0.0f;
    dsynthsub_config.eg_p_decay = 0.0f;
    dsynthsub_config.eg_p_sustain = 0.0f;
    dsynthsub_config.eg_p_release = 0.0f;
    dsynthsub_config.eg_f_level = 1.0f;
    dsynthsub_config.eg_f_attack = 0.3f;
    dsynthsub_config.eg_f_decay = 0.01f;
    dsynthsub_config.eg_f_sustain = 1.0f;
    dsynthsub_config.eg_f_release = 0.2f;
    dsynthsub_config.eg_a_attack = 0.1f;
    dsynthsub_config.eg_a_decay = 0.01f;
    dsynthsub_config.eg_a_sustain = 1.0f;
    dsynthsub_config.eg_a_release = 0.7f;
    dsynthsub_config.lfo_waveform = DSynthSub::WAVE_TRI;
    dsynthsub_config.lfo_freq = 0.5f;
    dsynthsub_config.lfo_amp = 0.7f;
    dsynthsub_config.lfo_p_level = 0.0f;
    dsynthsub_config.lfo_f_level = 0.5f;
    dsynthsub_config.lfo_a_level = 0.0f;
    dsynthsub_config.portamento = 0.0f;
    dsynthsub_config.delay_delay = 0.3f;
    dsynthsub_config.delay_feedback = 0.3f;
    dsynthsub_config.overdrive_gain = 0.0f;
    dsynthsub_config.overdrive_drive = 0.0f;
    dsynthsub.Init(dsynthsub_config);

    dsynthfm_config.sample_rate = settings.sampleRate;
    dsynthfm_config.voices = 2;
    dsynthfm_config.ratio = 1.0f; // x
    dsynthfm_config.index = 0.5f; // x
    dsynthfm_config.tune = 0.0f;
    dsynthfm_config.transpose = 0;
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
    dsynthfm_config.eg_a_decay = 0.2f;
    dsynthfm_config.eg_a_sustain = 0.0f;
    dsynthfm_config.eg_a_release = 0.1f;
    dsynthfm_config.lfo_waveform = DSynthFm::WAVE_TRI;
    dsynthfm_config.lfo_freq = 0.6f;
    dsynthfm_config.lfo_amp = 0.8f;
    dsynthfm_config.lfo_p_level = 0.0f;
    dsynthfm_config.lfo_f_level = 0.0f;
    dsynthfm_config.lfo_a_level = 0.0f;
    dsynthfm_config.portamento = 0.0f;
    dsynthfm_config.delay_delay = 1.0f;
    dsynthfm_config.delay_feedback = 0.4f;
    dsynthfm_config.overdrive_gain = 0.0f;
    dsynthfm_config.overdrive_drive = 0.0f;
    dsynthfm.Init(dsynthfm_config);

    dsynthvar_config.sample_rate = settings.sampleRate;
    dsynthvar_config.voices = 1;
    dsynthvar_config.waveshape = 0.5f;
    dsynthvar_config.pulsewidth = 0.5f;
    dsynthvar_config.sync_enable = true;
    dsynthvar_config.sync_freq = 440.0f;
    dsynthvar_config.osc_level = 0.4f;
    dsynthvar_config.noise_level = 0.0f;
    dsynthvar_config.tune = 0.0f;
    dsynthvar_config.transpose = 0;
    dsynthvar_config.filter_type = DSynthVar::LOW;
    dsynthvar_config.filter_cutoff = 500.0f;
    dsynthvar_config.filter_res = 0.0f;
    dsynthvar_config.mod_eg_p = DSYNTHVAR_MOD_NONE;
    dsynthvar_config.mod_eg_f = DSYNTHVAR_MOD_EG0;
    dsynthvar_config.mod_eg_a = DSYNTHVAR_MOD_EG1;
    dsynthvar_config.mod_filter_cutoff = DSYNTHVAR_MOD_NONE;
    dsynthvar_config.mod_waveshape = DSYNTHVAR_MOD_NONE;
    dsynthvar_config.mod_pulsewidth = DSYNTHVAR_MOD_LFO1;
    dsynthvar_config.mod_sync_freq = DSYNTHVAR_MOD_LFO1; // preferably same as mod_eg_p
    dsynthvar_config.mod_delay = DSYNTHVAR_MOD_NONE;
    dsynthvar_config.eg_0_level = 1.0f;
    dsynthvar_config.eg_0_attack = 5.0f;
    dsynthvar_config.eg_0_decay = 0.01f;
    dsynthvar_config.eg_0_sustain = 1.0f;
    dsynthvar_config.eg_0_release = 5.0f;
    dsynthvar_config.eg_1_level = 1.0f;
    dsynthvar_config.eg_1_attack = 5.0f;
    dsynthvar_config.eg_1_decay = 0.01f;
    dsynthvar_config.eg_1_sustain = 1.0f;
    dsynthvar_config.eg_1_release = 5.0f;
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
    dsynthvar_config.lfo_1_freq = 0.06f;
    dsynthvar_config.lfo_1_amp = 0.6f;
    dsynthvar_config.lfo_1_offset = 0.3f;
    dsynthvar_config.lfo_2_waveform = DSynthVar::WAVE_TRI;
    dsynthvar_config.lfo_2_freq = 0.8f;
    dsynthvar_config.lfo_2_amp = 0.3f;
    dsynthvar_config.lfo_2_offset = 0.0f;
    dsynthvar_config.sm_0_type = DSTUDIO_SM_TYPE_NOISE;
    dsynthvar_config.sm_0_freq = 10.0f;
    dsynthvar_config.sm_0_amp = 1.0f;;
    dsynthvar_config.sm_0_offset = 0.0;
    dsynthvar_config.sm_0_seq_len = 1;
    dsynthvar_config.sm_0_seq_val = {1.0};
    dsynthvar_config.sm_1_type = DSTUDIO_SM_TYPE_CRAWL;
    dsynthvar_config.sm_1_freq = 100.0f;
    dsynthvar_config.sm_1_amp = 0.1f; // how much to change divided by 10
    dsynthvar_config.sm_1_offset = 0.3f; // prob of no change
    dsynthvar_config.sm_1_seq_len = 1;
    dsynthvar_config.sm_1_seq_val = {1.0};
    dsynthvar_config.sm_2_type = DSTUDIO_SM_TYPE_SEQ;
    dsynthvar_config.sm_2_freq = 16.1f;
    dsynthvar_config.sm_2_amp = 0.8f;;
    dsynthvar_config.sm_2_offset = 0.0;
    dsynthvar_config.sm_2_seq_len = 8;
    dsynthvar_config.sm_2_seq_val = {1.0f, 0.0f, 0.8f, 0.2f, 0.7f, 0.3f, 0.6f, 0.4f};
    dsynthvar_config.portamento = 0.2f;
    dsynthvar_config.delay_delay = 0.6f;
    dsynthvar_config.delay_feedback = 0.5f;
    dsynthvar_config.overdrive_gain = 0.0f;
    dsynthvar_config.overdrive_drive = 0.0f;
    dsynthvar.Init(dsynthvar_config);

    dsampler_config.sample_rate = settings.sampleRate;
    dsampler_config.voices = 4;
    dsampler_config.tune = 0.0f;
    dsampler_config.transpose = 0;
    dsampler_config.filter_type = DSampler::PASSTHROUGH;
    dsampler_config.filter_cutoff = 2000.0f;
    dsampler_config.filter_res = 0.0f;
    dsampler_config.eg_p_level = 0.0f;
    dsampler_config.eg_p_attack = 0.0f;
    dsampler_config.eg_p_decay = 0.5f;
    dsampler_config.eg_p_sustain = 0.5f;
    dsampler_config.eg_p_release = 0.5f;
    dsampler_config.eg_f_level = 1.0f;
    dsampler_config.eg_f_attack = 0.0f;
    dsampler_config.eg_f_decay = 0.0f;
    dsampler_config.eg_f_sustain = 1.0f;
    dsampler_config.eg_f_release = 0.2f;
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
    dsampler_config.sample_file_name = "data/test.wav";
    dsampler.Init(dsampler_config);
    dsampler.Load(dsampler_config.sample_file_name);
    // read back values after Load() as GUI depends on structs
    dsampler_config.sample_length = dsampler.GetLength();
    dsampler.GetPhase(&dsampler_config.sample_phase_start, &dsampler_config.sample_phase_loop_start, &dsampler_config.sample_phase_loop_end, &dsampler_config.sample_phase_end);
    // ignore dsampler_config.sample_channels for now

    // drum bass
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
    dsnare_config.sample_rate = settings.sampleRate;
    dsnare_config.type = DTYPE_SYNTHETIC;
    dsnare_config.vol = 1.0f;
    // common
    if (dsnare_config.type == DTYPE_OPD)
        dsnare_config.freq = 200.0f;
    else
        dsnare_config.freq = 100.0f;
    dsnare_config.tone = 0.5f;
    dsnare_config.decay = 0.5f;
    // analog
    dsnare_config.snappy = 0.3f;
    // synthetic
    dsnare_config.fm_amount = 0.1f;
    // opd
    dsnare_config.freq_noise = 1000.0f; // highpass
    dsnare_config.amp = 0.8f;
    dsnare_config.res = 0.3f;
    dsnare_config.drive = 0.3f;
    dsnare_config.min = 0.3f;
    dsnare.Init(dsnare_config);

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
    dhihat.Init(dhihat_config);

    // drum clap
    dclap_config.sample_rate = settings.sampleRate;
    dclap_config.vol = 1.0f;
    dclap_config.freq = 1200.0f;
    dclap_config.res = 0.5f;
    dclap_config.drive = 0.1f;
    dclap_config.amp = 0.8f;
    dclap_config.decay = 0.15f;
    dclap.Init(dclap_config);

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
    dcymbal.Init(dcymbal_config);

    // drum tom
    ddrum_config.sample_rate = settings.sampleRate;
    ddrum_config.vol = 1.0f;
    ddrum_config.freq = 150.0f;
    ddrum_config.amp = 0.5f;
    ddrum_config.decay = 0.4f;
    ddrum_config.min = 0.1f;
    ddrum.Init(ddrum_config);

    // init
    for (uint8_t i = 0; i < GUI_NOTE_MAX; i++)
    {
        note_play[i] = 0;
    }

    // gui

    ofxGuiEnableHiResDisplay();
    // gui.setDefaultHeight(32);
    gui_save.set("Save");
    gui_load.set("Load");
    gui_save.addListener(this, &ofApp::saveButtonPressed);
    gui_load.addListener(this, &ofApp::loadButtonPressed);

    // GUI dsynthsub
    GuiSetupSub();
    GuiSetSub();

    // GUI dsynthfm
    GuiSetupFm();
    GuiSetFm();

    // GUI dsynthvar
    GuiSetupVar();
    GuiSetVar();

    // GUI dsampler
    GuiSetupSampler();
    GuiSetSampler();

    // GUI dsynthvar seq
    GuiSetupSeq();
    GuiSetSeq();

    // GUI drums
    GuiSetupD();
    GuiSetD();

    // start soundstream
    settings.setOutListener(this);
    soundStream.setup(settings);
}



void ofApp::audioOut(ofSoundBuffer &outBuffer)
{
    float sigL, sigR;

    for (size_t i = 0; i < outBuffer.getNumFrames(); i++) {

        switch (synth_engine)
        {
        case SUB:
            dsynthsub.Process(&sigL, &sigR);
            break;
        case FM:
            dsynthfm.Process(&sigL, &sigR);
            break;
        case VAR:
        case VAR_SEQ:
            dsynthvar.Process(&sigL, &sigR);
            break;
        case SAMPLER:
            dsampler.Process(&sigL, &sigR);
            break;
        case DRUM:
            float sigBass, sigSnare, sigHihat, sigClap, sigCymbal, sigTom;
            sigBass = dbass.Process();
            sigSnare = dsnare.Process();
            sigHihat = dhihat.Process();
            sigClap = dclap.Process();
            sigCymbal = dcymbal.Process();
            sigTom = ddrum.Process();
            sigL = sigBass + sigSnare + sigHihat + sigClap + sigCymbal + sigTom;
            sigR = sigL;
            break;
        }

        outBuffer.getSample(i, 0) = sigL;
        outBuffer.getSample(i, 1) = sigR;
    }
}



void ofApp::update()
{
    switch (synth_engine)
    {
    case SUB:

        if (gui_synth_engine != synth_engine)
        {
            synth_engine = static_cast<SynthEngine>(static_cast<int>(gui_synth_engine));
        }

        // osc

        if (gui_sub_voices != dsynthsub_config.voices)
        {
            dsynthsub_config.voices = gui_sub_voices;
            dsynthsub.Init(dsynthsub_config);
        }

        if (gui_sub_waveform0 != dsynthsub_config.waveform0)
        {
            int foo = gui_sub_waveform0;
            dsynthsub_config.waveform0 = (DSynthSub::Waveform)foo;
            dsynthsub.SetWaveform(dsynthsub_config.waveform0, dsynthsub_config.waveform1);
        }

        if (gui_sub_waveform1 != dsynthsub_config.waveform1)
        {
            int foo = gui_sub_waveform1;
            dsynthsub_config.waveform1 = (DSynthSub::Waveform)foo;
            dsynthsub.SetWaveform(dsynthsub_config.waveform0, dsynthsub_config.waveform1);
        }

        if (gui_sub_tune != dsynthsub_config.tune)
        {
            dsynthsub_config.tune = gui_sub_tune;
            dsynthsub.SetTuning(dsynthsub_config.tune, dsynthsub_config.detune);
        }

        if (gui_sub_detune != dsynthsub_config.detune)
        {
            dsynthsub_config.detune = gui_sub_detune;
            dsynthsub.SetTuning(dsynthsub_config.tune, dsynthsub_config.detune);
        }

        if (gui_sub_transpose != dsynthsub_config.transpose)
        {
            dsynthsub_config.transpose = gui_sub_transpose;
            dsynthsub.SetTranspose(dsynthsub_config.transpose);
        }

        if (gui_sub_osc0_level != dsynthsub_config.osc0_level)
        {
            dsynthsub_config.osc0_level = gui_sub_osc0_level;
            dsynthsub.SetLevel(dsynthsub_config.osc0_level, dsynthsub_config.osc1_level, dsynthsub_config.noise_level);
        }

        if (gui_sub_osc1_level != dsynthsub_config.osc1_level)
        {
            dsynthsub_config.osc1_level = gui_sub_osc1_level;
            dsynthsub.SetLevel(dsynthsub_config.osc0_level, dsynthsub_config.osc1_level, dsynthsub_config.noise_level);
        }

        if (gui_sub_noise_level != dsynthsub_config.noise_level)
        {
            dsynthsub_config.noise_level = gui_sub_noise_level;
            dsynthsub.SetLevel(dsynthsub_config.osc0_level, dsynthsub_config.osc1_level, dsynthsub_config.noise_level);
        }

        // filter

        if (gui_sub_filter_type != dsynthsub_config.filter_type)
        {
            int foo = gui_sub_filter_type;
            dsynthsub_config.filter_type = (DSynthSub::FilterType)foo;
            dsynthsub.SetFilter(dsynthsub_config.filter_type, dsynthsub_config.filter_cutoff, dsynthsub_config.filter_res);
        }

        if (gui_sub_filter_cutoff != dsynthsub_config.filter_cutoff)
        {
            dsynthsub_config.filter_cutoff = gui_sub_filter_cutoff;
            dsynthsub.SetFilter(dsynthsub_config.filter_type, dsynthsub_config.filter_cutoff, dsynthsub_config.filter_res);
        }

        if (gui_sub_filter_res != dsynthsub_config.filter_res)
        {
            dsynthsub_config.filter_res = gui_sub_filter_res;
            dsynthsub.SetFilter(dsynthsub_config.filter_type, dsynthsub_config.filter_cutoff, dsynthsub_config.filter_res);
        }

        // EG p

        if (gui_sub_eg_p_level != dsynthsub_config.eg_p_level)
        {
            dsynthsub_config.eg_p_level = gui_sub_eg_p_level;
            dsynthsub.SetEGLevel(DSynthSub::PITCH, dsynthsub_config.eg_p_level);
        }

        if (gui_sub_eg_p_attack != dsynthsub_config.eg_p_attack)
        {
            dsynthsub_config.eg_p_attack = gui_sub_eg_p_attack;
            dsynthsub.SetEG(DSynthSub::PITCH, dsynthsub_config.eg_p_attack, dsynthsub_config.eg_p_decay, dsynthsub_config.eg_p_sustain, dsynthsub_config.eg_p_release);
        }

        if (gui_sub_eg_p_decay != dsynthsub_config.eg_p_decay)
        {
            dsynthsub_config.eg_p_decay = gui_sub_eg_p_decay;
            dsynthsub.SetEG(DSynthSub::PITCH, dsynthsub_config.eg_p_attack, dsynthsub_config.eg_p_decay, dsynthsub_config.eg_p_sustain, dsynthsub_config.eg_p_release);
        }

        if (gui_sub_eg_p_sustain != dsynthsub_config.eg_p_sustain)
        {
            dsynthsub_config.eg_p_sustain = gui_sub_eg_p_sustain;
            dsynthsub.SetEG(DSynthSub::PITCH, dsynthsub_config.eg_p_attack, dsynthsub_config.eg_p_decay, dsynthsub_config.eg_p_sustain, dsynthsub_config.eg_p_release);
        }

        if (gui_sub_eg_p_release != dsynthsub_config.eg_p_release)
        {
            dsynthsub_config.eg_p_release = gui_sub_eg_p_release;
            dsynthsub.SetEG(DSynthSub::PITCH, dsynthsub_config.eg_p_attack, dsynthsub_config.eg_p_decay, dsynthsub_config.eg_p_sustain, dsynthsub_config.eg_p_release);
        }

        // EG f

        if (gui_sub_eg_f_level != dsynthsub_config.eg_f_level)
        {
            dsynthsub_config.eg_f_level = gui_sub_eg_f_level;
            dsynthsub.SetEGLevel(DSynthSub::FILTER, dsynthsub_config.eg_f_level);
        }

        if (gui_sub_eg_f_attack != dsynthsub_config.eg_f_attack)
        {
            dsynthsub_config.eg_f_attack = gui_sub_eg_f_attack;
            dsynthsub.SetEG(DSynthSub::FILTER, dsynthsub_config.eg_f_attack, dsynthsub_config.eg_f_decay, dsynthsub_config.eg_f_sustain, dsynthsub_config.eg_f_release);
        }

        if (gui_sub_eg_f_decay != dsynthsub_config.eg_f_decay)
        {
            dsynthsub_config.eg_f_decay = gui_sub_eg_f_decay;
            dsynthsub.SetEG(DSynthSub::FILTER, dsynthsub_config.eg_f_attack, dsynthsub_config.eg_f_decay, dsynthsub_config.eg_f_sustain, dsynthsub_config.eg_f_release);
        }

        if (gui_sub_eg_f_sustain != dsynthsub_config.eg_f_sustain)
        {
            dsynthsub_config.eg_f_sustain = gui_sub_eg_f_sustain;
            dsynthsub.SetEG(DSynthSub::FILTER, dsynthsub_config.eg_f_attack, dsynthsub_config.eg_f_decay, dsynthsub_config.eg_f_sustain, dsynthsub_config.eg_f_release);
        }

        if (gui_sub_eg_f_release != dsynthsub_config.eg_f_release)
        {
            dsynthsub_config.eg_f_release = gui_sub_eg_f_release;
            dsynthsub.SetEG(DSynthSub::FILTER, dsynthsub_config.eg_f_attack, dsynthsub_config.eg_f_decay, dsynthsub_config.eg_f_sustain, dsynthsub_config.eg_f_release);
        }

        // EG a

        if (gui_sub_eg_a_attack != dsynthsub_config.eg_a_attack)
        {
            dsynthsub_config.eg_a_attack = gui_sub_eg_a_attack;
            dsynthsub.SetEG(DSynthSub::AMP, dsynthsub_config.eg_a_attack, dsynthsub_config.eg_a_decay, dsynthsub_config.eg_a_sustain, dsynthsub_config.eg_a_release);
        }

        if (gui_sub_eg_a_decay != dsynthsub_config.eg_a_decay)
        {
            dsynthsub_config.eg_a_decay = gui_sub_eg_a_decay;
            dsynthsub.SetEG(DSynthSub::AMP, dsynthsub_config.eg_a_attack, dsynthsub_config.eg_a_decay, dsynthsub_config.eg_a_sustain, dsynthsub_config.eg_a_release);
        }

        if (gui_sub_eg_a_sustain != dsynthsub_config.eg_a_sustain)
        {
            dsynthsub_config.eg_a_sustain = gui_sub_eg_a_sustain;
            dsynthsub.SetEG(DSynthSub::AMP, dsynthsub_config.eg_a_attack, dsynthsub_config.eg_a_decay, dsynthsub_config.eg_a_sustain, dsynthsub_config.eg_a_release);
        }

        if (gui_sub_eg_a_release != dsynthsub_config.eg_a_release)
        {
            dsynthsub_config.eg_a_release = gui_sub_eg_a_release;
            dsynthsub.SetEG(DSynthSub::AMP, dsynthsub_config.eg_a_attack, dsynthsub_config.eg_a_decay, dsynthsub_config.eg_a_sustain, dsynthsub_config.eg_a_release);
        }

        // LFO

        if (gui_sub_lfo_waveform != dsynthsub_config.lfo_waveform)
        {
            int foo = gui_sub_lfo_waveform;
            dsynthsub_config.lfo_waveform = (DSynthSub::Waveform)foo;
            dsynthsub.SetLFO(dsynthsub_config.lfo_waveform, dsynthsub_config.lfo_freq, dsynthsub_config.lfo_amp, dsynthsub_config.lfo_p_level, dsynthsub_config.lfo_f_level, dsynthsub_config.lfo_a_level);
        }

        if (gui_sub_lfo_freq != dsynthsub_config.lfo_freq)
        {
            dsynthsub_config.lfo_freq = gui_sub_lfo_freq;
            dsynthsub.SetLFO(dsynthsub_config.lfo_waveform, dsynthsub_config.lfo_freq, dsynthsub_config.lfo_amp, dsynthsub_config.lfo_p_level, dsynthsub_config.lfo_f_level, dsynthsub_config.lfo_a_level);
        }

        if (gui_sub_lfo_amp != dsynthsub_config.lfo_amp)
        {
            dsynthsub_config.lfo_amp = gui_sub_lfo_amp;
            dsynthsub.SetLFO(dsynthsub_config.lfo_waveform, dsynthsub_config.lfo_freq, dsynthsub_config.lfo_amp, dsynthsub_config.lfo_p_level, dsynthsub_config.lfo_f_level, dsynthsub_config.lfo_a_level);
        }

        if (gui_sub_lfo_p_level != dsynthsub_config.lfo_p_level)
        {
            dsynthsub_config.lfo_p_level = gui_sub_lfo_p_level;
            dsynthsub.SetLFO(dsynthsub_config.lfo_waveform, dsynthsub_config.lfo_freq, dsynthsub_config.lfo_amp, dsynthsub_config.lfo_p_level, dsynthsub_config.lfo_f_level, dsynthsub_config.lfo_a_level);
        }

        if (gui_sub_lfo_f_level != dsynthsub_config.lfo_f_level)
        {
            dsynthsub_config.lfo_f_level = gui_sub_lfo_f_level;
            dsynthsub.SetLFO(dsynthsub_config.lfo_waveform, dsynthsub_config.lfo_freq, dsynthsub_config.lfo_amp, dsynthsub_config.lfo_p_level, dsynthsub_config.lfo_f_level, dsynthsub_config.lfo_a_level);
        }

        if (gui_sub_lfo_a_level != dsynthsub_config.lfo_a_level)
        {
            dsynthsub_config.lfo_a_level = gui_sub_lfo_a_level;
            dsynthsub.SetLFO(dsynthsub_config.lfo_waveform, dsynthsub_config.lfo_freq, dsynthsub_config.lfo_amp, dsynthsub_config.lfo_p_level, dsynthsub_config.lfo_f_level, dsynthsub_config.lfo_a_level);
        }

        // FX

        if (gui_sub_portamento != dsynthsub_config.portamento)
        {
            dsynthsub_config.portamento = gui_sub_portamento;
            dsynthsub.SetPortamento(dsynthsub_config.portamento);
        }

        if (gui_sub_delay_delay != dsynthsub_config.delay_delay)
        {
            dsynthsub_config.delay_delay = gui_sub_delay_delay;
            dsynthsub.SetDelay(dsynthsub_config.delay_delay, dsynthsub_config.delay_feedback);
        }

        if (gui_sub_delay_feedback != dsynthsub_config.delay_feedback)
        {
            dsynthsub_config.delay_feedback = gui_sub_delay_feedback;
            dsynthsub.SetDelay(dsynthsub_config.delay_delay, dsynthsub_config.delay_feedback);
        }

        if (gui_sub_overdrive_gain != dsynthsub_config.overdrive_gain)
        {
            dsynthsub_config.overdrive_gain = gui_sub_overdrive_gain;
            dsynthsub.SetOverdrive(dsynthsub_config.overdrive_gain, dsynthsub_config.overdrive_drive);
        }

        if (gui_sub_overdrive_drive != dsynthsub_config.overdrive_drive)
        {
            dsynthsub_config.overdrive_drive = gui_sub_overdrive_drive;
            dsynthsub.SetOverdrive(dsynthsub_config.overdrive_gain, dsynthsub_config.overdrive_drive);
        }

        break;

    case FM:

        if (gui_synth_engine != synth_engine)
        {
            synth_engine = static_cast<SynthEngine>(static_cast<int>(gui_synth_engine));
        }

        // osc

        if (gui_fm_voices != dsynthfm_config.voices)
        {
            dsynthfm_config.voices = gui_fm_voices;
            dsynthfm.Init(dsynthfm_config);
        }

        if (gui_fm_ratio != dsynthfm_config.ratio)
        {
            dsynthfm_config.ratio = gui_fm_ratio;
            dsynthfm.SetRatio(dsynthfm_config.ratio);
        }

        if (gui_fm_index != dsynthfm_config.index)
        {
            dsynthfm_config.index = gui_fm_index;
            dsynthfm.SetIndex(dsynthfm_config.index);
        }

        if (gui_fm_tune != dsynthfm_config.tune)
        {
            dsynthfm_config.tune = gui_fm_tune;
            dsynthfm.SetTuning(dsynthfm_config.tune);
        }

        if (gui_fm_transpose != dsynthfm_config.transpose)
        {
            dsynthfm_config.transpose = gui_fm_transpose;
            dsynthfm.SetTranspose(dsynthfm_config.transpose);
        }

        if (gui_fm_noise_level != dsynthfm_config.noise_level)
        {
            dsynthfm_config.noise_level = gui_fm_noise_level;
            dsynthfm.SetLevel(dsynthfm_config.noise_level);
        }

        // filter

        if (gui_fm_filter_type != dsynthfm_config.filter_type)
        {
            int foo = gui_fm_filter_type;
            dsynthfm_config.filter_type = (DSynthFm::FilterType)foo;
            dsynthfm.SetFilter(dsynthfm_config.filter_type, dsynthfm_config.filter_cutoff, dsynthfm_config.filter_res);
        }

        if (gui_fm_filter_cutoff != dsynthfm_config.filter_cutoff)
        {
            dsynthfm_config.filter_cutoff = gui_fm_filter_cutoff;
            dsynthfm.SetFilter(dsynthfm_config.filter_type, dsynthfm_config.filter_cutoff, dsynthfm_config.filter_res);
        }

        if (gui_fm_filter_res != dsynthfm_config.filter_res)
        {
            dsynthfm_config.filter_res = gui_fm_filter_res;
            dsynthfm.SetFilter(dsynthfm_config.filter_type, dsynthfm_config.filter_cutoff, dsynthfm_config.filter_res);
        }

        // EG p

        if (gui_fm_eg_p_level != dsynthfm_config.eg_p_level)
        {
            dsynthfm_config.eg_p_level = gui_fm_eg_p_level;
            dsynthfm.SetEGLevel(DSynthFm::PITCH, dsynthfm_config.eg_p_level);
        }

        if (gui_fm_eg_p_attack != dsynthfm_config.eg_p_attack)
        {
            dsynthfm_config.eg_p_attack = gui_fm_eg_p_attack;
            dsynthfm.SetEG(DSynthFm::PITCH, dsynthfm_config.eg_p_attack, dsynthfm_config.eg_p_decay, dsynthfm_config.eg_p_sustain, dsynthfm_config.eg_p_release);
        }

        if (gui_fm_eg_p_decay != dsynthfm_config.eg_p_decay)
        {
            dsynthfm_config.eg_p_decay = gui_fm_eg_p_decay;
            dsynthfm.SetEG(DSynthFm::PITCH, dsynthfm_config.eg_p_attack, dsynthfm_config.eg_p_decay, dsynthfm_config.eg_p_sustain, dsynthfm_config.eg_p_release);
        }

        if (gui_fm_eg_p_sustain != dsynthfm_config.eg_p_sustain)
        {
            dsynthfm_config.eg_p_sustain = gui_fm_eg_p_sustain;
            dsynthfm.SetEG(DSynthFm::PITCH, dsynthfm_config.eg_p_attack, dsynthfm_config.eg_p_decay, dsynthfm_config.eg_p_sustain, dsynthfm_config.eg_p_release);
        }

        if (gui_fm_eg_p_release != dsynthfm_config.eg_p_release)
        {
            dsynthfm_config.eg_p_release = gui_fm_eg_p_release;
            dsynthfm.SetEG(DSynthFm::PITCH, dsynthfm_config.eg_p_attack, dsynthfm_config.eg_p_decay, dsynthfm_config.eg_p_sustain, dsynthfm_config.eg_p_release);
        }

        // EG f

        if (gui_fm_eg_f_level != dsynthfm_config.eg_f_level)
        {
            dsynthfm_config.eg_f_level = gui_fm_eg_f_level;
            dsynthfm.SetEGLevel(DSynthFm::FILTER, dsynthfm_config.eg_f_level);
        }

        if (gui_fm_eg_f_attack != dsynthfm_config.eg_f_attack)
        {
            dsynthfm_config.eg_f_attack = gui_fm_eg_f_attack;
            dsynthfm.SetEG(DSynthFm::FILTER, dsynthfm_config.eg_f_attack, dsynthfm_config.eg_f_decay, dsynthfm_config.eg_f_sustain, dsynthfm_config.eg_f_release);
        }

        if (gui_fm_eg_f_decay != dsynthfm_config.eg_f_decay)
        {
            dsynthfm_config.eg_f_decay = gui_fm_eg_f_decay;
            dsynthfm.SetEG(DSynthFm::FILTER, dsynthfm_config.eg_f_attack, dsynthfm_config.eg_f_decay, dsynthfm_config.eg_f_sustain, dsynthfm_config.eg_f_release);
        }

        if (gui_fm_eg_f_sustain != dsynthfm_config.eg_f_sustain)
        {
            dsynthfm_config.eg_f_sustain = gui_fm_eg_f_sustain;
            dsynthfm.SetEG(DSynthFm::FILTER, dsynthfm_config.eg_f_attack, dsynthfm_config.eg_f_decay, dsynthfm_config.eg_f_sustain, dsynthfm_config.eg_f_release);
        }

        if (gui_fm_eg_f_release != dsynthfm_config.eg_f_release)
        {
            dsynthfm_config.eg_f_release = gui_fm_eg_f_release;
            dsynthfm.SetEG(DSynthFm::FILTER, dsynthfm_config.eg_f_attack, dsynthfm_config.eg_f_decay, dsynthfm_config.eg_f_sustain, dsynthfm_config.eg_f_release);
        }

        // EG a

        if (gui_fm_eg_a_attack != dsynthfm_config.eg_a_attack)
        {
            dsynthfm_config.eg_a_attack = gui_fm_eg_a_attack;
            dsynthfm.SetEG(DSynthFm::AMP, dsynthfm_config.eg_a_attack, dsynthfm_config.eg_a_decay, dsynthfm_config.eg_a_sustain, dsynthfm_config.eg_a_release);
        }

        if (gui_fm_eg_a_decay != dsynthfm_config.eg_a_decay)
        {
            dsynthfm_config.eg_a_decay = gui_fm_eg_a_decay;
            dsynthfm.SetEG(DSynthFm::AMP, dsynthfm_config.eg_a_attack, dsynthfm_config.eg_a_decay, dsynthfm_config.eg_a_sustain, dsynthfm_config.eg_a_release);
        }

        if (gui_fm_eg_a_sustain != dsynthfm_config.eg_a_sustain)
        {
            dsynthfm_config.eg_a_sustain = gui_fm_eg_a_sustain;
            dsynthfm.SetEG(DSynthFm::AMP, dsynthfm_config.eg_a_attack, dsynthfm_config.eg_a_decay, dsynthfm_config.eg_a_sustain, dsynthfm_config.eg_a_release);
        }

        if (gui_fm_eg_a_release != dsynthfm_config.eg_a_release)
        {
            dsynthfm_config.eg_a_release = gui_fm_eg_a_release;
            dsynthfm.SetEG(DSynthFm::AMP, dsynthfm_config.eg_a_attack, dsynthfm_config.eg_a_decay, dsynthfm_config.eg_a_sustain, dsynthfm_config.eg_a_release);
        }

        // LFO

        if (gui_fm_lfo_waveform != dsynthfm_config.lfo_waveform)
        {
            int foo = gui_fm_lfo_waveform;
            dsynthfm_config.lfo_waveform = (DSynthFm::Waveform)foo;
            dsynthfm.SetLFO(dsynthfm_config.lfo_waveform, dsynthfm_config.lfo_freq, dsynthfm_config.lfo_amp, dsynthfm_config.lfo_p_level, dsynthfm_config.lfo_f_level, dsynthfm_config.lfo_a_level);
        }

        if (gui_fm_lfo_freq != dsynthfm_config.lfo_freq)
        {
            dsynthfm_config.lfo_freq = gui_fm_lfo_freq;
            dsynthfm.SetLFO(dsynthfm_config.lfo_waveform, dsynthfm_config.lfo_freq, dsynthfm_config.lfo_amp, dsynthfm_config.lfo_p_level, dsynthfm_config.lfo_f_level, dsynthfm_config.lfo_a_level);
        }

        if (gui_fm_lfo_amp != dsynthfm_config.lfo_amp)
        {
            dsynthfm_config.lfo_amp = gui_fm_lfo_amp;
            dsynthfm.SetLFO(dsynthfm_config.lfo_waveform, dsynthfm_config.lfo_freq, dsynthfm_config.lfo_amp, dsynthfm_config.lfo_p_level, dsynthfm_config.lfo_f_level, dsynthfm_config.lfo_a_level);
        }

        if (gui_fm_lfo_p_level != dsynthfm_config.lfo_p_level)
        {
            dsynthfm_config.lfo_p_level = gui_fm_lfo_p_level;
            dsynthfm.SetLFO(dsynthfm_config.lfo_waveform, dsynthfm_config.lfo_freq, dsynthfm_config.lfo_amp, dsynthfm_config.lfo_p_level, dsynthfm_config.lfo_f_level, dsynthfm_config.lfo_a_level);
        }

        if (gui_fm_lfo_f_level != dsynthfm_config.lfo_f_level)
        {
            dsynthfm_config.lfo_f_level = gui_fm_lfo_f_level;
            dsynthfm.SetLFO(dsynthfm_config.lfo_waveform, dsynthfm_config.lfo_freq, dsynthfm_config.lfo_amp, dsynthfm_config.lfo_p_level, dsynthfm_config.lfo_f_level, dsynthfm_config.lfo_a_level);
        }

        if (gui_fm_lfo_a_level != dsynthfm_config.lfo_a_level)
        {
            dsynthfm_config.lfo_a_level = gui_fm_lfo_a_level;
            dsynthfm.SetLFO(dsynthfm_config.lfo_waveform, dsynthfm_config.lfo_freq, dsynthfm_config.lfo_amp, dsynthfm_config.lfo_p_level, dsynthfm_config.lfo_f_level, dsynthfm_config.lfo_a_level);
        }

        // FX

        if (gui_fm_portamento != dsynthfm_config.portamento)
        {
            dsynthfm_config.portamento = gui_fm_portamento;
            dsynthfm.SetPortamento(dsynthfm_config.portamento);
        }

        if (gui_fm_delay_delay != dsynthfm_config.delay_delay)
        {
            dsynthfm_config.delay_delay = gui_fm_delay_delay;
            dsynthfm.SetDelay(dsynthfm_config.delay_delay, dsynthfm_config.delay_feedback);
        }

        if (gui_fm_delay_feedback != dsynthfm_config.delay_feedback)
        {
            dsynthfm_config.delay_feedback = gui_fm_delay_feedback;
            dsynthfm.SetDelay(dsynthfm_config.delay_delay, dsynthfm_config.delay_feedback);
        }

        if (gui_fm_overdrive_gain != dsynthfm_config.overdrive_gain)
        {
            dsynthfm_config.overdrive_gain = gui_fm_overdrive_gain;
            dsynthfm.SetOverdrive(dsynthfm_config.overdrive_gain, dsynthfm_config.overdrive_drive);
        }

        if (gui_fm_overdrive_drive != dsynthfm_config.overdrive_drive)
        {
            dsynthfm_config.overdrive_drive = gui_fm_overdrive_drive;
            dsynthfm.SetOverdrive(dsynthfm_config.overdrive_gain, dsynthfm_config.overdrive_drive);
        }

        break;

    case VAR:
        if (gui_synth_engine != synth_engine)
        {
            synth_engine = static_cast<SynthEngine>(static_cast<int>(gui_synth_engine));
        }

        // osc

        if (gui_var_voices != dsynthvar_config.voices)
        {
            dsynthvar_config.voices = gui_var_voices;
            dsynthvar.Init(dsynthvar_config);
        }

        if (gui_var_waveshape != dsynthvar_config.waveshape)
        {
            dsynthvar_config.waveshape = gui_var_waveshape;
            dsynthvar.SetWaveshape(dsynthvar_config.waveshape);
        }

        if (gui_var_pulsewidth != dsynthvar_config.pulsewidth)
        {
            dsynthvar_config.pulsewidth = gui_var_pulsewidth;
            dsynthvar.SetPulsewidth(dsynthvar_config.pulsewidth);
        }

        if (gui_var_sync_enable != dsynthvar_config.sync_enable)
        {
            dsynthvar_config.sync_enable = gui_var_sync_enable;
            dsynthvar.SetSync(dsynthvar_config.sync_enable);
        }

        if (gui_var_sync_freq != dsynthvar_config.sync_freq)
        {
            dsynthvar_config.sync_freq = gui_var_sync_freq;
            dsynthvar.SetSyncFreq(dsynthvar_config.sync_freq);
        }

        if (gui_var_tune != dsynthvar_config.tune)
        {
            dsynthvar_config.tune = gui_var_tune;
            dsynthvar.SetTuning(dsynthvar_config.tune, 0.0f);
        }

        if (gui_var_transpose != dsynthvar_config.transpose)
        {
            dsynthvar_config.transpose = gui_var_transpose;
            dsynthvar.SetTranspose(dsynthvar_config.transpose);
        }

        if (gui_var_osc_level != dsynthvar_config.osc_level)
        {
            dsynthvar_config.osc_level = gui_var_osc_level;
            dsynthvar.SetLevel(dsynthvar_config.osc_level, dsynthvar_config.noise_level);
        }

        if (gui_var_noise_level != dsynthvar_config.noise_level)
        {
            dsynthvar_config.noise_level = gui_var_noise_level;
            dsynthvar.SetLevel(dsynthvar_config.osc_level, dsynthvar_config.noise_level);
        }

        // filter

        if (gui_var_filter_type != dsynthvar_config.filter_type)
        {
            int foo = gui_var_filter_type;
            dsynthvar_config.filter_type = (DSynthVar::FilterType)foo;
            dsynthvar.SetFilter(dsynthvar_config.filter_type, dsynthvar_config.filter_cutoff, dsynthvar_config.filter_res);
        }

        if (gui_var_filter_cutoff != dsynthvar_config.filter_cutoff)
        {
            dsynthvar_config.filter_cutoff = gui_var_filter_cutoff;
            dsynthvar.SetFilter(dsynthvar_config.filter_type, dsynthvar_config.filter_cutoff, dsynthvar_config.filter_res);
        }

        if (gui_var_filter_res != dsynthvar_config.filter_res)
        {
            dsynthvar_config.filter_res = gui_var_filter_res;
            dsynthvar.SetFilter(dsynthvar_config.filter_type, dsynthvar_config.filter_cutoff, dsynthvar_config.filter_res);
        }

        // Mod

        if (gui_var_mod_eg_p != dsynthvar_config.mod_eg_p)
        {
            dsynthvar_config.mod_eg_p = gui_var_mod_eg_p;
            dsynthvar.SetMod(dsynthvar_config.mod_eg_p, dsynthvar_config.mod_eg_f, dsynthvar_config.mod_eg_a, dsynthvar_config.mod_filter_cutoff, dsynthvar_config.mod_waveshape, dsynthvar_config.mod_pulsewidth, dsynthvar_config.mod_sync_freq, dsynthvar_config.mod_delay);
        }

        if (gui_var_mod_eg_f != dsynthvar_config.mod_eg_f)
        {
            dsynthvar_config.mod_eg_f = gui_var_mod_eg_f;
            dsynthvar.SetMod(dsynthvar_config.mod_eg_p, dsynthvar_config.mod_eg_f, dsynthvar_config.mod_eg_a, dsynthvar_config.mod_filter_cutoff, dsynthvar_config.mod_waveshape, dsynthvar_config.mod_pulsewidth, dsynthvar_config.mod_sync_freq, dsynthvar_config.mod_delay);
        }

        if (gui_var_mod_eg_a != dsynthvar_config.mod_eg_a)
        {
            dsynthvar_config.mod_eg_a = gui_var_mod_eg_a;
            dsynthvar.SetMod(dsynthvar_config.mod_eg_p, dsynthvar_config.mod_eg_f, dsynthvar_config.mod_eg_a, dsynthvar_config.mod_filter_cutoff, dsynthvar_config.mod_waveshape, dsynthvar_config.mod_pulsewidth, dsynthvar_config.mod_sync_freq, dsynthvar_config.mod_delay);
        }

        if (gui_var_filter_cutoff != dsynthvar_config.mod_filter_cutoff)
        {
            dsynthvar_config.mod_filter_cutoff = gui_var_mod_filter_cutoff;
            dsynthvar.SetMod(dsynthvar_config.mod_eg_p, dsynthvar_config.mod_eg_f, dsynthvar_config.mod_eg_a, dsynthvar_config.mod_filter_cutoff, dsynthvar_config.mod_waveshape, dsynthvar_config.mod_pulsewidth, dsynthvar_config.mod_sync_freq, dsynthvar_config.mod_delay);
        }

        if (gui_var_mod_waveshape != dsynthvar_config.mod_waveshape)
        {
            dsynthvar_config.mod_waveshape = gui_var_mod_waveshape;
            dsynthvar.SetMod(dsynthvar_config.mod_eg_p, dsynthvar_config.mod_eg_f, dsynthvar_config.mod_eg_a, dsynthvar_config.mod_filter_cutoff, dsynthvar_config.mod_waveshape, dsynthvar_config.mod_pulsewidth, dsynthvar_config.mod_sync_freq, dsynthvar_config.mod_delay);
        }

        if (gui_var_mod_pulsewidth != dsynthvar_config.mod_pulsewidth)
        {
            dsynthvar_config.mod_pulsewidth = gui_var_mod_pulsewidth;
            dsynthvar.SetMod(dsynthvar_config.mod_eg_p, dsynthvar_config.mod_eg_f, dsynthvar_config.mod_eg_a, dsynthvar_config.mod_filter_cutoff, dsynthvar_config.mod_waveshape, dsynthvar_config.mod_pulsewidth, dsynthvar_config.mod_sync_freq, dsynthvar_config.mod_delay);
        }

        if (gui_var_mod_sync_freq != dsynthvar_config.mod_sync_freq)
        {
            dsynthvar_config.mod_sync_freq = gui_var_mod_sync_freq;
            dsynthvar.SetMod(dsynthvar_config.mod_eg_p, dsynthvar_config.mod_eg_f, dsynthvar_config.mod_eg_a, dsynthvar_config.mod_filter_cutoff, dsynthvar_config.mod_waveshape, dsynthvar_config.mod_pulsewidth, dsynthvar_config.mod_sync_freq, dsynthvar_config.mod_delay);
        }

        if (gui_var_mod_delay != dsynthvar_config.mod_delay)
        {
            dsynthvar_config.mod_delay = gui_var_mod_delay;
            dsynthvar.SetMod(dsynthvar_config.mod_eg_p, dsynthvar_config.mod_eg_f, dsynthvar_config.mod_eg_a, dsynthvar_config.mod_filter_cutoff, dsynthvar_config.mod_waveshape, dsynthvar_config.mod_pulsewidth, dsynthvar_config.mod_sync_freq, dsynthvar_config.mod_delay);
        }

        // EG 0

        if (gui_var_eg_0_level != dsynthvar_config.eg_0_level)
        {
            dsynthvar_config.eg_0_level = gui_var_eg_0_level;
            dsynthvar.SetEGLevel(0, dsynthvar_config.eg_0_level);
        }

        if (gui_var_eg_0_attack != dsynthvar_config.eg_0_attack)
        {
            dsynthvar_config.eg_0_attack = gui_var_eg_0_attack;
            dsynthvar.SetEG(0, dsynthvar_config.eg_0_attack, dsynthvar_config.eg_0_decay, dsynthvar_config.eg_0_sustain, dsynthvar_config.eg_0_release);
        }

        if (gui_var_eg_0_decay != dsynthvar_config.eg_0_decay)
        {
            dsynthvar_config.eg_0_decay = gui_var_eg_0_decay;
            dsynthvar.SetEG(0, dsynthvar_config.eg_0_attack, dsynthvar_config.eg_0_decay, dsynthvar_config.eg_0_sustain, dsynthvar_config.eg_0_release);
        }

        if (gui_var_eg_0_sustain != dsynthvar_config.eg_0_sustain)
        {
            dsynthvar_config.eg_0_sustain = gui_var_eg_0_sustain;
            dsynthvar.SetEG(0, dsynthvar_config.eg_0_attack, dsynthvar_config.eg_0_decay, dsynthvar_config.eg_0_sustain, dsynthvar_config.eg_0_release);
        }

        if (gui_var_eg_0_release != dsynthvar_config.eg_0_release)
        {
            dsynthvar_config.eg_0_release = gui_var_eg_0_release;
            dsynthvar.SetEG(0, dsynthvar_config.eg_0_attack, dsynthvar_config.eg_0_decay, dsynthvar_config.eg_0_sustain, dsynthvar_config.eg_0_release);
        }

        // EG 1

        if (gui_var_eg_1_level != dsynthvar_config.eg_1_level)
        {
            dsynthvar_config.eg_1_level = gui_var_eg_1_level;
            dsynthvar.SetEGLevel(1, dsynthvar_config.eg_1_level);
        }

        if (gui_var_eg_1_attack != dsynthvar_config.eg_1_attack)
        {
            dsynthvar_config.eg_1_attack = gui_var_eg_1_attack;
            dsynthvar.SetEG(1, dsynthvar_config.eg_1_attack, dsynthvar_config.eg_1_decay, dsynthvar_config.eg_1_sustain, dsynthvar_config.eg_1_release);
        }

        if (gui_var_eg_1_decay != dsynthvar_config.eg_1_decay)
        {
            dsynthvar_config.eg_1_decay = gui_var_eg_1_decay;
            dsynthvar.SetEG(1, dsynthvar_config.eg_1_attack, dsynthvar_config.eg_1_decay, dsynthvar_config.eg_1_sustain, dsynthvar_config.eg_1_release);
        }

        if (gui_var_eg_1_sustain != dsynthvar_config.eg_1_sustain)
        {
            dsynthvar_config.eg_1_sustain = gui_var_eg_1_sustain;
            dsynthvar.SetEG(1, dsynthvar_config.eg_1_attack, dsynthvar_config.eg_1_decay, dsynthvar_config.eg_1_sustain, dsynthvar_config.eg_1_release);
        }

        if (gui_var_eg_1_release != dsynthvar_config.eg_1_release)
        {
            dsynthvar_config.eg_1_release = gui_var_eg_1_release;
            dsynthvar.SetEG(1, dsynthvar_config.eg_1_attack, dsynthvar_config.eg_1_decay, dsynthvar_config.eg_1_sustain, dsynthvar_config.eg_1_release);
        }

        // EG 2

        if (gui_var_eg_2_level != dsynthvar_config.eg_2_level)
        {
            dsynthvar_config.eg_2_level = gui_var_eg_2_level;
            dsynthvar.SetEGLevel(2, dsynthvar_config.eg_2_level);
        }

        if (gui_var_eg_2_attack != dsynthvar_config.eg_2_attack)
        {
            dsynthvar_config.eg_2_attack = gui_var_eg_2_attack;
            dsynthvar.SetEG(2, dsynthvar_config.eg_2_attack, dsynthvar_config.eg_2_decay, dsynthvar_config.eg_2_sustain, dsynthvar_config.eg_2_release);
        }

        if (gui_var_eg_2_decay != dsynthvar_config.eg_2_decay)
        {
            dsynthvar_config.eg_2_decay = gui_var_eg_2_decay;
            dsynthvar.SetEG(2, dsynthvar_config.eg_2_attack, dsynthvar_config.eg_2_decay, dsynthvar_config.eg_2_sustain, dsynthvar_config.eg_2_release);
        }

        if (gui_var_eg_2_sustain != dsynthvar_config.eg_2_sustain)
        {
            dsynthvar_config.eg_2_sustain = gui_var_eg_2_sustain;
            dsynthvar.SetEG(2, dsynthvar_config.eg_2_attack, dsynthvar_config.eg_2_decay, dsynthvar_config.eg_2_sustain, dsynthvar_config.eg_2_release);
        }

        if (gui_var_eg_2_release != dsynthvar_config.eg_2_release)
        {
            dsynthvar_config.eg_2_release = gui_var_eg_2_release;
            dsynthvar.SetEG(2, dsynthvar_config.eg_2_attack, dsynthvar_config.eg_2_decay, dsynthvar_config.eg_2_sustain, dsynthvar_config.eg_2_release);
        }

        // LFO 0

        if (gui_var_lfo_0_waveform != dsynthvar_config.lfo_0_waveform)
        {
            int foo = gui_var_lfo_0_waveform;
            dsynthvar_config.lfo_0_waveform = (DSynthVar::Waveform)foo;
            dsynthvar.SetLFO(0, dsynthvar_config.lfo_0_waveform, dsynthvar_config.lfo_0_freq, dsynthvar_config.lfo_0_amp, dsynthvar_config.lfo_0_offset);
        }

        if (gui_var_lfo_0_freq != dsynthvar_config.lfo_0_freq)
        {
            dsynthvar_config.lfo_0_freq = gui_var_lfo_0_freq;
            dsynthvar.SetLFO(0, dsynthvar_config.lfo_0_waveform, dsynthvar_config.lfo_0_freq, dsynthvar_config.lfo_0_amp, dsynthvar_config.lfo_0_offset);
        }

        if (gui_var_lfo_0_amp != dsynthvar_config.lfo_0_amp)
        {
            dsynthvar_config.lfo_0_amp = gui_var_lfo_0_amp;
            dsynthvar.SetLFO(0, dsynthvar_config.lfo_0_waveform, dsynthvar_config.lfo_0_freq, dsynthvar_config.lfo_0_amp, dsynthvar_config.lfo_0_offset);
        }

        if (gui_var_lfo_0_offset != dsynthvar_config.lfo_0_offset)
        {
            dsynthvar_config.lfo_0_offset = gui_var_lfo_0_offset;
            dsynthvar.SetLFO(0, dsynthvar_config.lfo_0_waveform, dsynthvar_config.lfo_0_freq, dsynthvar_config.lfo_0_amp, dsynthvar_config.lfo_0_offset);
        }

        // LFO 1

        if (gui_var_lfo_1_waveform != dsynthvar_config.lfo_1_waveform)
        {
            int foo = gui_var_lfo_1_waveform;
            dsynthvar_config.lfo_1_waveform = (DSynthVar::Waveform)foo;
            dsynthvar.SetLFO(0, dsynthvar_config.lfo_1_waveform, dsynthvar_config.lfo_1_freq, dsynthvar_config.lfo_1_amp, dsynthvar_config.lfo_1_offset);
        }

        if (gui_var_lfo_1_freq != dsynthvar_config.lfo_1_freq)
        {
            dsynthvar_config.lfo_1_freq = gui_var_lfo_1_freq;
            dsynthvar.SetLFO(0, dsynthvar_config.lfo_1_waveform, dsynthvar_config.lfo_1_freq, dsynthvar_config.lfo_1_amp, dsynthvar_config.lfo_1_offset);
        }

        if (gui_var_lfo_1_amp != dsynthvar_config.lfo_1_amp)
        {
            dsynthvar_config.lfo_1_amp = gui_var_lfo_1_amp;
            dsynthvar.SetLFO(0, dsynthvar_config.lfo_1_waveform, dsynthvar_config.lfo_1_freq, dsynthvar_config.lfo_1_amp, dsynthvar_config.lfo_1_offset);
        }

        if (gui_var_lfo_1_offset != dsynthvar_config.lfo_1_offset)
        {
            dsynthvar_config.lfo_1_offset = gui_var_lfo_1_offset;
            dsynthvar.SetLFO(0, dsynthvar_config.lfo_1_waveform, dsynthvar_config.lfo_1_freq, dsynthvar_config.lfo_1_amp, dsynthvar_config.lfo_1_offset);
        }

        // LFO 2

        if (gui_var_lfo_2_waveform != dsynthvar_config.lfo_2_waveform)
        {
            int foo = gui_var_lfo_2_waveform;
            dsynthvar_config.lfo_2_waveform = (DSynthVar::Waveform)foo;
            dsynthvar.SetLFO(0, dsynthvar_config.lfo_2_waveform, dsynthvar_config.lfo_2_freq, dsynthvar_config.lfo_2_amp, dsynthvar_config.lfo_2_offset);
        }

        if (gui_var_lfo_2_freq != dsynthvar_config.lfo_2_freq)
        {
            dsynthvar_config.lfo_2_freq = gui_var_lfo_2_freq;
            dsynthvar.SetLFO(0, dsynthvar_config.lfo_2_waveform, dsynthvar_config.lfo_2_freq, dsynthvar_config.lfo_2_amp, dsynthvar_config.lfo_2_offset);
        }

        if (gui_var_lfo_2_amp != dsynthvar_config.lfo_2_amp)
        {
            dsynthvar_config.lfo_2_amp = gui_var_lfo_2_amp;
            dsynthvar.SetLFO(0, dsynthvar_config.lfo_2_waveform, dsynthvar_config.lfo_2_freq, dsynthvar_config.lfo_2_amp, dsynthvar_config.lfo_2_offset);
        }

        if (gui_var_lfo_2_offset != dsynthvar_config.lfo_2_offset)
        {
            dsynthvar_config.lfo_2_offset = gui_var_lfo_2_offset;
            dsynthvar.SetLFO(0, dsynthvar_config.lfo_2_waveform, dsynthvar_config.lfo_2_freq, dsynthvar_config.lfo_2_amp, dsynthvar_config.lfo_2_offset);
        }

        // SM 0

        if (gui_var_sm_0_type != dsynthvar_config.sm_0_type)
        {
            dsynthvar_config.sm_0_type = gui_var_sm_0_type;
            dsynthvar.SetSM(0, dsynthvar_config.sm_0_type, dsynthvar_config.sm_0_freq, dsynthvar_config.sm_0_amp, dsynthvar_config.sm_0_offset);
        }

        if (gui_var_sm_0_freq != dsynthvar_config.sm_0_freq)
        {
            dsynthvar_config.sm_0_freq = gui_var_sm_0_freq;
            dsynthvar.SetSM(0, dsynthvar_config.sm_0_type, dsynthvar_config.sm_0_freq, dsynthvar_config.sm_0_amp, dsynthvar_config.sm_0_offset);
        }

        if (gui_var_sm_0_amp != dsynthvar_config.sm_0_amp)
        {
            dsynthvar_config.sm_0_amp = gui_var_sm_0_amp;
            dsynthvar.SetSM(0, dsynthvar_config.sm_0_type, dsynthvar_config.sm_0_freq, dsynthvar_config.sm_0_amp, dsynthvar_config.sm_0_offset);
        }

        if (gui_var_sm_0_offset != dsynthvar_config.sm_0_offset)
        {
            dsynthvar_config.sm_0_offset = gui_var_sm_0_offset;
            dsynthvar.SetSM(0, dsynthvar_config.sm_0_type, dsynthvar_config.sm_0_freq, dsynthvar_config.sm_0_amp, dsynthvar_config.sm_0_offset);
        }

        // SM 1

        if (gui_var_sm_1_type != dsynthvar_config.sm_1_type)
        {
            dsynthvar_config.sm_1_type = gui_var_sm_1_type;
            dsynthvar.SetSM(1, dsynthvar_config.sm_1_type, dsynthvar_config.sm_1_freq, dsynthvar_config.sm_1_amp, dsynthvar_config.sm_1_offset);
        }

        if (gui_var_sm_1_freq != dsynthvar_config.sm_1_freq)
        {
            dsynthvar_config.sm_1_freq = gui_var_sm_1_freq;
            dsynthvar.SetSM(1, dsynthvar_config.sm_1_type, dsynthvar_config.sm_1_freq, dsynthvar_config.sm_1_amp, dsynthvar_config.sm_1_offset);
        }

        if (gui_var_sm_1_amp != dsynthvar_config.sm_1_amp)
        {
            dsynthvar_config.sm_1_amp = gui_var_sm_1_amp;
            dsynthvar.SetSM(1, dsynthvar_config.sm_1_type, dsynthvar_config.sm_1_freq, dsynthvar_config.sm_1_amp, dsynthvar_config.sm_1_offset);
        }

        if (gui_var_sm_1_offset != dsynthvar_config.sm_1_offset)
        {
            dsynthvar_config.sm_1_offset = gui_var_sm_1_offset;
            dsynthvar.SetSM(1, dsynthvar_config.sm_1_type, dsynthvar_config.sm_1_freq, dsynthvar_config.sm_1_amp, dsynthvar_config.sm_1_offset);
        }

        // SM 2

        if (gui_var_sm_2_type != dsynthvar_config.sm_2_type)
        {
            dsynthvar_config.sm_2_type = gui_var_sm_2_type;
            dsynthvar.SetSM(2, dsynthvar_config.sm_2_type, dsynthvar_config.sm_2_freq, dsynthvar_config.sm_2_amp, dsynthvar_config.sm_2_offset);
        }

        if (gui_var_sm_2_freq != dsynthvar_config.sm_2_freq)
        {
            dsynthvar_config.sm_2_freq = gui_var_sm_2_freq;
            dsynthvar.SetSM(2, dsynthvar_config.sm_2_type, dsynthvar_config.sm_2_freq, dsynthvar_config.sm_2_amp, dsynthvar_config.sm_2_offset);
        }

        if (gui_var_sm_2_amp != dsynthvar_config.sm_2_amp)
        {
            dsynthvar_config.sm_2_amp = gui_var_sm_2_amp;
            dsynthvar.SetSM(2, dsynthvar_config.sm_2_type, dsynthvar_config.sm_2_freq, dsynthvar_config.sm_2_amp, dsynthvar_config.sm_2_offset);
        }

        if (gui_var_sm_2_offset != dsynthvar_config.sm_2_offset)
        {
            dsynthvar_config.sm_2_offset = gui_var_sm_2_offset;
            dsynthvar.SetSM(2, dsynthvar_config.sm_2_type, dsynthvar_config.sm_2_freq, dsynthvar_config.sm_2_amp, dsynthvar_config.sm_2_offset);
        }

        // FX

        if (gui_var_portamento != dsynthvar_config.portamento)
        {
            dsynthvar_config.portamento = gui_var_portamento;
            dsynthvar.SetPortamento(dsynthvar_config.portamento);
        }

        if (gui_var_delay_delay != dsynthvar_config.delay_delay)
        {
            dsynthvar_config.delay_delay = gui_var_delay_delay;
            dsynthvar.SetDelay(dsynthvar_config.delay_delay, dsynthvar_config.delay_feedback);
        }

        if (gui_var_delay_feedback != dsynthvar_config.delay_feedback)
        {
            dsynthvar_config.delay_feedback = gui_var_delay_feedback;
            dsynthvar.SetDelay(dsynthvar_config.delay_delay, dsynthvar_config.delay_feedback);
        }

        if (gui_var_overdrive_gain != dsynthvar_config.overdrive_gain)
        {
            dsynthvar_config.overdrive_gain = gui_var_overdrive_gain;
            dsynthvar.SetOverdrive(dsynthvar_config.overdrive_gain, dsynthvar_config.overdrive_drive);
        }

        if (gui_var_overdrive_drive != dsynthvar_config.overdrive_drive)
        {
            dsynthvar_config.overdrive_drive = gui_var_overdrive_drive;
            dsynthvar.SetOverdrive(dsynthvar_config.overdrive_gain, dsynthvar_config.overdrive_drive);
        }


        break;

    case SAMPLER:

        if (gui_synth_engine != synth_engine)
        {
            synth_engine = static_cast<SynthEngine>(static_cast<int>(gui_synth_engine));
        }

        // osc
        if (gui_sampler_voices != dsampler_config.voices)
        {
            dsampler_config.voices = gui_sampler_voices;
            dsampler.Init(dsampler_config);
        }

        // sample
        if (gui_sampler_phase_start != dsampler_config.sample_phase_start)
        {
            dsampler_config.sample_phase_start = gui_sampler_phase_start;
            dsampler.SetPhase(dsampler_config.sample_phase_start, dsampler_config.sample_phase_loop_start, dsampler_config.sample_phase_loop_end, dsampler_config.sample_phase_end);
        }
        if (gui_sampler_phase_end != dsampler_config.sample_phase_end)
        {
            dsampler_config.sample_phase_end = gui_sampler_phase_end;
            dsampler.SetPhase(dsampler_config.sample_phase_start, dsampler_config.sample_phase_loop_start, dsampler_config.sample_phase_loop_end, dsampler_config.sample_phase_end);
        }
        if (gui_sampler_phase_loop_start != dsampler_config.sample_phase_loop_start)
        {
            dsampler_config.sample_phase_loop_start = gui_sampler_phase_loop_start;
            dsampler.SetPhase(dsampler_config.sample_phase_start, dsampler_config.sample_phase_loop_start, dsampler_config.sample_phase_loop_end, dsampler_config.sample_phase_end);
        }
        if (gui_sampler_phase_loop_end != dsampler_config.sample_phase_loop_end)
        {
            dsampler_config.sample_phase_loop_end = gui_sampler_phase_loop_end;
            dsampler.SetPhase(dsampler_config.sample_phase_start, dsampler_config.sample_phase_loop_start, dsampler_config.sample_phase_loop_end, dsampler_config.sample_phase_end);
        }
        if (gui_sampler_loop != dsampler_config.loop)
        {
            dsampler_config.loop = gui_sampler_loop;
            dsampler.SetLoop(dsampler_config.loop);
        }

        if (gui_sampler_tune != dsampler_config.tune)
        {
            dsampler_config.tune = gui_sampler_tune;
            dsampler.SetTuning(dsampler_config.tune);
        }

        if (gui_sampler_transpose != dsampler_config.transpose)
        {
            dsampler_config.transpose = gui_sampler_transpose;
            dsampler.SetTranspose(dsampler_config.transpose);
        }

        // filter

        if (gui_sampler_filter_type != dsampler_config.filter_type)
        {
            int foo = gui_sampler_filter_type;
            dsampler_config.filter_type = (DSampler::FilterType)foo;
            dsampler.SetFilter(dsampler_config.filter_type, dsampler_config.filter_cutoff, dsampler_config.filter_res);
        }

        if (gui_sampler_filter_cutoff != dsampler_config.filter_cutoff)
        {
            dsampler_config.filter_cutoff = gui_sampler_filter_cutoff;
            dsampler.SetFilter(dsampler_config.filter_type, dsampler_config.filter_cutoff, dsampler_config.filter_res);
        }

        if (gui_sampler_filter_res != dsampler_config.filter_res)
        {
            dsampler_config.filter_res = gui_sampler_filter_res;
            dsampler.SetFilter(dsampler_config.filter_type, dsampler_config.filter_cutoff, dsampler_config.filter_res);
        }

        // EG p

        if (gui_sampler_eg_p_level != dsampler_config.eg_p_level)
        {
            dsampler_config.eg_p_level = gui_sampler_eg_p_level;
            dsampler.SetEGLevel(DSampler::PITCH, dsampler_config.eg_p_level);
        }

        if (gui_sampler_eg_p_attack != dsampler_config.eg_p_attack)
        {
            dsampler_config.eg_p_attack = gui_sampler_eg_p_attack;
            dsampler.SetEG(DSampler::PITCH, dsampler_config.eg_p_attack, dsampler_config.eg_p_decay, dsampler_config.eg_p_sustain, dsampler_config.eg_p_release);
        }

        if (gui_sampler_eg_p_decay != dsampler_config.eg_p_decay)
        {
            dsampler_config.eg_p_decay = gui_sampler_eg_p_decay;
            dsampler.SetEG(DSampler::PITCH, dsampler_config.eg_p_attack, dsampler_config.eg_p_decay, dsampler_config.eg_p_sustain, dsampler_config.eg_p_release);
        }

        if (gui_sampler_eg_p_sustain != dsampler_config.eg_p_sustain)
        {
            dsampler_config.eg_p_sustain = gui_sampler_eg_p_sustain;
            dsampler.SetEG(DSampler::PITCH, dsampler_config.eg_p_attack, dsampler_config.eg_p_decay, dsampler_config.eg_p_sustain, dsampler_config.eg_p_release);
        }

        if (gui_sampler_eg_p_release != dsampler_config.eg_p_release)
        {
            dsampler_config.eg_p_release = gui_sampler_eg_p_release;
            dsampler.SetEG(DSampler::PITCH, dsampler_config.eg_p_attack, dsampler_config.eg_p_decay, dsampler_config.eg_p_sustain, dsampler_config.eg_p_release);
        }

        // EG f

        if (gui_sampler_eg_f_level != dsampler_config.eg_f_level)
        {
            dsampler_config.eg_f_level = gui_sampler_eg_f_level;
            dsampler.SetEGLevel(DSampler::FILTER, dsampler_config.eg_f_level);
        }

        if (gui_sampler_eg_f_attack != dsampler_config.eg_f_attack)
        {
            dsampler_config.eg_f_attack = gui_sampler_eg_f_attack;
            dsampler.SetEG(DSampler::FILTER, dsampler_config.eg_f_attack, dsampler_config.eg_f_decay, dsampler_config.eg_f_sustain, dsampler_config.eg_f_release);
        }

        if (gui_sampler_eg_f_decay != dsampler_config.eg_f_decay)
        {
            dsampler_config.eg_f_decay = gui_sampler_eg_f_decay;
            dsampler.SetEG(DSampler::FILTER, dsampler_config.eg_f_attack, dsampler_config.eg_f_decay, dsampler_config.eg_f_sustain, dsampler_config.eg_f_release);
        }

        if (gui_sampler_eg_f_sustain != dsampler_config.eg_f_sustain)
        {
            dsampler_config.eg_f_sustain = gui_sampler_eg_f_sustain;
            dsampler.SetEG(DSampler::FILTER, dsampler_config.eg_f_attack, dsampler_config.eg_f_decay, dsampler_config.eg_f_sustain, dsampler_config.eg_f_release);
        }

        if (gui_sampler_eg_f_release != dsampler_config.eg_f_release)
        {
            dsampler_config.eg_f_release = gui_sampler_eg_f_release;
            dsampler.SetEG(DSampler::FILTER, dsampler_config.eg_f_attack, dsampler_config.eg_f_decay, dsampler_config.eg_f_sustain, dsampler_config.eg_f_release);
        }

        // EG a

        if (gui_sampler_eg_a_attack != dsampler_config.eg_a_attack)
        {
            dsampler_config.eg_a_attack = gui_sampler_eg_a_attack;
            dsampler.SetEG(DSampler::AMP, dsampler_config.eg_a_attack, dsampler_config.eg_a_decay, dsampler_config.eg_a_sustain, dsampler_config.eg_a_release);
        }

        if (gui_sampler_eg_a_decay != dsampler_config.eg_a_decay)
        {
            dsampler_config.eg_a_decay = gui_sampler_eg_a_decay;
            dsampler.SetEG(DSampler::AMP, dsampler_config.eg_a_attack, dsampler_config.eg_a_decay, dsampler_config.eg_a_sustain, dsampler_config.eg_a_release);
        }

        if (gui_sampler_eg_a_sustain != dsampler_config.eg_a_sustain)
        {
            dsampler_config.eg_a_sustain = gui_sampler_eg_a_sustain;
            dsampler.SetEG(DSampler::AMP, dsampler_config.eg_a_attack, dsampler_config.eg_a_decay, dsampler_config.eg_a_sustain, dsampler_config.eg_a_release);
        }

        if (gui_sampler_eg_a_release != dsampler_config.eg_a_release)
        {
            dsampler_config.eg_a_release = gui_sampler_eg_a_release;
            dsampler.SetEG(DSampler::AMP, dsampler_config.eg_a_attack, dsampler_config.eg_a_decay, dsampler_config.eg_a_sustain, dsampler_config.eg_a_release);
        }

        // LFO

        if (gui_sampler_lfo_waveform != dsampler_config.lfo_waveform)
        {
            int foo = gui_sampler_lfo_waveform;
            dsampler_config.lfo_waveform = (DSampler::Waveform)foo;
            dsampler.SetLFO(dsampler_config.lfo_waveform, dsampler_config.lfo_freq, dsampler_config.lfo_amp, dsampler_config.lfo_p_level, dsampler_config.lfo_f_level, dsampler_config.lfo_a_level);
        }

        if (gui_sampler_lfo_freq != dsampler_config.lfo_freq)
        {
            dsampler_config.lfo_freq = gui_sampler_lfo_freq;
            dsampler.SetLFO(dsampler_config.lfo_waveform, dsampler_config.lfo_freq, dsampler_config.lfo_amp, dsampler_config.lfo_p_level, dsampler_config.lfo_f_level, dsampler_config.lfo_a_level);
        }

        if (gui_sampler_lfo_amp != dsampler_config.lfo_amp)
        {
            dsampler_config.lfo_amp = gui_sampler_lfo_amp;
            dsampler.SetLFO(dsampler_config.lfo_waveform, dsampler_config.lfo_freq, dsampler_config.lfo_amp, dsampler_config.lfo_p_level, dsampler_config.lfo_f_level, dsampler_config.lfo_a_level);
        }

        if (gui_sampler_lfo_p_level != dsampler_config.lfo_p_level)
        {
            dsampler_config.lfo_p_level = gui_sampler_lfo_p_level;
            dsampler.SetLFO(dsampler_config.lfo_waveform, dsampler_config.lfo_freq, dsampler_config.lfo_amp, dsampler_config.lfo_p_level, dsampler_config.lfo_f_level, dsampler_config.lfo_a_level);
        }

        if (gui_sampler_lfo_f_level != dsampler_config.lfo_f_level)
        {
            dsampler_config.lfo_f_level = gui_sampler_lfo_f_level;
            dsampler.SetLFO(dsampler_config.lfo_waveform, dsampler_config.lfo_freq, dsampler_config.lfo_amp, dsampler_config.lfo_p_level, dsampler_config.lfo_f_level, dsampler_config.lfo_a_level);
        }

        if (gui_sampler_lfo_a_level != dsampler_config.lfo_a_level)
        {
            dsampler_config.lfo_a_level = gui_sampler_lfo_a_level;
            dsampler.SetLFO(dsampler_config.lfo_waveform, dsampler_config.lfo_freq, dsampler_config.lfo_amp, dsampler_config.lfo_p_level, dsampler_config.lfo_f_level, dsampler_config.lfo_a_level);
        }

        // FX

        if (gui_sampler_portamento != dsampler_config.portamento)
        {
            dsampler_config.portamento = gui_sampler_portamento;
            dsampler.SetPortamento(dsampler_config.portamento);
        }

        if (gui_sampler_delay_delay != dsampler_config.delay_delay)
        {
            dsampler_config.delay_delay = gui_sampler_delay_delay;
            dsampler.SetDelay(dsampler_config.delay_delay, dsampler_config.delay_feedback);
        }

        if (gui_sampler_delay_feedback != dsampler_config.delay_feedback)
        {
            dsampler_config.delay_feedback = gui_sampler_delay_feedback;
            dsampler.SetDelay(dsampler_config.delay_delay, dsampler_config.delay_feedback);
        }

        if (gui_sampler_overdrive_gain != dsampler_config.overdrive_gain)
        {
            dsampler_config.overdrive_gain = gui_sampler_overdrive_gain;
            dsampler.SetOverdrive(dsampler_config.overdrive_gain, dsampler_config.overdrive_drive);
        }

        if (gui_sampler_overdrive_drive != dsampler_config.overdrive_drive)
        {
            dsampler_config.overdrive_drive = gui_sampler_overdrive_drive;
            dsampler.SetOverdrive(dsampler_config.overdrive_gain, dsampler_config.overdrive_drive);
        }
        break;
    case VAR_SEQ:
        if (gui_synth_engine != synth_engine)
        {
            synth_engine = static_cast<SynthEngine>(static_cast<int>(gui_synth_engine));
        }

        if (gui_seq_0_step_max != dsynthvar_config.sm_0_seq_len)
        {
            dsynthvar_config.sm_0_seq_len = gui_seq_0_step_max;
            dsynthvar_config.sm_0_seq_val.resize(dsynthvar_config.sm_0_seq_len);
            dsynthvar.SetSMSeq(0, dsynthvar_config.sm_0_seq_len, dsynthvar_config.sm_0_seq_val);
        }
        if (gui_seq_1_step_max != dsynthvar_config.sm_1_seq_len)
        {
            dsynthvar_config.sm_1_seq_len = gui_seq_1_step_max;
            dsynthvar_config.sm_1_seq_val.resize(dsynthvar_config.sm_1_seq_len);
            dsynthvar.SetSMSeq(1, dsynthvar_config.sm_1_seq_len, dsynthvar_config.sm_1_seq_val);
        }
        if (gui_seq_2_step_max != dsynthvar_config.sm_2_seq_len)
        {
            dsynthvar_config.sm_2_seq_len = gui_seq_2_step_max;
            dsynthvar_config.sm_2_seq_val.resize(dsynthvar_config.sm_2_seq_len);
            dsynthvar.SetSMSeq(2, dsynthvar_config.sm_2_seq_len, dsynthvar_config.sm_2_seq_val);
        }
        for (uint8_t v = 0; v < dsynthvar_config.sm_0_seq_len; v++)
        {
            if (gui_seq_0_step[v] != dsynthvar_config.sm_0_seq_val[v])
            {
                dsynthvar_config.sm_0_seq_val[v] = gui_seq_0_step[v];
            }
        }
        for (uint8_t v = 0; v < dsynthvar_config.sm_1_seq_len; v++)
        {
            if (gui_seq_1_step[v] != dsynthvar_config.sm_1_seq_val[v])
            {
                dsynthvar_config.sm_1_seq_val[v] = gui_seq_1_step[v];
            }
        }
        for (uint8_t v = 0; v < dsynthvar_config.sm_2_seq_len; v++)
        {
            if (gui_seq_2_step[v] != dsynthvar_config.sm_2_seq_val[v])
            {
                dsynthvar_config.sm_2_seq_val[v] = gui_seq_2_step[v];
            }
        }
        break;
    case DRUM:
        if (gui_synth_engine != synth_engine)
        {
            synth_engine = static_cast<SynthEngine>(static_cast<int>(gui_synth_engine));
        }

        // bass
        if (gui_d_bass_type != dbass_config.type)
        {
            dbass_config.type = gui_d_bass_type;
            dbass.SetDType(dbass_config.type);
        }
        if (gui_d_bass_freq != dbass_config.freq)
        {
            dbass_config.freq = gui_d_bass_freq;
            dbass.SetFreq(dbass_config.freq);
        }
        if (gui_d_bass_tone != dbass_config.tone)
        {
            dbass_config.tone = gui_d_bass_tone;
            dbass.SetTone(dbass_config.tone);
        }
        if (gui_d_bass_decay != dbass_config.decay)
        {
            dbass_config.decay = gui_d_bass_decay;
            dbass.SetDecay(dbass_config.decay);
        }
        if (gui_d_bass_fm_attack != dbass_config.fm_attack)
        {
            dbass_config.fm_attack = gui_d_bass_fm_attack;
            dbass.SetFMAttack(dbass_config.fm_attack);
        }
        if (gui_d_bass_fm_self != dbass_config.fm_self)
        {
            dbass_config.fm_self = gui_d_bass_fm_self;
            dbass.SetFMSelf(dbass_config.fm_self);
        }
        if (gui_d_bass_dirtiness != dbass_config.dirtiness)
        {
            dbass_config.dirtiness = gui_d_bass_dirtiness;
            dbass.SetDirtiness(dbass_config.dirtiness);
        }
        if (gui_d_bass_fm_env_amount != dbass_config.fm_env_amount)
        {
            dbass_config.fm_env_amount = gui_d_bass_fm_env_amount;
            dbass.SetFMEnv(dbass_config.fm_env_amount);
        }
        if (gui_d_bass_fm_env_decay != dbass_config.fm_env_decay)
        {
            dbass_config.fm_env_decay = gui_d_bass_fm_env_decay;
            dbass.SetFMEnvDecay(dbass_config.fm_env_decay);
        }
        if (gui_d_bass_min != dbass_config.min)
        {
            dbass_config.min = gui_d_bass_min;
            dbass.SetMin(dbass_config.min);
        }

        // snare
        if (gui_d_snare_type != dsnare_config.type)
        {
            dsnare_config.type = gui_d_snare_type;
            dsnare.SetDType(dsnare_config.type);
        }
        if (gui_d_snare_freq != dsnare_config.freq)
        {
            dsnare_config.freq = gui_d_snare_freq;
            dsnare.SetFreq(dsnare_config.freq);
        }
        if (gui_d_snare_tone != dsnare_config.tone)
        {
            dsnare_config.tone = gui_d_snare_tone;
            dsnare.SetTone(dsnare_config.tone);
        }
        if (gui_d_snare_decay != dsnare_config.decay)
        {
            dsnare_config.decay = gui_d_snare_decay;
            dsnare.SetDecay(dsnare_config.decay);
        }
        if (gui_d_snare_snappy != dsnare_config.snappy)
        {
            dsnare_config.snappy = gui_d_snare_snappy;
            dsnare.SetSnappy(dsnare_config.snappy);
        }
        if (gui_d_snare_fm_amount != dsnare_config.fm_amount)
        {
            dsnare_config.fm_amount = gui_d_snare_fm_amount;
            dsnare.SetFM(dsnare_config.fm_amount);
        }
        if (gui_d_snare_freq_noise != dsnare_config.freq_noise)
        {
            dsnare_config.freq_noise = gui_d_snare_freq_noise;
            dsnare.SetFreqNoise(dsnare_config.freq_noise);
        }
        if (gui_d_snare_amp != dsnare_config.amp)
        {
            dsnare_config.amp = gui_d_snare_amp;
            dsnare.SetAmp(dsnare_config.amp);
        }
        if (gui_d_snare_res != dsnare_config.res)
        {
            dsnare_config.res = gui_d_snare_res;
            dsnare.SetRes(dsnare_config.res);
        }
        if (gui_d_snare_drive != dsnare_config.drive)
        {
            dsnare_config.drive = gui_d_snare_drive;
            dsnare.SetDrive(dsnare_config.drive);
        }
        if (gui_d_snare_min != dsnare_config.min)
        {
            dsnare_config.min = gui_d_snare_min;
            dsnare.SetMin(dsnare_config.min);
        }

        // hihat
        if (gui_d_hihat_type != dhihat_config.type)
        {
            dhihat_config.type = gui_d_hihat_type;
            dhihat.SetDType(dhihat_config.type);
        }
        if (gui_d_hihat_freq != dhihat_config.freq)
        {
            dhihat_config.freq = gui_d_hihat_freq;
            dhihat.SetFreq(dhihat_config.freq);
        }
        if (gui_d_hihat_tone != dhihat_config.tone)
        {
            dhihat_config.tone = gui_d_hihat_tone;
            dhihat.SetTone(dhihat_config.tone);
        }
        if (gui_d_hihat_decay != dhihat_config.decay)
        {
            dhihat_config.decay = gui_d_hihat_decay;
            dhihat.SetDecay(dhihat_config.decay);
        }
        if (gui_d_hihat_noisiness != dhihat_config.noisiness)
        {
            dhihat_config.noisiness = gui_d_hihat_noisiness;
            dhihat.SetNoisiness(dhihat_config.noisiness);
        }
        if (gui_d_hihat_amp != dhihat_config.amp)
        {
            dhihat_config.amp = gui_d_hihat_amp;
            dhihat.SetAmp(dhihat_config.amp);
        }
        if (gui_d_hihat_res != dhihat_config.res)
        {
            dhihat_config.res = gui_d_hihat_res;
            dhihat.SetRes(dhihat_config.res);
        }
        if (gui_d_hihat_drive != dhihat_config.drive)
        {
            dhihat_config.drive = gui_d_hihat_drive;
            dhihat.SetDrive(dhihat_config.drive);
        }

        // clap
        if (gui_d_clap_freq != dclap_config.freq)
        {
            dclap_config.freq = gui_d_clap_freq;
            dclap.SetFreq(dclap_config.freq);
        }
        if (gui_d_clap_res != dclap_config.res)
        {
            dclap_config.res = gui_d_clap_res;
            dclap.SetRes(dclap_config.res);
        }
        if (gui_d_clap_drive != dclap_config.drive)
        {
            dclap_config.drive = gui_d_clap_drive;
            dclap.SetDrive(dclap_config.drive);
        }
        if (gui_d_clap_amp != dclap_config.amp)
        {
            dclap_config.amp = gui_d_clap_amp;
            dclap.SetAmp(dclap_config.amp);
        }
        if (gui_d_clap_decay != dclap_config.decay)
        {
            dclap_config.decay = gui_d_clap_decay;
            dclap.SetDecay(dclap_config.decay);
        }

        // cymbal
        if (gui_d_cymbal_freq != dcymbal_config.freq)
        {
            dcymbal_config.freq = gui_d_cymbal_freq;
            dcymbal.SetFreq(dcymbal_config.freq);
        }
        if (gui_d_cymbal_res != dcymbal_config.res)
        {
            dcymbal_config.res = gui_d_cymbal_res;
            dcymbal.SetRes(dcymbal_config.res);
        }
        if (gui_d_cymbal_drive != dcymbal_config.drive)
        {
            dcymbal_config.drive = gui_d_cymbal_drive;
            dcymbal.SetDrive(dcymbal_config.drive);
        }
        if (gui_d_cymbal_amp != dcymbal_config.amp)
        {
            dcymbal_config.amp = gui_d_cymbal_amp;
            dcymbal.SetAmp(dcymbal_config.amp);
        }
        if (gui_d_cymbal_decay != dcymbal_config.decay)
        {
            dcymbal_config.decay = gui_d_cymbal_decay;
            dcymbal.SetDecay(dcymbal_config.decay);
        }
        if (gui_d_cymbal_min != dcymbal_config.min)
        {
            dcymbal_config.min = gui_d_cymbal_min;
            dcymbal.SetMin(dcymbal_config.min);
        }
        if (gui_d_cymbal_mix != dcymbal_config.mix)
        {
            dcymbal_config.mix = gui_d_cymbal_mix;
            dcymbal.SetMix(dcymbal_config.mix);
        }

        // tom
        if (gui_d_drum_freq != ddrum_config.freq)
        {
            ddrum_config.freq = gui_d_drum_freq;
            ddrum.SetFreq(ddrum_config.freq);
        }
        if (gui_d_drum_amp != ddrum_config.amp)
        {
            ddrum_config.amp = gui_d_drum_amp;
            ddrum.SetAmp(ddrum_config.amp);
        }
        if (gui_d_drum_decay != ddrum_config.decay)
        {
            ddrum_config.decay = gui_d_drum_decay;
            ddrum.SetDecay(ddrum_config.decay);
        }
        if (gui_d_drum_min != ddrum_config.min)
        {
            ddrum_config.min = gui_d_drum_min;
            ddrum.SetMin(ddrum_config.min);
        }

        break;
    }

}



void ofApp::draw()
{
    switch (synth_engine)
    {
    case SUB:
        gui_sub.draw();
        break;
    case FM:
        gui_fm.draw();
        break;
    case VAR:
        gui_var.draw();
        break;
    case SAMPLER:
        gui_sampler.draw();
        break;
    case VAR_SEQ:
        gui_seq.draw();
        break;
    case DRUM:
        gui_d.draw();
        break;
    }
}



uint8_t ofApp::noteMap(int key)
{
    // search for key in note_map[]
    uint8_t map_pos = GUI_NOTE_MAP_MAX; // 1 too much
    for (uint8_t i = 0; i < GUI_NOTE_MAP_MAX; i++)
    {
        if (key == note_map[i][0])
        {
            map_pos = i;
            break;
        }
    }
    return (map_pos);
}



void ofApp::keyPressed(int key)
{
    uint8_t map_pos = noteMap(key);
    if (map_pos != GUI_NOTE_MAP_MAX)
    {
        uint8_t note = GUI_NOTE_MIDI_BASE + note_map[map_pos][1];
        // is key already pressed and is there room for another
        bool found = false;
        uint8_t empty_pos = GUI_NOTE_MAX; // not usable
        for (uint8_t i = 0; i < GUI_NOTE_MAX; i++)
        {
            if (note_play[i] == note)
            {
                found = true;
            }
            if (note_play[i] == 0)
            {
                empty_pos = i;
            }
        }
        if (!found && (empty_pos != GUI_NOTE_MAX))
        {
            note_play[empty_pos] = note;
            switch (synth_engine)
            {
            case SUB:
                dsynthsub.MidiIn(MIDI_MESSAGE_NOTEON, note, GUI_SYNTH_VELOCITY);
                break;
            case FM:
                dsynthfm.MidiIn(MIDI_MESSAGE_NOTEON, note, GUI_SYNTH_VELOCITY);
                break;
            case VAR:
            case VAR_SEQ:
                dsynthvar.MidiIn(MIDI_MESSAGE_NOTEON, note, GUI_SYNTH_VELOCITY);
                break;
            case SAMPLER:
                dsampler.MidiIn(MIDI_MESSAGE_NOTEON, note, GUI_SYNTH_VELOCITY);
                break;
            case DRUM:
                switch (map_pos)
                {
                case 0:
                    dbass.MidiIn(MIDI_MESSAGE_NOTEON, GUI_DRUM_NOTE, GUI_DRUM_VELOCITY);
                    break;
                case 1:
                    dsnare.MidiIn(MIDI_MESSAGE_NOTEON, GUI_DRUM_NOTE, GUI_DRUM_VELOCITY);
                    break;
                case 2:
                    dhihat.MidiIn(MIDI_MESSAGE_NOTEON, GUI_DRUM_NOTE, GUI_DRUM_VELOCITY);
                    break;
                case 3:
                    dclap.MidiIn(MIDI_MESSAGE_NOTEON, GUI_DRUM_NOTE, GUI_DRUM_VELOCITY);
                    break;
                case 4:
                    dcymbal.MidiIn(MIDI_MESSAGE_NOTEON, GUI_DRUM_NOTE, GUI_DRUM_VELOCITY);
                    break;
                case 5:
                    ddrum.MidiIn(MIDI_MESSAGE_NOTEON, GUI_DRUM_NOTE, GUI_DRUM_VELOCITY);
                    break;
                default:
                    break;
                }
                break;
            }
        }
    }
}



void ofApp::keyReleased(int key)
{
    uint8_t map_pos = noteMap(key);
    if (map_pos != GUI_NOTE_MAP_MAX)
    {
        uint8_t note = GUI_NOTE_MIDI_BASE + note_map[map_pos][1];
        // is key already pressed and is there room for another
        for (uint8_t i = 0; i < GUI_NOTE_MAX; i++)
        {
            if (note_play[i] == note)
            {
                note_play[i] = 0;
                break;
            }
        }
        switch (synth_engine)
        {
        case SUB:
            dsynthsub.MidiIn(MIDI_MESSAGE_NOTEOFF, note, 0);
            break;
        case FM:
            dsynthfm.MidiIn(MIDI_MESSAGE_NOTEOFF, note, 0);
            break;
        case VAR:
        case VAR_SEQ:
            dsynthvar.MidiIn(MIDI_MESSAGE_NOTEOFF, note, 0);
            break;
        case SAMPLER:
            dsampler.MidiIn(MIDI_MESSAGE_NOTEOFF, note, 0);
            break;
        case DRUM:
            // nothing to do
            break;
        }
    }
}




void ofApp::newMidiMessage(ofxMidiMessage& msg)
{
    uint8_t midi_message = msg.status & MIDI_MESSAGE_MASK;
    uint8_t midi_channel = msg.channel;

    // ofxMidi: channel 1-16
    midi_channel--;

    switch (midi_message)
    {
    case MIDI_MESSAGE_NOTEON:
    case MIDI_MESSAGE_NOTEOFF:
        // mixer will send note on/off to synth on channel 0
        //dmixer.MidiIn(, msg.pitch, msg.velocity);
        switch (synth_engine)
        {
        case SUB:
            dsynthsub.MidiIn(midi_message + midi_channel, msg.pitch, msg.velocity);
            break;
        case FM:
            dsynthfm.MidiIn(midi_message + midi_channel, msg.pitch, msg.velocity);
            break;
        case VAR:
        case VAR_SEQ:
            dsynthvar.MidiIn(midi_message + midi_channel, msg.pitch, msg.velocity);
            break;
        case SAMPLER:
            dsampler.MidiIn(midi_message + midi_channel, msg.pitch, msg.velocity);
            break;
        case DRUM:
            switch (msg.pitch)
            {
            case 36: // bass 1
                dbass.MidiIn(MIDI_MESSAGE_NOTEON, GUI_DRUM_NOTE, GUI_DRUM_VELOCITY);
                break;
            case 38: // snare 1
                dsnare.MidiIn(MIDI_MESSAGE_NOTEON, GUI_DRUM_NOTE, GUI_DRUM_VELOCITY);
                break;
            case 42: // closed hihat
            case 46: // open hihat
                dhihat.MidiIn(MIDI_MESSAGE_NOTEON, GUI_DRUM_NOTE, GUI_DRUM_VELOCITY);
                break;
            case 39:
                dclap.MidiIn(MIDI_MESSAGE_NOTEON, GUI_DRUM_NOTE, GUI_DRUM_VELOCITY);
                break;
            case 49: // crash 1
                dcymbal.MidiIn(MIDI_MESSAGE_NOTEON, GUI_DRUM_NOTE, GUI_DRUM_VELOCITY);
                break;
            case 47: // mid tom 1
                ddrum.MidiIn(MIDI_MESSAGE_NOTEON, GUI_DRUM_NOTE, GUI_DRUM_VELOCITY);
                break;
            default:
                break;
            }
        }
        break;
    case MIDI_MESSAGE_CC:
        // mixer willl handle pan and level
        // and send cutoff and res to synth on channel 0
//        dmixer.MidiIn(midi_message + midi_channel, msg.control, msg.value);
        switch (synth_engine)
        {
        case SUB:
            dsynthsub.MidiIn(midi_message + midi_channel, msg.control, msg.value);
            break;
        case FM:
            dsynthfm.MidiIn(midi_message + midi_channel, msg.control, msg.value);
            break;
        case VAR:
        case VAR_SEQ:
            dsynthvar.MidiIn(midi_message + midi_channel, msg.control, msg.value);
            break;
        case SAMPLER:
            dsampler.MidiIn(midi_message + midi_channel, msg.control, msg.value);
            break;
        case DRUM:
            // do nothing
            break;
        }
        break;
    default:
        break;
    }

}



void ofApp::GuiSetupSub()
{

    gui_sub.setDefaultWidth(GUI_DEFAULT_WIDTH);
    gui_sub.setup("DSynthSub");
    gui_sub.add(gui_load);
    gui_sub.add(gui_save);
    gui_sub.add(gui_synth_engine);

    gui_sub_group_osc.setName("Oscillators");
    gui_sub_group_osc.add(gui_sub_voices);
    gui_sub_group_osc.add(gui_sub_waveform0);
    gui_sub_group_osc.add(gui_sub_waveform1);
    gui_sub_group_osc.add(gui_sub_tune);
    gui_sub_group_osc.add(gui_sub_detune);
    gui_sub_group_osc.add(gui_sub_transpose);
    gui_sub_group_osc.add(gui_sub_osc0_level);
    gui_sub_group_osc.add(gui_sub_osc1_level);
    gui_sub_group_osc.add(gui_sub_noise_level);
    gui_sub.add(gui_sub_group_osc);

    gui_sub_group_filter.setName("Filter");
    gui_sub_group_filter.add(gui_sub_filter_type);
    gui_sub_group_filter.add(gui_sub_filter_cutoff);
    gui_sub_group_filter.add(gui_sub_filter_res);
    gui_sub.add(gui_sub_group_filter);

    gui_sub_group_eg_p.setName("EG pitch");
    gui_sub_group_eg_p.add(gui_sub_eg_p_level);
    gui_sub_group_eg_p.add(gui_sub_eg_p_attack);
    gui_sub_group_eg_p.add(gui_sub_eg_p_decay);
    gui_sub_group_eg_p.add(gui_sub_eg_p_sustain);
    gui_sub_group_eg_p.add(gui_sub_eg_p_release);
    gui_sub.add(gui_sub_group_eg_p);

    gui_sub_group_eg_f.setName("EG filter");
    gui_sub_group_eg_f.add(gui_sub_eg_f_level);
    gui_sub_group_eg_f.add(gui_sub_eg_f_attack);
    gui_sub_group_eg_f.add(gui_sub_eg_f_decay);
    gui_sub_group_eg_f.add(gui_sub_eg_f_sustain);
    gui_sub_group_eg_f.add(gui_sub_eg_f_release);
    gui_sub.add(gui_sub_group_eg_f);

    gui_sub_group_eg_a.setName("EG amp");
    gui_sub_group_eg_a.add(gui_sub_eg_a_attack);
    gui_sub_group_eg_a.add(gui_sub_eg_a_decay);
    gui_sub_group_eg_a.add(gui_sub_eg_a_sustain);
    gui_sub_group_eg_a.add(gui_sub_eg_a_release);
    gui_sub.add(gui_sub_group_eg_a);

    gui_sub_group_lfo.setName("LFO");
    gui_sub_group_lfo.add(gui_sub_lfo_waveform);
    gui_sub_group_lfo.add(gui_sub_lfo_freq);
    gui_sub_group_lfo.add(gui_sub_lfo_amp);
    gui_sub_group_lfo.add(gui_sub_lfo_p_level);
    gui_sub_group_lfo.add(gui_sub_lfo_f_level);
    gui_sub_group_lfo.add(gui_sub_lfo_a_level);
    gui_sub.add(gui_sub_group_lfo);

    gui_sub_group_fx.setName("FX");
    gui_sub_group_fx.add(gui_sub_portamento);
    gui_sub_group_fx.add(gui_sub_delay_delay);
    gui_sub_group_fx.add(gui_sub_delay_feedback);
    gui_sub_group_fx.add(gui_sub_overdrive_gain);
    gui_sub_group_fx.add(gui_sub_overdrive_drive);
    gui_sub.add(gui_sub_group_fx);

    gui_sub.minimizeAll();


}


void ofApp::GuiSetupFm()
{
    gui_fm.setDefaultWidth(GUI_DEFAULT_WIDTH);
    gui_fm.setup("DSynthFm");
    gui_fm.add(gui_load);
    gui_fm.add(gui_save);
    gui_fm.add(gui_synth_engine);

    gui_fm_group_osc.setName("Oscillators");
    gui_fm_group_osc.add(gui_fm_voices);
    gui_fm_group_osc.add(gui_fm_ratio);
    gui_fm_group_osc.add(gui_fm_index);
    gui_fm_group_osc.add(gui_fm_tune);
    gui_fm_group_osc.add(gui_fm_transpose);
    gui_fm_group_osc.add(gui_fm_noise_level);
    gui_fm.add(gui_fm_group_osc);

    gui_fm_group_filter.setName("Filter");
    gui_fm_group_filter.add(gui_fm_filter_type);
    gui_fm_group_filter.add(gui_fm_filter_cutoff);
    gui_fm_group_filter.add(gui_fm_filter_res);
    gui_fm.add(gui_fm_group_filter);

    gui_fm_group_eg_p.setName("EG pitch");
    gui_fm_group_eg_p.add(gui_fm_eg_p_level);
    gui_fm_group_eg_p.add(gui_fm_eg_p_attack);
    gui_fm_group_eg_p.add(gui_fm_eg_p_decay);
    gui_fm_group_eg_p.add(gui_fm_eg_p_sustain);
    gui_fm_group_eg_p.add(gui_fm_eg_p_release);
    gui_fm.add(gui_fm_group_eg_p);

    gui_fm_group_eg_f.setName("EG filter");
    gui_fm_group_eg_f.add(gui_fm_eg_f_level);
    gui_fm_group_eg_f.add(gui_fm_eg_f_attack);
    gui_fm_group_eg_f.add(gui_fm_eg_f_decay);
    gui_fm_group_eg_f.add(gui_fm_eg_f_sustain);
    gui_fm_group_eg_f.add(gui_fm_eg_f_release);
    gui_fm.add(gui_fm_group_eg_f);

    gui_fm_group_eg_a.setName("EG amp");
    gui_fm_group_eg_a.add(gui_fm_eg_a_attack);
    gui_fm_group_eg_a.add(gui_fm_eg_a_decay);
    gui_fm_group_eg_a.add(gui_fm_eg_a_sustain);
    gui_fm_group_eg_a.add(gui_fm_eg_a_release);
    gui_fm.add(gui_fm_group_eg_a);

    gui_fm_group_lfo.setName("LFO");
    gui_fm_group_lfo.add(gui_fm_lfo_waveform);
    gui_fm_group_lfo.add(gui_fm_lfo_freq);
    gui_fm_group_lfo.add(gui_fm_lfo_amp);
    gui_fm_group_lfo.add(gui_fm_lfo_p_level);
    gui_fm_group_lfo.add(gui_fm_lfo_f_level);
    gui_fm_group_lfo.add(gui_fm_lfo_a_level);
    gui_fm.add(gui_fm_group_lfo);

    gui_fm_group_fx.setName("FX");
    gui_fm_group_fx.add(gui_fm_portamento);
    gui_fm_group_fx.add(gui_fm_delay_delay);
    gui_fm_group_fx.add(gui_fm_delay_feedback);
    gui_fm_group_fx.add(gui_fm_overdrive_gain);
    gui_fm_group_fx.add(gui_fm_overdrive_drive);
    gui_fm.add(gui_fm_group_fx);

    gui_fm.minimizeAll();


}



void ofApp::GuiSetupVar()
{

    gui_var.setDefaultWidth(GUI_DEFAULT_WIDTH);
    gui_var.setup("DSynthVar");
    gui_var.add(gui_load);
    gui_var.add(gui_save);
    gui_var.add(gui_synth_engine);

    gui_var_group_osc.setName("Oscillators");
    gui_var_group_osc.add(gui_var_voices);
    gui_var_group_osc.add(gui_var_waveshape);
    gui_var_group_osc.add(gui_var_pulsewidth);
    gui_var_group_osc.add(gui_var_sync_enable);
    gui_var_group_osc.add(gui_var_sync_freq);
    gui_var_group_osc.add(gui_var_tune);
    gui_var_group_osc.add(gui_var_transpose);
    gui_var_group_osc.add(gui_var_osc_level);
    gui_var_group_osc.add(gui_var_noise_level);
    gui_var.add(gui_var_group_osc);

    gui_var_group_filter.setName("Filter");
    gui_var_group_filter.add(gui_var_filter_type);
    gui_var_group_filter.add(gui_var_filter_cutoff);
    gui_var_group_filter.add(gui_var_filter_res);
    gui_var.add(gui_var_group_filter);

    gui_var_group_mod.setName("Mod NEEELLLSSS");
    gui_var_group_mod.add(gui_var_mod_eg_p);
    gui_var_group_mod.add(gui_var_mod_eg_f);
    gui_var_group_mod.add(gui_var_mod_eg_a);
    gui_var_group_mod.add(gui_var_mod_filter_cutoff);
    gui_var_group_mod.add(gui_var_mod_waveshape);
    gui_var_group_mod.add(gui_var_mod_pulsewidth);
    gui_var_group_mod.add(gui_var_mod_sync_freq);
    gui_var_group_mod.add(gui_var_mod_delay);
    gui_var.add(gui_var_group_mod);

    gui_var_group_eg_0.setName("EG 0");
    gui_var_group_eg_0.add(gui_var_eg_0_level);
    gui_var_group_eg_0.add(gui_var_eg_0_attack);
    gui_var_group_eg_0.add(gui_var_eg_0_decay);
    gui_var_group_eg_0.add(gui_var_eg_0_sustain);
    gui_var_group_eg_0.add(gui_var_eg_0_release);
    gui_var.add(gui_var_group_eg_0);

    gui_var_group_eg_1.setName("EG 1");
    gui_var_group_eg_1.add(gui_var_eg_1_level);
    gui_var_group_eg_1.add(gui_var_eg_1_attack);
    gui_var_group_eg_1.add(gui_var_eg_1_decay);
    gui_var_group_eg_1.add(gui_var_eg_1_sustain);
    gui_var_group_eg_1.add(gui_var_eg_1_release);
    gui_var.add(gui_var_group_eg_1);

    gui_var_group_eg_2.setName("EG 2");
    gui_var_group_eg_2.add(gui_var_eg_2_level);
    gui_var_group_eg_2.add(gui_var_eg_2_attack);
    gui_var_group_eg_2.add(gui_var_eg_2_decay);
    gui_var_group_eg_2.add(gui_var_eg_2_sustain);
    gui_var_group_eg_2.add(gui_var_eg_2_release);
    gui_var.add(gui_var_group_eg_2);

    gui_var_group_lfo_0.setName("LFO 0");
    gui_var_group_lfo_0.add(gui_var_lfo_0_waveform);
    gui_var_group_lfo_0.add(gui_var_lfo_0_freq);
    gui_var_group_lfo_0.add(gui_var_lfo_0_amp);
    gui_var_group_lfo_0.add(gui_var_lfo_0_offset);
    gui_var.add(gui_var_group_lfo_0);

    gui_var_group_lfo_1.setName("LFO 1");
    gui_var_group_lfo_1.add(gui_var_lfo_1_waveform);
    gui_var_group_lfo_1.add(gui_var_lfo_1_freq);
    gui_var_group_lfo_1.add(gui_var_lfo_1_amp);
    gui_var_group_lfo_1.add(gui_var_lfo_1_offset);
    gui_var.add(gui_var_group_lfo_1);

    gui_var_group_lfo_2.setName("LFO 2");
    gui_var_group_lfo_2.add(gui_var_lfo_2_waveform);
    gui_var_group_lfo_2.add(gui_var_lfo_2_freq);
    gui_var_group_lfo_2.add(gui_var_lfo_2_amp);
    gui_var_group_lfo_2.add(gui_var_lfo_2_offset);
    gui_var.add(gui_var_group_lfo_2);

    gui_var_group_sm_0.setName("SM 0");
    gui_var_group_sm_0.add(gui_var_sm_0_type);
    gui_var_group_sm_0.add(gui_var_sm_0_freq);
    gui_var_group_sm_0.add(gui_var_sm_0_amp);
    gui_var_group_sm_0.add(gui_var_sm_0_offset);
    gui_var.add(gui_var_group_sm_0);

    gui_var_group_sm_1.setName("SM 1");
    gui_var_group_sm_1.add(gui_var_sm_1_type);
    gui_var_group_sm_1.add(gui_var_sm_1_freq);
    gui_var_group_sm_1.add(gui_var_sm_1_amp);
    gui_var_group_sm_1.add(gui_var_sm_1_offset);
    gui_var.add(gui_var_group_sm_1);

    gui_var_group_sm_2.setName("SM 2");
    gui_var_group_sm_2.add(gui_var_sm_2_type);
    gui_var_group_sm_2.add(gui_var_sm_2_freq);
    gui_var_group_sm_2.add(gui_var_sm_2_amp);
    gui_var_group_sm_2.add(gui_var_sm_2_offset);
    gui_var.add(gui_var_group_sm_2);

    gui_var_group_fx.setName("FX");
    gui_var_group_fx.add(gui_var_portamento);
    gui_var_group_fx.add(gui_var_delay_delay);
    gui_var_group_fx.add(gui_var_delay_feedback);
    gui_var_group_fx.add(gui_var_overdrive_gain);
    gui_var_group_fx.add(gui_var_overdrive_drive);
    gui_var.add(gui_var_group_fx);

    gui_var.minimizeAll();


}



void ofApp::GuiSetupSampler()
{
//    dsampler_config.sample_length = dsampler.GetLength();
//    dsampler.GetPhase(&dsampler_config.sample_phase_start, &dsampler_config.sample_phase_loop_start, &dsampler_config.sample_phase_loop_end, &dsampler_config.sample_phase_end);
//    gui_sampler_save.addListener(this, &ofApp::saveButtonPressed);
//    gui_sampler_load.addListener(this, &ofApp::loadButtonPressed);

    gui_sampler_sample.set("Sample");
    gui_sampler_sample.addListener(this, &ofApp::sampleButtonPressed);

    gui_sampler.setDefaultWidth(GUI_DEFAULT_WIDTH);
    gui_sampler.setup("DSampler");
    gui_sampler.add(gui_load);
    gui_sampler.add(gui_save);
    gui_sampler.add(gui_synth_engine);

    gui_sampler_group_osc.setName("Oscillators");
    gui_sampler_group_osc.add(gui_sampler_voices);
    gui_sampler_group_osc.add(gui_sampler_sample);
    gui_sampler_group_osc.add(gui_sampler_file_name);
    gui_sampler_group_osc.add(gui_sampler_phase_start);
    gui_sampler_group_osc.add(gui_sampler_phase_loop_start);
    gui_sampler_group_osc.add(gui_sampler_phase_loop_end);
    gui_sampler_group_osc.add(gui_sampler_phase_end);
    gui_sampler_group_osc.add(gui_sampler_loop);
    gui_sampler_group_osc.add(gui_sampler_tune);
    gui_sampler_group_osc.add(gui_sampler_transpose);
    gui_sampler.add(gui_sampler_group_osc);

    gui_sampler_group_filter.setName("Filter");
    gui_sampler_group_filter.add(gui_sampler_filter_type);
    gui_sampler_group_filter.add(gui_sampler_filter_cutoff);
    gui_sampler_group_filter.add(gui_sampler_filter_res);
    gui_sampler.add(gui_sampler_group_filter);

    gui_sampler_group_eg_p.setName("EG pitch");
    gui_sampler_group_eg_p.add(gui_sampler_eg_p_level);
    gui_sampler_group_eg_p.add(gui_sampler_eg_p_attack);
    gui_sampler_group_eg_p.add(gui_sampler_eg_p_decay);
    gui_sampler_group_eg_p.add(gui_sampler_eg_p_sustain);
    gui_sampler_group_eg_p.add(gui_sampler_eg_p_release);
    gui_sampler.add(gui_sampler_group_eg_p);

    gui_sampler_group_eg_f.setName("EG filter");
    gui_sampler_group_eg_f.add(gui_sampler_eg_f_level);
    gui_sampler_group_eg_f.add(gui_sampler_eg_f_attack);
    gui_sampler_group_eg_f.add(gui_sampler_eg_f_decay);
    gui_sampler_group_eg_f.add(gui_sampler_eg_f_sustain);
    gui_sampler_group_eg_f.add(gui_sampler_eg_f_release);
    gui_sampler.add(gui_sampler_group_eg_f);

    gui_sampler_group_eg_a.setName("EG amp");
    gui_sampler_group_eg_a.add(gui_sampler_eg_a_attack);
    gui_sampler_group_eg_a.add(gui_sampler_eg_a_decay);
    gui_sampler_group_eg_a.add(gui_sampler_eg_a_sustain);
    gui_sampler_group_eg_a.add(gui_sampler_eg_a_release);
    gui_sampler.add(gui_sampler_group_eg_a);

    gui_sampler_group_lfo.setName("LFO");
    gui_sampler_group_lfo.add(gui_sampler_lfo_waveform);
    gui_sampler_group_lfo.add(gui_sampler_lfo_freq);
    gui_sampler_group_lfo.add(gui_sampler_lfo_amp);
    gui_sampler_group_lfo.add(gui_sampler_lfo_p_level);
    gui_sampler_group_lfo.add(gui_sampler_lfo_f_level);
    gui_sampler_group_lfo.add(gui_sampler_lfo_a_level);
    gui_sampler.add(gui_sampler_group_lfo);

    gui_sampler_group_fx.setName("FX");
    gui_sampler_group_fx.add(gui_sampler_portamento);
    gui_sampler_group_fx.add(gui_sampler_delay_delay);
    gui_sampler_group_fx.add(gui_sampler_delay_feedback);
    gui_sampler_group_fx.add(gui_sampler_overdrive_gain);
    gui_sampler_group_fx.add(gui_sampler_overdrive_drive);
    gui_sampler.add(gui_sampler_group_fx);

    gui_sampler.minimizeAll();


}



void ofApp::GuiSetupSeq()
{
    gui_seq.setDefaultWidth(GUI_DEFAULT_WIDTH);
    gui_seq.setup("DSynthVar - seq");
    gui_seq.add(gui_load);
    gui_seq.add(gui_save);
    gui_seq.add(gui_synth_engine);

    gui_seq_0_group.setName("Seq 0");
    gui_seq_0_group.add(gui_seq_0_step_max);
    for (uint8_t i = 0; i < GUI_SEQ_STEP_MAX; i++)
    {
        std::string name = "Value " + std::to_string(i);
        gui_seq_0_step[i].setName(name);
        gui_seq_0_step[i].setMin(0);
        gui_seq_0_step[i].setMax(1.0f);
        gui_seq_0_step[i] = 0;
        gui_seq_0_group.add(gui_seq_0_step[i]);
    }
    gui_seq.add(gui_seq_0_group);

    gui_seq_1_group.setName("Seq 1");
    gui_seq_1_group.add(gui_seq_1_step_max);
    for (uint8_t i = 0; i < GUI_SEQ_STEP_MAX; i++)
    {
        std::string name = "Value " + std::to_string(i);
        gui_seq_1_step[i].setName(name);
        gui_seq_1_step[i].setMin(0);
        gui_seq_1_step[i].setMax(1.0f);
        gui_seq_1_step[i] = 0;
        gui_seq_1_group.add(gui_seq_1_step[i]);
    }
    gui_seq.add(gui_seq_1_group);

    gui_seq_2_group.setName("Seq 2");
    gui_seq_2_group.add(gui_seq_2_step_max);
    for (uint8_t i = 0; i < GUI_SEQ_STEP_MAX; i++)
    {
        std::string name = "Value " + std::to_string(i);
        gui_seq_2_step[i].setName(name);
        gui_seq_2_step[i].setMin(0);
        gui_seq_2_step[i].setMax(1.0f);
        gui_seq_2_step[i] = 0;
        gui_seq_2_group.add(gui_seq_2_step[i]);
    }
    gui_seq.add(gui_seq_2_group);

    gui_seq.minimizeAll();
}



void ofApp::GuiSetupD()
{

    gui_d.setDefaultWidth(GUI_DEFAULT_WIDTH);
    gui_d.setup("Drums");
    gui_d.add(gui_load);
    gui_d.add(gui_save);
    gui_d.add(gui_synth_engine);

    gui_d_bass.setName("DBass");
    gui_d_bass.add(gui_d_bass_type);
    gui_d_bass.add(gui_d_bass_freq);
    gui_d_bass.add(gui_d_bass_tone);
    gui_d_bass.add(gui_d_bass_decay);
    gui_d_bass.add(gui_d_bass_fm_attack);
    gui_d_bass.add(gui_d_bass_fm_self);
    gui_d_bass.add(gui_d_bass_dirtiness);
    gui_d_bass.add(gui_d_bass_fm_env_amount);
    gui_d_bass.add(gui_d_bass_fm_env_decay);
    gui_d_bass.add(gui_d_bass_min);

    gui_d_snare.setName("DSnare");
    gui_d_snare.add(gui_d_snare_type);
    gui_d_snare.add(gui_d_snare_freq);
    gui_d_snare.add(gui_d_snare_tone);
    gui_d_snare.add(gui_d_snare_decay);
    gui_d_snare.add(gui_d_snare_snappy);
    gui_d_snare.add(gui_d_snare_fm_amount);
    gui_d_snare.add(gui_d_snare_freq_noise);
    gui_d_snare.add(gui_d_snare_amp);
    gui_d_snare.add(gui_d_snare_res);
    gui_d_snare.add(gui_d_snare_drive);
    gui_d_snare.add(gui_d_snare_min);

    gui_d_hihat.setName("DHihat");
    gui_d_hihat.add(gui_d_hihat_type);
    gui_d_hihat.add(gui_d_hihat_freq);
    gui_d_hihat.add(gui_d_hihat_tone);
    gui_d_hihat.add(gui_d_hihat_decay);
    gui_d_hihat.add(gui_d_hihat_noisiness);
    gui_d_hihat.add(gui_d_hihat_amp);
    gui_d_hihat.add(gui_d_hihat_res);
    gui_d_hihat.add(gui_d_hihat_drive);

    gui_d_clap.setName("DClap");
    gui_d_clap.add(gui_d_clap_freq);
    gui_d_clap.add(gui_d_clap_res);
    gui_d_clap.add(gui_d_clap_drive);
    gui_d_clap.add(gui_d_clap_amp);
    gui_d_clap.add(gui_d_clap_decay);

    gui_d_cymbal.setName("DCymbal");
    gui_d_cymbal.add(gui_d_cymbal_freq);
    gui_d_cymbal.add(gui_d_cymbal_res);
    gui_d_cymbal.add(gui_d_cymbal_drive);
    gui_d_cymbal.add(gui_d_cymbal_amp);
    gui_d_cymbal.add(gui_d_cymbal_decay);
    gui_d_cymbal.add(gui_d_cymbal_min);
    gui_d_cymbal.add(gui_d_cymbal_mix);

    gui_d_drum.setName("DDrum");
    gui_d_drum.add(gui_d_drum_freq);
    gui_d_drum.add(gui_d_drum_amp);
    gui_d_drum.add(gui_d_drum_decay);
    gui_d_drum.add(gui_d_drum_min);

    gui_d.add(gui_d_bass);
    gui_d.add(gui_d_snare);
    gui_d.add(gui_d_hihat);
    gui_d.add(gui_d_clap);
    gui_d.add(gui_d_cymbal);
    gui_d.add(gui_d_drum);
    gui_d.minimizeAll();
}

void ofApp::GuiSetSeq()
{
    gui_seq_0_step_max = dsynthvar_config.sm_0_seq_len;
    for (uint8_t i = 0; i < dsynthvar_config.sm_0_seq_len; i++)
    {
        gui_seq_0_step[i] = dsynthvar_config.sm_0_seq_val[i];
    }

    gui_seq_1_step_max = dsynthvar_config.sm_1_seq_len;
    for (uint8_t i = 0; i < dsynthvar_config.sm_1_seq_len; i++)
    {
        gui_seq_1_step[i] = dsynthvar_config.sm_1_seq_val[i];
    }

    gui_seq_2_step_max = dsynthvar_config.sm_2_seq_len;
    for (uint8_t i = 0; i < dsynthvar_config.sm_2_seq_len; i++)
    {
        gui_seq_2_step[i] = dsynthvar_config.sm_2_seq_val[i];
    }
};



void ofApp::saveButtonPressed()
{
    ofFileDialogResult result = ofSystemSaveDialog("setting.xml", "Load sample file");
    if (result.bSuccess)
    {
        // string name = result.getName();
        string path = result.getPath();
        // path includes filename

        switch (synth_engine)
        {
        case SUB:
            DSettings::SaveSetting(DSettings::DSYNTHSUB, DSettings::NONE, path, &dsynthsub_config);
            break;
        case FM:
            DSettings::SaveSetting(DSettings::DSYNTHFM, DSettings::NONE, path, &dsynthfm_config);
            break;
        case VAR:
        case VAR_SEQ:
            DSettings::SaveSetting(DSettings::DSYNTHVAR, DSettings::NONE, path, &dsynthvar_config);
            break;
        case SAMPLER:
            DSettings::SaveSetting(DSettings::DSAMPLER, DSettings::NONE, path, &dsampler_config);
            break;
        case DRUM:
            {
                string drum_type = ofSystemTextBoxDialog("Which drum type (Bass, Snare, Hihat, Clap, cYmbal, Drum)?");
                if (drum_type == "B")
                {
                    DSettings::SaveSetting(DSettings::DRUM, DSettings::DBASS, path, &dbass_config);
                } else if (drum_type == "S") {
                    DSettings::SaveSetting(DSettings::DRUM, DSettings::DSNARE, path, &dsnare_config);
                } else if (drum_type == "H") {
                    DSettings::SaveSetting(DSettings::DRUM, DSettings::DHIHAT, path, &dhihat_config);
                } else if (drum_type == "C") {
                    DSettings::SaveSetting(DSettings::DRUM, DSettings::DCLAP, path, &dclap_config);
                } else if (drum_type == "Y") {
                    DSettings::SaveSetting(DSettings::DRUM, DSettings::DCYMBAL, path, &dcymbal_config);
                } else if (drum_type == "D") {
                    DSettings::SaveSetting(DSettings::DRUM, DSettings::DDRUM, path, &ddrum_config);
                }
            }
            break;
        }
    } // if
}



void ofApp::loadButtonPressed()
{
    ofFileDialogResult result = ofSystemLoadDialog("Load sample file");
    if (result.bSuccess)
    {
        // string name = result.getName();
        string path = result.getPath();
        // path includes filename

        switch (synth_engine)
        {
        case SUB:
            DSettings::LoadSetting(DSettings::DSYNTHSUB, DSettings::NONE, path, &dsynthsub_config);
            dsynthsub.Init(dsynthsub_config);
            GuiSetSub();
            break;
        case FM:
            DSettings::LoadSetting(DSettings::DSYNTHFM, DSettings::NONE, path, &dsynthfm_config);
            dsynthfm.Init(dsynthfm_config);
            GuiSetFm();
            break;
        case VAR:
        case VAR_SEQ:
            DSettings::LoadSetting(DSettings::DSYNTHVAR, DSettings::NONE, path, &dsynthvar_config);
            dsynthvar.Init(dsynthvar_config);
            GuiSetVar();
            break;
        case SAMPLER:
            DSettings::LoadSetting(DSettings::DSAMPLER, DSettings::NONE, path, &dsampler_config);
            dsampler.Init(dsampler_config);
            dsampler.Load(dsampler_config.sample_file_name);
            // read back values after Load() as GUI depends on structs
            dsampler_config.sample_length = dsampler.GetLength();
            dsampler.GetPhase(&dsampler_config.sample_phase_start, &dsampler_config.sample_phase_loop_start, &dsampler_config.sample_phase_loop_end, &dsampler_config.sample_phase_end);
            // ignore dsampler_config.sample_channels for now
            GuiSetSampler();
            break;
        case DRUM:
            {
                string drum_type = ofSystemTextBoxDialog("Which drum type (Bass, Snare, Hihat, Clap, cYmbal, Drum)?");
                if (drum_type == "B")
                {
                    DSettings::LoadSetting(DSettings::DRUM, DSettings::DBASS, path, &dbass_config);
                } else if (drum_type == "S") {
                    DSettings::LoadSetting(DSettings::DRUM, DSettings::DSNARE, path, &dsnare_config);
                } else if (drum_type == "H") {
                    DSettings::LoadSetting(DSettings::DRUM, DSettings::DHIHAT, path, &dhihat_config);
                } else if (drum_type == "C") {
                    DSettings::LoadSetting(DSettings::DRUM, DSettings::DCLAP, path, &dclap_config);
                } else if (drum_type == "Y") {
                    DSettings::LoadSetting(DSettings::DRUM, DSettings::DCYMBAL, path, &dcymbal_config);
                } else if (drum_type == "D") {
                    DSettings::LoadSetting(DSettings::DRUM, DSettings::DDRUM, path, &ddrum_config);
                }
            }
            break;
        }
    }
}



void ofApp::sampleButtonPressed()
{
    ofFileDialogResult result = ofSystemLoadDialog("Load sample file");
    if (result.bSuccess)
    {
        string name = result.getName();
        string path = result.getPath();
        cout << "Name:" << name << " path:" << path << endl;
        // load your file at `path`
// Name:test.wav
// path:/home/staffan/Documents/projects/tech/audioprogramming/of/apps/myApps/ofDStudioDemo11Editor/bin/data/test.wav

    }
}


void ofApp::GuiSetSub()
{
    gui_sub_voices = dsynthsub_config.voices;
    gui_sub_waveform0 = (int)dsynthsub_config.waveform0;
    gui_sub_waveform1 = (int)dsynthsub_config.waveform1;
    gui_sub_tune = dsynthsub_config.tune;
    gui_sub_detune = dsynthsub_config.detune;
    gui_sub_transpose = dsynthsub_config.transpose;
    gui_sub_osc0_level = dsynthsub_config.osc0_level;
    gui_sub_osc1_level = dsynthsub_config.osc1_level;
    gui_sub_noise_level = dsynthsub_config.noise_level;

    gui_sub_filter_type = (int)dsynthsub_config.filter_type;
    gui_sub_filter_cutoff = dsynthsub_config.filter_cutoff;
    gui_sub_filter_res = dsynthsub_config.filter_res;

    gui_sub_eg_p_level = dsynthsub_config.eg_p_level;
    gui_sub_eg_p_attack = dsynthsub_config.eg_p_attack;
    gui_sub_eg_p_decay = dsynthsub_config.eg_p_decay;
    gui_sub_eg_p_sustain = dsynthsub_config.eg_p_sustain;
    gui_sub_eg_p_release = dsynthsub_config.eg_p_release;

    gui_sub_eg_f_level = dsynthsub_config.eg_f_level;
    gui_sub_eg_f_attack = dsynthsub_config.eg_f_attack;
    gui_sub_eg_f_decay = dsynthsub_config.eg_f_decay;
    gui_sub_eg_f_sustain = dsynthsub_config.eg_f_sustain;
    gui_sub_eg_f_release = dsynthsub_config.eg_f_release;

    gui_sub_eg_a_attack = dsynthsub_config.eg_a_attack;
    gui_sub_eg_a_decay = dsynthsub_config.eg_a_decay;
    gui_sub_eg_a_sustain = dsynthsub_config.eg_a_sustain;
    gui_sub_eg_a_release = dsynthsub_config.eg_a_release;

    gui_sub_lfo_waveform = (int)dsynthsub_config.lfo_waveform;
    gui_sub_lfo_freq = dsynthsub_config.lfo_freq;
    gui_sub_lfo_amp = dsynthsub_config.lfo_amp;
    gui_sub_lfo_p_level = dsynthsub_config.lfo_p_level;
    gui_sub_lfo_f_level = dsynthsub_config.lfo_f_level;
    gui_sub_lfo_a_level = dsynthsub_config.lfo_a_level;

    gui_sub_portamento = dsynthsub_config.portamento;
    gui_sub_delay_delay = dsynthsub_config.delay_delay;
    gui_sub_delay_feedback = dsynthsub_config.delay_feedback;
    gui_sub_overdrive_gain = dsynthsub_config.overdrive_gain;
    gui_sub_overdrive_drive = dsynthsub_config.overdrive_drive;

}



void ofApp::GuiSetFm()
{
    gui_fm_voices = dsynthfm_config.voices;
    gui_fm_ratio = dsynthfm_config.ratio;
    gui_fm_index = dsynthfm_config.index;
    gui_fm_tune = dsynthfm_config.tune;
    gui_fm_transpose = dsynthfm_config.transpose;
    gui_fm_noise_level = dsynthfm_config.noise_level;

    gui_fm_filter_type = (int)dsynthfm_config.filter_type;
    gui_fm_filter_cutoff = dsynthfm_config.filter_cutoff;
    gui_fm_filter_res = dsynthfm_config.filter_res;

    gui_fm_eg_p_level = dsynthfm_config.eg_p_level;
    gui_fm_eg_p_attack = dsynthfm_config.eg_p_attack;
    gui_fm_eg_p_decay = dsynthfm_config.eg_p_decay;
    gui_fm_eg_p_sustain = dsynthfm_config.eg_p_sustain;
    gui_fm_eg_p_release = dsynthfm_config.eg_p_release;

    gui_fm_eg_f_level = dsynthfm_config.eg_f_level;
    gui_fm_eg_f_attack = dsynthfm_config.eg_f_attack;
    gui_fm_eg_f_decay = dsynthfm_config.eg_f_decay;
    gui_fm_eg_f_sustain = dsynthfm_config.eg_f_sustain;
    gui_fm_eg_f_release = dsynthfm_config.eg_f_release;

    gui_fm_eg_a_attack = dsynthfm_config.eg_a_attack;
    gui_fm_eg_a_decay = dsynthfm_config.eg_a_decay;
    gui_fm_eg_a_sustain = dsynthfm_config.eg_a_sustain;
    gui_fm_eg_a_release = dsynthfm_config.eg_a_release;

    gui_fm_lfo_waveform = (int)dsynthfm_config.lfo_waveform;
    gui_fm_lfo_freq = dsynthfm_config.lfo_freq;
    gui_fm_lfo_amp = dsynthfm_config.lfo_amp;
    gui_fm_lfo_p_level = dsynthfm_config.lfo_p_level;
    gui_fm_lfo_f_level = dsynthfm_config.lfo_f_level;
    gui_fm_lfo_a_level = dsynthfm_config.lfo_a_level;

    gui_fm_portamento = dsynthfm_config.portamento;
    gui_fm_delay_delay = dsynthfm_config.delay_delay;
    gui_fm_delay_feedback = dsynthfm_config.delay_feedback;
    gui_fm_overdrive_gain = dsynthfm_config.overdrive_gain;
    gui_fm_overdrive_drive = dsynthfm_config.overdrive_drive;

}



void ofApp::GuiSetVar()
{
    gui_var_voices = dsynthvar_config.voices;
    gui_var_waveshape = dsynthvar_config.waveshape;
    gui_var_pulsewidth = dsynthvar_config.pulsewidth;
    gui_var_sync_enable = dsynthvar_config.sync_enable;
    gui_var_sync_freq = dsynthvar_config.sync_freq;
    gui_var_tune = dsynthvar_config.tune;
    gui_var_transpose = dsynthvar_config.transpose;
    gui_var_osc_level = dsynthvar_config.osc_level;
    gui_var_noise_level = dsynthvar_config.noise_level;

    gui_var_filter_type = (int)dsynthvar_config.filter_type;
    gui_var_filter_cutoff = dsynthvar_config.filter_cutoff;
    gui_var_filter_res = dsynthvar_config.filter_res;

    gui_var_mod_eg_p = dsynthvar_config.mod_eg_p;
    gui_var_mod_eg_f = dsynthvar_config.mod_eg_f;
    gui_var_mod_eg_a = dsynthvar_config.mod_eg_a;
    gui_var_mod_filter_cutoff = dsynthvar_config.mod_filter_cutoff;
    gui_var_mod_waveshape = dsynthvar_config.mod_waveshape;
    gui_var_mod_pulsewidth = dsynthvar_config.mod_pulsewidth;
    gui_var_mod_sync_freq = dsynthvar_config.mod_sync_freq;
    gui_var_mod_delay = dsynthvar_config.mod_delay;

    gui_var_eg_0_level = dsynthvar_config.eg_0_level;
    gui_var_eg_0_attack = dsynthvar_config.eg_0_attack;
    gui_var_eg_0_decay = dsynthvar_config.eg_0_decay;
    gui_var_eg_0_sustain = dsynthvar_config.eg_0_sustain;
    gui_var_eg_0_release = dsynthvar_config.eg_0_release;

    gui_var_eg_1_level = dsynthvar_config.eg_1_level;
    gui_var_eg_1_attack = dsynthvar_config.eg_1_attack;
    gui_var_eg_1_decay = dsynthvar_config.eg_1_decay;
    gui_var_eg_1_sustain = dsynthvar_config.eg_1_sustain;
    gui_var_eg_1_release = dsynthvar_config.eg_1_release;

    gui_var_eg_2_level = dsynthvar_config.eg_2_level;
    gui_var_eg_2_attack = dsynthvar_config.eg_2_attack;
    gui_var_eg_2_decay = dsynthvar_config.eg_2_decay;
    gui_var_eg_2_sustain = dsynthvar_config.eg_2_sustain;
    gui_var_eg_2_release = dsynthvar_config.eg_2_release;

    gui_var_lfo_0_waveform = (int)dsynthvar_config.lfo_0_waveform;
    gui_var_lfo_0_freq = dsynthvar_config.lfo_0_freq;
    gui_var_lfo_0_amp = dsynthvar_config.lfo_0_amp;
    gui_var_lfo_0_offset = dsynthvar_config.lfo_0_offset;

    gui_var_lfo_1_waveform = (int)dsynthvar_config.lfo_1_waveform;
    gui_var_lfo_1_freq = dsynthvar_config.lfo_1_freq;
    gui_var_lfo_1_amp = dsynthvar_config.lfo_1_amp;
    gui_var_lfo_1_offset = dsynthvar_config.lfo_1_offset;

    gui_var_lfo_2_waveform = (int)dsynthvar_config.lfo_2_waveform;
    gui_var_lfo_2_freq = dsynthvar_config.lfo_2_freq;
    gui_var_lfo_2_amp = dsynthvar_config.lfo_2_amp;
    gui_var_lfo_2_offset = dsynthvar_config.lfo_2_offset;

    gui_var_sm_0_type = dsynthvar_config.sm_0_type;
    gui_var_sm_0_freq = dsynthvar_config.sm_0_freq;
    gui_var_sm_0_amp = dsynthvar_config.sm_0_amp;
    gui_var_sm_0_offset = dsynthvar_config.sm_0_offset;

    gui_var_sm_1_type = dsynthvar_config.sm_1_type;
    gui_var_sm_1_freq = dsynthvar_config.sm_1_freq;
    gui_var_sm_1_amp = dsynthvar_config.sm_1_amp;
    gui_var_sm_1_offset = dsynthvar_config.sm_1_offset;

    gui_var_sm_2_type = dsynthvar_config.sm_2_type;
    gui_var_sm_2_freq = dsynthvar_config.sm_2_freq;
    gui_var_sm_2_amp = dsynthvar_config.sm_2_amp;
    gui_var_sm_2_offset = dsynthvar_config.sm_2_offset;

    gui_var_portamento = dsynthvar_config.portamento;
    gui_var_delay_delay = dsynthvar_config.delay_delay;
    gui_var_delay_feedback = dsynthvar_config.delay_feedback;
    gui_var_overdrive_gain = dsynthvar_config.overdrive_gain;
    gui_var_overdrive_drive = dsynthvar_config.overdrive_drive;
}



void ofApp::GuiSetSampler()
{
    gui_sampler_voices = dsampler_config.voices;
    gui_sampler_file_name = dsampler_config.sample_file_name;
    gui_sampler_phase_start = dsampler_config.sample_phase_start;
    gui_sampler_phase_start.setMax(dsampler_config.sample_length);
    gui_sampler_phase_loop_start = dsampler_config.sample_phase_loop_start;
    gui_sampler_phase_loop_start.setMax(dsampler_config.sample_length);
    gui_sampler_phase_loop_end = dsampler_config.sample_phase_loop_end;
    gui_sampler_phase_loop_end.setMax(dsampler_config.sample_length);
    gui_sampler_phase_end = dsampler_config.sample_phase_end;
    gui_sampler_phase_end.setMax(dsampler_config.sample_length);
    gui_sampler_loop = dsampler_config.loop;
    gui_sampler_tune = dsampler_config.tune;
    gui_sampler_transpose = dsampler_config.transpose;

    gui_sampler_filter_type = (int)dsampler_config.filter_type;
    gui_sampler_filter_cutoff = dsampler_config.filter_cutoff;
    gui_sampler_filter_res = dsampler_config.filter_res;

    gui_sampler_eg_p_level = dsampler_config.eg_p_level;
    gui_sampler_eg_p_attack = dsampler_config.eg_p_attack;
    gui_sampler_eg_p_decay = dsampler_config.eg_p_decay;
    gui_sampler_eg_p_sustain = dsampler_config.eg_p_sustain;
    gui_sampler_eg_p_release = dsampler_config.eg_p_release;

    gui_sampler_eg_f_level = dsampler_config.eg_f_level;
    gui_sampler_eg_f_attack = dsampler_config.eg_f_attack;
    gui_sampler_eg_f_decay = dsampler_config.eg_f_decay;
    gui_sampler_eg_f_sustain = dsampler_config.eg_f_sustain;
    gui_sampler_eg_f_release = dsampler_config.eg_f_release;

    gui_sampler_eg_a_attack = dsampler_config.eg_a_attack;
    gui_sampler_eg_a_decay = dsampler_config.eg_a_decay;
    gui_sampler_eg_a_sustain = dsampler_config.eg_a_sustain;
    gui_sampler_eg_a_release = dsampler_config.eg_a_release;

    gui_sampler_lfo_waveform = (int)dsampler_config.lfo_waveform;
    gui_sampler_lfo_freq = dsampler_config.lfo_freq;
    gui_sampler_lfo_amp = dsampler_config.lfo_amp;
    gui_sampler_lfo_p_level = dsampler_config.lfo_p_level;
    gui_sampler_lfo_f_level = dsampler_config.lfo_f_level;
    gui_sampler_lfo_a_level = dsampler_config.lfo_a_level;

    gui_sampler_portamento = dsampler_config.portamento;
    gui_sampler_delay_delay = dsampler_config.delay_delay;
    gui_sampler_delay_feedback = dsampler_config.delay_feedback;
    gui_sampler_overdrive_gain = dsampler_config.overdrive_gain;
    gui_sampler_overdrive_drive = dsampler_config.overdrive_drive;

}



void ofApp::GuiSetD()
{
    // dbass
    gui_d_bass_type = dbass_config.type;
    gui_d_bass_freq = dbass_config.freq;
    gui_d_bass_tone = dbass_config.tone;
    gui_d_bass_decay = dbass_config.decay;
    gui_d_bass_fm_attack = dbass_config.fm_attack;
    gui_d_bass_fm_self = dbass_config.fm_self;
    gui_d_bass_dirtiness = dbass_config.dirtiness;
    gui_d_bass_fm_env_amount = dbass_config.fm_env_amount;
    gui_d_bass_fm_env_decay = dbass_config.fm_env_decay;
    gui_d_bass_min = dbass_config.min;

    // dsnare
    gui_d_snare_type = dsnare_config.type;
    gui_d_snare_freq = dsnare_config.freq;
    gui_d_snare_tone = dsnare_config.tone;
    gui_d_snare_decay = dsnare_config.decay;
    gui_d_snare_snappy = dsnare_config.snappy;
    gui_d_snare_fm_amount = dsnare_config.fm_amount;
    gui_d_snare_freq_noise = dsnare_config.freq_noise;
    gui_d_snare_amp = dsnare_config.amp;
    gui_d_snare_res = dsnare_config.res;
    gui_d_snare_drive = dsnare_config.drive;
    gui_d_snare_min = dsnare_config.min;

    // dhihat
    gui_d_hihat_type = dhihat_config.type;
    gui_d_hihat_freq = dhihat_config.freq;
    gui_d_hihat_tone = dhihat_config.tone;
    gui_d_hihat_decay = dhihat_config.decay;
    gui_d_hihat_noisiness = dhihat_config.noisiness;
    gui_d_hihat_amp = dhihat_config.amp;
    gui_d_hihat_res = dhihat_config.res;
    gui_d_hihat_drive = dhihat_config.drive;

    // dclap
    gui_d_clap_freq = dclap_config.freq;
    gui_d_clap_res = dclap_config.res;
    gui_d_clap_drive = dclap_config.drive;
    gui_d_clap_amp = dclap_config.amp;
    gui_d_clap_decay = dclap_config.decay;

    // dcymbal
    gui_d_cymbal_freq = dcymbal_config.freq;
    gui_d_cymbal_res = dcymbal_config.res;
    gui_d_cymbal_drive = dcymbal_config.drive;
    gui_d_cymbal_amp = dcymbal_config.amp;
    gui_d_cymbal_decay = dcymbal_config.decay;
    gui_d_cymbal_min = dcymbal_config.min;
    gui_d_cymbal_mix = dcymbal_config.mix;

    // ddrum
    gui_d_drum_freq = ddrum_config.freq;
    gui_d_drum_amp = ddrum_config.amp;
    gui_d_drum_decay = ddrum_config.decay;
    gui_d_drum_min = ddrum_config.min;

}



void ofApp::exit()
{
    ofSoundStreamClose();
}
