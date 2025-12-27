#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>

#include "Node.h"
#include <vector>

class BinarySearchTree {
	private:
		//variables
		Node* m_root;
		std::uint32_t m_count;

		//methods
		int getCount(Node*);
		void clearTree(Node*);
		void insertHelper(Node*, std::uint8_t);
		void fillInorder(Node*, std::vector<struct Data>&);

	public:
		//constructor
		BinarySearchTree();
		~BinarySearchTree();

		//methods
		Node* getRoot();
		int getCount();
		void insert(std::uint8_t);
		std::vector<struct Data> inorder();
		void printInorder();
};

#endif
