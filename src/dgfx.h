#pragma once

#include "dstudio.h"
#include "dsound.h"

#include "overdrive.h"

class DGFXBase : public DSound
{

	public:

    DGFXBase() {}
    ~DGFXBase() {}

	struct Config
	{
		float sample_rate;
        uint8_t channels;
        DSound *child;
	};

    void Init(const Config&);
    float Process();
    void Process(float *, float *);
    void MidiIn(uint8_t, uint8_t, uint8_t);
    void NoteOn(uint8_t midi_note, uint8_t midi_velocity = MIDI_VELOCITY_MAX);
    void NoteOff(uint8_t midi_note);
    void Silence();
    void Draw();

private:

	// config
    float sample_rate_;
    uint8_t channels_;
    DSound *child_;

    // objects
    bool note_new_[MIDI_CHANNELS_MAX];
    uint8_t note_[MIDI_CHANNELS_MAX];
    uint8_t note_velocity_[MIDI_CHANNELS_MAX];

};


