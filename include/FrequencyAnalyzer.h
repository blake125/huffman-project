#ifndef FREQUENCY_ANALYZER_H
#define FREQUENCY_ANALYZER_H

#include <map>
#include <vector>
#include <algorithm>

#include "Node.h"

class FrequencyAnalyzer {
	private:
		std::map<std::uint8_t, std::uint32_t> m_freqMap;
	public:
		FrequencyAnalyzer();

		void add(const std::uint8_t*, const int);
		std::vector<Data> getMap();
};

#endif
