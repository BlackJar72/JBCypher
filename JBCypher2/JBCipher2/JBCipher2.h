#pragma once
// Including control guards for use in other compilers / OSes
#ifndef JBCIPHER2_H
#define JBCIPHER2_H

namespace jbcipher2 {

	const size_t BS_BYTES = 256;          // Total bytes in a block
	const size_t BS_DATA = BS_BYTES - 1; // Total bytes from file in a block

}

#endif
