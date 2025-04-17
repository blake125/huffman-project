#ifndef NODE_H
#define NODE_H

#include <cstdint>

struct CharData {
	std::uint32_t freq;
	char data;
};

class Node;

class Node {
	Node* m_left;
	Node* m_right;

	int m_freq;
	char m_data;

	public:
	Node(int, char);

	Node* getLeft();
	Node* getRight();
	int getFreq();
	char getData();
	
	void setLeft(Node*);
	void setRight(Node*);
	void incrementFreq();
};

#endif

