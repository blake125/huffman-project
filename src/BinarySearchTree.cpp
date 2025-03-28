#include "../include/BinarySearchTree.h"

BinarySearchTree::BinarySearchTree() {
	m_root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
	clearTree(m_root);
}

BinarySearchNode* BinarySearchTree::getRoot() {
	return m_root;
}

void BinarySearchTree::clearTree(BinarySearchNode* subroot) {
	if(subroot == nullptr) {
		return;
	}

	clearTree(subroot->getRight());
	clearTree(subroot->getLeft());

	delete subroot;
}

void BinarySearchTree::insert(char data) {
	insertHelper(m_root, data);
}

void BinarySearchTree::insertHelper(BinarySearchNode* subroot, char data) {
	if(subroot == nullptr) {
		m_root = new BinarySearchNode(1, data);
		return;
	}

	char rootData = subroot->getData();

	if(rootData == data) {
		subroot->incrementFreq();
		return;
	}

	if(data < rootData) {
		if(subroot->getLeft() == nullptr) {
			subroot->setLeft(new BinarySearchNode(1, data));
		} else {
			insertHelper(subroot->getLeft(), data);
		}
	} else {
		if(subroot->getRight() == nullptr) {
			subroot->setRight(new BinarySearchNode(1, data));
		} else {
			insertHelper(subroot->getRight(), data);
		}
	}
}

void BinarySearchTree::inorder() {
	inorderHelper(m_root);	
}

void BinarySearchTree::inorderHelper(BinarySearchNode* subroot) {
	if(subroot == nullptr) {
		return;
	}

	inorderHelper(subroot->getLeft());
	std::cout << '[' << subroot->getData() << ", " << subroot->getFreq() << ']';
	inorderHelper(subroot->getRight());
}
