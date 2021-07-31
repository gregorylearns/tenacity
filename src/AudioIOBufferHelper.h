#ifndef AUDIOIO_BUFFER_HELPER_H
#define AUDIOIO_BUFFER_HELPER_H

#include "AudioIO.h"
#include "../libraries/lib-utility/MemoryX.h"

class AudioIOBufferHelper
{

    private:

    unsigned int numPlaybackChannels;
    unsigned long framesPerBuffer;

    public:
    WaveTrack** chans;
    float** tempBufs;

    AudioIOBufferHelper(const unsigned int numPlaybackChannels, const unsigned long framesPerBuffer) {
        this->numPlaybackChannels = numPlaybackChannels;
        this->framesPerBuffer = framesPerBuffer;

        this->chans = safenew WaveTrack * [numPlaybackChannels];
        this->tempBufs = safenew float* [numPlaybackChannels];

        tempBufs[0] = safenew float[(size_t)numPlaybackChannels * framesPerBuffer];

        for (unsigned int c = 1; c < numPlaybackChannels; c++) {
            tempBufs[c] = tempBufs[c - 1] + framesPerBuffer;
        }
    }

    ~AudioIOBufferHelper() {

        delete[] tempBufs[0];

        delete[] tempBufs;

        tempBufs = nullptr;

        delete[] chans;

        chans = nullptr;
    }
};

#endif
