#include "../include/HuffmanTree.h"

HuffmanTree::HuffmanTree(CharData* data, int size) {
	m_count = (std::uint8_t)size;

	std::vector<Node*> list;

	for(int i = 0; i < size; i++) {
		list.push_back(new Node(data[i].freq, data[i].data));
	}

	while((int)list.size() != 1) {
		Node* parent = new Node(list.at(0)->getFreq() + list.at(1)->getFreq(), '0');
		parent->setLeft(list.at(0));
		parent->setRight(list.at(1));

		list.erase(list.begin(), list.begin() + 2);

		int index = 0;
		while(index != (int)list.size() 
				&& list.at(index)->getFreq() < parent->getFreq()) {
			index++;
		}

		list.insert(list.begin() + index, parent);
		
	}

	m_root = list.at(0);

}

HuffmanTree::~HuffmanTree() {
	clearTree(m_root);
}

void HuffmanTree::clearTree(Node* subroot) {
	if(subroot == nullptr) {
		return;
	}

	clearTree(subroot->getLeft());
	clearTree(subroot->getRight());

	delete subroot;
}

std::string HuffmanTree::findPath(char data) {
	std::vector<char> path;
	std::string pathStr;

	if(!getPath(m_root, path, data, -1)) {
		std::cout << "Couldn't find " << data << std::endl;
		return "0";
	} else {
		for(int i = 0; i < (int)path.size(); i++) {
			pathStr += path[i];
		}
		
		return pathStr;
	}
}

bool HuffmanTree::getPath(Node* subroot, std::vector<char>& path, char target, char dir) {
	if(subroot == nullptr) {
		return false;
	}

	if(m_root != subroot) {
		path.push_back(dir);
	}

	if(subroot->getData() == target 
			&& subroot->getLeft() == nullptr 
			&& subroot->getRight() == nullptr) {
		return true;
	}	

	if(getPath(subroot->getLeft(), path, target, '0') 
			|| getPath(subroot->getRight(), path, target, '1')) {
				return true;
	}

	path.pop_back();
	return false;
}

Node* HuffmanTree::getRoot() {
	return m_root;
}
