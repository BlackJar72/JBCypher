#pragma once
#ifndef JBCIPHER2_H
#define JBCIPHER2_H

#include <cstddef>

namespace jbcipher2 {

	const std::size_t BS_BYTES = 256;          // Total bytes in a block
	const std::size_t BS_DATA  = BS_BYTES - 1; // Total bytes from file in a block

}

#endif
