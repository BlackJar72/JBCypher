#include "BlockScrambler.h"
#include "BitMovers.h"

#include <iostream>

using namespace jbcipher2;

BlockScrambler::BlockScrambler(IRandomSource& rngIn) : data(new unsigned char[256]), rng(&rngIn) {}


BlockScrambler::~BlockScrambler() {}


void BlockScrambler::passData(unsigned char* in) {
    data = in;
}


void BlockScrambler::process() {
    shuffleBytes();
    shuffleBits();
    shuffleChunks();
    randomizeBytes();
}


void BlockScrambler::shuffleBytes() {
    unsigned char tmp, loc;
    for(int i = 0; i < 256; i++) {
        loc = rng->nextByte();
        tmp = data[i];
        data[i] = data[loc];
        data[loc] = tmp;
    }
}


void BlockScrambler::shuffleBits() {
    for(int i = 0; i < 256; i++)
        for(int j = 0; j < 8; j++) {
            swapBitsInBytes(data[i], data[rng->nextByte()], j);
    }
}


void BlockScrambler::shuffleChunks() {
    for(int i = 0; i < 256; i++) {
        lRotateBits(data[i], rng->nextByte());
    }
}


void BlockScrambler::randomizeBytes() {
    for(int i = 0; i < 256; i++) {
        data[i] ^= rng->nextByte();
    }
    unsigned char loc;
    for(int i = 0; i < 256; i++) {
        loc = rng->nextByte();
        if(loc != i) {
            data[i] ^= data[loc];
        }
    }
}

