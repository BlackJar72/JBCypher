#pragma once
#ifndef BLOCKENCRYPTOR_H
#define BLOCKENCRYPTOR_H

#include <ostream>
#include "JBCipher2.h"
#include "IRandomSource.h"
#include <vector>

class BlockOutput {
private:
	unsigned char* buffer;
	size_t bptr;
	IRandomSource* rng;
	std::ostream* out;
	bool decrypting;
	void reset();
	void writeout();
	size_t readsize;
	bool ownRng;
protected:
public:
	BlockOutput(std::string key, std::ostream* out, char mode = 'e');
	BlockOutput(std::ostream* out, IRandomSource* random, char mode = 'e');
	BlockOutput() = delete;
	BlockOutput(const BlockOutput& na) = delete;
	BlockOutput operator=(const BlockOutput& na) = delete;
	virtual ~BlockOutput();
	void writeByte(unsigned char byte);
	void writeByte(char byte);
	void writeBytes(const char* bytes, size_t n);
	void writeBytes(const unsigned char* bytes, size_t n);
	void writeBytes(const std::vector<char>& bytes);
	void writeBytes(const std::vector<unsigned char>& bytes);
	void flush();
	void encrypt();
	void decrypt();
};

#endif // BLOCKENCRYPTOR_H
