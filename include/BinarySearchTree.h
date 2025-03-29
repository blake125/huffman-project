#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "../src/BinarySearchNode.cpp"
#include <string>

struct CharData {
	int freq;
	char data;
};

class BinarySearchTree {
	BinarySearchNode* m_root;
	int m_count;

	public:
	BinarySearchTree();
	~BinarySearchTree();
	BinarySearchNode* getRoot();

	void clearTree(BinarySearchNode*);
	void insert(char);
	void insertHelper(BinarySearchNode*, char);

	CharData* inorder();
	void printInorder();
};

#endif
