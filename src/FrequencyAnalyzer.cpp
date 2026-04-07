#include "../include/FrequencyAnalyzer.h"

FrequencyAnalyzer::FrequencyAnalyzer() = default;

void FrequencyAnalyzer::add(const std::uint8_t* buffer, const int size) {
	for(int i = 0; i < size; i++) {
		++m_frequencies[buffer[i]];
	}
}

std::vector<Data> FrequencyAnalyzer::getFrequencies() const {
	std::vector<Data> data;
	for(int i = 0; i < (256); i++) {
		if(m_frequencies[i] != 0) {
			Data piece;
			piece.symbol = i;
			piece.freq = m_frequencies[i];
			data.push_back(piece);
		}
	}

	std::sort(data.begin(), data.end());

	return data;
}