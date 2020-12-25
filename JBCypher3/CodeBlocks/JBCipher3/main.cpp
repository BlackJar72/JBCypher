#include <iostream>
#include <string>
#include "FileEncryptor.h"
#include "JBCipher2.h"

using namespace std;

int main(int argc, char** argv)
{

	if (argc < 5) {
		std::cerr << std::endl << "ERROR!" << std::endl;
		std::cerr << "Usage: jbc3 [e / d] [key / seed] [filename] [outfile]"
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
		std::cerr << "Usage: jbcipher2 [e / d] [key / seed] [filename] [outfile]"
			<< std::endl << std::endl;
		return 1;
	}
	return 0;
}
