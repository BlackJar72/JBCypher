#ifndef IRANDOMSOURCE_H
#define IRANDOMSOURCE_H

#include <string>

/**
 * An abstract interface for supplying random numbers, allowing
 * for easy alteration and extensibility.
 *
 * This needs to have the ability to return a random byte, as well
 * intialize itself.
 */


class IRandomSource
{
    public:
        virtual ~IRandomSource() noexcept;
        virtual unsigned char nextByte() = 0;
        virtual void initFromString(char* s) = 0;
        virtual void initFromString(const std::string& s) = 0;
    protected:
        IRandomSource() noexcept;
    private:
};

#endif // IRANDOMSOURCE_H
