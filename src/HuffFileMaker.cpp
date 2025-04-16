#include "../include/HuffFileMaker.h"

void makeEncodedFile(const char* fileName) {
	std::ifstream infile(fileName);

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
	fileStr= fileStr.substr(0, fileStr.find("."));
	
	infile.clear();
	infile.seekg(0, std::ios::beg);
	encodeFile(fileStr, infile, huffTree);

	infile.close();
	delete[] charData;
	delete huffTree;
	delete freqTree;
}

void makeDecodedFile(const char* fileName) {

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

void makeFileHeader(std::ofstream& outfile, HuffmanTree* tree) {
	
}

void encodeFile(std::string fileName, std::ifstream& infile, HuffmanTree* tree) {
	std::ofstream outfile(fileName + ".huff");
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
				if(bitstream[i] == 1) {
					value = value | (std::uint8_t)pow(2, 7 - i);
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
				value = value | (std::uint8_t)pow(2, 7 - i);
			}
		}

		outfile << value;

		bitstream.erase(bitstream.begin(), bitstream.begin() + 8);

	}

	outfile.close();
}
