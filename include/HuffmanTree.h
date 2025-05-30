#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include <queue>

#include "Node.h"

class HuffmanTree {
	Node* m_root;
	std::uint8_t m_count;	
	
	private:
	void clearTree(Node*);
	bool getPath(Node*, std::vector<char>&, char, char);
	
	public:
	HuffmanTree(std::vector<struct Data>);
	~HuffmanTree();

	std::string findPath(char);
	Node* getRoot();
};

#endif
