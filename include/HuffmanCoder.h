#ifndef HUFFMAN_CODER_H
#define HUFFMAN_CODER_H

#include <fstream>
#include <cstring>

#include "FrequencyAnalyzer.h"
#include "HuffmanTree.h"
#include "Node.h"

typedef struct {
	bool encodeFlag;
	std::string filename;
} Arguments;

class HuffmanCoder {
	private:
		//variables
		FrequencyAnalyzer m_freq;
		HuffmanTree m_htree;

		//methods
		void encodeFile(std::ifstream&, std::ofstream&, std::uint32_t&);
		void createFreqTree(std::ifstream&);
		void makeFileHeader(std::ofstream&) const;
		void decodeFile(std::ifstream&, std::ofstream&, std::uint32_t);

	public:
		//constructor
		HuffmanCoder();

		//methods
		void encode(const std::string&);
		void decode(const std::string&);
};

#endif
