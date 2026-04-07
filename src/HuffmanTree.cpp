#include "../include/HuffmanTree.h"

#include <sys/stat.h>

HuffmanTree::HuffmanTree() {
	m_root = nullptr;
	m_count = 0;
};

void HuffmanTree::populateTree(const std::vector<Data> &data) {
	if (data.empty()) {
		m_root = nullptr;
		return;
	}

	std::vector<Node*> list;
	for(const auto i : data) {
		list.push_back(new Node(i.freq, i.symbol));
	}

	while(static_cast<int>(list.size()) > 1) {
		Node* parent;
		parent = new Node(list.at(0)->getData().freq + list.at(1)->getData().freq, '0');
		parent->setLeft(list.at(0));
		parent->setRight(list.at(1));

		list.erase(list.begin(), list.begin() + 2);

		int index = 0;
		while(index != static_cast<int>(list.size())
				&& list.at(index)->getData().freq < parent->getData().freq) {
			index++;
		}

		list.insert(list.begin() + index, parent);
		m_count++;
	}

	m_root = list.at(0);

	//populates a map with the list of
	//paths so lookup is easier when encoding
	populateMap(m_root);
	canonizeCodes();
}

void HuffmanTree::populateMap(Node* subroot) {
	if(subroot == nullptr) {
		return;
	}

	if(subroot->isLeaf()) {
		const std::uint8_t data = subroot->getData().symbol;
		symbol_map[data] = findPath(data); 
	}

	populateMap(subroot->getLeft());
	populateMap(subroot->getRight());
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

std::string HuffmanTree::retrievePath(std::uint8_t data) {
	return symbol_map[data];
}

std::string HuffmanTree::findPath(std::uint8_t data) {
	if(std::vector<char> path; !getPath(m_root, path, data, -1)) {
		std::cout << "Couldn't find " << data << std::endl;
		return "";
	} else {
		std::string pathStr;
		for(const char i : path) {
			pathStr += i;
		}
		
		return pathStr;
	}
}

bool HuffmanTree::getPath(Node* subroot, std::vector<char>& path, const std::uint8_t target, const char dir) {
	if(subroot == nullptr) {
		return false;
	}

	if(m_root != subroot) {
		path.push_back(dir);
	}

	if(subroot->getData().symbol == target 
			&& subroot->isLeaf()) {
		return true;
	}	

	if(getPath(subroot->getLeft(), path, target, '0') 
			|| getPath(subroot->getRight(), path, target, '1')) {
				return true;
	}

	path.pop_back();
	return false;
}

Node* HuffmanTree::getRoot() const {
	return m_root;
}

void HuffmanTree::canonizeCodes() {

}

bool HuffmanTree::empty() const {
	return m_root == nullptr;
}