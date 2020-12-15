#include "stdafx.h"
#include "IRandomSource.h"

/**
 * An abstract interface for supplying random numbers, allowing
 * for easy alteration and extensibility.
 *
 * This needs to have the ability to return a random byte, as well
 * intialize itself.
 */

IRandomSource::IRandomSource()  noexcept {}
IRandomSource::~IRandomSource() noexcept {}
