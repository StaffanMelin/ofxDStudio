#pragma once

#include <stdint.h>
#include <vector>

#include "ofThread.h"

#include "dstudio.h"
#include "dmixer.h"
#include "dseq.h"

typedef std::vector<std::vector<DMidiSongStep>> dmidisong_t;
typedef std::vector<std::vector<DMidiSeqStep>> dmidiseq_t;

class DSeqMidi : public ofThread
{
public:

    DSeqMidi() {}
    ~DSeqMidi() {}

    struct Config
    {
        uint8_t bpm; // BPM
        uint16_t rep; // how many times to repeat song
        bool silence; // silence all synths after each song step
        dmidisong_t dmidisong; // vector of vectors with song step data
        dmidiseq_t dmidiseq; // vector of vectors with sequences data
        uint8_t channels; // number of active channels
        DMixer *mixer; // address of mixer so sequencer can send MIDI data
    };

    void Init(const Config&);
    void Start();
    void Stop();
    void threadedFunction();
    void Process();
    void SetBPM(uint8_t);

private:

    uint8_t bpm_;
    uint16_t rep_;
    bool silence_;
    dmidisong_t dmidisong_;
    dmidiseq_t dmidiseq_;
    uint8_t channels_;
    DMixer *mixer_;

    uint64_t upt_; // microseconds per tick
    uint64_t now_us_;
    uint64_t prev_us_;
    bool running_;
    uint64_t ticks_[MIXER_CHANNELS_MAX];
    uint16_t note_[MIXER_CHANNELS_MAX];
    uint16_t song_step_;
    uint16_t rep_count_;
    std::vector<uint8_t> channel_max_len_; // channel with seq max len of sequence for each song step

    void CalcTempo();
};
