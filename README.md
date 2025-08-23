# Huffman Compression Tool

An implementation of the Huffman coding algorithm for file compression in **C++**

## Features
- Compression using Huffman coding algorithm  
- Binary search tree for frequency analysis  
- Bit-level encoding/decoding with proper padding handling  
- Works with any file type (text, binary, images, etc.)  
- Custom `.huff` file format with magic number validation  

## How to install/run: 

``` bash
    git clone https://github.com/blake125/huffman-project
    cd huffman-project 
    make
    ./bin/huffman -f [FILENAME] [-e(ncode) || -d(ecode)]
```

## Example:

I've also included a quick/basic test where the README of this project gets encoded and decoded

``` bash
    make test
```

## Technical Implementation
- **Data Structures:** BST for frequency counting, priority queue for Huffman tree construction  
- **File Format:** Custom header with magic number `"HUFF"` + frequency table + compressed data  
- **Bit Manipulation:** Manual bit packing/unpacking  

## Current Limitations
- Since the frequency tables are developed locally, smaller files may actually end up getting expanded rather than decoded
- ASCII/single-byte characters fully supported, multibyte UTF-8 is not working correctly yet  
