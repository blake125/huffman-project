//
// Created by blake on 3/8/2026.
//

#include <string>
#include <cstdio>
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

TEST(HuffmanCoderTests, EncodeDecodeTest) {
    const std::string readme = "../Google_tests/test_files/readme.md";
    HuffmanCoder coder;

    coder.encode(readme);
    coder.decode(readme + ".huff");

    const std::string expected = readFile(readme);
    const std::string real = readFile(readme + ".test");

    ASSERT_EQ(expected, real);

    const std::string readmeTest = readme + ".test";
    std::remove(readmeTest.c_str());

    const std::string readmeHuff = readme + ".huff";
    std::remove(readmeHuff.c_str());
}

TEST(HuffmanCoderTests, EmptyFileTest) {
    const std::string empty = "../Google_tests/test_files/empty.txt";
    HuffmanCoder coder;
    coder.encode(empty);
    coder.decode(empty + ".huff");

    ASSERT_EQ(readFile(empty), readFile(empty + ".test"));

    const std::string emptyTest = empty + ".test";
    std::remove(emptyTest.c_str());

    const std::string emptyHuff = empty + ".huff";
    std::remove(emptyHuff.c_str());
}