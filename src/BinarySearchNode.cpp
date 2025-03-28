#include "../include/BinarySearchNode.h"

BinarySearchNode::BinarySearchNode(int freq, char data) {
	m_left = nullptr;
	m_right = nullptr;
	m_freq = freq;
	m_data = data;
}	

BinarySearchNode* BinarySearchNode::getLeft() {
	return m_left;
}

BinarySearchNode* BinarySearchNode::getRight() {
	return m_right;
}

int BinarySearchNode::getFreq() {
	return m_freq;
}

char BinarySearchNode::getData() {
	return m_data;
}

void BinarySearchNode::setLeft(BinarySearchNode* left) {
	m_left = left;
}

void BinarySearchNode::setRight(BinarySearchNode* right) {
	m_right = right;
}

void BinarySearchNode::incrementFreq() {
	m_freq++;
}
