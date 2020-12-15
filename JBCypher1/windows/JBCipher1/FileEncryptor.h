#ifndef FILEENCRYPTOR_H
#define FILEENCRYPTOR_H

#include <string>
#include <fstream>
#include <ostream>
#include "IRandomSource.h"

class FileEncryptor
{
    public:
        FileEncryptor() = delete;
        FileEncryptor(const FileEncryptor& na) = delete;
        FileEncryptor(std::string key, std::string inFilePath, std::string outFilePath);
        virtual ~FileEncryptor();
        void encrypt();
        void decrypt();
        FileEncryptor operator=(const FileEncryptor& na) = delete;
    protected:
    private:
        std::ifstream inFile;
        std::ofstream outFile;
        IRandomSource* rng;
        long long fileSize;
        long long blocks;
        unsigned char extra;
};

#endif // FILEENCRYPTOR_H
