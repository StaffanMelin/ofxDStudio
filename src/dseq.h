#pragma once

// seq resolution in microseconds
// only check for advance in seq
// if time passed in us is > this
// ie if DSEQRESOLUTION = 1000
// then only check every ms
#define DSEQRESOLUTION 1000

// seq event type "shortcut" (DE = Dstudio Event)
#define DEN MIDI_MESSAGE_NOTEON // note on

// note lengths (DT = Dstudio Ticks)
#define DT1 1024
#define DT2 512
#define DT4 256
#define DT8 128
#define DT16 64
#define DT32 32
#define DTD 32

// note volume/velocity "shortcuts" (DV = Dstudio Velocity)
#define DVOFF 0 // note off
#define DV1 10
#define DV2 20
#define DV3 30
#define DV4 40
#define DV5 50
#define DV6 60
#define DV7 70
#define DV8 80
#define DV9 90
#define DV10 100
#define DVMAX MIDI_VELOCITY_MAX

struct DMidiSeqStep
{
    uint64_t pos;
    uint8_t status;
    uint8_t data0;
    uint8_t data1;
};

struct DMidiSongStep
{
    uint8_t seq_nr;
    uint32_t seq_len;
};

