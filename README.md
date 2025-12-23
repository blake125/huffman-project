# Huffman Compression Tool

An implementation of the Huffman coding algorithm for file compression in **C++**

## Features
- File compression and decompression using Huffman coding.
- All file types supported! 
- Character frequency analysis via a custom binary search tree.
- Huffman tree implementation generated via priority queue.
- Custom file format for Huffman-encoded data.

## Future/in-progress updates  
- Canonical Huffman codes to reduce file header size.
- Bitset implementation for storing binary codes.

## How to install/run: 

``` bash
    git clone https://github.com/blake125/huffman-project
    cd huffman-project 
    make # (OPTIONAL) DEBUG=1
    ./bin/huffman -f [FILENAME] [-e(ncode) || -d(ecode)]
```

## Example:

I've also included a quick/basic test where this README.md gets encoded and decoded:

``` bash
    make test
```
You will see README.huff and README.md.test as outputs of this command, which are the compressed and decompressed files respectively. To remove these files, use the command:

```bash
    make clean
```

## Technologies Used
- **Make** for building
- **C++** for algorithm implementation
- **Python** and **bash** for testing

## Current Limitations
- Since the frequency tables are developed locally and the file format follows the "naive" approach according to the Wikipedia, smaller files may actually end up getting expanded rather than compressed.

## Sources 

Huffman coding on Wikipedia [here](https://en.wikipedia.org/wiki/Huffman_coding).
