#include "../include/HuffFileMaker.h"

void makeEncodedFile(const char* fileName) {
	std::ifstream infile(fileName, std::ios::binary);

	if(!infile.is_open()) {
		std::cout << "File doesn't exist!\n";
		return;
	}
	
	BinarySearchTree* freqTree = new BinarySearchTree();
		
	createFreqTree(infile, freqTree);
	
	CharData* charData = freqTree->inorder();	

	quickSort(charData, 0, freqTree->getCount() - 1);
	
	HuffmanTree* huffTree = new HuffmanTree(charData, freqTree->getCount());
	
	std::string fileStr = fileName;
	
	infile.clear();
	infile.seekg(0, std::ios::beg);
	
	std::ofstream outfile(fileStr + ".huff", std::ios::binary);
	makeFileHeader(outfile, freqTree);
	encodeFile(infile, huffTree, outfile);

	infile.close();
	outfile.close();
	delete[] charData;
	delete huffTree;
	delete freqTree;
}

void encodeFile(std::ifstream& infile, HuffmanTree* tree, std::ofstream& outfile) {
	std::vector<int> bitstream;
	bitstream.reserve(1024);

	char byte;

	while(infile.get(byte)) {
		std::string newRep = tree->findPath(byte);

		for(int i = 0; i < (int)newRep.size(); i++) {
			if(newRep.at(i) == '1') {
				bitstream.push_back(1);
			} else {
				bitstream.push_back(0);
			}
		}

		if(bitstream.size() >= 8) {
			std::uint8_t value = 0;
			for(int i = 0; i < 8; i++) {
				if(bitstream.at(i) == 1) {
					value = value | (1 << (7 - i));
				}
			}

			outfile.put(value);

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
			if(bitstream.at(i) == 1) {
				value = value | (1 << (7 - i));
			}
		}

		outfile.put(value);

	}

}

void createFreqTree(std::ifstream& infile, BinarySearchTree* tree) {
	char byte;
	while(infile.get(byte)) {
		tree->insert(byte);
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

void makeDecodedFile(const char* fileName) {
	std::ifstream infile(fileName, std::ios::binary);
	if(!infile.is_open()) {
		std::cout << "File doesn't exist!" << std::endl;
		return;
	}
	
	char magicNumber[5];
	infile.read(magicNumber, 4);

	if(strcmp(magicNumber, "HUFF") != 0) {
		std::cout << "Not a compressed file!" << std::endl;
		return;
	}
	
	BinarySearchTree* freqTree = new BinarySearchTree();

	std::uint32_t data[256] = {0};
	infile.read(reinterpret_cast<char*>(data), sizeof(data));
	
	std::vector<struct CharData> charDataV;
	for(int i = 0; i < 256; i++) {
		if(data[i] != 0) {
			charDataV.push_back({data[i], (char)i});	
		}
	}

	CharData charData[(int)charDataV.size()];
	for(int i = 0; i < (int)charDataV.size(); i++) {
		charData[i] = charDataV.at(i);	
	}

	quickSort(charData, 0, charDataV.size() - 1);
	HuffmanTree* huffTree = new HuffmanTree(charData, charDataV.size());
	
	std::string decodedFileStr = fileName;
	decodedFileStr = decodedFileStr.substr(0, decodedFileStr.size() - 5);
	decodedFileStr += ".test";

	std::ofstream outfile(decodedFileStr, std::ios::binary);
	decodeFile(infile, huffTree, outfile);

	infile.close();
	outfile.close();
	delete freqTree;
	delete huffTree;
}

void makeFileHeader(std::ofstream& outfile, BinarySearchTree* tree) {
	outfile.write("HUFF", 4);
	
	std::uint32_t frequencies[256];
	for(int i = 0; i < 256; i++) {
		frequencies[i] = 0;
	}

	CharData* data = tree->inorder();
	for(int j = 0; j < tree->getCount(); j++) {
		frequencies[static_cast<std::uint8_t>(data[j].data)] = data[j].freq;
	}

	outfile.write(reinterpret_cast<const char*>(frequencies), sizeof(frequencies));

	delete[] data;
}

void decodeFile(std::ifstream& infile, HuffmanTree* tree, std::ofstream& outfile) {
	char byte;
	Node* walk = tree->getRoot();
	
	while(infile.get(byte)) {
		for(int i = 0; i < 8; i++) {
		    	int bit = (byte & (1 << (7 - i))) != 0 ? 1 : 0;
		    
			if(bit == 0) {
				walk = walk->getLeft(); 
		    	} else { 
				walk = walk->getRight();
		    	}
		    
			if(walk->getLeft() == nullptr && walk->getRight() == nullptr) {
				outfile.put(walk->getData());
				walk = tree->getRoot();
		    	}
		}
    	}
}
