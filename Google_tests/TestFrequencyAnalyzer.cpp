//
// Created by blake on 3/21/2026.
//

#include <cmath>
#include <gtest/gtest.h>
#include "../include/FrequencyAnalyzer.h"

TEST(FrequencyAnalyzerTests, BasicInsertionTest) {
    FrequencyAnalyzer f;

    constexpr unsigned char data[] = { 'a' };

    f.add(data, 1);

    std::vector<Data> v = f.getFrequencies();

    std::vector<Data> expected;
    expected.emplace_back(1, 'a');

    ASSERT_EQ(expected, v);
}

TEST(FrequencyAnalyzerTests, BasicIncrementTest) {
    FrequencyAnalyzer f;

    constexpr unsigned char data[] = { 'a', 'a', 'b', 'b' };

    f.add(data, 4);

    std::vector<Data> v = f.getFrequencies();

    std::vector<Data> expected;
    expected.emplace_back(2, 'a');
    expected.emplace_back(2, 'b');

    ASSERT_EQ(expected, v);
}