#pragma once
#ifndef BLOCK_THROUGHPUT_H
#define BLOCK_THROUGHPUT_H

#include "JBCipher2.h"
#include "IRandomSource.h"
#include <queue>


class BlockThroughput {
private:
	unsigned char* buffer;
	std::queue<unsigned char> buf2;
	size_t bptr;
	size_t count;
	size_t dataSize;
	IRandomSource* rng;
	bool decrypting;
	bool ownRng;
	void encrypt();
	void decrypt();
	void process();
	void reset();
public:
	// Constructors
	BlockThroughput(std::string key, char mode = 'e');
	BlockThroughput(IRandomSource* random, char mode = 'e');
	BlockThroughput(const BlockThroughput& na) = delete;
	BlockThroughput operator=(const BlockThroughput& na) = delete;
	BlockThroughput() = delete;
	virtual ~BlockThroughput();
	// Feeding data in
	void writeByte(unsigned char byte);
	void writeByte(char byte);
	void writeBytes(const char* bytes, size_t n);
	void writeBytes(const unsigned char* bytes, size_t n);
	void writeBytes(const std::vector<char>& bytes);
	void writeBytes(const std::vector<unsigned char>& bytes);
	// Getting data out
	unsigned char readByte();
	void readBytes(char* bytes, size_t n);
	void readBytes(unsigned char* bytes, size_t n);
	void readBytes(std::vector<char>& bytes, size_t n);
	void readBytes(std::vector<unsigned char>& bytes, size_t n);
	void readBytes(std::vector<char>& bytes);
	void readBytes(std::vector<unsigned char>& bytes);
	// Information and control methods (e.g., empty())
	bool empty() const;
	bool ready() const;
	size_t bytesQueued();
	size_t bytesBuffered();
    void flush();
    size_t gcount();
};

#endif // BLOCK_THROUGHPUT_H
