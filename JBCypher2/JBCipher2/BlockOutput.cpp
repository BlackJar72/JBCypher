#include "stdafx.h"
#include "BlockOutput.h"
#include "BlockScrambler.h"
#include "BlockDescrambler.h"
#include "Arc4JB.h"

#include <iostream>

using namespace std;
using namespace jbcipher2;

BlockOutput::BlockOutput(std::string key, std::ostream* out, char mode)
			: buffer(new unsigned char[256]), bptr(0), rng(new Arc4JB()),
			  out(out), decrypting(mode == 'd'), readsize(jbcipher2::BS_DATA), ownRng(1) {
	rng->initFromString(key);
	for (int i = 0; i < 256; i++) {
		buffer[i] = 0;
	}
	if (decrypting) readsize++;
}


BlockOutput::BlockOutput(std::ostream* out, IRandomSource* random, char mode)
			: buffer(new unsigned char[256]), bptr(0), rng(random),
			  out(out), decrypting(mode == 'd'), readsize(jbcipher2::BS_DATA), ownRng(0) {
	for (int i = 0; i < 256; i++) {
		buffer[i] = 0;
	}
	if (decrypting) readsize++;
}


BlockOutput:: ~BlockOutput() { 
	flush(); 
	delete[] buffer;
	if(ownRng) delete rng; 
}


void BlockOutput::writeByte(char byte) {
	buffer[bptr++] = byte;
	if (bptr >= readsize) {
		writeout();
	}
}


void BlockOutput::writeByte(unsigned char byte) {
	buffer[bptr++] = byte;
	if (bptr >= readsize) {
		writeout();
	}
}


void BlockOutput::writeBytes(const unsigned char* bytes, size_t n) {
	for (size_t i = 0; i < n; i++) {
		buffer[bptr++] = bytes[i];
		if (bptr >= readsize) {
			writeout();
		}
	}
}


void BlockOutput::writeBytes(const char* bytes, size_t n) {
	for (size_t i = 0; i < n; i++) {
		buffer[bptr++] = bytes[i];
		if (bptr >= readsize) {
			writeout();
		}
	}
}


void BlockOutput::writeBytes(const vector<char>& bytes) {
	for (char c : bytes) {
		buffer[bptr++] = c;
		if (bptr >= readsize) {
			writeout();
		}
	}
}


void BlockOutput::writeBytes(const vector<unsigned char>& bytes) {
	for (unsigned char c : bytes) {
		buffer[bptr++] = c;
		if (bptr >= readsize) {
			writeout();
		}
	}
}


void BlockOutput::flush() {
	if(bptr) writeout();
}


void BlockOutput::encrypt() {
	BlockScrambler cipher(*rng);
	cipher.passData(buffer);
	cipher.process();
}


void BlockOutput::decrypt() {
	BlockDescrambler cipher(*rng);
	cipher.passData(buffer);
	cipher.process();
}


void BlockOutput::writeout() {
	if(decrypting) {
		decrypt();
		out->write((char*)buffer, buffer[jbcipher2::BS_DATA]);
	}
	else {
		buffer[jbcipher2::BS_DATA] = bptr;
		encrypt();
		out->write((char*)buffer, jbcipher2::BS_BYTES);
	}
	reset();
}


void BlockOutput::reset() {
	bptr = 0;
}
