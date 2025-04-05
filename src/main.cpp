#include <iostream>
#include <fstream>
#include <cstring>

#include "BinarySearchTree.cpp"
#include "HuffmanTree.cpp"

void createFreqTree(std::ifstream&, BinarySearchTree*);
void quickSort(CharData*, int, int);
int partition(CharData*, int, int);

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

	CharData* charData = freqTree->inorder();	

	quickSort(charData, 0, freqTree->getCount() - 1);
	
	HuffmanTree* huffTree = new HuffmanTree(charData, freqTree->getCount());

	delete[] charData;
	delete huffTree;
	delete freqTree;

	infile.close();
	outfile.close();

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
