// JBCipher1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FileEncryptor.h"
#include "FileDecryptor.h"

using namespace std;

int main(int argc, char** argv)
{

	if (argc < 5) {
		std::cerr << std::endl << "ERROR!" << std::endl;
		std::cerr << "Usage: jbcipher [e / d] [key / seed] [filename] [outfile]"
			<< std::endl << std::endl;
		return 1;
	}
	string key(argv[2]);
	string inFilePath(argv[3]);
	string outFilePath(argv[4]);
	if (argv[1][0] == 'e') {
		FileEncryptor cipher(key, inFilePath, outFilePath);
		cipher.encrypt();
	}
	else if (argv[1][0] == 'd') {
		FileEncryptor cipher(key, inFilePath, outFilePath);
		cipher.decrypt();
	}
	else {
		std::cerr << std::endl
			<< "Error, first arguments must be 'e' (encrcypt) or 'd' (decrypt)"
			<< std::endl << std::endl;
		std::cerr << "Usage: jbcipher [e / d] [key / seed] [filename] [outfile]"
			<< std::endl << std::endl;
		return 1;
	}
	return 0;
}
