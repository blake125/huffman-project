#ifndef HUFF_FILE_MAKER_H
#define HUFF_FILE_MAKER_H

#include <fstream>
#include <cstring>

#include "BinarySearchTree.h"
#include "HuffmanTree.h"
#include "Node.h"

void makeEncodedFile(const char*);
void encodeFile(std::ifstream&, HuffmanTree*, std::ofstream&);

void createFreqTree(std::ifstream&, BinarySearchTree*);
void quickSort(CharData*, int, int);
int partition(CharData*, int, int);

void makeDecodedFile(const char*);
void makeFileHeader(std::ofstream&, BinarySearchTree*);
void decodeFile(std::ifstream&, HuffmanTree*, std::ofstream&);
#endif
