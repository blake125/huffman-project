project(Google_tests)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(Google_Tests_run TestHuffmanCoder.cpp
        TestFrequencyAnalyzer.cpp
)

# linking Google_Tests_run with DateConverter_lib which will be teste
target_link_libraries(Google_Tests_run PRIVATE
        GTest::gtest
        GTest::gtest_main
        huffman_lib
)
