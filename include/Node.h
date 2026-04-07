#ifndef INCLUDE_NODE_H
#define INCLUDE_NODE_H

#include <cstdint>

struct Data {
	std::uint32_t freq;
	std::uint8_t symbol;

	Data() : freq(0), symbol('0') {}
	Data(std::uint32_t frequency, std::uint8_t character) : freq(frequency), symbol(character) {}
	bool operator<(const Data& data) const { return freq < data.freq; }
	bool operator>(const Data& data) const { return freq > data.freq; }
	bool operator==(const Data& data) const { return (freq == data.freq) && (symbol == data.symbol); }
};

class Node {
	Node* m_left;
	Node* m_right;
	Data m_data;

	public:
		Node() : m_left(nullptr), m_right(nullptr), m_data() {}
		Node(Data data) : m_left(nullptr), m_right(nullptr), m_data(data) {}
		Node(std::uint32_t freq, std::uint8_t data) {
			m_data.freq = freq;
			m_data.symbol = data;

			m_left = nullptr;
			m_right = nullptr;
		}

		Node* getLeft() { return m_left; }
		Node* getRight(){ return m_right; }
		Data getData() { return m_data; }

		void setLeft(Node* node){ m_left = node; }
		void setRight(Node* node){ m_right = node; }
		void incrementFreq(){ m_data.freq++; }

		bool isLeaf() { return (m_left == nullptr && m_right == nullptr); }
};

class CompareNodePtrs {
	public:
		bool operator()(Node* node1, Node* node2) { return node1->getData().freq < node2->getData().freq; }
};

#endif