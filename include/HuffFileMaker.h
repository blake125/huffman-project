#ifndef HUFF_FILE_MAKER_H
#define HUFF_FILE_MAKER_H

#include <fstream>
#include <cstring>
#include <algorithm>

#include "BinarySearchTree.h"
#include "HuffmanTree.h"
#include "Node.h"

void makeEncodedFile(const char*);
void encodeFile(std::ifstream&, HuffmanTree*, std::ofstream&, std::uint32_t&);

void createFreqTree(std::ifstream&, BinarySearchTree*);

void makeDecodedFile(const char*);
void makeFileHeader(std::ofstream&, BinarySearchTree*);
void decodeFile(std::ifstream&, HuffmanTree*, std::ofstream&, std::uint32_t);
#endif
