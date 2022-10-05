#include "dstudio.h"
#include "dmixer.h"

void DMixer::Init(const Config& config)
{
	sample_rate_ = config.sample_rate;
	channels_ = config.channels;

    amp_ = config.amp;

	for (uint8_t i = 0; i < channels_; i++)
	{
		synth_[i] = config.synth[i];
		pan_[i] = config.pan[i];
        level_[i] = config.level[i];
        chorus_level_[i] = config.chorus_level[i];
        reverb_level_[i] = config.reverb_level[i];
        mono_[i] = config.mono[i];
        group_[i] = config.group[i];
    }

    reverb_return_ = config.reverb_return;
    chorus_return_ = config.chorus_return;
    mix_dry_ = config.mix_dry;
    
    // chorus
    chorus_delay_ = 0.75f; // 0-1
    chorus_feedback_ = 0.2f; // 0-1
    chorus_lfo_depth_ = 0.5; // 0-1
    chorus_lfo_freq_ = 0.3f; // Hz
    chorus_pan_ = 0.5f; // 0-1
    chorus_.Init(sample_rate_);
    chorus_.SetDelay(chorus_delay_);
    chorus_.SetFeedback(chorus_feedback_);
    chorus_.SetLfoDepth(chorus_lfo_depth_);
    chorus_.SetLfoFreq(chorus_lfo_freq_);
    chorus_.SetPan(chorus_pan_);

	// reverb
    reverb_feedback_ = 0.4f;
	reverb_lpffreq_ = 6000;
    reverb_.Init(sample_rate_);
	reverb_.SetFeedback(reverb_feedback_);
	reverb_.SetLpFreq(reverb_lpffreq_);

    SetType(DSound::MIXER); // default
}



void DMixer::Process(float *out_left, float *out_right)
{
    float mix_left = 0;
    float mix_right = 0;
    float synth_out;
    float synth_left, synth_right;
    float chorus_send = 0;
    float reverb_send_left = 0;
    float reverb_send_right = 0;
    float reverb_out_left, reverb_out_right;
	
	// voices
	
    for (uint8_t i = 0; i < channels_; i++)
	{
        if (mono_[i])
        {
            // level
            synth_out = synth_[i]->Process() * level_[i];

            // pan
            synth_left = synth_out * (1.0f - pan_[i]);
            synth_right = synth_out * (pan_[i]);
        } else {
            synth_[i]->Process(&synth_left, &synth_right);
            // level and pan
            synth_left = synth_left * level_[i] * (1.0f - pan_[i]);
            synth_right = synth_right * level_[i] * (pan_[i]);
            // chorus needs mono
            synth_out = (synth_left + synth_right) / 2;
        }
        // chorus send (DaisySP chorus is mono input)
        chorus_send += synth_out * chorus_level_[i];

        // reverb send
        reverb_send_left += synth_left * reverb_level_[i];
        reverb_send_right += synth_right * reverb_level_[i];
		
		// mix
        mix_left += synth_left;
        mix_right += synth_right;
	}

    // chorus send fx
    chorus_.Process(chorus_send);

    // reverb send fx
    reverb_.Process(reverb_send_left, reverb_send_right, &reverb_out_left, &reverb_out_right);

    // add chorus and reverb
    *out_left = (mix_left * mix_dry_+ reverb_out_left * reverb_return_ + chorus_.GetLeft() * chorus_return_) * amp_;
    *out_right = (mix_right * mix_dry_ + reverb_out_right * reverb_return_ + chorus_.GetRight() * chorus_return_) * amp_;
}



void DMixer::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
{

    switch (GetType())
    {
    case MIXER:
    {
        // mixer handles pan and level
        // everything else goes to channel
        uint8_t midi_channel = midi_status & MIDI_CHANNEL_MASK;
        if (midi_channel < channels_)
        {
            uint8_t midi_message = midi_status & MIDI_MESSAGE_MASK;
            switch (midi_message)
            {
            case MIDI_MESSAGE_CC:
                switch (midi_data0 & MIDI_DATA_MASK)
                {
                case MIDI_CC_VOLUME:
                    SetLevel(midi_channel, (midi_data1 & MIDI_DATA_MASK) / (float)MIDI_DATA_MAX);
                    break;
                case MIDI_CC_PAN:
                    SetPan(midi_channel, (midi_data1 & MIDI_DATA_MASK) / (float)MIDI_DATA_MAX);
                    break;
                default:
                    synth_[midi_channel]->MidiIn(midi_status, midi_data0, midi_data1);
                    break;
                }
                break;
            default:
                synth_[midi_channel]->MidiIn(midi_status, midi_data0, midi_data1);
                break;
            }
        }

        break;
    }
    case MIXER_SUB:
    {
        // send same message to all channels
        for (uint8_t c = 0; c < channels_; c++)
        {
            synth_[c]->MidiIn(midi_status, midi_data0, midi_data1);
        }
        break;
    }
    case MIXER_PERCUSSION:
    {
        // only deal with note on events
        // send message to channel derived from note value -36
        // ref: https://soundprogramming.net/file-formats/general-midi-drum-note-numbers/
        uint8_t midi_message = midi_status & MIDI_MESSAGE_MASK;
        if (midi_message == MIDI_MESSAGE_NOTEON)
        {
            uint8_t c = (midi_data0 & MIDI_DATA_MASK) - MIDI_PERCUSSION_START;
            if (c < channels_)
            {
                synth_[c]->MidiIn(midi_status, midi_data0, midi_data1);
                // handle sound groups
                // eg hihat, turn off closed when open
                uint8_t group = group_[c];
                for (uint8_t i = 0; i < channels_; i++)
                {
                    if ((i != c) && (group_[i] == group))
                    {
                        synth_[i]->Silence();
                    }
                }
            }
        }
        break;
    }
    default:
        break;
    } // switch GetType()

}



void DMixer::Silence(uint8_t c)
{
    synth_[c]->Silence();
}



void DMixer::Silence()
{
    for (uint8_t c = 0; c < channels_; c++)
    {
        synth_[c]->Silence();
    }
}



void DMixer::SetPan(uint8_t channel, float value)
{
    if (channel < channels_)
    {
        pan_[channel] = value;

    }
}



void DMixer::SetLevel(uint8_t channel, float value)
{
    if (channel < channels_)
    {
        level_[channel] = value;
    }
}



void DMixer::SetChorus(float delay, float feedback, float lfo_depth, float lfo_freq, float pan)
{
    chorus_delay_ = delay; // 0-1
    chorus_feedback_ = feedback; // 0-1
    chorus_lfo_depth_ = lfo_depth; // 0-1
    chorus_lfo_freq_ = lfo_freq; // Hz
    chorus_pan_ = pan; // 0-1

    chorus_.SetDelay(chorus_delay_);
    chorus_.SetFeedback(chorus_feedback_);
    chorus_.SetLfoDepth(chorus_lfo_depth_);
    chorus_.SetLfoFreq(chorus_lfo_freq_);
    chorus_.SetPan(chorus_pan_);

}



void DMixer::SetChorusLevel(uint8_t channel, float value)
{
    if (channel < channels_)
    {
        chorus_level_[channel] = value;
    }
}



void DMixer::SetReverb(float feedback, float lpffreq)
{
    reverb_feedback_ = feedback;
    reverb_lpffreq_ = lpffreq;
    reverb_.SetFeedback(reverb_feedback_);
    reverb_.SetLpFreq(reverb_lpffreq_);
}



void DMixer::SetReverbLevel(uint8_t channel, float value)
{
    if (channel < channels_)
    {
        reverb_level_[channel] = value;
    }
}



uint8_t DMixer::GetChannels()
{
    return (channels_);
}



void DMixer::SetChorusReturn(float chorus_return)
{
    chorus_return_ = chorus_return;
}



void DMixer::SetReverbReturn(float reverb_return)
{
    reverb_return_ = reverb_return;
}



void DMixer::SetMixDry(float mix_dry)
{
    mix_dry_ = mix_dry;
}
