#pragma once
#ifndef JBCIPHER2_H
#define JBCIPHER2_H

#include <cstddef>
#include <istream>
#include <queue>
#include <ostream>
#include <vector>
#include <queue>
#include <string>

#ifdef JBCIPHER2_API  
#define JBCIPHER2_API __declspec(dllexport)   
#else  
#define JBCIPHER2_API __declspec(dllimport)   
#endif

namespace jbcipher2 {

const std::size_t BS_BYTES = 256;          // Total bytes in a block
const std::size_t BS_DATA  = BS_BYTES - 1; // Total bytes from file in a block


/**
 * An abstract interface for supplying random numbers, allowing
 * for easy alteration and extensibility.
 *
 * This needs to have the ability to return a random byte, as well
 * intialize itself.
 */class IRandomSource
{
    public:
        virtual ~IRandomSource();
        virtual unsigned char nextByte() = 0;
        virtual void initFromString(char* s) = 0;
        virtual void initFromString(const std::string& s) = 0;
    protected:
        IRandomSource();
    private:
};


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

}

#endif
