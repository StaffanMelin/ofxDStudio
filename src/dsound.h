#pragma once

#include <stdint.h>

#include "dstudio.h"

class DSound
{


public:
    enum SoundType
    {
        NONE,
        TUNED,
        PERCUSSION,
        FX,
        MIXER,
        MIXER_SUB,
        MIXER_PERCUSSION,
        LAST
    };

    virtual void Init();
    virtual float Process();
    virtual void Process(float *, float *);
    virtual void MidiIn(uint8_t, uint8_t, uint8_t);
    virtual void NoteOn(uint8_t, uint8_t);
    virtual void NoteOn(uint8_t);
    virtual void NoteOff(uint8_t);
    virtual void Silence();
    virtual void Silence(uint8_t);
    SoundType GetType();
    void SetType(SoundType);

private:
    SoundType sound_type_;

};
