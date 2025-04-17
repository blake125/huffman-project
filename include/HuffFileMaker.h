#ifndef HUFF_FILE_MAKER_H
#define HUFF_FILE_MAKER_H

#include <fstream>

#include "../include/BinarySearchTree.h"
#include "../include/HuffmanTree.h"

void makeEncodedFile(const char*);
void encodeFile(std::string, std::ifstream&, HuffmanTree*);

void createFreqTree(std::ifstream&, BinarySearchTree*);
void quickSort(CharData*, int, int);
int partition(CharData*, int, int);

/*WORKING ON IT...
void makeDecodedFile(const char*);
void makeFileHeader(std::ofstream&, HuffmanTree*);
void decodeFile(std::ifstream&, HuffmanTree*, std::string);
*/
#endif
