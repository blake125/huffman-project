# huffman-project
My implementation of a Huffman encoder/decoder in C++.

As of right now, it can only encode/decode one byte UTF-8 characters.
Full UTF-8 functionality coming soon!

Usage/build instructions:

After cloning the repo, use the command "make" in the root folder.
To run, use the command
    "./bin/huffman.exe -f [FILENAME/FILEPATH] -[e(encode)/d(decode)]"
in the root folder as well.

This program will create a huffman tree that it'll use to make a new (compressed) file in the root directory.

Since the frequency analysis is local to the file, it requires a (rather large) header to aid in the decoding process.

For a more simple test, I added a "make test" that will encode this very markdown file.
Because of the file header, this small example doesn't show off the actual capabilities of the compressor. 
