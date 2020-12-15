#include "BlockInput.h"
#include "BlockScrambler.h"
#include "BlockDescrambler.h"
#include "Arc4JB.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

using namespace std;


BlockInput::BlockInput(std::string key, std::istream* in, char mode)
			: buffer(new unsigned char[256]), buf2(queue<unsigned char>()), count(0), rng(new Arc4JB()),
			  instream(in), decrypting(mode == 'd'), ownRng(true) {
	rng->initFromString(key);
	for (int i = 0; i < 256; i++) {
		buffer[i] = 0;
	}
}


BlockInput::BlockInput(std::istream* in, IRandomSource* random, char mode)
			: buffer(new unsigned char[256]), buf2(queue<unsigned char>()), count(0), rng(random),
			  instream(in), decrypting(mode == 'd'), ownRng(false) {
	for (int i = 0; i < 256; i++) {
		buffer[i] = 0;
	}
}


BlockInput::~BlockInput() {
	delete[] buffer;
	if (ownRng) delete rng;
}


void BlockInput::encrypt() {
	BlockScrambler cipher(*rng);
	cipher.passData(buffer);
	cipher.process();
}


void BlockInput::decrypt() {
	BlockDescrambler cipher(*rng);
	cipher.passData(buffer);
	cipher.process();
}


void BlockInput::readin() {
	if (decrypting) {
		// FIXME: If the number != 256 (aka, BS_BYTES) then the data is corrupted or
		//        incomplete -- how to handle this?  Just because it shouldn't happen
		//        does not mean it won't!!!
		instream->read((char*)buffer, jbcipher2::BS_BYTES);
		if (instream->gcount()) {
			decrypt();
			for (size_t i = 0; i < buffer[jbcipher2::BS_DATA]; i++) {
				buf2.push(buffer[i]);
			}
		}
	} else {
		instream->read((char*)buffer, jbcipher2::BS_DATA);
		buffer[jbcipher2::BS_DATA] = (unsigned char)instream->gcount();
		encrypt();
		for (size_t i = 0; i < jbcipher2::BS_BYTES; i++) {
			buf2.push(buffer[i]);
		}
	}
}


unsigned char BlockInput::readByte() {
	if (buf2.empty()) {
		readin();
	}
	if (buf2.empty()) {
		count = 0;
		return 0;
	}
	unsigned char out = buf2.front();
	buf2.pop();
	count = 1;
	return out;
}


void BlockInput::readBytes(char* bytes, size_t n) {
	for (size_t i = 0; i < n; i++) {
		if (buf2.empty()) {
			if (instream->good()) {
				readin();
			}
			else {
				count = i;
				return;
			}
		}
		if (buf2.empty()) {
			count = i;
			return;
		}
		bytes[i] = buf2.front();
		buf2.pop();
	}
	count = n;
}


void BlockInput::readBytes(unsigned char* bytes, size_t n) {
	for (size_t i = 0; i < n; i++) {
		if (buf2.empty()) {
			if (instream->good()) {
				readin();
			}
			else {
				count = i;
				return;
			}
		}
		if (buf2.empty()) {
			count = i;
			return;
		}
		bytes[i] = buf2.front();
		buf2.pop();
	}
	count = n;
}


void BlockInput::readBytes(std::vector<char>& bytes, size_t n) {
	for (size_t i = 0; i < n; i++) {
		if (buf2.empty()) {
			if (instream->good()) {
				readin();
			}
			else {
				count = i;
				return;
			}
		}
		if (buf2.empty()) {
			count = i;
			return;
		}
		bytes.push_back(buf2.front());
		buf2.pop();
	}
	count = n;
}


void BlockInput::readBytes(std::vector<unsigned char>& bytes, size_t n) {
	for (size_t i = 0; i < n; i++) {
		if (buf2.empty()) {
			if (instream->good()) {
				readin();
			}
			else {
				count = i;
				return;
			}
		}
		if (buf2.empty()) {
			count = i;
			return;
		}
		bytes.push_back(buf2.front());
		buf2.pop();
	}
	count = n;
}

size_t BlockInput::gcount() const {
	return count;
}



