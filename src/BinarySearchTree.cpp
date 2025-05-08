#include "../include/BinarySearchTree.h"

BinarySearchTree::BinarySearchTree() {
	m_root = nullptr;
	m_count = 0;
}

BinarySearchTree::~BinarySearchTree() {
	clearTree(m_root);
}

Node* BinarySearchTree::getRoot() {
	return m_root;
}

int BinarySearchTree::getCount() {
	return getCount(m_root);	
}

int BinarySearchTree::getCount(Node* subroot) {
	if(subroot == nullptr) {
		return 0;
	}

	return getCount(subroot->getLeft()) + getCount(subroot->getRight()) + 1;
}

void BinarySearchTree::clearTree(Node* subroot) {
	if(subroot == nullptr) {
		return;
	}

	clearTree(subroot->getRight());
	clearTree(subroot->getLeft());

	delete subroot;
}

void BinarySearchTree::insert(char data) {
	if(m_root == nullptr) {
		m_root = new Node(1, data);
		m_count++;
		return;
	} 

	insertHelper(m_root, data);		
}

void BinarySearchTree::insertHelper(Node* subroot, char data) {	
	char rootData = subroot->getData();

	if(rootData == data) {
		subroot->incrementFreq();
		return;
	}

	if(data < rootData) {
		if(subroot->getLeft() == nullptr) {
			subroot->setLeft(new Node(1, data));
			m_count++;
		} else {
			insertHelper(subroot->getLeft(), data);
		}
	} else {
		if(subroot->getRight() == nullptr) {
			subroot->setRight(new Node(1, data));
			m_count++;
		} else {
			insertHelper(subroot->getRight(), data);
		}
	}
}


CharData* BinarySearchTree::inorder() {
	CharData* charData = new CharData[m_count];
	int index = 0;
	fillInorder(m_root, charData, index);
	return charData;
}

void BinarySearchTree::fillInorder(Node* subroot, CharData* array, int& index) {
	if (subroot == nullptr) return;

	fillInorder(subroot->getLeft(), array, index);
	array[index].freq = subroot->getFreq();
    	array[index].data = subroot->getData();
    	index++;
    	fillInorder(subroot->getRight(), array, index);
}

void BinarySearchTree::printInorder() {
	CharData* charData = inorder();

	for(int i = 0; i < m_count - 1; i++) {
		std::cout << '[' << charData[i].data << ':' << charData[i].freq << "]->";
	}

	std::cout << '[' << charData[m_count - 1].data << ':' << charData[m_count - 1].freq << ']';

	std::cout << '\n';

	delete[] charData;
}
