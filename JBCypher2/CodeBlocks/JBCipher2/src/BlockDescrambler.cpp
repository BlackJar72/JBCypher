#include "BlockDescrambler.h"
#include "BitMovers.h"

#include <iostream>

BlockDescrambler::BlockDescrambler(IRandomSource& rngIn) :
            bytes(new std::array<char, DS_NEEDED_BYTES>()), data(0), rng(&rngIn), index(0) {}


BlockDescrambler::~BlockDescrambler()
{
    delete bytes;
}


void BlockDescrambler::passData(unsigned char* in) {
    data = in;
    index = DS_NEEDED_BYTES;
    for(int i = 0; i < index; i++) {
        (*bytes)[i] = rng->nextByte();
    }
}


void BlockDescrambler::process() {
    derandomizeBytes();
    restoreChunks();
    restoreBits();
    restoreBytes();
}


void BlockDescrambler::restoreBytes() {
    unsigned char tmp, loc;
    for(int i = 255; i > -1; i--) {
        loc = (*bytes)[--index];
        tmp = data[i];
        data[i] = data[loc];
        data[loc] = tmp;
    }
}


void BlockDescrambler::restoreBits() {
    unsigned char loc;
    for(int i = 255; i > -1; i--)
        for(int j = 7; j > -1; j--) {
            loc = (*bytes)[--index];
            swapBitsInBytes(data[i], data[loc], j);
    }
}


void BlockDescrambler::restoreChunks() {
    for(int i = 255; i > -1; i--) {
        rRotateBits(data[i], (*bytes)[--index]);
    }
}


void BlockDescrambler::derandomizeBytes() {
    unsigned char loc;
    for(int i = 255; i > -1; i--) {
        loc = (*bytes)[--index];
        if(loc != i) {
            data[i] ^= data[loc];
        }
    }
    for(int i = 255; i > -1; i--) {
        data[i] ^= (*bytes)[--index];
    }
}

