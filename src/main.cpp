#include <iostream>
#include <cstring>

#include "../include/HuffmanCoder.h"

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

	std::string filename = argv[2];

	HuffmanCoder coder;
	if(strcmp(argv[3], "-e") == 0) {
		coder.encode(filename.c_str());
	} else if(strcmp(argv[3], "-d") == 0) {
		coder.decode(filename.c_str());
	} else {
		return usageError();
	}
}
