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

void BinarySearchTree::insert(std::uint8_t data) {
	if(m_root == nullptr) {
		m_root = new Node(1, data);
		m_count++;
		return;
	} 

	insertHelper(m_root, data);		
}

void BinarySearchTree::insertHelper(Node* subroot, std::uint8_t data) {	
	std::uint8_t rootData = subroot->getData().symbol;

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


std::vector<struct Data> BinarySearchTree::inorder() {
	std::vector<struct Data> data;

	fillInorder(m_root, data);

	return data;
}

void BinarySearchTree::fillInorder(Node* subroot, std::vector<struct Data> &data) {
	if (subroot == nullptr) return;

	fillInorder(subroot->getLeft(), data);
	data.push_back(subroot->getData());
	fillInorder(subroot->getRight(), data);
}

void BinarySearchTree::printInorder() {
	std::vector<struct Data> data = inorder();

	for(int i = 0; i < (int)data.size() - 1; i++) {
		std::cout << '[' << data.at(i).symbol << ':' << data.at(i).freq << "]->";
	}

	std::cout << '[' << data.back().symbol << ':' << data.back().freq << ']';

	std::cout << '\n';
}
