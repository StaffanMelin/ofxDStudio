#include "dstudio.h"
#include "dsplit.h"

void DSplit::Init(const Config& config)
{
	sample_rate_ = config.sample_rate;
	channels_ = config.channels;

	for (uint8_t i = 0; i < channels_; i++)
	{
		synth_[i] = config.synth[i];
        split_[i] = config.split[i];
    }

    SetType(DSound::FX); // default
}



void DSplit::Process(float *out_left, float *out_right)
{
    float mix_left = 0;
    float mix_right = 0;
    float synth_left, synth_right;
	
	// voices	
	for (uint8_t i = 0; i < channels_; i++)
	{
        synth_[i]->Process(&synth_left, &synth_right);
		
		// mix
        mix_left += synth_left;
        mix_right += synth_right;
	}

    *out_left = mix_left;
    *out_right = mix_right;
}



void DSplit::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
{

    // mixer handles pan and level
    // everything else goes to channel
    uint8_t midi_channel = midi_status & MIDI_CHANNEL_MASK;
//    if (midi_channel < channels_)
    {
        uint8_t midi_message = midi_status & MIDI_MESSAGE_MASK;
        switch (midi_message)
        {
        case MIDI_MESSAGE_NOTEON:
        case MIDI_MESSAGE_NOTEOFF:
            {
                uint8_t midi_note = midi_data0 & MIDI_DATA_MASK;
                uint8_t c = 0;
                while (c < channels_)
                {
                    if (midi_note <= split_[c].split_end)
                    {
                        synth_[split_[c].split_channel]->MidiIn(midi_status, midi_data0 + split_[c].split_offset, midi_data1);
                        break;
                    }
                    c++;
                }
            }
            break;
        case MIDI_MESSAGE_CC:
            synth_[midi_channel]->MidiIn(midi_status, midi_data0, midi_data1);
            break;
        default:
            synth_[midi_channel]->MidiIn(midi_status, midi_data0, midi_data1);
            break;
        }
    }
}



void DSplit::Silence(uint8_t c)
{
    synth_[c]->Silence();
}



void DSplit::Silence()
{
    for (uint8_t c = 0; c < channels_; c++)
    {
        synth_[c]->Silence();
    }
}



uint8_t DSplit::GetChannels()
{
    return (channels_);
}
