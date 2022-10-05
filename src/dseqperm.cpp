#include "ofUtils.h"
#include "ofMath.h"

#include "dstudio.h"
#include "dseqperm.h"

#include <iostream>
using namespace std;

void DSeqPerm::Init(const Config& config)
{
    bpm_ = config.bpm;
    rep_ = config.rep;
    silence_ = config.silence;
    dmidisong_ = config.dmidisong;
    dmidiseq_ = config.dmidiseq;
    dmidiseq_org_ = dmidiseq_; // make copy that we never permutate
    channels_ = config.channels;
    mixer_ = config.mixer;
    strength_ = config.strength;

    CalcTempo();
}

void DSeqPerm::Start()
{
    for (uint8_t c = 0; c < channels_; c++)
    {
        ticks_[c] = 0;
        queue_note_[c] = 0;
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

    // add all seqs to queue
    for (uint8_t c = 0; c < channels_; c++)
    {
        uint16_t s = dmidisong_[song_step_][c].seq_nr;
        // go through each seq and add to queue
        Permutate(s);
        FillVector(c, s);
    }

    now_us_ = ofGetElapsedTimeMicros();
    prev_us_ = now_us_;
    running_ = true;
}



void DSeqPerm::Stop()
{
    running_ = false;
}


void DSeqPerm::threadedFunction()
{
    while(isThreadRunning())
        Process();
}



void DSeqPerm::Process()
{
    bool song_step_inc_ = false;
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

                if (dmidiseq_[s].size() > 0)
    //            if (dmidisong_[song_step_][c].seq_len > 0)
                {

                    ticks_[c] += ticks_inc;
                    // notes left in seq?
    //                if (note_[c] < dmidiseq_[s].size())
                    if (queue_note_[c] < queue_[c].size())
                    {
                        // while because possibly more events on pos < ticks
    //                    while (ticks_[c] >= dmidiseq_[s][note_[c]].pos)
                        while (ticks_[c] >= (queue_[c][queue_note_[c]].pos * upt_))
                        {
                            uint16_t note = queue_note_[c];
                            uint8_t status = queue_[c][note].status;

                            // add channel and
                            // let dmixer handle midi
                            mixer_->MidiIn((status & MIDI_MESSAGE_MASK) + c,
                                           queue_[c][note].data0,
                                           queue_[c][note].data1);

                            queue_note_[c]++;
                            if (queue_note_[c] >= queue_[c].size())
                            {
                                 break;
                            }
                        }
                    }
                    // sequence length passed
                    if (ticks_[c] >= (dmidisong_[song_step_][c].seq_len * upt_))
                    {
                        // repeat shorter channel sequences
                        queue_note_[c] = 0;
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
                            song_step_inc_ = true;
                            song_step_inc_ticks = ticks_[c];
                        }
                    }

                }

            } // for
            if (song_step_inc_)
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
                    ticks_[c] = song_step_inc_ticks;
                    queue_note_[c] = 0;
                    uint16_t s = dmidisong_[song_step_][c].seq_nr;
                    // go through each seq and add to queue
                    Permutate(s);
                    // silence some channels
                    if (ofRandom(1) > ((strength_ * strength_) / 2.0f))
                    {
                        FillVector(c, s);
                    } else {
                        queue_[c].clear();
                    }
                }

            }
        }
    } // if running_
}



void DSeqPerm::SetBPM(uint8_t bpm)
{
    bpm_ = bpm;
    CalcTempo();

    // TODO: reset anything?
    if (running_)
    {

    }
}



void DSeqPerm::CalcTempo()
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



void DSeqPerm::Permutate(uint16_t seq)
{

    PermutateType permutation = static_cast<PermutateType>((int)ofRandom(100) % PERMUTATE_LAST);

    if (ofRandom(1) < strength_)
    {
        switch (permutation)
        {
        case PERMUTATE_SWAP:
        {
            // swap pitch with other random note
            std::vector<uint16_t> pnotes1, pnotes2;
            // create array of all indexes of notes
            for (uint16_t note = 0; note < dmidiseq_[seq].size(); note++)
            {
                if ((dmidiseq_[seq][note].status & MIDI_MESSAGE_MASK) == MIDI_MESSAGE_NOTEON)
                {
                    pnotes1.push_back(note);
                }
            }
            // randomize order
            pnotes2 = pnotes1;
            std::random_shuffle(pnotes1.begin(), pnotes1.end());
            // copy in new order
            uint16_t psize = pnotes1.size() * strength_;
            for (uint16_t note = 0; note < psize; note++)
            {
                dmidiseq_[seq][pnotes1[note]].data0 = dmidiseq_[seq][pnotes2[note]].data0;
            }
            break;
        }
        case PERMUTATE_RHYTHM:
        {
            // swap length with other random note
            std::vector<uint16_t> pnotes1, pnotes2;
            // create array of all indexes of notes
            for (uint16_t note = 0; note < dmidiseq_[seq].size(); note++)
            {
                if ((dmidiseq_[seq][note].status & MIDI_MESSAGE_MASK) == MIDI_MESSAGE_NOTEON)
                {
                    pnotes1.push_back(note);
                }
            }
            // randomize order
            pnotes2 = pnotes1;
            std::random_shuffle(pnotes1.begin(), pnotes1.end());
            // copy in new order
            uint16_t psize = pnotes1.size() * strength_;
            for (uint16_t note = 0; note < psize; note++)
            {
                dmidiseq_[seq][pnotes1[note]].len = dmidiseq_[seq][pnotes2[note]].len;
            }
            break;
        }

        case PERMUTATE_SIMPLIFY:
        {
            // remove random notes
            for (uint16_t note = 0; note < dmidiseq_[seq].size(); note++)
            {
                if ((dmidiseq_[seq][note].status & MIDI_MESSAGE_MASK) == MIDI_MESSAGE_NOTEON)
                {
                    if (ofRandom(1) < strength_)
                    {
                        // TODO: remove note
                        dmidiseq_[seq][note].status = MIDI_MESSAGE_NOTEOFF;
                    }
                }
            }
            break;
        }

        case PERMUTATE_ADD:
        {
            // find "long" note and split in two
            // or find "rest" and add note in it
            std::vector<uint16_t> pnotes1;
            std::vector<DMidiSeqStepIn> pnotes2;
            // create array of all indexes of notes
            for (uint16_t note = 0; note < dmidiseq_[seq].size(); note++)
            {
                if ((dmidiseq_[seq][note].status & MIDI_MESSAGE_MASK) == MIDI_MESSAGE_NOTEON)
                {
                    if (dmidiseq_[seq][note].len >= DT16)
                    {
                        pnotes1.push_back(note);
                    }
                }
            }
            uint16_t psize = pnotes1.size();
            // uint16_t padd = 0;
            if (psize > 0)
            {
                for (uint16_t note = 0; note < psize; note++)
                {
                    uint64_t len_new = dmidiseq_[seq][pnotes1[note]].len / 2;
                    // halve duration of existing note
                    dmidiseq_[seq][pnotes1[note]].len = len_new;
                    // create new note
                    DMidiSeqStepIn step_new = dmidiseq_[seq][pnotes1[note]];
                    step_new.pos += len_new;
                    step_new.len = len_new;

                    pnotes2.push_back(step_new);
                }
                // append
                if (pnotes2.size() > 0)
                {
                    dmidiseq_[seq].insert(dmidiseq_[seq].end(), pnotes2.begin(), pnotes2.end());
                }
                // sort
                sort(dmidiseq_[seq].begin(),
                     dmidiseq_[seq].end(),
                     [](DMidiSeqStepIn a, DMidiSeqStepIn b) {
                         return a.pos < b.pos;
                     }
                );
            } // if psize > 0
            break;
        }

        case PERMUTATE_SHIFT:
        {
            // determine direction
            // take pitch value from neighbour
            // swap pitch with other random note
            std::vector<uint16_t> pnotes1;
            // create array of all indexes of notes
            for (uint16_t note = 0; note < dmidiseq_[seq].size(); note++)
            {
                if ((dmidiseq_[seq][note].status & MIDI_MESSAGE_MASK) == MIDI_MESSAGE_NOTEON)
                {
                    pnotes1.push_back(note);
                }
            }
            uint16_t psize = pnotes1.size();// * strength_;
            if (psize > 1)
            {
                if (ofRandom(1) > 0.5f)
                {
                    // borrow pitch from left (before)
                    uint8_t saved_pitch = dmidiseq_[seq][pnotes1[psize - 1]].data0;
                    for (uint16_t note = psize - 1; note > 0; note--)
                    {
                        dmidiseq_[seq][pnotes1[note]].data0 = dmidiseq_[seq][pnotes1[note - 1 ]].data0;
                    }
                    dmidiseq_[seq][pnotes1[0]].data0 =  saved_pitch;
                } else {
                    // borrow pitch from right (after)
                    uint8_t saved_pitch = dmidiseq_[seq][pnotes1[0]].data0;
                    for (uint16_t note = 0; note < psize - 1; note++)
                    {
                        dmidiseq_[seq][pnotes1[note]].data0 = dmidiseq_[seq][pnotes1[note + 1 ]].data0;
                    }
                    dmidiseq_[seq][pnotes1[psize - 1]].data0 =  saved_pitch;
                }

            }
            break;
        }

        case PERMUTATE_TRANSPOSE:
        {
            // determine direction
            // accumulate all pitches
            // shift note to a new saved pitch
            // collect pitches
            std::vector<uint16_t> pnotes1;
            for (uint16_t note = 0; note < dmidiseq_[seq].size(); note++)
            {
                if ((dmidiseq_[seq][note].status & MIDI_MESSAGE_MASK) == MIDI_MESSAGE_NOTEON)
                {
                    pnotes1.push_back(dmidiseq_[seq][note].data0);
                }
            }
            uint16_t psize = pnotes1.size();// * strength_;
            if (psize > 1)
            {
                // assign new pitch from another random note
                for (uint16_t note = 0; note < dmidiseq_[seq].size(); note++)
                {
                    if ((dmidiseq_[seq][note].status & MIDI_MESSAGE_MASK) == MIDI_MESSAGE_NOTEON)
                    {
                        uint16_t note2 = (uint16_t)ofRandom(psize);
                        dmidiseq_[seq][note].data0 = pnotes1[note2];
                    }
                }
            }
            break;
        }

        case PERMUTATE_ORIGINAL:
            // revert to original sequence
            // TODO: restore dep on strength
            dmidiseq_[seq] = dmidiseq_org_[seq];
            break;

        default:
            break;
        }
    }
}



void DSeqPerm::FillVector(uint8_t channel, uint16_t seq)
{
    // clear vector
    queue_[channel].clear();

    // add midi on and off events
    for (uint16_t note = 0; note < dmidiseq_[seq].size(); note++)
    {
        DMidiSeqStep step;
        step.pos = dmidiseq_[seq][note].pos;
        step.status = dmidiseq_[seq][note].status;
        step.data0 = dmidiseq_[seq][note].data0;
        step.data1 = dmidiseq_[seq][note].data1;

        if ((step.status & MIDI_MESSAGE_MASK) == MIDI_MESSAGE_NOTEON)
        {
            queue_[channel].push_back(step);
            // add NOTE OFF event
            step.pos  += dmidiseq_[seq][note].len;
            step.status = MIDI_MESSAGE_NOTEOFF;
            step.data1 = DVOFF;
            queue_[channel].push_back(step);
        } else {
            queue_[channel].push_back(step);
        }
    }

    // sort
    sort(queue_[channel].begin(),
         queue_[channel].end(),
         [](DMidiSeqStep a, DMidiSeqStep b) {
             return a.pos < b.pos;
         }
     );
}
