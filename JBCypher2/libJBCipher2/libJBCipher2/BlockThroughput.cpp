#include "stdafx.h"
#include "JBCipher2.h"
#include "BlockScrambler.h"
#include "BlockDescrambler.h"
#include "Arc4JB.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


using namespace std;
using namespace jbcipher2;

BlockThroughput::BlockThroughput(std::string key, char mode)
            : buffer(new unsigned char[256]), buf2(queue<unsigned char>()), bptr(0),
              count(0), dataSize(255), rng(new Arc4JB()), decrypting(mode == 'd'), ownRng(true) {
    rng->initFromString(key);
    for(int i = 0; i < 256; i++) {
        buffer[i] = 0;
    }
    if(decrypting) dataSize++;
}


BlockThroughput::BlockThroughput(IRandomSource* random, char mode)
            : buffer(new unsigned char[256]), buf2(queue<unsigned char>()), bptr(0),
              count(0), dataSize(255), rng(random), decrypting(mode == 'd'), ownRng(false) {
    for(int i = 0; i < 256; i++) {
        buffer[i] = 0;
    }
    if(decrypting) dataSize++;
}



BlockThroughput::~BlockThroughput() {
	delete[] buffer;
	if(ownRng) delete rng;
}


void BlockThroughput::encrypt() {
	BlockScrambler cipher(*rng);
	cipher.passData(buffer);
	cipher.process();
}


void BlockThroughput::decrypt() {
	BlockDescrambler cipher(*rng);
	cipher.passData(buffer);
	cipher.process();
}



void BlockThroughput::process() {
    if(decrypting) {
        decrypt();
        for(int i = 0; i < buffer[255]; i++) {
            buf2.push(buffer[i]);
        }
    } else {
        buffer[255] = bptr;
        encrypt();
        for(int i = 0; i < 256; i++) {
            buf2.push(buffer[i]);
        }
    }
    reset();
}


// Feeding data in

void BlockThroughput::writeByte(unsigned char byte) {
    buffer[bptr++] =  byte;
    if(bptr >= dataSize) process();
}


void BlockThroughput::writeByte(char byte) {
    buffer[bptr++] =  *reinterpret_cast<const unsigned char*>(&byte);
    if(bptr >= dataSize) process();
}


void BlockThroughput::writeBytes(const char* bytes, size_t n) {
	for (size_t i = 0; i < n; i++) {
		buffer[bptr++] = reinterpret_cast<const unsigned char*>(bytes)[i];
        if(bptr >= dataSize) process();
	}
}


void BlockThroughput::writeBytes(const unsigned char* bytes, size_t n) {
	for (size_t i = 0; i < n; i++) {
		buffer[bptr++] = bytes[i];
        if(bptr >= dataSize) process();
	}
}


void BlockThroughput::writeBytes(const std::vector<char>& bytes) {
	for (unsigned char c : bytes) {
		buffer[bptr++] = *reinterpret_cast<const unsigned char*>(&c);
        if(bptr >= dataSize) process();
	}
}


void BlockThroughput::writeBytes(const std::vector<unsigned char>& bytes) {
	for (unsigned char c : bytes) {
		buffer[bptr++] = c;
        if(bptr >= dataSize) process();
	}
}


// Getting data out

unsigned char BlockThroughput::readByte() {
    if(!buf2.empty()) {
        unsigned char out = buf2.front();
        buf2.pop();
        count = 1;
        return out;
    } else {
        count = 0;
        return 0;
    }
}


void BlockThroughput::readBytes(char* bytes, size_t n) {
    size_t i;
	for(i = 0; (i < n) && ! buf2.empty(); i++) {
        bytes[i] = *reinterpret_cast<const char*>(&(buf2.front()));
        buf2.pop();
	}
	count = i;
}


void BlockThroughput::readBytes(unsigned char* bytes, size_t n) {
    size_t i;
	for (i = 0; (i < n) && ! buf2.empty(); i++) {
        bytes[i] = buf2.front();
        buf2.pop();
	}
	count = i;
}


void BlockThroughput::readBytes(std::vector<char>& bytes, size_t n) {
    size_t i;
	for (i = 0; (i < n) && ! buf2.empty(); i++) {
        bytes.push_back(*reinterpret_cast<const char*>(&(buf2.front())));
        buf2.pop();
	}
	count = i;
}


void BlockThroughput::readBytes(std::vector<unsigned char>& bytes, size_t n) {
    size_t i;
	for (i = 0; (i < n) && ! buf2.empty(); i++) {
        bytes.push_back(buf2.front());
        buf2.pop();
	}
	count = i;
}


void BlockThroughput::readBytes(std::vector<char>& bytes) {
    count = 0;
	while(!buf2.empty()) {
        bytes.push_back(*reinterpret_cast<char*>(&(buf2.front())));
        buf2.pop();
        count++;
	}
}


void BlockThroughput::readBytes(std::vector<unsigned char>& bytes) {
    count = 0;
	while(!buf2.empty()) {
        bytes.push_back(buf2.front());
        buf2.pop();
        count++;
	}
}


// Information and control methods (e.g., empty())

bool BlockThroughput::empty() const {
    return buf2.empty() && !bptr;
}


bool BlockThroughput::ready() const {
    return !buf2.empty();
}


size_t BlockThroughput::bytesQueued() {
    return buf2.size();
}


size_t BlockThroughput::bytesBuffered() {
    return bptr;
}


void BlockThroughput::reset() {
	bptr = 0;
}


void BlockThroughput::flush() {
	if(bptr) process();
}


size_t BlockThroughput::gcount() {
    return count;
}

