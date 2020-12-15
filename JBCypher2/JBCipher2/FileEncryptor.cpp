#include "stdafx.h"
#include "FileEncryptor.h"
#include "Arc4JB.h"
#include "BlockOutput.h"
#include "BlockInput.h"
#include "JBCipher2.h"
#include <sys/stat.h>
#include <iostream>

//Inlcudes used only for debugging
#include <iostream>

long long GetFileSize(std::string filename) {
	struct stat stat_buf;
	int a = stat(filename.c_str(), &stat_buf);
	return a == 0 ? stat_buf.st_size : -1;
}



FileEncryptor::FileEncryptor(std::string key, std::string inFilePath, std::string outFilePath)
	: inFile(), outFile(), rng(new Arc4JB()) {
	rng->initFromString(key);
	inFile.open(inFilePath, std::ifstream::binary);
	outFile.open(outFilePath, std::ifstream::binary);
	if (!inFile.is_open() || !outFile.is_open()) {
		std::cerr << std::endl << "Error! File " << inFilePath
			<< " and / or " << outFilePath << " failed to open!"
			<< std::endl << std::endl;
		exit(1);
	}
}


FileEncryptor::~FileEncryptor() {
	inFile.close();
	outFile.close();
	delete rng;
}


void FileEncryptor::encrypt() {
	size_t written;
	BlockOutput* bout = new BlockOutput(&outFile, rng, 'e');
	unsigned char inDat[256];
	do {
		inFile.read((char*)inDat, 255);
		written = inFile.gcount();
		bout->writeBytes(inDat, written);
	} while (inFile.good());
	bout->flush();
}


void FileEncryptor::decrypt() {
	size_t written;
	BlockOutput* bout = new BlockOutput(&outFile, rng, 'd');
	unsigned char inDat[256];
	do {
		inFile.read((char*)inDat, 256);
		written = inFile.gcount();
		bout->writeBytes(inDat, written);
	} while (inFile.good());
	bout->flush();
}
