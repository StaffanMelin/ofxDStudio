#pragma once

#include <stdint.h>
#include <vector>

#include "ofThread.h"

#include "dstudio.h"
#include "dsound.h"
#include "dmixer.h"
#include "dseq.h"

struct DMidiSeqStepIn
{
    uint64_t pos;
    uint8_t status;
    uint8_t data0;
    uint8_t data1;
    uint64_t len;
};

typedef std::vector<std::vector<DMidiSongStep>> dmidisong_t;
typedef std::vector<std::vector<DMidiSeqStepIn>> dmidiseqin_t;

class DSeqPerm : public ofThread
{
public:

    DSeqPerm() {}
    ~DSeqPerm() {}

    enum PermutateType
    {
        PERMUTATE_SWAP = 0,
        PERMUTATE_RHYTHM,
        PERMUTATE_SIMPLIFY,
        PERMUTATE_ADD,
        PERMUTATE_SHIFT,
        PERMUTATE_TRANSPOSE,
        PERMUTATE_ORIGINAL,
        PERMUTATE_LAST
    };

    struct Config
    {
        uint8_t bpm;
        uint16_t rep;
        bool silence; // silence all synths after each song step
        dmidisong_t dmidisong;
        dmidiseqin_t dmidiseq;
        uint8_t channels;
        DSound *mixer;
        float strength; // permutation strengt (0 - 1, where 0 is no change)
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
    dmidiseqin_t dmidiseq_, dmidiseq_org_;
    uint8_t channels_;
    DSound *mixer_;
    float strength_;

    uint64_t upt_; // microseconds per tick
    uint64_t now_us_;
    uint64_t prev_us_;
    bool running_;
    uint64_t ticks_[MIXER_CHANNELS_MAX];
    uint16_t song_step_;
    uint16_t rep_count_;
    std::vector<uint8_t> channel_max_len_; // channel with seq max len of sequence for each song step

    // buffer, circular
    std::vector<DMidiSeqStep> queue_[MIXER_CHANNELS_MAX];
    uint32_t queue_note_[MIXER_CHANNELS_MAX];

    void CalcTempo();
    void Permutate(uint16_t);
    void FillVector(uint8_t, uint16_t);
};
