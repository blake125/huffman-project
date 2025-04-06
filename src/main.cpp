#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <cstdint>

#include "BinarySearchTree.cpp"
#include "HuffmanTree.cpp"

void createFreqTree(std::ifstream&, BinarySearchTree*);
void quickSort(CharData*, int, int);
int partition(CharData*, int, int);
void makeOutfile(std::ifstream&, HuffmanTree*);

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

	std::ifstream infile;
	infile.open(argv[2]);

	if(!infile.is_open()) {
		std::cout << "File doesn't exist!\n";
		return 0;
	}

	BinarySearchTree* freqTree = new BinarySearchTree();
		
	createFreqTree(infile, freqTree);
	
	infile.close();

	CharData* charData = freqTree->inorder();	

	quickSort(charData, 0, freqTree->getCount() - 1);
	
	HuffmanTree* huffTree = new HuffmanTree(charData, freqTree->getCount());

	infile.open(argv[2]);

	makeOutfile(infile, huffTree);

	delete[] charData;
	delete huffTree;
	delete freqTree;
	
	infile.close();

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

void quickSort(CharData* arr, int low, int high) {
	if(low >= high) {
			return; 
	}

	int pivot = partition(arr, low, high);

	quickSort(arr, low, pivot - 1);
	quickSort(arr, pivot + 1, high);
}

int partition(CharData* arr, int low, int high) {
	CharData pivot = arr[high];

	int j = low;

	for(int i = low; i < high; i++) {
		if(arr[i].freq <= pivot.freq) {
			CharData temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;

			j++;
		}
	}

	CharData temp = arr[j];
	arr[j] = arr[high];
	arr[high] = temp;

	return j;
}

void makeOutfile(std::ifstream& infile, HuffmanTree* tree) {
	std::ofstream outfile("outfile.huff");
	std::vector<int> bitstream;
	bitstream.reserve(1024);

	char byte;

	while(infile.get(byte)) {
		std::string newRep = tree->findPath(byte);

		for(int i = 0; i < newRep.size(); i++) {
			if(newRep.at(i) == '1') {
				bitstream.push_back(1);
			} else {
				bitstream.push_back(0);
			}
		}

		if(bitstream.size() >= 8) {
			std::uint8_t value = 0;
			for(int i = 0; i < 8; i++) {
				if(bitstream[i] == 1) {
					value = value | (std::uint8_t)pow(2, i);
				}
			}

			outfile << value;

			bitstream.erase(bitstream.begin(), bitstream.begin() + 8);
		}
	}

	if(bitstream.size() != 0) {	
		int remaining = 8 - bitstream.size();

		for(int j = 0; j < remaining; j++) {
			bitstream.push_back(0);
		}

		std::uint8_t value = 0;
		for(int i = 0; i < 8; i++) {
			if(bitstream[i] == 1) {
				value = value | (std::uint8_t)pow(2, i);
			}
		}

		outfile << value;

		bitstream.erase(bitstream.begin(), bitstream.begin() + 8);

	}

	outfile.close();
}
