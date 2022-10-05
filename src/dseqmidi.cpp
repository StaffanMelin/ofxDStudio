
#include "ofUtils.h"
#include "dstudio.h"
#include "dseqmidi.h"

void DSeqMidi::Init(const Config& config)
{
    bpm_ = config.bpm;
    rep_ = config.rep;
    silence_ = config.silence;
    dmidisong_ = config.dmidisong;
    dmidiseq_ = config.dmidiseq;
    channels_ = config.channels;
    mixer_ = config.mixer;

    CalcTempo();
}

void DSeqMidi::Start()
{
    for (uint8_t c = 0; c < channels_; c++)
    {
        ticks_[c] = 0;
        note_[c] = 0;
    }
    song_step_ = 0;
    rep_count_ = rep_;

    // store channel with max seq len for every song step
    channel_max_len_.clear();
    for (uint16_t i = 0; i < dmidisong_.size(); i++)
    {
        uint32_t max_len = 0;
        uint8_t max_len_channel = 0;
        for (uint16_t j = 0; j < dmidisong_[i].size(); j++)
        {
            if (dmidisong_[i][j].seq_len > max_len)
            {
                max_len = dmidisong_[i][j].seq_len;
                max_len_channel = j;
            }
        }
        channel_max_len_.push_back(max_len_channel);
    }

    now_us_ = ofGetElapsedTimeMicros();
    prev_us_ = now_us_;
    running_ = true;
}



void DSeqMidi::Stop()
{
    running_ = false;
    for (uint8_t c = 0; c < channels_; c++)
    {
        mixer_->Silence(c);
    }
}



void DSeqMidi::threadedFunction()
{
    while(isThreadRunning())
        Process();
}



void DSeqMidi::Process()
{
    bool song_step_inc = false;
    uint64_t song_step_inc_ticks;

    if (running_)
    {
        now_us_ = ofGetElapsedTimeMicros();

        uint64_t ticks_inc = now_us_ - prev_us_;
        if (ticks_inc > DSEQRESOLUTION)
        {
            prev_us_ = now_us_;

            for (uint8_t c = 0; c < channels_; c++)
            {
                uint16_t s = dmidisong_[song_step_][c].seq_nr;

    //            if (dmidiseq_[s].size() > 0)
                if (dmidisong_[song_step_][c].seq_len > 0)
                {

                    ticks_[c] += ticks_inc;
                    // notes left in seq?
                    if (note_[c] < dmidiseq_[s].size())
                    {
                        // while because possibly more events on pos < ticks
                        while (ticks_[c] >= (dmidiseq_[s][note_[c]].pos * upt_))
                        {
                            uint16_t note = note_[c];
                            uint8_t status = dmidiseq_[s][note].status;

                            // add channel and
                            // let dmixer handle midi
                            mixer_->MidiIn((status & MIDI_MESSAGE_MASK) + c,
                                           dmidiseq_[s][note].data0,
                                           dmidiseq_[s][note].data1);

                            note_[c]++;
                            if (note_[c] >= dmidiseq_[s].size())
                            {
                                 break;
                            }
                        }
                    }
                    // sequence length passed
                    if (ticks_[c] >= (dmidisong_[song_step_][c].seq_len * upt_))
                    {
                        // repeat shorter channel sequences
                        note_[c] = 0;
                        // we have possibly passed zero ticks, so set start of next iteration to this difference
//                        ticks_[c] = (ticks_[c] - dmidisong_[song_step_][c].seq_len);
                        ticks_[c] -= (dmidisong_[song_step_][c].seq_len * upt_);
                        if (silence_)
                        {
                            mixer_->Silence(c);
                        }
                        // increase song step when last sequence reaches end
                        if (c == channel_max_len_[song_step_])
                        {
                            song_step_inc = true;
                            song_step_inc_ticks = ticks_[c];
                        }
                    }

                }

            } // for
            if (song_step_inc)
            {
                // sync all channels
                song_step_++;
                if (song_step_ >= dmidisong_.size())
                {
                    song_step_ = 0;
                    if (rep_count_ > 0)
                    {
                        rep_count_--;
                    } else {
                        Stop();
                    }
                }
                for (uint8_t c = 0; c < channels_; c++)
                {
                    note_[c] = 0;
                    ticks_[c] = song_step_inc_ticks;
                    if (silence_)
                    {
                        mixer_->Silence(c);
                    }
                }
            }
        }
    } // if running_
}



void DSeqMidi::SetBPM(uint8_t bpm)
{
    bpm_ = bpm;
    CalcTempo();

    // TODO: reset anything?
    if (running_)
    {

    }
}



void DSeqMidi::CalcTempo()
{
    /*
    #define T4 256
    bpm_ 120
    bps = 120 / 60 = 2
    sec per beat = 1 / bps
    ms per beat = 1000 / bps
    micros per beat = 1000000 / bps

    micros per T4 = 1000000 / bps
    upb = 1000000 / (bpm / 60)
    ticks per T4 = 256
    micros per tick:
    upt = upb / T4
    tick += ((now_us - prev_us) / upt)
    */

    float bps = bpm_ / 60.0f;
    uint64_t upb = 1000000 / bps; // micros per beat (T4)
    upt_ = upb / DT4;
}
