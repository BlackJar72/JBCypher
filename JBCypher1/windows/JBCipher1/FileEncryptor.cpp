#include "stdafx.h"
#include "FileEncryptor.h"
#include "Arc4JB.h"
#include "BlockScrambler.h"
#include "BlockDescrambler.h"
#include <sys/stat.h>
#include <iostream>

long long GetFileSize(std::string filename) {
    struct stat stat_buf;
    int a = stat(filename.c_str(), &stat_buf);
    return a == 0 ? stat_buf.st_size : -1;
}



FileEncryptor::FileEncryptor(std::string key, std::string inFilePath, std::string outFilePath)
            : inFile(), outFile(), rng(0), fileSize(GetFileSize(inFilePath) + 1),
              blocks(fileSize / 256), extra(fileSize % 256) {
    if(extra) {
        blocks++;
    }
	rng = new Arc4JB();
	rng->initFromString(key);
    if(!fileSize) {
        std::cerr << std::endl << "Error! File " << inFilePath
                  << " is not valid! " << std::endl << std::endl;
        exit(1);
    }
	inFile.open(inFilePath, std::ifstream::binary);
	outFile.open(outFilePath, std::ifstream::binary);
	if(!inFile.is_open() || !outFile.is_open()) {
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
    BlockScrambler cipher(*rng);
    unsigned char inDat[256];
    inDat[0] = extra;
    inFile.read((char*)(inDat + 1), 255);
    cipher.passData(inDat);
    cipher.process();
    outFile.write((char*)inDat, 256);
    for(int i = 1; i < blocks; i++) {
        inFile.read((char*)inDat, 256);
        cipher.passData(inDat);
        cipher.process();
        outFile.write((char*)inDat, 256);
    }
}


void FileEncryptor::decrypt() {
    BlockDescrambler cipher(*rng);
    unsigned char inDat[256];
    inFile.read((char*)inDat, 256);
    cipher.passData(inDat);
    cipher.process();
    extra = inDat[0];
    if(extra == 1) {
        blocks--;
    }
    if(blocks < 3) {
        outFile.write((char*)(inDat + 1), extra - 1);
    } else {
        outFile.write((char*)(inDat + 1), 255);
        for(int i = 1; i < blocks - 2; i++) {
            inFile.read((char*)inDat, 256);
            cipher.passData(inDat);
            cipher.process();
            outFile.write((char*)inDat, 256);
        }
        inFile.read((char*)inDat, 256);
        cipher.passData(inDat);
        cipher.process();
        outFile.write((char*)inDat, extra);
    }
}
