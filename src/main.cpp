#include <iostream>
#include <cstring>
#include <exception>

#include "../include/HuffmanCoder.h"

void usageError() {
	std::cout << "Usage: huffman -f [FILENAME] -[e(encode), d(decode)]" << std::endl;
	exit(1);
}

Arguments parse(int argc, char **argv) {
	bool encodeFlag;
	std::string filename = argv[2];
	
	if(argc != 4) {
		usageError();
	}

	if(strcmp("-f", argv[1]) != 0) {
		usageError();	
	}
	
	if(strcmp("-d", argv[3]) == 0) {
		encodeFlag = false;
	} else if(strcmp("-e", argv[3]) == 0) {
		encodeFlag = true;
	} else {
		usageError();
	}

	return { encodeFlag, filename };
}

int main(int argc, char** argv) {
	try {
		Arguments args = parse(argc, argv);
		HuffmanCoder coder(args);
	} catch(std::exception &e) {
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
