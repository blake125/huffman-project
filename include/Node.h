#ifndef INCLUDE_NODE_H
#define INCLUDE_NODE_H

#include <cstdint>

struct CharData {
	std::uint32_t freq;
	char data;
};

class Node {
	Node* m_left;
	Node* m_right;

	std::uint32_t m_freq;
	char m_data;

	public:

	inline Node() : m_left(nullptr), m_right(nullptr), m_freq(0), m_data('0') {}

	inline Node(std::uint32_t freq, char data){
		m_freq = freq; 
		m_data = data;

		m_left = nullptr;
		m_right = nullptr;
	}

	inline Node* getLeft() { return m_left; }
	inline Node* getRight(){ return m_right; }
	inline std::uint32_t getFreq(){ return m_freq; }
	inline char getData(){ return m_data; }
	
	inline void setLeft(Node* node){ m_left = node; }
	inline void setRight(Node* node){ m_right = node; }
	inline void incrementFreq(){ m_freq++; }
};

#endif

