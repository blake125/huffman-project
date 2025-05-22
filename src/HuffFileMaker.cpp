#include "../include/HuffFileMaker.h"

void makeEncodedFile(const char* fileName) {
	std::ifstream infile(fileName, std::ios::binary);

	if(!infile.is_open()) {
		std::cout << "File doesn't exist!\n";
		return;
	}
	
	BinarySearchTree* freqTree = new BinarySearchTree();
		
	createFreqTree(infile, freqTree);
	
	std::vector<struct Data> data = freqTree->inorder();	
	
	std::sort(data.begin(), data.end());
	
	HuffmanTree* huffTree = new HuffmanTree(data);
	
	std::string fileStr = fileName;
	
	infile.clear();
	infile.seekg(0, std::ios::beg);
	
	std::ofstream outfile(fileStr + ".huff", std::ios::binary);
	makeFileHeader(outfile, freqTree);
	encodeFile(infile, huffTree, outfile);

	infile.close();
	outfile.close();
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
	
	std::vector<struct Data> dataV;
	for(int i = 0; i < 256; i++) {
		if(data[i] != 0) {
			Data charData(data[i], (char)i);
			dataV.push_back(charData);	
		}
	}

	std::sort(dataV.begin(), dataV.end());
	HuffmanTree* huffTree = new HuffmanTree(dataV);
	
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
	
	std::uint32_t frequencies[256] = {0};

	std::vector<struct Data> data = tree->inorder();
	for(int j = 0; j < tree->getCount(); j++) {
		frequencies[static_cast<std::uint8_t>(data.at(j).symbol)] = data.at(j).freq;
	}

	outfile.write(reinterpret_cast<const char*>(frequencies), sizeof(frequencies));
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
				outfile.put(walk->getData().symbol);
				walk = tree->getRoot();
		    	}
		}
    	}
}
