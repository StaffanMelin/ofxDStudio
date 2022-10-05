#include <random>

#include "dstudio.h"
#include "dsm.h"

void DSM::Init(const Config& config)
{
    sample_rate_ = config.sample_rate;
    type_ = config.type;
    freq_ = config.freq;
    amp_ = config.amp;
    offset_ = config.offset;
    seq_len_ = config.seq_len;
    seq_val_ = config.seq_val;
    // make sure we have at least one element in seq
    if (seq_len_ == 0)
    {
        seq_len_++;
        seq_val_.push_back(0.5);
    }
    val_ = 0;
    step_ = 0;
    gate_ = 0.0f;
	
    extra_ = 0;

	CalcInc();
}



void DSM::CalcInc()
{
    inc_ = (freq_ / sample_rate_);
}



float DSM::Process()
{
	/*
		c += (1/sr) * f
		
		f = 1000
		sr = 48 000
		c = 1/48
	*/
    bool next_note = (step_ == 0);

    if (next_note)
	{
        switch (type_)
		{
        case DSTUDIO_SM_TYPE_NOISE:
			// int theDice = std::rand() % 100;
			// return ((float)rand() / (float)RAND_MAX) <= prob ? true : false;
            val_ = ((float)rand() / (float)RAND_MAX) * amp_ + offset_;
            val_ = DMIN(val_, 1);
			break;
        case DSTUDIO_SM_TYPE_CRAWL:
            // extra_ = direction (0 = down, 1 = up)
            // amp_ = how much to change / 10, ie 50 = 5 steps
            // offset_ = probabibilty to NOT CHANGE
            if (extra_ == 0)
			{
                val_ += (amp_ / 10);
                val_ = DMIN(val_, 1);
			} else {
                val_ -= (amp_ / 10);
                val_ = DMAX(val_, 0);
			}
            if (((float)rand() / (float)RAND_MAX) > offset_)
			{
                if (extra_ == 0)
				{
                    extra_ = 1;
				} else {
                    extra_ = 0;
				}
			}
			break;
        case DSTUDIO_SM_TYPE_INTERVAL:
			// interval can be made longer by NOT CHANGING smVal based on probability
            // amp_ = value that should be output
            // offset_ = probabibilty to NOT CHANGE
            if (((float)rand() / (float)RAND_MAX) > offset_)
			{
                if (val_ == amp_)
				{
                    val_ = 0;
				} else {
                    val_ = amp_;
				}
			}		
			break;
        case DSTUDIO_SM_TYPE_CHAOS:
            // offset_ = probabibilty to NOT CHANGE
            if (((float)rand() / (float)RAND_MAX) > offset_)
			{
                val_ = ((float)rand() / (float)RAND_MAX) * amp_;
                val_ = DMIN(val_, 1);
			}		
			break;
        case DSTUDIO_SM_TYPE_SEQ:
            extra_++;
            if (extra_ >= seq_len_)
			{
                extra_ = 0;
			}
            val_ = seq_val_[extra_];
			break;
		}
	}

    step_ += inc_;
    if (step_ >= 1)
	{
        step_ = 0;
	}
	
    return (val_);
}



/*
float DSM::Gate()
{

	if (fxSettings.smSyncMod[smNumber] == MOD_SOURCE_NONE)
	{
		if (smStep > fxSettings.smGateLen)
		{
			smGate = 0.0f;
		}
	} else {
		smGate = (modSources.smSync[smNumber] ? 1.0f : 0.0f);
	}

	return (smGate);
}
*/



void DSM::SetType(uint8_t type)
{
    type_ = type;
    extra_ = 0;

	CalcInc();
}



void DSM::SetFreq(float freq)
{
    freq_ = freq;

	CalcInc();
}



void DSM::SetAmp(float amp)
{
    amp_ = amp;

	CalcInc();
}



void DSM::SetOffset(float offset)
{
    offset_ = offset;

	CalcInc();
}



void DSM::SetSeq(uint8_t seq_len, std::vector<float>& seq_val)
{
    seq_len_ = seq_len;
    seq_val_ = seq_val;

    CalcInc();
}



void DSM::SetSeqStep(uint8_t step, float val)
{
    seq_val_[step] = val;
}
