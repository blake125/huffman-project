#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <vector>
#include <string>
#include "Node.h"

class HuffmanTree {
	Node* m_root;

	public:
	HuffmanTree(CharData*, int);
	~HuffmanTree();
	void clearTree(Node*);

	std::string findPath(char);
	bool getPath(Node*, std::vector<char>&, char, char);
};

#endif
