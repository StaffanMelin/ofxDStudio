#include "ofUtils.h"
#include "ofMath.h"

#include "dstudio.h"
#include "dgen.h"
#include "dseq.h"

#include <iostream>
using namespace std;



// DGenDrone

void DGenDrone::Init(const Config& config)
{
    bpm_ = config.bpm;
    channels_ = config.channels;
    child_ = config.child;

//    DGenLFO::Config lfo_config;

    for (uint8_t i = 0; i < channels_; i++)
    {
        channel_type_[i] = config.channel_type[i];
        drama_fade_[i] = config.drama_fade[i];
        level_[i] = config.level[i];
    }

    note_base_ = config.note_base;
    note_pad_ = config.note_pad;
    note_arp_ = config.note_arp;
    note_melody_ = config.note_melody;

    note_pad_len_ = note_pad_.size();
    note_arp_len_ = note_arp_.size();
    note_melody_len_ = note_melody_.size();

    CalcTempo();
}



void DGenDrone::Start()
{
    now_us_ = ofGetElapsedTimeMicros();
    prev_us_ = now_us_;

    running_ = true;
    drama_ = VERSE;
    drama_start_ = ticks_[0];
    drama_end_ = ticks_[0] + (DRAMA_MIN_LEN + ofRandom(DRAMA_MAX_LEN - DRAMA_MIN_LEN)) * DT1 * upt_;
    drama_ticks_ = ticks_[0];

    for (uint8_t c = 0; c < channels_; c++)
    {
        ticks_[c] = 0;
        queue_note_[c] = 0;

        NoteCreate(c);
    }


}



void DGenDrone::Stop()
{
    running_ = false;
    child_->Silence();
}



void DGenDrone::threadedFunction()
{
    while (isThreadRunning())
        Process();
}



void DGenDrone::Process()
{
    if (running_)
    {
        now_us_ = ofGetElapsedTimeMicros();

        uint64_t ticks_inc = now_us_ - prev_us_;

        if (ticks_inc > DSEQRESOLUTION)
        {

            // drama
            drama_ticks_ += ticks_inc;

            // drama change? enough time passed for drama change?
            if (drama_ticks_ > drama_end_)
            {
                drama_start_ = drama_end_;

                // what new drama state should we move to
                // 60 30 10
                float dice = ofRandom(1);
                if (dice < 0.6f)
                {
                    drama_ = drama_order_[drama_][0];
                } else if (dice < 0.9f) {
                    drama_ = drama_order_[drama_][1];
                } else {
                    drama_ = drama_order_[drama_][2];
                }

                uint64_t drama_add = (DRAMA_MIN_LEN + ofRandom(DRAMA_MAX_LEN - DRAMA_MIN_LEN)) * DT1 * upt_;
                drama_end_ += drama_add;

                cout << "DRAMA " << unsigned(drama_) << " length: " << (drama_add / upt_ / DT1) << endl;
            }

            // process channels

            prev_us_ = now_us_;

            float drama_fraction =
                    (float)(drama_ticks_ - drama_start_) /
                    (drama_end_ - drama_start_);

            for (uint8_t c = 0; c < channels_; c++)
            {
                ticks_[c] += ticks_inc;

                // process fade in/out

                if (drama_fade_[c] > 0.0f)
                {
                    if (drama_fraction < drama_fade_[c])
                    {
                        // fade in
                        float fade_fraction =
                                drama_fraction / drama_fade_[c];
                        child_->MidiIn(MIDI_MESSAGE_CC + c,
                                       MIDI_CC_VOLUME,
                                       MIDI_DATA_MAX * level_[c] * fade_fraction);
                    } else if (drama_fraction > (1 - drama_fade_[c])) {
                        // fade out
                        float fade_fraction =
                                (1 - drama_fraction) / drama_fade_[c];
                        child_->MidiIn(MIDI_MESSAGE_CC + c,
                                       MIDI_CC_VOLUME,
                                       MIDI_DATA_MAX * level_[c] * fade_fraction);
                    } else {
                        // original level
                        child_->MidiIn(MIDI_MESSAGE_CC + c,
                                       MIDI_CC_VOLUME,
                                       MIDI_DATA_MAX * level_[c]);
                    }
                }

                // process notes

                // notes left in seq?
                size_t notes = queue_[c].size();
                if (notes > 0)
                {
                    // while because possibly more events on pos < ticks
                    uint16_t note = notes - 1;
                    while (ticks_[c] >= (queue_[c][note].pos))
                    {
                        uint8_t status = queue_[c][note].status;
                        uint8_t pitch = queue_[c][note].data0;

                        if (pitch != DREST)
                        {
                            // add channel and
                            // let dmixer handle midi
                            child_->MidiIn((status & MIDI_MESSAGE_MASK) + c,
                                           pitch,
                                           queue_[c][note].data1);
                        } else {
                            // rest
                        }

                        queue_[c].pop_back();
                        if (note == 0)
                        {
                            break;
                        } else {
                            note--;
                        }
                    }
                } else {
                    // create and queue new notes
                    NoteCreate(c);
                }

            } // for
        } // if
    } // if running_
}



void DGenDrone::SetBPM(uint8_t bpm)
{
    bpm_ = bpm;
    CalcTempo();

    // TODO: reset anything?
    if (running_)
    {

    }
}



void DGenDrone::CalcTempo()
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



// c = channel
void DGenDrone::NoteCreate(uint8_t c)
{

    switch (channel_type_[c])
    {

        case BASS:
        {
            switch (drama_)
            {
                case DGenDrone::INTRO:
                {
                    break;
                }
                case DGenDrone::VERSE:
                case DGenDrone::CHORUS:
                {
                    // always on; long
                    // base note or 3rd or 5th
                    float dice = ofRandom(1);
                    uint64_t length = ofRandom(10) * DT1 * upt_;
                    uint8_t velocity = 60 + ofRandom(40);
                    if (dice < .6f)
                    {
                        NoteQueue(c, ticks_[c], note_base_[c], velocity, length);
                        // base note
                    } else if (dice < .8f) {
                        // 3rd
                        if (note_pad_len_ > 1)
                        {
                            NoteQueue(c, ticks_[c], note_base_[c] + note_pad_[1], velocity, length);
                        }
                    } else {
                        // 5th
                        if (note_pad_len_ > 2)
                        {
                            NoteQueue(c, ticks_[c], note_base_[c] + note_pad_[2], velocity, length);
                        }
                    }
                    break;
                }
                case DGenDrone::BREAK:
                {
                    break;
                }
                case DGenDrone::OUTRO:
                {
                    break;
                }
            } // switch drama
            break;
        } // case BASS

        case TREBLE:
        {
            switch (drama_)
            {
                case DGenDrone::INTRO:
                {
                    float dice = ofRandom(1);
                    uint64_t length = ofRandom(1) * 10 *  DT4 * upt_;
                    if (dice > 0.2f)
                    {
                        uint8_t velocity = 57 + ofRandom(30);
                        NoteQueue(c, ticks_[c], note_base_[c] + note_pad_[int(ofRandom(4))], velocity, length);

                    } else {
                        // queue a pause
                        NoteQueue(c, ticks_[c], DREST, 0, length);
                    }
                    break;
                }
                case DGenDrone::VERSE:
                {
                    float dice = ofRandom(1);
                    uint64_t length = ofRandom(1) * 10 *  DT4 * upt_;
                    if (dice > 0.4f)
                    {
                        uint8_t velocity = 57 + ofRandom(60);
                        NoteQueue(c, ticks_[c], note_base_[c] + note_pad_[int(ofRandom(4))], velocity, length);
                        // sometimes add 2nd note
                        dice = ofRandom(1);
                        if (dice > 0.9f)
                        {
                            // uint64_t length = ofRandom(1) * 10 *  DT4 * upt_;
                            uint8_t velocity = 57 + ofRandom(70);
                            NoteQueue(c, ticks_[c], note_base_[c] + note_pad_[int(ofRandom(4))], velocity, length);
                        }
                        // queue a pause
                        // NoteQueue(c, ticks_[c]+length, DREST, 0, length*2);
                    } else {
                        // queue a pause
                        NoteQueue(c, ticks_[c], DREST, 0, length);
                    }
                    break;
                }
                case DGenDrone::CHORUS:
                {
                    float dice = ofRandom(1);
                    uint64_t length = ofRandom(1) * 6 *  DT4 * upt_;
                    if (dice > 0.2f)
                    {
                        uint8_t velocity = 57 + ofRandom(60);
                        NoteQueue(c, ticks_[c], note_base_[c] + note_pad_[int(ofRandom(4))], velocity, length);
                        // sometimes add 2nd note
                        dice = ofRandom(1);
                        if (dice > 0.3f)
                        {
                            // uint64_t length = ofRandom(1) * 10 *  DT4 * upt_;
                            uint8_t velocity = 57 + ofRandom(70);
                            NoteQueue(c, ticks_[c], note_base_[c] + note_pad_[int(ofRandom(4))], velocity, length);
                        }
                        // queue a pause
                        // NoteQueue(c, ticks_[c]+length, DREST, 0, length*2);
                    } else {
                        // queue a pause
                        NoteQueue(c, ticks_[c], DREST, 0, length);
                    }
                    break;
                }
                case DGenDrone::BREAK:
                {
                    break;
                }
                case DGenDrone::OUTRO:
                {
                    uint64_t length = ofRandom(1) * 10 *  DT4 * upt_;
                    uint8_t velocity = 57 + ofRandom(30);
                    NoteQueue(c, ticks_[c], note_base_[c] + note_pad_[int(ofRandom(4))], velocity, length);
                    break;
                }
            } // switch (DRAMA)
            break;
        } // case TREBLE

        case PAD:
        {
            switch (drama_)
            {
                case DGenDrone::INTRO:
                {
                    break;
                }
                case DGenDrone::VERSE:
                {
                    float dice;
                    uint64_t length;
                    for (int n = 0; n < note_pad_len_; n++)
                    {
                        dice = ofRandom(1);
                        length = ofRandom(1) * 10 *  DT4 * upt_;
                        if (dice > 0.3f)
                        {
                            uint8_t velocity = 57 + ofRandom(40);
                            NoteQueue(c, ticks_[c], note_base_[c] + note_pad_[n], velocity, length);
                        } else {
                            // queue a rest
                            NoteQueue(c, ticks_[c], DREST, 0, length);
                        }
                    }
                    break;
                }
                case DGenDrone::CHORUS:
                {
                    float dice;
                    uint64_t length;
                    for (int n = 0; n < note_pad_len_; n++)
                    {
                        dice = ofRandom(1);
                        length = ofRandom(1) * 10 *  DT4 * upt_;
                        if (dice > 0.1f)
                        {
                            uint8_t velocity = 57 + ofRandom(70);
                            NoteQueue(c, ticks_[c], note_base_[c] + 12 + note_pad_[n], velocity, length);
                        } else {
                            // queue a rest
                            NoteQueue(c, ticks_[c], DREST, 0, length);
                        }
                    }
                    break;
                }
                case DGenDrone::BREAK:
                {
                    break;
                }
                case DGenDrone::OUTRO:
                {
                    float dice;
                    uint64_t length;
                    for (int n = 0; n < note_pad_len_; n++)
                    {
                        dice = ofRandom(1);
                        length = ofRandom(1) * 10 *  DT4 * upt_;
                        if (dice > 0.1f)
                        {
                            uint8_t velocity = 57 + ofRandom(40);
                            NoteQueue(c, ticks_[c], note_base_[c] + note_pad_[n], velocity, length);
                        } else {
                            // queue a rest
                            NoteQueue(c, ticks_[c], DREST, 0, length);
                        }
                    }
                    break;
                }
            } // switch drama
            break;
        } // case PAD

        case MELODY:
        {
            float dice;
            uint64_t length;

            switch (drama_)
            {
                case DGenDrone::INTRO:
                {
                    // sometimes 1-3 slow notes from melody
                    dice = ofRandom(1);
                    length = (1 + ofRandom(1)) * 5 * DT4 * upt_;
                    if (dice > 0.8f)
                    {
                        dice = 1 + ofRandom(5);
                        uint8_t velocity = 57 + ofRandom(70);
                        for (uint8_t n = 0; n < dice; n++)
                        {
                            uint8_t m = int(ofRandom(note_melody_len_));
                            NoteQueue(c, ticks_[c], note_base_[c] + note_melody_[m], velocity, length);
                        }

                    } else {
                        // queue a rest
                        NoteQueue(c, ticks_[c], DREST, 0, length);
                    }
                    break;
                }
                case DGenDrone::VERSE:
                {
                    dice = ofRandom(1);
                    length = (1 + ofRandom(1)) * 4 *  DT4 * upt_;
                    if (dice > 0.2f)
                    {
                        dice = 2 + ofRandom(note_melody_len_);
                        if (dice > note_melody_len_)
                        {
                            dice = note_melody_len_;
                        }
                        uint8_t velocity = 57 + ofRandom(70);
                        for (uint8_t n = 0; n < dice; n++)
                        {
                            NoteQueue(c, ticks_[c] + n * length, note_base_[c] + note_melody_[n], velocity, length);
                        }
                    } else {
                        // queue a rest
                        NoteQueue(c, ticks_[c], DREST, 0, length);
                    }
                    break;
                }
                case DGenDrone::CHORUS:
                {
                    dice = ofRandom(1);
                    length = (1 + ofRandom(1)) * 2 *  DT4 * upt_;
                    if (dice > 0.1f)
                    {
                        dice = note_melody_len_;
                        uint8_t velocity = 57 + ofRandom(70);
                        for (uint8_t n = 0; n < dice; n++)
                        {
                            NoteQueue(c, ticks_[c], note_base_[c] + 12 + note_melody_[n], velocity, length);
                        }
                    } else {
                        // queue a rest
                        NoteQueue(c, ticks_[c], DREST, 0, length);
                    }
                    break;
                }
                case DGenDrone::BREAK:
                {
                    dice = ofRandom(1);
                    length = (2 + ofRandom(1)) * 2 *  DT4 * upt_;
                    if (dice > 0.5f)
                    {
                        dice = note_melody_len_;
                        uint8_t velocity = 57 + ofRandom(40);
                        for (uint8_t n = 0; n < dice; n++)
                        {
                            NoteQueue(c, ticks_[c], note_base_[c] + 12 + note_melody_[n], velocity, length);
                        }
                    } else {
                        // queue a rest
                        NoteQueue(c, ticks_[c], DREST, 0, length);
                    }
                    break;
                }
                case DGenDrone::OUTRO:
                {
                    break;
                }
            } // switch drama
            break;
        } // case MELODY

        case ARPEGGIO:
        {
            switch (drama_)
            {
                case DGenDrone::INTRO:
                {
                    break;
                }
                case DGenDrone::VERSE:
                {
                    // arp
                    uint64_t length = DT16 * upt_;
                    uint8_t velocity = 80;
                    for (uint8_t m = 0; m < note_arp_len_; m++)
                    {
                        NoteQueue(c, ticks_[c] + length * (2 * m), note_base_[c] + note_arp_[m], velocity, length);
                        NoteQueue(c, ticks_[c] + length * (2 * m + 1), DREST, velocity, length);
                    }
                    break;
                }
                case DGenDrone::CHORUS:
                {
                    break;
                }
                case DGenDrone::BREAK:
                {
                    // arp
                    uint64_t length = DT8 * upt_;
                    uint8_t velocity = 80;
                    for (uint8_t m = 0; m < note_arp_len_; m++)
                    {
                        NoteQueue(c, ticks_[c] + length * (2 * m), note_base_[c] + note_arp_[m], velocity, length);
                        NoteQueue(c, ticks_[c] + length * (2 * m + 1), DREST, velocity, length);
                    }
                    break;
                }
                case DGenDrone::OUTRO:
                {
                    break;
                }
                break;
            } // switch (drama_)
            break;
        } // case ARPEGGIO

        case EMBELLISH:
        {
            switch (drama_)
            {
                case DGenDrone::INTRO:
                {
                    break;
                }
                case DGenDrone::VERSE:
                case DGenDrone::BREAK:
                case DGenDrone::OUTRO:
                {
                    uint8_t m = 0;
                    if (ofRandom(1) > 0.3f)
                    {
                        // pling of random length from melody
                        float dice;
                        uint64_t length = DT16 * upt_;
                        dice = ofRandom(1) * note_melody_len_ / 2;
                        uint8_t velocity = 80;
                        for (uint8_t n = 0; n < dice; n++)
                        {
                            NoteQueue(c, ticks_[c] + length * m, note_base_[c] + note_melody_[n], velocity, length);
                            m++;
                            if (ofRandom(1) > 0.7)
                            {
                                NoteQueue(c, ticks_[c] + length * m, DREST, velocity, length);
                                m++;
                            }
                        }
                    }
                    // queue a pause
                    uint64_t length = DT1 * upt_ * ofRandom(3);
                    NoteQueue(c, ticks_[c] + length * m , DREST, 0, length);
                    break;
                }
                case DGenDrone::CHORUS:
                {
                    break;
                }
            } // switch (DRAMA)
            break;
        } // case EMBELLISH

    }

    // sort so last element is closest in time
    // and ready to be popped
    sort(queue_[c].begin(),
         queue_[c].end(),
         [](DMidiSeqStep a, DMidiSeqStep b) {
             return a.pos > b.pos;
         }
     );

    queue_note_[c] = 0;
}



void DGenDrone::NoteQueue(uint8_t c, uint64_t tick, uint8_t pitch, uint8_t velocity, uint64_t length)
{
    DMidiSeqStep step;
    // cout << "queued " << unsigned(c) << " tick " << tick << " " << pitch << endl;
    // add NOTE ON event
    step.pos = tick;
    step.status = MIDI_MESSAGE_NOTEON + c;
    step.data0 = pitch;
    step.data1 = velocity;
    queue_[c].push_back(step);
    // add NOTE OFF event
    step.pos  += length;
    step.status = MIDI_MESSAGE_NOTEOFF + c;
    step.data1 = DVOFF;
    queue_[c].push_back(step);
}
