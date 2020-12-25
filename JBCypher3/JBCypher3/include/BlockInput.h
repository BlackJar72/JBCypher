#pragma once
#ifndef BLOCK_INPUT_H
#define BLOCK_INPUT_H

#include <istream>
#include "JBCipher2.h"
#include "IRandomSource.h"
#include <queue>

class BlockInput {
	private:
		unsigned char* buffer;
		std::queue<unsigned char> buf2;
		size_t count;
		IRandomSource* rng;
		std::istream* instream;
		bool decrypting;
		bool ownRng;
		void readin();
		void encrypt();
		void decrypt();
	public:
		BlockInput(std::string key, std::istream* in, char mode = 'd');
		BlockInput(std::istream* in, IRandomSource* random, char mode = 'd');
		BlockInput(const BlockInput& na) = delete;
		BlockInput operator=(const BlockInput& na) = delete;
		BlockInput() = delete;
		~BlockInput();
		unsigned char readByte();
		void readBytes(char* bytes, size_t n);
		void readBytes(unsigned char* bytes, size_t n);
		void readBytes(std::vector<char>& bytes, size_t n);
		void readBytes(std::vector<unsigned char>& bytes, size_t n);
		size_t gcount() const;
};

#endif // !BLOCK_INPUT_H
