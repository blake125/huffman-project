#include "../include/BinarySearchTree.h"

BinarySearchTree::BinarySearchTree() {
	m_root = nullptr;
	m_count = 0;
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
	if(m_root == nullptr) {
		m_root = new BinarySearchNode(1, data);
		m_count++;
	} else {
		insertHelper(m_root, data);
	}
}

void BinarySearchTree::insertHelper(BinarySearchNode* subroot, char data) {	
	char rootData = subroot->getData();

	if(rootData == data) {
		subroot->incrementFreq();
		return;
	}

	if(data < rootData) {
		if(subroot->getLeft() == nullptr) {
			subroot->setLeft(new BinarySearchNode(1, data));
			m_count++;
		} else {
			insertHelper(subroot->getLeft(), data);
		}
	} else {
		if(subroot->getRight() == nullptr) {
			subroot->setRight(new BinarySearchNode(1, data));
			m_count++;
		} else {
			insertHelper(subroot->getRight(), data);
		}
	}
}

CharData* BinarySearchTree::inorder() {
	CharData* charData = new CharData[m_count];	
	int index = 0;
	
	BinarySearchNode* current = m_root;
	while(current != nullptr) {
		if(current->getLeft() == nullptr) {
			charData[index].freq = current->getFreq();
			charData[index].data = current->getData();
			index++;
			current = current->getRight();
		} else {
			BinarySearchNode* pre = current->getLeft();

			while(pre->getRight() != nullptr && pre->getRight() != current) {
				pre = pre->getRight();
			}

			if(pre->getRight() == nullptr) {
				pre->setRight(current);
				current = current->getLeft();
			} else {
				pre->setRight(nullptr);
				charData[index].freq = current->getFreq();
				charData[index].data = current->getData();
				index++;

				current = current->getRight();
			}
		}
	}

	return charData;
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
