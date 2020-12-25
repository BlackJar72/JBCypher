#ifndef BLOCKDESCRAMBLER_H
#define BLOCKDESCRAMBLER_H

#include <array>
#include "IRandomSource.h"

const unsigned int DS_NEEDED_BYTES = 256 * 16;


class BlockDescrambler
{
    public:
        BlockDescrambler() = delete;
        BlockDescrambler(const BlockDescrambler& none) = delete;
        BlockDescrambler(IRandomSource& rngIn);
        virtual ~BlockDescrambler();
        void passData(unsigned char* in);
        void process();
        BlockDescrambler operator=(const BlockDescrambler none) = delete;
    protected:
    private:
        std::array<char, DS_NEEDED_BYTES>* bytes;
        unsigned char* data;
        IRandomSource* rng;
        int index;
        void restoreBytes();
        void restoreBits();
        void restoreChunks();
        void derandomizeBytes();
};

#endif // BLOCKDESCRAMBLER_H
