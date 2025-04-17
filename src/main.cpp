#include <iostream>
#include <cstring>

#include "../include/HuffFileMaker.h"

int main(int argc, char** argv) {
	if(argc != 4) {
		std::cout << "Usage: huffman -f [FILENAME] -[e(encode), d(decode)]\n";
		return 0;
	}

	if(strcmp(argv[1], "-f") != 0 
			|| (strcmp(argv[3], "-e") != 0 
			&& strcmp(argv[3], "-d") != 0)) {
		
		std::cout << "Usage: huffman -f [FILENAME] -[e(encode), d(decode)]\n";
		return 0;
	}

	if(strcmp(argv[3], "-e") == 0) {
		makeEncodedFile(argv[2]);
	}
	
	return 0;
}
