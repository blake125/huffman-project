cmake_minimum_required(VERSION 3.16)
project(huffman-project)

set(SOURCE_FILES
    src/main.cpp
        src/HuffmanTree.cpp
        src/HuffmanCoder.cpp
        src/FrequencyAnalyzer.cpp
)

set(HEADER_FILES
    include/FrequencyAnalyzer.h
        include/HuffmanCoder.h
        include/HuffmanTree.h
        include/Node.h
)

add_executable(huffman ${SOURCE_FILES})
target_include_directories(huffman PRIVATE include)

add_library(huffman_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_subdirectory(Google_tests)