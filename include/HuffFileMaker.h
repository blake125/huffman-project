#ifndef HUFF_FILE_MAKER_H
#define HUFF_FILE_MAKER_H

#include <fstream>
#include <cstdint>
#include <cmath>
#include <cstring>
#include <iostream>
#include "../include/BinarySearchTree.h"
#include "../include/HuffmanTree.h"

void makeEncodedFile(const char*);
//void makeDecodedFile(const char*);

void createFreqTree(std::ifstream&, BinarySearchTree*);
void quickSort(CharData*, int, int);
int partition(CharData*, int, int);

void encodeFile(std::string, std::ifstream&, HuffmanTree*);

//void makeFileHeader(std::ofstream&, HuffmanTree*);
void decodeFile(std::ifstream&);

#endif
