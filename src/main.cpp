#include <iostream>
#include <fstream>

#include "BinarySearchTree.cpp"
#include <cstring>

void createFreqTree(std::ifstream&, BinarySearchTree*);

int main(int argc, char** argv) {
	if(argc != 4) {
		std::cout << "Usage: huffman -f [FILENAME] -[e(encode), d(decode)]\n";
		return 0;
	}

	if(strcmp(argv[1], "-f") != 0 || (strcmp(argv[3], "-e") != 0 && strcmp(argv[3], "-d") != 0)) {
		std::cout << "Usage: huffman -f [FILENAME] -[e(encode), d(decode)]\n";
		return 0;
	}

	std::ifstream infile;
	infile.open(argv[2]);

	if(!infile.is_open()) {
		std::cout << "File doesn't exist!\n";
		return 0;
	}

	BinarySearchTree* freqTree = new BinarySearchTree();
		
	createFreqTree(infile, freqTree);

	freqTree->printInorder();

	delete freqTree;

	return 0;
}

void createFreqTree(std::ifstream& infile, BinarySearchTree* tree) {
	char buffer[2048];

	while(infile.getline(buffer, 2048)) {
		for(int i = 0; i < 2048; i++) {
			if(buffer[i] == '\0') {
				break;
			}
			tree->insert(buffer[i]);
		}
	}
}
