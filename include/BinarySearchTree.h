#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>

#include "Node.h"
#include <vector>

class BinarySearchTree {
	Node* m_root;
	std::uint32_t m_count;

	public:
	BinarySearchTree();
	~BinarySearchTree();
	Node* getRoot();
	int getCount();
	int getCount(Node*);

	void clearTree(Node*);
	void insert(char);
	void insertHelper(Node*, char);

	std::vector<struct Data> inorder();
	void fillInorder(Node*, std::vector<struct Data>&);
	void printInorder();
};

#endif
