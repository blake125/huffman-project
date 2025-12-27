#include "../include/HuffmanCoder.h"

static const int BUFFER_SIZE = 4096;

HuffmanCoder::HuffmanCoder() {
	m_htree = nullptr;
	m_bst = nullptr;
}

void HuffmanCoder::encode(const char* fileName) {
	std::ifstream infile(fileName, std::ios::binary);

	if(!infile.is_open()) {
		std::cout << "File doesn't exist!\n";
		return;
	}
	
	m_bst = new BinarySearchTree();
		
	createFreqTree(infile);
	
	std::vector<struct Data> data = m_bst->inorder();	
	
	std::sort(data.begin(), data.end());
	
	m_htree = new HuffmanTree(data);
	
	std::string fileStr = fileName;
	
	infile.clear();
	infile.seekg(0, std::ios::beg);
	
	std::ofstream outfile(fileStr + ".huff", std::ios::binary);
	std::uint32_t bc = 0;

	std::ofstream temp(fileStr + ".temp", std::ios::binary);
	encodeFile(infile, temp, bc);
	temp.close();

	makeFileHeader(outfile);
	outfile.write(reinterpret_cast<const char*>(&bc), sizeof(bc));

	std::ifstream writer(fileStr + ".temp", std::ios::binary);

	char bytes[BUFFER_SIZE];
	while(writer) {
		writer.read(bytes, sizeof(bytes));
		outfile.write(bytes, writer.gcount());
	}

	int status = remove((fileStr + ".temp").c_str());
	if(status != 0) {
		std::cout << "Error removing the temp file!\n";
	} else {
		std::cout << "Temp file successfully deleted.\n";
	}

	infile.close();
	outfile.close();
	writer.close();
	delete m_htree;
	delete m_bst;
}

void HuffmanCoder::encodeFile(std::ifstream& infile, std::ofstream& outfile, std::uint32_t &bc) {
	std::vector<int> bitstream;
	bitstream.reserve(1024);

	char bytes[BUFFER_SIZE];
	while(infile) {
		infile.read(bytes, sizeof(bytes));
		for(int j = 0; j < infile.gcount(); j++) {
			std::string newRep = m_htree->retrievePath(bytes[j]);
			bc += newRep.size();
			for(int i = 0; i < (int)newRep.size(); i++) {
				if(newRep.at(i) == '1') {
					bitstream.push_back(1);
				} else {
					bitstream.push_back(0);
				}
			}

			while(bitstream.size() >= 8) {
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
	}

	if(bitstream.size() != 0) {	
		int remaining = (8 - bitstream.size());

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

void HuffmanCoder::createFreqTree(std::ifstream& infile) {
	char bytes[BUFFER_SIZE];
	while(infile) {
		infile.read(bytes, sizeof(bytes));
		for(int i = 0; i < infile.gcount(); i++) {
			m_bst->insert(bytes[i]);
		}
	}
}

void HuffmanCoder::decode(const char* fileName) {
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
	
	m_bst = new BinarySearchTree();

	std::uint32_t data[256] = {0};
	infile.read(reinterpret_cast<char*>(data), sizeof(data));

	std::uint32_t bc = 0;
	infile.read(reinterpret_cast<char*>(&bc), sizeof(bc));

	
	std::vector<struct Data> dataV;
	for(int i = 0; i < 256; i++) {
		if(data[i] != 0) {
			Data charData(data[i], (char)i);
			dataV.push_back(charData);	
		}
	}

	std::sort(dataV.begin(), dataV.end());
	m_htree = new HuffmanTree(dataV);
	
	std::string decodedFileStr = fileName;
	decodedFileStr = decodedFileStr.substr(0, decodedFileStr.size() - 5);
	decodedFileStr += ".test";

	std::ofstream outfile(decodedFileStr, std::ios::binary);
	decodeFile(infile, outfile, bc);

	infile.close();
	outfile.close();
	delete m_bst;
	delete m_htree;
}

void HuffmanCoder::makeFileHeader(std::ofstream& outfile) {
	outfile.write("HUFF", 4);
	
	std::uint32_t frequencies[256] = {0};

	std::vector<struct Data> data = m_bst->inorder();
	for(int j = 0; j < m_bst->getCount(); j++) {
		frequencies[static_cast<std::uint8_t>(data.at(j).symbol)] = data.at(j).freq;
	}

	outfile.write(reinterpret_cast<const char*>(frequencies), sizeof(frequencies));
}

void HuffmanCoder::decodeFile(std::ifstream& infile, std::ofstream& outfile, std::uint32_t bit_count) {
	char bytes[BUFFER_SIZE];
	Node* walk = m_htree->getRoot();
	
	std::uint32_t bc = 0;
	while(infile) {
		infile.read(bytes, sizeof(bytes));
		for(int j = 0; j < infile.gcount(); j++) {
			for(int i = 0; i < 8; i++) {
				if(bit_count == bc) {
					return;
				}
				int bit = (bytes[j] & (1 << (7 - i))) != 0 ? 1 : 0;
			    
				if(bit == 0) {
					walk = walk->getLeft();
				} else { 
					walk = walk->getRight();
				}
			    
				if(walk->getLeft() == nullptr && walk->getRight() == nullptr) {
					outfile.put(walk->getData().symbol);
					walk = m_htree->getRoot();
				}

				bc++;
			}
		}

    	}
}
