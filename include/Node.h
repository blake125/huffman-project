#ifndef INCLUDE_NODE_H
#define INCLUDE_NODE_H

#include <cstdint>

struct Data {
	std::uint32_t freq;
	char symbol;

	bool operator<(Data& data) const { return freq < data.freq; }
	Data() : freq(0), symbol('0') {}
	Data(std::uint32_t frequency, char character) : freq(frequency), symbol(character) {}
};

class Node {
	Node* m_left;
	Node* m_right;

	struct Data m_data;

	public:

	inline Node() : m_left(nullptr), m_right(nullptr), m_data() {}

	inline Node(std::uint32_t freq, char data) {
		m_data.freq = freq; 
		m_data.symbol = data;

		m_left = nullptr;
		m_right = nullptr;
	}

	inline Node* getLeft() { return m_left; }
	inline Node* getRight(){ return m_right; }
	inline Data getData() { return m_data; }

	inline void setLeft(Node* node){ m_left = node; }
	inline void setRight(Node* node){ m_right = node; }
	inline void incrementFreq(){ m_data.freq++; }
};

#endif

