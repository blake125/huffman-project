#ifndef FREQUENCY_ANALYZER_H
#define FREQUENCY_ANALYZER_H

#include <vector>
#include <algorithm>

#include "Node.h"

class FrequencyAnalyzer {
	private:
		std::uint32_t m_frequencies[256];
	public:
		FrequencyAnalyzer();

		void add(const std::uint8_t*, int);
		[[nodiscard]] std::vector<Data> getFrequencies() const;
};

#endif
