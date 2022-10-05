#include "dstudio.h"
#include "dgfx.h"

#include "ofMain.h"


void DGFXBase::Init(const Config& config)
{
    sample_rate_ = config.sample_rate;
    channels_ = config.channels;
    child_ = config.child;

    // init internal data
    for (uint8_t c = 0; c < channels_; c++)
    {
        note_[c] = 0;
        note_new_[c] = false;
        note_velocity_[c] = 0;
    }

    // TODO
    SetType(FX);
}



void DGFXBase::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
{
    child_->MidiIn(midi_status, midi_data0, midi_data1);

    uint8_t midi_channel = midi_status & MIDI_CHANNEL_MASK;
    if (midi_channel < channels_)
    {
        uint8_t midi_message = midi_status & MIDI_MESSAGE_MASK;
        switch (midi_message)
        {
        case MIDI_MESSAGE_NOTEON:
//            if (midi_data0 != note_[midi_channel])
            {
                note_[midi_channel] = midi_data0;
                note_new_[midi_channel] = true;
                note_velocity_[midi_channel] = midi_data1;
            }

            break;
        case MIDI_MESSAGE_NOTEOFF:
            note_[midi_channel] = midi_data0;
            note_new_[midi_channel] = false;
            note_velocity_[midi_channel] = midi_data1;
            break;
        }
    }
}



void DGFXBase::NoteOn(uint8_t midi_note, uint8_t midi_velocity)
{
    child_->NoteOn(midi_note, midi_velocity);
}



void DGFXBase::NoteOff(uint8_t midi_note)
{
    child_->NoteOff(midi_note);
}



void DGFXBase::Silence()
{
    child_->Silence();
}



float DGFXBase::Process()
{
    float child_l, child_r;
    float fx_in;

    child_->Process(&child_l, &child_r);
    fx_in = (child_l + child_r) / 2;

    return (fx_in);
}



void DGFXBase::Process(float *out_l, float *out_r)
{
    float child_l, child_r;

    child_->Process(&child_l, &child_r);
    *out_l = child_l;
    *out_r = child_r;

}


// call in main app draw()
void DGFXBase::Draw()
{
    // basw output on note_new_ and note_

    for (uint8_t c = 0; c < channels_; c++)
    {
        ofDrawCircle(64 + c * 127, 64 + note_[c] * 5, note_velocity_[c]/2);
    }

}
