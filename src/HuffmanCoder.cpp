#include "../include/HuffmanCoder.h"

static constexpr int BUFFER_SIZE = 4096;

HuffmanCoder::HuffmanCoder() = default;

void HuffmanCoder::encode(const std::string &fileName) {
	std::ifstream infile(fileName, std::ios::binary);

	if(!infile.is_open()) {
		std::cout << "File doesn't exist!\n";
		return;
	}
	
	createFreqTree(infile);
	
	std::vector<Data> data = m_freq.getFrequencies();
	
	m_htree.populateTree(data);

	if (m_htree.empty()) {
		return;
	}
	
	infile.clear();
	infile.seekg(0, std::ios::beg);
	
	std::ofstream outfile(fileName + ".huff", std::ios::binary);
	std::uint32_t bc = 0;

	makeFileHeader(outfile);
	encodeFile(infile, outfile, bc);

	outfile.clear();
	outfile.seekp(0, std::ios::beg);

	//Now that I know the bitcount of the encoded file
	//I can overwrite the placeholder value I had there.
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
			for(char i : newRep) {
				if(i == '1') {
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

	if(!bitstream.empty()) {
		int remaining;
		remaining = (8 - bitstream.size());

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
		m_freq.add(reinterpret_cast<const std::uint8_t*>(bytes), infile.gcount());
	}
}

void HuffmanCoder::decode(const std::string& fileName) {
	std::ifstream infile(fileName, std::ios::binary);
	if(!infile.is_open()) {
		std::cout << "File doesn't exist!" << std::endl;
		return;
	}
	
	char magicNumber[5] = {0}; // Initialize all to 0
	infile.read(magicNumber, 4);
	if(std::string(magicNumber) != "HUFF") { // Safer comparison
		std::cout << "Not a HUFF file?";
		return;
	}

	std::uint32_t bc = 0;
	infile.read(reinterpret_cast<char*>(&bc), sizeof(bc));
	
	std::uint32_t data[256] = {};
	infile.read(reinterpret_cast<char*>(data), sizeof(data));
	
	std::vector<Data> dataV;
	for(int i = 0; i < 256; i++) {
		if(data[i] != 0) {
			Data charData(data[i], (char)i);
			dataV.push_back(charData);	
		}
	}

	std::sort(dataV.begin(), dataV.end());
	m_htree.populateTree(dataV);
	
	std::ofstream outfile(fileName.substr(0, fileName.size() - 5) + ".test", std::ios::binary);

	if (m_htree.empty()) {
		return;
	}

	decodeFile(infile, outfile, bc);

	infile.close();
	outfile.close();
}

void HuffmanCoder::makeFileHeader(std::ofstream& outfile) const {
	outfile.write("HUFF", 4);

	//since I don't know the value of bitcount until the file is encoded
	//we are putting a placeholder to be overwritten later.
	std::uint32_t bc = 0;
	outfile.write(reinterpret_cast<char*>(&bc), sizeof(bc));
	
	std::uint32_t frequencies[256] = {};

	const std::vector<Data> data = m_freq.getFrequencies();
	for(auto & j : data) {
		frequencies[static_cast<std::uint8_t>(j.symbol)] = j.freq;
	}

	outfile.write(reinterpret_cast<const char*>(frequencies), sizeof(frequencies));
}

void HuffmanCoder::decodeFile(std::ifstream& infile, std::ofstream& outfile, std::uint32_t bit_count) {
	char bytes[BUFFER_SIZE];
	Node* walk = m_htree.getRoot();
	
	while(infile) {
		infile.read(bytes, sizeof(bytes));
		for(int j = 0; j < infile.gcount(); j++) {
			for(int i = 0; i < 8; i++) {
				if(bit_count == 0) {
					return;
				}

				if(int bit = (bytes[j] & (1 << (7 - i))) != 0 ? 1 : 0; bit == 0) {
					walk = walk->getLeft();
				} else { 
					walk = walk->getRight();
				}
			    
				if(walk->isLeaf()) {
					outfile.put(walk->getData().symbol);
					walk = m_htree.getRoot();
				}

				bit_count--;
			}
		}

    	}
}
