#pragma once

#include <stdint.h>
#include <vector>

#include "dstudio.h"

#define DSTUDIO_SM_TYPE_NOISE 0
#define DSTUDIO_SM_TYPE_CRAWL 1
#define DSTUDIO_SM_TYPE_INTERVAL 2
#define DSTUDIO_SM_TYPE_CHAOS 3
#define DSTUDIO_SM_TYPE_SEQ 4
#define DSTUDIO_SM_TYPE_MAX 5

class DSM
{
public:
    struct Config
    {
        float sample_rate;
        uint8_t type;
        float freq;
        float amp;
        float offset;
        uint8_t seq_len;
        std::vector<float> seq_val;
    };

    void Init(const Config&);
    float Process();
    void SetType(uint8_t);
    void SetFreq(float);
    void SetAmp(float);
    void SetOffset(float);
    void SetSeq(uint8_t, std::vector<float>&);
    void SetSeqStep(uint8_t, float);

private:
	uint8_t smNumber;
    float sample_rate_;
    uint8_t type_;
    float freq_;
    float amp_;
    float offset_;
    uint8_t seq_len_;
    std::vector<float> seq_val_;
	
    float val_;
    float step_;
    float inc_;
    float gate_;
    uint8_t extra_;
	
    void CalcInc();


};
