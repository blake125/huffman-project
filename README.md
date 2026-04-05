# Huffman Compression Tool

An implementation of the Huffman coding algorithm for file compression in **C++**

## Prerequisites

- **g++** (GNU C++ Compiler), version 13 or higher 
- **CMake** 3.16 or newer
- **[GoogleTest](https://github.com/google/googletest)**

## Features
- File compression and decompression using Huffman coding.
- All file types supported!
- Huffman tree implementation generated via priority queue.
- Custom file format for Huffman-encoded data.

## Future/in-progress updates  
- Canonical Huffman codes to reduce file header size.
- Bitset implementation for storing binary codes.

## Installation instructions: 

``` bash
    git clone https://github.com/blake125/huffman-project
    cd huffman-project
```

## Build instructions:

``` bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
```

## Usage instructions
From the root directory, the command is structured as follows:
```
    ./build/huffman -f [FILENAME] -[e (for encoding) | d (for decoding) ]
```

## If you want to run my test(s):
From the build directory, run the following:
```
    ./Google_tests/Google_Tests_run
```

## Extra Information

To avoid file loss, newly decoded files are written to a new file with the name "[ORIGINAL FILENAME].test".
The "-d" flag requires that [FILENAME] has a ".huff" extension.

## Current Limitations
- Since the frequency tables are developed locally and the file format follows the "naive" approach according to the Wikipedia, smaller files may actually end up getting expanded rather than compressed.

## Sources 

Huffman coding on Wikipedia [here](https://en.wikipedia.org/wiki/Huffman_coding).
