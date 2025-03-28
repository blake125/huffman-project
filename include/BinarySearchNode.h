#ifndef BINARY_SEARCH_NODE_H
#define BINARY_SEARCH_NODE_H

class BinarySearchNode;

class BinarySearchNode {
	BinarySearchNode* m_left;
	BinarySearchNode* m_right;

	int m_freq;
	char m_data;

	public:
	BinarySearchNode(int, char);

	BinarySearchNode* getLeft();
	BinarySearchNode* getRight();
	int getFreq();
	char getData();
	
	void setLeft(BinarySearchNode*);
	void setRight(BinarySearchNode*);
	void incrementFreq();
};

#endif

