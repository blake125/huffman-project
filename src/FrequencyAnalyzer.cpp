#include "../include/FrequencyAnalyzer.h"

FrequencyAnalyzer::FrequencyAnalyzer() = default;

void FrequencyAnalyzer::add(const std::uint8_t* buffer, const int size) {
	for(int i = 0; i < size; i++) {
		++m_freqMap[buffer[i]];
	}
}

std::vector<Data> FrequencyAnalyzer::getMap() {
	std::vector<Data> data;
	for(int i = 0; i < (std::uint8_t)255; i++) {
		if(m_freqMap.count(i) != 0) {
			Data piece;
			piece.symbol = i;
			piece.freq = m_freqMap.at(i);
			data.push_back(piece);
		}
	}

	std::sort(data.begin(), data.end());

	return data;
}
