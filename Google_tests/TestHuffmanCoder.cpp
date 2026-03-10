//
// Created by blake on 3/8/2026.
//

#include <string>
#include <fstream>
#include <sstream>
#include <gtest/gtest.h>
#include "../include/HuffmanCoder.h"

std::string readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);

    std::ostringstream ss;
    ss << file.rdbuf();

    return ss.str();
}

TEST(HuffmanCoderTest, EncodeDecodeTest) {
    HuffmanCoder coder;

    std::string readme = "../README.md";
    std::string readmeHuff = readme + ".huff";
    std::string outputFile = readme + ".test";

    coder.encode(readme);
    coder.decode(readmeHuff);

    const std::string expected = readFile(readme);
    const std::string real = readFile(outputFile);

    ASSERT_EQ(expected, real);
}