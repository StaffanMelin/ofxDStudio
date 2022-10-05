#pragma once

// helper macros
#define DMAX(x,y) ((x > y) ? (x) : (y))
#define DMIN(x,y) ((x > y) ? (y) : (x))

// system
#define DSTUDIO_SAMPLE_RATE 44100
#define DSTUDIO_BUFFER_SIZE 512
#define DSTUDIO_NUM_BUFFERS 4
#define DSTUDIO_FILTER_BASE (DSTUDIO_SAMPLE_RATE / 2)
// mixer
#define MIXER_CHANNELS_MAX 16

// drums
#define DTYPE_ANALOG 1
#define DTYPE_SYNTHETIC 2
#define DTYPE_OPD 3

// MIDI
#define MIDI_CHANNELS_MAX 16
#define MIDI_VELOCITY_MAX 127
#define MIDI_DATA_MAX 127
#define MIDI_CHANNEL_MASK 0b00001111
#define MIDI_MESSAGE_MASK 0b11110000
#define MIDI_MESSAGE_NOTEOFF 0b10000000
#define MIDI_MESSAGE_NOTEON 0b10010000
#define MIDI_MESSAGE_CC 0b10110000
#define MIDI_DATA_MASK 0b01111111
#define MIDI_CC_VOLUME 7
#define MIDI_CC_PAN 10
#define MIDI_CC_RESONANCE 71
#define MIDI_CC_CUTOFF 74

// this is the start note for percussion sounds
// this number is subtracted from the note value
// to figure out which DSound object a MIXER_PERC
// sends the note to
// see dmixer.cpp > MidiIn()
#define MIDI_PERCUSSION_START 36
#define DEKICK 36
#define DESNARE 37
#define DEHHC 38
#define DEHHO 39
#define DECLAP 40
#define DERIDE 41
#define DECRASH 42
#define DETOMHI 43
#define DETOMLO 44
