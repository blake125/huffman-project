#ifndef HUFFMAN_CODER_H
#define HUFFMAN_CODER_H

#include <fstream>
#include <cstring>
#include <algorithm>
#include <cstdio>

#include "BinarySearchTree.h"
#include "HuffmanTree.h"
#include "Node.h"

typedef struct {
	bool encodeFlag;
	std::string filename;
} Arguments;

class HuffmanCoder {
	private:
		//variables
		BinarySearchTree m_bst;
		HuffmanTree m_htree;

		//methods
		void encodeFile(std::ifstream&, std::ofstream&, std::uint32_t&);
		void createFreqTree(std::ifstream&);
		void makeFileHeader(std::ofstream&);
		void decodeFile(std::ifstream&, std::ofstream&, std::uint32_t);

	public:
		//constructor
		HuffmanCoder(Arguments);

		//methods
		void encode(const char*);
		void decode(const char*);
};

#endif
