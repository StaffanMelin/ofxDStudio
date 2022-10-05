#include "dsound.h"

void DSound::Init()
{}

float DSound::Process()
{
    return 0;
}

void DSound::Process(float *out_l, float *out_r)
{
    *out_l = 0;
    *out_r = 0;
}

void DSound::MidiIn(uint8_t midi_status, uint8_t midi_data0, uint8_t midi_data1 = 0)
{}

void DSound::NoteOn(uint8_t, uint8_t)
{}

void DSound::NoteOn(uint8_t )
{}

void DSound::NoteOff(uint8_t )
{}

void DSound::Silence()
{}

void DSound::Silence(uint8_t c)
{}

DSound::SoundType DSound::GetType()
{
    return sound_type_;
}

void DSound::SetType(SoundType sound_type)
{
    sound_type_ = sound_type;
}

