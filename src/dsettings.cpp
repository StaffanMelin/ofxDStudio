#include "ofxXmlSettings.h"

#include "dsettings.h"
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

void DSettings::SaveSetting(DSoundType type, DSoundSubType subtype, string file_name, void *config)
{
    ofxXmlSettings settings;

    switch (type)
    {
    case DSettings::DSYNTHSUB:
        {
            DSynthSub::Config *p;
            p = (DSynthSub::Config *)config;
            settings.setValue("settings:settingstype", "DSynthSub");
            settings.setValue("settings:voices", p->voices);
            settings.setValue("settings:waveform0", p->waveform0);
            settings.setValue("settings:waveform1", p->waveform1);
            settings.setValue("settings:tune", p->tune);
            settings.setValue("settings:detune", p->detune);
            settings.setValue("settings:transpose", p->transpose);
            settings.setValue("settings:osc0_level", p->osc0_level);
            settings.setValue("settings:osc1_level", p->osc1_level);
            settings.setValue("settings:noise_level", p->noise_level);
            settings.setValue("settings:filter_type", p->filter_type);
            settings.setValue("settings:filter_cutoff", p->filter_cutoff);
            settings.setValue("settings:filter_res", p->filter_res);

            settings.setValue("settings:eg_p_level", p->eg_p_level);
            settings.setValue("settings:eg_p_attack", p->eg_p_attack);
            settings.setValue("settings:eg_p_decay", p->eg_p_decay);
            settings.setValue("settings:eg_p_sustain", p->eg_p_sustain);
            settings.setValue("settings:eg_p_release", p->eg_p_release);

            settings.setValue("settings:eg_f_level", p->eg_f_level);
            settings.setValue("settings:eg_f_attack", p->eg_f_attack);
            settings.setValue("settings:eg_f_decay", p->eg_f_decay);
            settings.setValue("settings:eg_f_sustain", p->eg_f_sustain);
            settings.setValue("settings:eg_f_release", p->eg_f_release);

            settings.setValue("settings:eg_a_attack", p->eg_a_attack);
            settings.setValue("settings:eg_a_decay", p->eg_a_decay);
            settings.setValue("settings:eg_a_sustain", p->eg_a_sustain);
            settings.setValue("settings:eg_a_release", p->eg_a_release);

            settings.setValue("settings:lfo_waveform", p->lfo_waveform);
            settings.setValue("settings:lfo_freq", p->lfo_freq);
            settings.setValue("settings:lfo_amp", p->lfo_amp);
            settings.setValue("settings:lfo_p_level", p->lfo_p_level);
            settings.setValue("settings:lfo_f_level", p->lfo_f_level);
            settings.setValue("settings:lfo_a_level", p->lfo_a_level);

            settings.setValue("settings:portamento", p->portamento);
            settings.setValue("settings:delay_delay", p->delay_delay);
            settings.setValue("settings:delay_feedback", p->delay_feedback);
            settings.setValue("settings:overdrive_gain", p->overdrive_gain);
            settings.setValue("settings:overdrive_drive", p->overdrive_drive);
        }
        break;
    case DSettings::DSYNTHFM:
        {
            DSynthFm::Config *p;
            p = (DSynthFm::Config *)config;
            settings.setValue("settings:settingstype", "DSynthFm");
            settings.setValue("settings:voices", p->voices);
            settings.setValue("settings:ratio", p->ratio);
            settings.setValue("settings:index", p->index);
            settings.setValue("settings:tune", p->tune);
            settings.setValue("settings:transpose", p->transpose);
            settings.setValue("settings:noise_level", p->noise_level);
            settings.setValue("settings:filter_type", p->filter_type);
            settings.setValue("settings:filter_cutoff", p->filter_cutoff);
            settings.setValue("settings:filter_res", p->filter_res);

            settings.setValue("settings:eg_p_level", p->eg_p_level);
            settings.setValue("settings:eg_p_attack", p->eg_p_attack);
            settings.setValue("settings:eg_p_decay", p->eg_p_decay);
            settings.setValue("settings:eg_p_sustain", p->eg_p_sustain);
            settings.setValue("settings:eg_p_release", p->eg_p_release);

            settings.setValue("settings:eg_f_level", p->eg_f_level);
            settings.setValue("settings:eg_f_attack", p->eg_f_attack);
            settings.setValue("settings:eg_f_decay", p->eg_f_decay);
            settings.setValue("settings:eg_f_sustain", p->eg_f_sustain);
            settings.setValue("settings:eg_f_release", p->eg_f_release);

            settings.setValue("settings:eg_a_attack", p->eg_a_attack);
            settings.setValue("settings:eg_a_decay", p->eg_a_decay);
            settings.setValue("settings:eg_a_sustain", p->eg_a_sustain);
            settings.setValue("settings:eg_a_release", p->eg_a_release);

            settings.setValue("settings:lfo_waveform", p->lfo_waveform);
            settings.setValue("settings:lfo_freq", p->lfo_freq);
            settings.setValue("settings:lfo_amp", p->lfo_amp);
            settings.setValue("settings:lfo_p_level", p->lfo_p_level);
            settings.setValue("settings:lfo_f_level", p->lfo_f_level);
            settings.setValue("settings:lfo_a_level", p->lfo_a_level);

            settings.setValue("settings:portamento", p->portamento);
            settings.setValue("settings:delay_delay", p->delay_delay);
            settings.setValue("settings:delay_feedback", p->delay_feedback);
            settings.setValue("settings:overdrive_gain", p->overdrive_gain);
            settings.setValue("settings:overdrive_drive", p->overdrive_drive);
        }
        break;
    case DSettings::DSYNTHVAR:
        {
            DSynthVar::Config *p;
            p = (DSynthVar::Config *)config;
            settings.setValue("settings:settingstype", "DSynthVar");
            settings.setValue("settings:voices", p->voices);
            settings.setValue("settings:waveshape", p->waveshape);
            settings.setValue("settings:pulsewidth", p->pulsewidth);
            settings.setValue("settings:sync_enable", p->sync_enable);
            settings.setValue("settings:sync_freq", p->sync_freq);
            settings.setValue("settings:tune", p->tune);
            settings.setValue("settings:transpose", p->transpose);
            settings.setValue("settings:osc_level", p->osc_level);
            settings.setValue("settings:noise_level", p->noise_level);
            settings.setValue("settings:filter_type", p->filter_type);
            settings.setValue("settings:filter_cutoff", p->filter_cutoff);
            settings.setValue("settings:filter_res", p->filter_res);

            settings.setValue("settings:mod_eg_p", p->mod_eg_p);
            settings.setValue("settings:mod_eg_f", p->mod_eg_f);
            settings.setValue("settings:mod_eg_a", p->mod_eg_a);
            settings.setValue("settings:mod_filter_cutoff", p->mod_filter_cutoff);
            settings.setValue("settings:mod_waveshape", p->mod_waveshape);
            settings.setValue("settings:mod_pulsewidth", p->mod_pulsewidth);
            settings.setValue("settings:mod_sync_freq", p->mod_sync_freq);
            settings.setValue("settings:mod_delay", p->mod_delay);

            settings.setValue("settings:eg_0_level", p->eg_0_level);
            settings.setValue("settings:eg_0_attack", p->eg_0_attack);
            settings.setValue("settings:eg_0_decay", p->eg_0_decay);
            settings.setValue("settings:eg_0_sustain", p->eg_0_sustain);
            settings.setValue("settings:eg_0_release", p->eg_0_release);

            settings.setValue("settings:eg_1_level", p->eg_1_level);
            settings.setValue("settings:eg_1_attack", p->eg_1_attack);
            settings.setValue("settings:eg_1_decay", p->eg_1_decay);
            settings.setValue("settings:eg_1_sustain", p->eg_1_sustain);
            settings.setValue("settings:eg_1_release", p->eg_1_release);

            settings.setValue("settings:eg_2_level", p->eg_2_level);
            settings.setValue("settings:eg_2_attack", p->eg_2_attack);
            settings.setValue("settings:eg_2_decay", p->eg_2_decay);
            settings.setValue("settings:eg_2_sustain", p->eg_2_sustain);
            settings.setValue("settings:eg_2_release", p->eg_2_release);

            settings.setValue("settings:lfo_0_waveform", p->lfo_0_waveform);
            settings.setValue("settings:lfo_0_freq", p->lfo_0_freq);
            settings.setValue("settings:lfo_0_amp", p->lfo_0_amp);
            settings.setValue("settings:lfo_0_offset", p->lfo_0_offset);

            settings.setValue("settings:lfo_1_waveform", p->lfo_1_waveform);
            settings.setValue("settings:lfo_1_freq", p->lfo_1_freq);
            settings.setValue("settings:lfo_1_amp", p->lfo_1_amp);
            settings.setValue("settings:lfo_1_offset", p->lfo_1_offset);

            settings.setValue("settings:lfo_2_waveform", p->lfo_2_waveform);
            settings.setValue("settings:lfo_2_freq", p->lfo_2_freq);
            settings.setValue("settings:lfo_2_amp", p->lfo_2_amp);
            settings.setValue("settings:lfo_2_offset", p->lfo_2_offset);

            settings.setValue("settings:sm_0_type", p->sm_0_type);
            settings.setValue("settings:sm_0_freq", p->sm_0_freq);
            settings.setValue("settings:sm_0_amp", p->sm_0_amp);
            settings.setValue("settings:sm_0_offset", p->sm_0_offset);
            settings.setValue("settings:sm_0_seq_val", VecToStr(p->sm_0_seq_val));

            settings.setValue("settings:sm_1_type", p->sm_1_type);
            settings.setValue("settings:sm_1_freq", p->sm_1_freq);
            settings.setValue("settings:sm_1_amp", p->sm_1_amp);
            settings.setValue("settings:sm_1_offset", p->sm_1_offset);
            settings.setValue("settings:sm_1_seq_val", VecToStr(p->sm_1_seq_val));

            settings.setValue("settings:sm_2_type", p->sm_2_type);
            settings.setValue("settings:sm_2_freq", p->sm_2_freq);
            settings.setValue("settings:sm_2_amp", p->sm_2_amp);
            settings.setValue("settings:sm_2_offset", p->sm_2_offset);
            settings.setValue("settings:sm_2_seq_val", VecToStr(p->sm_2_seq_val));

            settings.setValue("settings:portamento", p->portamento);
            settings.setValue("settings:delay_delay", p->delay_delay);
            settings.setValue("settings:delay_feedback", p->delay_feedback);
            settings.setValue("settings:overdrive_gain", p->overdrive_gain);
            settings.setValue("settings:overdrive_drive", p->overdrive_drive);
        }
        break;
    case DSettings::DSAMPLER:
        {
            DSampler::Config *p;
            p = (DSampler::Config *)config;
            settings.setValue("settings:settingstype", "DSampler");
            settings.setValue("settings:voices", p->voices);
            settings.setValue("settings:tune", p->tune);
            settings.setValue("settings:transpose", p->transpose);
            settings.setValue("settings:filter_type", p->filter_type);
            settings.setValue("settings:filter_cutoff", p->filter_cutoff);
            settings.setValue("settings:filter_res", p->filter_res);

            settings.setValue("settings:eg_p_level", p->eg_p_level);
            settings.setValue("settings:eg_p_attack", p->eg_p_attack);
            settings.setValue("settings:eg_p_decay", p->eg_p_decay);
            settings.setValue("settings:eg_p_sustain", p->eg_p_sustain);
            settings.setValue("settings:eg_p_release", p->eg_p_release);

            settings.setValue("settings:eg_f_level", p->eg_f_level);
            settings.setValue("settings:eg_f_attack", p->eg_f_attack);
            settings.setValue("settings:eg_f_decay", p->eg_f_decay);
            settings.setValue("settings:eg_f_sustain", p->eg_f_sustain);
            settings.setValue("settings:eg_f_release", p->eg_f_release);

            settings.setValue("settings:eg_a_attack", p->eg_a_attack);
            settings.setValue("settings:eg_a_decay", p->eg_a_decay);
            settings.setValue("settings:eg_a_sustain", p->eg_a_sustain);
            settings.setValue("settings:eg_a_release", p->eg_a_release);

            settings.setValue("settings:lfo_waveform", p->lfo_waveform);
            settings.setValue("settings:lfo_freq", p->lfo_freq);
            settings.setValue("settings:lfo_amp", p->lfo_amp);
            settings.setValue("settings:lfo_p_level", p->lfo_p_level);
            settings.setValue("settings:lfo_f_level", p->lfo_f_level);
            settings.setValue("settings:lfo_a_level", p->lfo_a_level);

            settings.setValue("settings:portamento", p->portamento);
            settings.setValue("settings:delay_delay", p->delay_delay);
            settings.setValue("settings:delay_feedback", p->delay_feedback);
            settings.setValue("settings:overdrive_gain", p->overdrive_gain);
            settings.setValue("settings:overdrive_drive", p->overdrive_drive);

            settings.setValue("settings:loop", p->loop);
            settings.setValue("settings:sample_file_name", p->sample_file_name);
            settings.setValue("settings:sample_phase_start", (int)(p->sample_phase_start));
            settings.setValue("settings:sample_phase_loop_start", (int)(p->sample_phase_loop_start));
            settings.setValue("settings:sample_phase_loop_end", (int)(p->sample_phase_loop_end));
            settings.setValue("settings:sample_phase_end", (int)(p->sample_phase_end));
            // sample_length, sample_channels ?
        }
        break;
    case DSettings::DRUM:
        switch (subtype)
        {
        case DSettings::DBASS:
            {
                DBass::Config *p;
                p = (DBass::Config *)config;
                settings.setValue("settings:settingstype", "DBass");
                settings.setValue("settings:type", p->type);
                settings.setValue("settings:vol", p->vol);
                settings.setValue("settings:freq", p->freq);
                settings.setValue("settings:tone", p->tone);
                settings.setValue("settings:decay", p->decay);
                settings.setValue("settings:fm_attack", p->fm_attack);
                settings.setValue("settings:fm_self", p->fm_self);
                settings.setValue("settings:decay", p->dirtiness);
                settings.setValue("settings:fm_env_amount", p->fm_env_amount);
                settings.setValue("settings:fm_env_decay", p->fm_env_decay);
                settings.setValue("settings:min", p->min);
            }
            break;
        case DSettings::DSNARE:
            {
                DSnare::Config *p;
                p = (DSnare::Config *)config;
                settings.setValue("settings:settingstype", "DSnare");
                settings.setValue("settings:type", p->type);
                settings.setValue("settings:vol", p->vol);
                settings.setValue("settings:freq", p->freq);
                settings.setValue("settings:decay", p->decay);
                settings.setValue("settings:snappy", p->snappy);
                settings.setValue("settings:tone", p->tone);
                settings.setValue("settings:fm_amount", p->fm_amount);
                settings.setValue("settings:amp", p->amp);
                settings.setValue("settings:min", p->min);
                settings.setValue("settings:res", p->res);
                settings.setValue("settings:drive", p->drive);
                settings.setValue("settings:freq_noise", p->freq_noise);
            }
            break;
        case DSettings::DHIHAT:
            {
                DHihat::Config *p;
                p = (DHihat::Config *)config;
                settings.setValue("settings:settingstype", "DHihat");
                settings.setValue("settings:type", p->type);
                settings.setValue("settings:vol", p->vol);
                settings.setValue("settings:freq", p->freq);
                settings.setValue("settings:decay", p->decay);
                settings.setValue("settings:tone", p->tone);
                settings.setValue("settings:noisiness", p->noisiness);
                settings.setValue("settings:amp", p->amp);
                settings.setValue("settings:res", p->res);
                settings.setValue("settings:drive", p->drive);
            }
            break;
        case DSettings::DCLAP:
            {
                DClap::Config *p;
                p = (DClap::Config *)config;
                settings.setValue("settings:settingstype", "DClap");
                settings.setValue("settings:vol", p->vol);
                settings.setValue("settings:freq", p->freq);
                settings.setValue("settings:res", p->res);
                settings.setValue("settings:drive", p->drive);
                settings.setValue("settings:amp", p->amp);
                settings.setValue("settings:decay", p->decay);
            }
            break;
        case DSettings::DCYMBAL:
            {
                DCymbal::Config *p;
                p = (DCymbal::Config *)config;
                settings.setValue("settings:settingstype", "DCymbal");
                settings.setValue("settings:vol", p->vol);
                settings.setValue("settings:freq", p->freq);
                settings.setValue("settings:res", p->res);
                settings.setValue("settings:drive", p->drive);
                settings.setValue("settings:amp", p->amp);
                settings.setValue("settings:decay", p->decay);
                settings.setValue("settings:min", p->min);
                settings.setValue("settings:mix", p->mix);
            }
        case DSettings::DDRUM:
            {
                DDrum::Config *p;
                p = (DDrum::Config *)config;
                settings.setValue("settings:settingstype", "DCymbal");
                settings.setValue("settings:vol", p->vol);
                settings.setValue("settings:freq", p->freq);
                settings.setValue("settings:amp", p->amp);
                settings.setValue("settings:decay", p->decay);
                settings.setValue("settings:min", p->min);
            }
            break;
        default:
            break;
        }
        break;
    }
    settings.saveFile(file_name); //puts settings.xml file in the bin/data folder
}

void DSettings::LoadSetting(DSoundType type, DSoundSubType subtype, string file_name, void *config)
{
    ofxXmlSettings settings;
    settings.loadFile(file_name);

    switch (type)
    {
    case DSettings::DSYNTHSUB:
        {
            DSynthSub::Config *p;
            p = (DSynthSub::Config *)config;
            p->sample_rate = DSTUDIO_SAMPLE_RATE;
            p->voices = settings.getValue("settings:voices", 1);
            p->waveform0 = static_cast<DSynthSub::Waveform>(settings.getValue("settings:waveform0", DSynthSub::WAVE_TRI));
            p->waveform1 = static_cast<DSynthSub::Waveform>(settings.getValue("settings:waveform1", DSynthSub::WAVE_TRI));
            p->tune = settings.getValue("settings:tune", 0.0f);
            p->detune = settings.getValue("settings:detune", 0.0f);
            p->transpose = settings.getValue("settings:transpose", 0);

            p->osc0_level = settings.getValue("settings:osc0_level", 0.5f);
            p->osc1_level = settings.getValue("settings:osc1_level", 0.5f);
            p->noise_level = settings.getValue("settings:noise_level", 0.0f);
            p->filter_type = static_cast<DSynthSub::FilterType>(settings.getValue("settings:filter_type", DSynthSub::LOW));
            p->filter_cutoff = settings.getValue("settings:filter_cutoff", 1000.0f);
            p->filter_res = settings.getValue("settings:filter_res", 0.0f);

            p->eg_p_level = settings.getValue("settings:eg_p_level", 0.0f);
            p->eg_p_attack = settings.getValue("settings:eg_p_attack", 0.0f);
            p->eg_p_decay = settings.getValue("settings:eg_p_decay", 0.0f);
            p->eg_p_sustain = settings.getValue("settings:eg_p_sustain", 0.0f);
            p->eg_p_release = settings.getValue("settings:eg_p_release", 0.0f);

            p->eg_f_level = settings.getValue("settings:eg_f_level", 1.0f);
            p->eg_f_attack = settings.getValue("settings:eg_f_attack", 0.0f);
            p->eg_f_decay = settings.getValue("settings:eg_f_decay", 0.0f);
            p->eg_f_sustain = settings.getValue("settings:eg_f_sustain", 1.0f);
            p->eg_f_release = settings.getValue("settings:eg_f_release", 0.0f);

            p->eg_a_attack = settings.getValue("settings:eg_a_attack", 0.0f);
            p->eg_a_decay = settings.getValue("settings:eg_a_decay", 0.0f);
            p->eg_a_sustain = settings.getValue("settings:eg_a_sustain", 1.0f);
            p->eg_a_release = settings.getValue("settings:eg_a_release", 0.0f);

            p->lfo_waveform = static_cast<DSynthSub::Waveform>(settings.getValue("settings:lfo_waveform", DSynthSub::WAVE_TRI));

            p->lfo_freq = settings.getValue("settings:lfo_freq", 0.0f);
            p->lfo_amp = settings.getValue("settings:lfo_amp", 0.0f);
            p->lfo_p_level = settings.getValue("settings:lfo_p_level", 0.0f);
            p->lfo_f_level = settings.getValue("settings:lfo_f_level", 0.0f);
            p->lfo_a_level = settings.getValue("settings:lfo_a_level", 0.0f);

            p->portamento = settings.getValue("settings:portamento", 0.0f);
            p->delay_delay = settings.getValue("settings:delay_delay", 0.0f);
            p->delay_feedback = settings.getValue("settings:delay_feedback", 0.0f);
            p->overdrive_gain = settings.getValue("settings:overdrive_gain", 0.0f);
            p->overdrive_drive = settings.getValue("settings:overdrive_drive", 0.0f);

        }
        break;
    case DSettings::DSYNTHFM:
        {
            DSynthFm::Config *p;
            p = (DSynthFm::Config *)config;
            p->sample_rate = DSTUDIO_SAMPLE_RATE;
            p->voices = settings.getValue("settings:voices", 1);
            p->ratio = settings.getValue("settings:ratio", 0.5f);
            p->index = settings.getValue("settings:index", 0.5f);
            p->tune = settings.getValue("settings:tune", 0.0f);
            p->transpose = settings.getValue("settings:transpose", 0);

            p->noise_level = settings.getValue("settings:noise_level", 0.0f);
            p->filter_type = static_cast<DSynthFm::FilterType>(settings.getValue("settings:filter_type", DSynthFm::LOW));
            p->filter_cutoff = settings.getValue("settings:filter_cutoff", 1000.0f);
            p->filter_res = settings.getValue("settings:filter_res", 0.0f);

            p->eg_p_level = settings.getValue("settings:eg_p_level", 0.0f);
            p->eg_p_attack = settings.getValue("settings:eg_p_attack", 0.0f);
            p->eg_p_decay = settings.getValue("settings:eg_p_decay", 0.0f);
            p->eg_p_sustain = settings.getValue("settings:eg_p_sustain", 0.0f);
            p->eg_p_release = settings.getValue("settings:eg_p_release", 0.0f);

            p->eg_f_level = settings.getValue("settings:eg_f_level", 1.0f);
            p->eg_f_attack = settings.getValue("settings:eg_f_attack", 0.0f);
            p->eg_f_decay = settings.getValue("settings:eg_f_decay", 0.0f);
            p->eg_f_sustain = settings.getValue("settings:eg_f_sustain", 1.0f);
            p->eg_f_release = settings.getValue("settings:eg_f_release", 0.0f);

            p->eg_a_attack = settings.getValue("settings:eg_a_attack", 0.0f);
            p->eg_a_decay = settings.getValue("settings:eg_a_decay", 0.0f);
            p->eg_a_sustain = settings.getValue("settings:eg_a_sustain", 1.0f);
            p->eg_a_release = settings.getValue("settings:eg_a_release", 0.0f);

            p->lfo_waveform = static_cast<DSynthFm::Waveform>(settings.getValue("settings:lfo_waveform", DSynthFm::WAVE_TRI));

            p->lfo_freq = settings.getValue("settings:lfo_freq", 0.0f);
            p->lfo_amp = settings.getValue("settings:lfo_amp", 0.0f);
            p->lfo_p_level = settings.getValue("settings:lfo_p_level", 0.0f);
            p->lfo_f_level = settings.getValue("settings:lfo_f_level", 0.0f);
            p->lfo_a_level = settings.getValue("settings:lfo_a_level", 0.0f);

            p->portamento = settings.getValue("settings:portamento", 0.0f);
            p->delay_delay = settings.getValue("settings:delay_delay", 0.0f);
            p->delay_feedback = settings.getValue("settings:delay_feedback", 0.0f);
            p->overdrive_gain = settings.getValue("settings:overdrive_gain", 0.0f);
            p->overdrive_drive = settings.getValue("settings:overdrive_drive", 0.0f);
        }
        break;
    case DSettings::DSYNTHVAR:
        {
            DSynthVar::Config *p;
            p = (DSynthVar::Config *)config;
            p->sample_rate = DSTUDIO_SAMPLE_RATE;
            p->voices = settings.getValue("settings:voices", 1);
            p->waveshape = settings.getValue("settings:waveshape", 0.5f);
            p->pulsewidth = settings.getValue("settings:pulsewidth", 0.5f);
            p->sync_enable = settings.getValue("settings:sync_enable", true);
            p->sync_freq = settings.getValue("settings:sync_freq", 440.0f);
            p->tune = settings.getValue("settings:tune", 0.0f);
            p->transpose = settings.getValue("settings:transpose", 0);
            p->osc_level = settings.getValue("settings:osc_level", 0.5f);
            p->noise_level = settings.getValue("settings:noise_level", 0.0f);
            p->filter_type = static_cast<DSynthVar::FilterType>(settings.getValue("settings:filter_type", DSynthVar::LOW));
            p->filter_cutoff = settings.getValue("settings:filter_cutoff", 1000.0f);
            p->filter_res = settings.getValue("settings:filter_res", 0.0f);

            p->mod_eg_p = settings.getValue("settings:mod_eg_p", 0.0f);
            p->mod_eg_f = settings.getValue("settings:mod_eg_f", 0.0f);
            p->mod_eg_a = settings.getValue("settings:mod_eg_a", 0.0f);
            p->mod_filter_cutoff = settings.getValue("settings:mod_filter_cutoff", 0.0f);
            p->mod_waveshape = settings.getValue("settings:mod_waveshape", 0.0f);
            p->mod_pulsewidth = settings.getValue("settings:mod_pulsewidth", 0.0f);
            p->mod_sync_freq = settings.getValue("settings:mod_sync_freq", 0.0f);
            p->mod_delay = settings.getValue("settings:mod_delay", 0.0f);

            p->eg_0_level = settings.getValue("settings:eg_0_level", 1.0f);
            p->eg_0_attack = settings.getValue("settings:eg_0_attack", 0.0f);
            p->eg_0_decay = settings.getValue("settings:eg_0_decay", 0.0f);
            p->eg_0_sustain = settings.getValue("settings:eg_0_sustain", 1.0f);
            p->eg_0_release = settings.getValue("settings:eg_0_release", 0.0f);

            p->eg_1_level = settings.getValue("settings:eg_1_level", 1.0f);
            p->eg_1_attack = settings.getValue("settings:eg_1_attack", 0.0f);
            p->eg_1_decay = settings.getValue("settings:eg_1_decay", 0.0f);
            p->eg_1_sustain = settings.getValue("settings:eg_1_sustain", 1.0f);
            p->eg_1_release = settings.getValue("settings:eg_1_release", 0.0f);

            p->eg_2_level = settings.getValue("settings:eg_2_level", 1.0f);
            p->eg_2_attack = settings.getValue("settings:eg_2_attack", 0.0f);
            p->eg_2_decay = settings.getValue("settings:eg_2_decay", 0.0f);
            p->eg_2_sustain = settings.getValue("settings:eg_2_sustain", 1.0f);
            p->eg_2_release = settings.getValue("settings:eg_2_release", 0.0f);

            p->lfo_0_waveform = static_cast<DSynthVar::Waveform>(settings.getValue("settings:lfo_0_waveform", DSynthVar::WAVE_TRI));
            p->lfo_0_freq = settings.getValue("settings:lfo_0_freq", 0.0f);
            p->lfo_0_amp = settings.getValue("settings:lfo_amp", 0.0f);
            p->lfo_0_offset = settings.getValue("settings:lfo_0_offset", 0.0f);

            p->lfo_1_waveform = static_cast<DSynthVar::Waveform>(settings.getValue("settings:lfo_1_waveform", DSynthVar::WAVE_TRI));
            p->lfo_1_freq = settings.getValue("settings:lfo_1_freq", 0.0f);
            p->lfo_1_amp = settings.getValue("settings:lfo_amp", 0.0f);
            p->lfo_1_offset = settings.getValue("settings:lfo_1_offset", 0.0f);

            p->lfo_2_waveform = static_cast<DSynthVar::Waveform>(settings.getValue("settings:lfo_2_waveform", DSynthVar::WAVE_TRI));
            p->lfo_2_freq = settings.getValue("settings:lfo_2_freq", 0.0f);
            p->lfo_2_amp = settings.getValue("settings:lfo_amp", 0.0f);
            p->lfo_2_offset = settings.getValue("settings:lfo_2_offset", 0.0f);

            p->sm_0_type = settings.getValue("settings:sm_0_type", DSTUDIO_SM_TYPE_NOISE);
            p->sm_0_freq = settings.getValue("settings:sm_0_freq", 0.0f);
            p->sm_0_amp = settings.getValue("settings:sm_0_amp", 1.0f);
            p->sm_0_offset = settings.getValue("settings:sm_0_offset", 0.0f);
            p->sm_0_seq_val = DSettings::StrToVec(settings.getValue("settings:sm_0_seq_val", ""));

            p->sm_1_type = settings.getValue("settings:sm_1_type", DSTUDIO_SM_TYPE_NOISE);
            p->sm_1_freq = settings.getValue("settings:sm_1_freq", 0.0f);
            p->sm_1_amp = settings.getValue("settings:sm_1_amp", 1.0f);
            p->sm_1_offset = settings.getValue("settings:sm_1_offset", 0.0f);
            p->sm_1_seq_val = DSettings::StrToVec(settings.getValue("settings:sm_1_seq_val", ""));

            p->sm_2_type = settings.getValue("settings:sm_2_type", DSTUDIO_SM_TYPE_NOISE);
            p->sm_2_freq = settings.getValue("settings:sm_2_freq", 0.0f);
            p->sm_2_amp = settings.getValue("settings:sm_2_amp", 1.0f);
            p->sm_2_offset = settings.getValue("settings:sm_2_offset", 0.0f);
            p->sm_2_seq_val = DSettings::StrToVec(settings.getValue("settings:sm_2_seq_val", ""));

            p->portamento = settings.getValue("settings:portamento", 0.0f);
            p->delay_delay = settings.getValue("settings:delay_delay", 0.0f);
            p->delay_feedback = settings.getValue("settings:delay_feedback", 0.0f);
            p->overdrive_gain = settings.getValue("settings:overdrive_gain", 0.0f);
            p->overdrive_drive = settings.getValue("settings:overdrive_drive", 0.0f);
        }
        break;
    case DSettings::DSAMPLER:
        {
            DSampler::Config *p;
            p = (DSampler::Config *)config;
            p->sample_rate = DSTUDIO_SAMPLE_RATE;
            p->voices = settings.getValue("settings:voices", 1);
            p->tune = settings.getValue("settings:tune", 0.0f);
            p->transpose = settings.getValue("settings:transpose", 0);

            p->filter_type = static_cast<DSampler::FilterType>(settings.getValue("settings:filter_type", DSampler::LOW));
            p->filter_cutoff = settings.getValue("settings:filter_cutoff", 1000.0f);
            p->filter_res = settings.getValue("settings:filter_res", 0.0f);

            p->eg_p_level = settings.getValue("settings:eg_p_level", 0.0f);
            p->eg_p_attack = settings.getValue("settings:eg_p_attack", 0.0f);
            p->eg_p_decay = settings.getValue("settings:eg_p_decay", 0.0f);
            p->eg_p_sustain = settings.getValue("settings:eg_p_sustain", 0.0f);
            p->eg_p_release = settings.getValue("settings:eg_p_release", 0.0f);

            p->eg_f_level = settings.getValue("settings:eg_f_level", 1.0f);
            p->eg_f_attack = settings.getValue("settings:eg_f_attack", 0.0f);
            p->eg_f_decay = settings.getValue("settings:eg_f_decay", 0.0f);
            p->eg_f_sustain = settings.getValue("settings:eg_f_sustain", 1.0f);
            p->eg_f_release = settings.getValue("settings:eg_f_release", 0.0f);

            p->eg_a_attack = settings.getValue("settings:eg_a_attack", 0.0f);
            p->eg_a_decay = settings.getValue("settings:eg_a_decay", 0.0f);
            p->eg_a_sustain = settings.getValue("settings:eg_a_sustain", 1.0f);
            p->eg_a_release = settings.getValue("settings:eg_a_release", 0.0f);

            p->lfo_waveform = static_cast<DSampler::Waveform>(settings.getValue("settings:lfo_waveform", DSampler::WAVE_TRI));
            p->lfo_freq = settings.getValue("settings:lfo_freq", 0.0f);
            p->lfo_amp = settings.getValue("settings:lfo_amp", 0.0f);
            p->lfo_p_level = settings.getValue("settings:lfo_p_level", 0.0f);
            p->lfo_f_level = settings.getValue("settings:lfo_f_level", 0.0f);
            p->lfo_a_level = settings.getValue("settings:lfo_a_level", 0.0f);

            p->portamento = settings.getValue("settings:portamento", 0.0f);
            p->delay_delay = settings.getValue("settings:delay_delay", 0.0f);
            p->delay_feedback = settings.getValue("settings:delay_feedback", 0.0f);
            p->overdrive_gain = settings.getValue("settings:overdrive_gain", 0.0f);
            p->overdrive_drive = settings.getValue("settings:overdrive_drive", 0.0f);
            p->loop = settings.getValue("settings:loop", false);
            p->sample_file_name = settings.getValue("settings:sample_file_name", "");
            p->sample_phase_start = settings.getValue("settings:sample_phase_start", 0);
            p->sample_phase_loop_start = settings.getValue("settings:sample_phase_loop_start", 0);
            p->sample_phase_loop_end = settings.getValue("settings:sample_phase_loop_end", 0);
            p->sample_phase_end = settings.getValue("settings:sample_phase_end", 0);
        }
        break;

    case DSettings::DRUM:
        switch (subtype)
        {
        case DSettings::DBASS:
            {
                DBass::Config *p;
                p = (DBass::Config *)config;
                p->sample_rate = DSTUDIO_SAMPLE_RATE;
                p->type = settings.getValue("settings:type", 1);
                p->vol = settings.getValue("settings:vol", 1.0f);
                p->freq = settings.getValue("settings:freq", 100.0f);
                p->tone = settings.getValue("settings:tone", 0.5f);
                p->decay = settings.getValue("settings:decay", 0.5f);
                p->fm_attack = settings.getValue("settings:fm_attack", 0.0f);
                p->fm_self = settings.getValue("settings:fm_self", 0.5f);
                p->dirtiness = settings.getValue("settings:decay", 0.5f);
                p->fm_env_amount = settings.getValue("settings:fm_env_amount", 0.5f);
                p->fm_env_decay = settings.getValue("settings:fm_env_decay", 0.5f);
                p->min = settings.getValue("settings:min", 0.5f);
            }
            break;
        case DSettings::DSNARE:
            {
                DSnare::Config *p;
                p = (DSnare::Config *)config;
                p->sample_rate = DSTUDIO_SAMPLE_RATE;
                p->type = settings.getValue("settings:type", 1);
                p->vol = settings.getValue("settings:vol", 1.0f);
                p->freq = settings.getValue("settings:freq", 100.0f);
                p->decay = settings.getValue("settings:decay", 0.5f);
                p->snappy = settings.getValue("settings:snappy", 0.5f);
                p->tone = settings.getValue("settings:tone", 0.5f);
                p->fm_amount = settings.getValue("settings:fm_amount", 0.5f);
                p->amp = settings.getValue("settings:amp", 0.5f);
                p->min = settings.getValue("settings:min", 0.5f);
                p->res = settings.getValue("settings:res", 0.5f);
                p->drive = settings.getValue("settings:drive", 0.5f);
                p->freq_noise = settings.getValue("settings:freq_noise", 1000.0f);
            }
            break;
        case DSettings::DHIHAT:
            {
                DHihat::Config *p;
                p = (DHihat::Config *)config;
                p->sample_rate = DSTUDIO_SAMPLE_RATE;
                p->type = settings.getValue("settings:type", 1.0f);
                p->vol = settings.getValue("settings:vol", 1.0f);
                p->freq = settings.getValue("settings:freq", 1000.0f);
                p->decay = settings.getValue("settings:decay", 0.5f);
                p->tone = settings.getValue("settings:tone", 0.5f);
                p->noisiness = settings.getValue("settings:noisiness", 0.5f);
                p->amp = settings.getValue("settings:amp", 0.5f);
                p->res = settings.getValue("settings:res", 0.5f);
                p->drive = settings.getValue("settings:drive", 0.5f);
            }
            break;
        case DSettings::DCLAP:
            {
                DClap::Config *p;
                p = (DClap::Config *)config;
                p->sample_rate = DSTUDIO_SAMPLE_RATE;
                p->vol = settings.getValue("settings:vol", 1.0f);
                p->freq = settings.getValue("settings:freq", 1000.0f);
                p->res = settings.getValue("settings:res", 0.5f);
                p->drive = settings.getValue("settings:drive", 0.5f);
                p->amp = settings.getValue("settings:amp", 0.5f);
                p->decay = settings.getValue("settings:decay", 0.5f);
            }
            break;
        case DSettings::DCYMBAL:
            {
                DCymbal::Config *p;
                p = (DCymbal::Config *)config;
                p->sample_rate = DSTUDIO_SAMPLE_RATE;
                p->vol = settings.getValue("settings:vol", 1.0f);
                p->freq = settings.getValue("settings:freq", 1000.0f);
                p->res = settings.getValue("settings:res", 0.5f);
                p->drive = settings.getValue("settings:drive", 0.5f);
                p->amp = settings.getValue("settings:amp", 0.5f);
                p->decay = settings.getValue("settings:decay", 0.5f);
                p->min = settings.getValue("settings:min", 0.5f);
                p->mix = settings.getValue("settings:mix", 0.5f);
            }
        case DSettings::DDRUM:
            {
                DDrum::Config *p;
                p = (DDrum::Config *)config;
                p->sample_rate = DSTUDIO_SAMPLE_RATE;
                p->vol = settings.getValue("settings:vol", 1.0f);
                p->freq = settings.getValue("settings:freq", 1000.0f);
                p->amp = settings.getValue("settings:amp", 0.5f);
                p->decay = settings.getValue("settings:decay", 0.5f);
                p->min = settings.getValue("settings:min", 0.5f);
            }
            break;
        default:
            break;
        } // switch
        break;
    } // switch
}



std::string DSettings::VecToStr(std::vector<float> vec)
{
    std::string str;

    for (size_t i = 0; i < vec.size(); i++)
    {
        if (i != 0)
        {
           str += ", ";
        }
        str += std::to_string(vec[i]);
    }

    return (str);
}



std::vector<float> DSettings::StrToVec(std::string str)
{
    std::vector<float> vec;

    std::string temp;
    for (int i = 0; i < str.length() ;i++)
    {
        char ch = str[i];
        if (ch == ' ')
        {
            continue;
        } else if (ch == ',') {
            if (temp.length() != 0)
                vec.push_back(std::stof(temp));
            temp = "";
        } else {
            temp += ch;
        }
    }
    if (temp.length() != 0)
    {
        vec.push_back(std::stof(temp));
    }

    return (vec);
}
