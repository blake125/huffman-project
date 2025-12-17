#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include <queue>
#include <unordered_map>

#include "Node.h"

class HuffmanTree {
	Node* m_root;
	std::uint8_t m_count;	
	std::unordered_map<std::uint8_t, std::string> symbol_map;
	
	private:
	void clearTree(Node*);
	bool getPath(Node*, std::vector<char>&, std::uint8_t, char);
	
	public:
	HuffmanTree(std::vector<struct Data>);
	~HuffmanTree();

	std::string findPath(std::uint8_t);
	Node* getRoot();
	std::string retrievePath(std::uint8_t);
	void populate_map(Node*);
};

#endif
