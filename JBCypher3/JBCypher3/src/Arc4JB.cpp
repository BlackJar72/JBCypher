#include "Arc4JB.h"

/**
 * This is a slight variation of the Arc4 (aka, RC4(tm)) random
 * number generator created by Ron Rivest for stream encryption.
 * It differs in that the variable i is set by a simpler RNG
 * (a xorshift variant) rather than simply incrementing.
 */

Arc4JB::Arc4JB() : bank(), seed(0), i(0), j(0), k(0) {}

Arc4JB::~Arc4JB() {}


unsigned long long stringHash(const std::string &s) {
    unsigned long long out = 0;
    unsigned int i = 0;
    const char* data = s.c_str();
    while(data[i] != 0) {
        out ^= (((long long)data[i]) << (8 * (i % 8)));
        out ^=  (out << 13);
        out ^=  (out >> 5);
        out ^=  (out << 17);
        i++;
    }
    return out;
}


unsigned long long stringHash(char* data) {
    unsigned long long out = 0;
    unsigned int i = 0;
    while(data[i] != 0) {
        out ^= (((long long)data[i]) << (8 * (i % 8)));
        out ^=  (out << 13);
        out ^=  (out >> 5);
        out ^=  (out << 17);
        i++;
    }
    return out;
}

inline int modRight(int n, int m) {
    return (n & 0x7fffffff) % m;
    //int out = n % m;
    //if(out < 0) {
    //    out += m;
    //}
    //return out;
}


unsigned char Arc4JB::nextByte() {
    unsigned char tmp;
	i = innerRandom();
	j = (j + bank[i]) % 256;
	k = (bank[i] + bank[j]) % 256;
	tmp = bank[i];
	bank[i] = bank[j];
	bank[j] = tmp;
	return k;
}


void Arc4JB::initFromString(char* s) {
    seed = stringHash(s);
    std::string str(s);
	for(int i = 0; i < 256; i++) {
		bank[i] = (unsigned char)i;
	}
	int j = 0;
	int tmp = 0;
	for(int i = 0; i < 256; i++) {
		j = modRight((j + bank[i] + str[i % str.size()]), 256);
		tmp = bank[i];
		bank[i] = bank[j];
		bank[j] = tmp;
	}
}


void Arc4JB::initFromString(const std::string& s) {
    seed = stringHash(s);
	for(int i = 0; i < 256; i++) {
		bank[i] = (unsigned char)i;
	}
	int j = 0;
	int tmp = 0;
	for(int i = 0; i < 256; i++) {
		j = modRight((j + bank[i] + s[i % s.size()]), 256);
		tmp = bank[i];
		bank[i] = bank[j];
		bank[j] = tmp;
	}
}


unsigned char Arc4JB::innerRandom() {
    seed *= 5443;
    seed += 1548586312338621L;
    seed ^= seed >> 19;
    seed ^= seed << 31;
    seed ^= seed >> 23;
    seed ^= seed << 7;
    return (unsigned char)((seed >> (((seed >> 8) & 0x1f) + 16)) & 0xff);
}

