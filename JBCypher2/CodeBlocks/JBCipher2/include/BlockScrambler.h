#ifndef BLOCKSCRAMBLER_H
#define BLOCKSCRAMBLER_H

#include <array>
#include "IRandomSource.h"

class BlockScrambler
{
    public:
        BlockScrambler() = delete;
        BlockScrambler(const BlockScrambler& none) = delete;
        BlockScrambler(IRandomSource& rngIn);
        virtual ~BlockScrambler();
        void passData(unsigned char* in);
        void process();
        BlockScrambler operator=(const BlockScrambler& none) = delete;
    protected:
    private:
        unsigned char* data;
        IRandomSource* rng;
        void shuffleBytes();
        void shuffleBits();
        void shuffleChunks();
        void randomizeBytes();
};

#endif // BLOCKSCRAMBLER_H
