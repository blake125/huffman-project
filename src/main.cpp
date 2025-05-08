#include <iostream>
#include <cstring>

#include "../include/HuffFileMaker.h"

int usageError() {
	std::cout << "Usage: huffman -f [FILENAME] -[e(encode), d(decode)]\n";
	return 1;
}

int main(int argc, char** argv) {
	if(argc != 4) {
		return usageError();		
	}

	if(strcmp(argv[1], "-f") != 0 
			|| (strcmp(argv[3], "-e") != 0 
			&& strcmp(argv[3], "-d") != 0)) {
		return usageError();	
	}

	if(strcmp(argv[3], "-e") == 0) {
		makeEncodedFile(argv[2]);
	} else if(strcmp(argv[3], "-d") == 0) {
		makeDecodedFile(argv[2]);
	} else {
		return usageError();
	}
}
