#ifndef ARC4JB_H
#define ARC4JB_H

#include <array>
#include <string>
#include "IRandomSource.h"

class Arc4JB : public IRandomSource
{
    public:
        Arc4JB();
        virtual ~Arc4JB();
        virtual unsigned char nextByte() override;
        virtual void initFromString(char* s) override;
        virtual void initFromString(const std::string& s) override;
    protected:
    private:
        unsigned char innerRandom();
        std::array<unsigned char, 256> bank;
        unsigned long long seed;
        unsigned int i;
        unsigned int j;
        unsigned int k;
};

#endif // ARC4JB_H
