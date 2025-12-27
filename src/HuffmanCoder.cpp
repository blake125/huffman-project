#include "../include/HuffmanCoder.h"

static const int BUFFER_SIZE = 4096;

HuffmanCoder::HuffmanCoder(Arguments args) {
	if(args.encodeFlag) {
		encode(args.filename.c_str());
	} else {
		decode(args.filename.c_str());
	}
};

void HuffmanCoder::encode(const char* fileName) {
	std::ifstream infile(fileName, std::ios::binary);

	if(!infile.is_open()) {
		std::cout << "File doesn't exist!\n";
		return;
	}
	
	createFreqTree(infile);
	
	std::vector<struct Data> data = m_bst.inorder();	
	
	std::sort(data.begin(), data.end());

	m_htree.populateTree(data);
	
	std::string fileStr = fileName;
	
	infile.clear();
	infile.seekg(0, std::ios::beg);
	
	std::ofstream outfile(fileStr + ".huff", std::ios::binary);
	std::uint32_t bc = 0;

	makeFileHeader(outfile);
	encodeFile(infile, outfile, bc);

	outfile.clear();
	outfile.seekp(0, std::ios::beg);

	outfile.write("HUFF", 4);
	outfile.write(reinterpret_cast<const char*>(&bc), sizeof(bc));


	infile.close();
	outfile.close();
}

void HuffmanCoder::encodeFile(std::ifstream& infile, std::ofstream& outfile, std::uint32_t &bc) {
	std::vector<int> bitstream;
	bitstream.reserve(1024);

	char bytes[BUFFER_SIZE];
	while(infile) {
		infile.read(bytes, sizeof(bytes));
		for(int j = 0; j < infile.gcount(); j++) {
			std::string newRep = m_htree.retrievePath(bytes[j]);
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
			m_bst.insert(bytes[i]);
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

	std::uint32_t bc = 0;
	infile.read(reinterpret_cast<char*>(&bc), sizeof(bc));
	
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
	m_htree.populateTree(dataV);
	
	std::string decodedFileStr = fileName;
	decodedFileStr = decodedFileStr.substr(0, decodedFileStr.size() - 5);
	decodedFileStr += ".test";

	std::ofstream outfile(decodedFileStr, std::ios::binary);
	decodeFile(infile, outfile, bc);

	infile.close();
	outfile.close();
}

void HuffmanCoder::makeFileHeader(std::ofstream& outfile) {
	outfile.write("HUFF", 4);

	std::uint32_t bc = 0;
	outfile.write(reinterpret_cast<char*>(&bc), sizeof(bc));
	
	std::uint32_t frequencies[256] = {0};

	std::vector<struct Data> data = m_bst.inorder();
	for(int j = 0; j < m_bst.getCount(); j++) {
		frequencies[static_cast<std::uint8_t>(data.at(j).symbol)] = data.at(j).freq;
	}

	outfile.write(reinterpret_cast<const char*>(frequencies), sizeof(frequencies));
}

void HuffmanCoder::decodeFile(std::ifstream& infile, std::ofstream& outfile, std::uint32_t bit_count) {
	char bytes[BUFFER_SIZE];
	Node* walk = m_htree.getRoot();
	
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
					walk = m_htree.getRoot();
				}

				bc++;
			}
		}

    	}
}
