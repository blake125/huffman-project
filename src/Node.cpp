#include "../include/Node.h"

Node::Node(int freq, char data) {
	m_left = nullptr;
	m_right = nullptr;
	m_freq = freq;
	m_data = data;
}	

Node* Node::getLeft() {
	return m_left;
}

Node* Node::getRight() {
	return m_right;
}

int Node::getFreq() {
	return m_freq;
}

char Node::getData() {
	return m_data;
}

void Node::setLeft(Node* left) {
	m_left = left;
}

void Node::setRight(Node* right) {
	m_right = right;
}

void Node::incrementFreq() {
	m_freq++;
}
