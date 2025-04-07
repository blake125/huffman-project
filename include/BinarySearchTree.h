#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include "Node.h"

class BinarySearchTree {
	Node* m_root;
	int m_count;

	public:
	BinarySearchTree();
	~BinarySearchTree();
	Node* getRoot();
	int getCount();
	int getCount(Node*);

	void clearTree(Node*);
	void insert(char);
	void insertHelper(Node*, char);

	CharData* inorder();
	void printInorder();
};

#endif
