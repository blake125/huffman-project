#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <algorithm>

#include "Node.h"

class HuffmanTree {
	private:
		//variables
		Node* m_root;
		std::uint8_t m_count;
		std::unordered_map<std::uint8_t, std::string> symbol_map;
	
		//methods
		static void clearTree(Node*);
		bool getPath(Node*, std::vector<char>&, std::uint8_t, char);
		void populateMap(Node*);
		std::string findPath(std::uint8_t);
		void canonizeCodes();
	public:
		//constructor
		HuffmanTree();
		~HuffmanTree();

		//methods
		void populateTree(const std::vector<struct Data>&);
		Node* getRoot() const;
		std::string retrievePath(std::uint8_t);
		bool empty() const;
};

#endif
