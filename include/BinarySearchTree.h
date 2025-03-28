#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "../src/BinarySearchNode.cpp"
#include <string>


class BinarySearchTree {
	BinarySearchNode* m_root;

	public:
	BinarySearchTree();
	~BinarySearchTree();
	BinarySearchNode* getRoot();

	void clearTree(BinarySearchNode*);
	void insert(char);
	void insertHelper(BinarySearchNode*, char);

	void inorder();
	void inorderHelper(BinarySearchNode*);
};

#endif
