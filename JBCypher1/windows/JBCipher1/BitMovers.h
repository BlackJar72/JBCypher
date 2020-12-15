#ifndef BITMOVERS_INCLUDED
#define BITMOVERS_INCLUDED

#include <bitset>
#include <iostream>

inline void swapBitsInBytes(unsigned char& a, unsigned char& b, int bit) {
    unsigned char mask = 1 << bit;
    unsigned char c = a & mask;
    a &= ~mask;
    a |= (b & mask);
    b &= ~mask;
    b |= c;
}

inline void lRotateBits(unsigned char in, unsigned char by) {
    by &= 0x7;
    unsigned char tmp = in >> (8 - by);
    in <<= by;
    in |= tmp;
}

inline void rRotateBits(unsigned char in, unsigned char by) {
    by &= 0x7;
    unsigned char tmp = in << (8 - by);
    in >>= by;
    in |= tmp;
}

#endif // BITMOVERS_INCLUDED
