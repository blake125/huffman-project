# huffman-project
My implementation of a Huffman encoder/decoder in C++.

I'm still in the prelimary steps of creating this, so the build and run instructions aren't complete (yet!).

Usage/build instructions:

After cloning the repo, use the command "make" in the root folder.
To run, use the command
    "./bin/huffman.exe -f [FILENAME/FILEPATH] -[e(encode)/d(decode)]"
in the root folder as well.

This program will create a huffman tree that it'll use to make a new (compressed) file in the root directory.

Keep in mind, I'm not keeping track of the tree data yet, so there's no way to decode...

I added the first chapter of Alice in Wonderland into a .txt file to help demonstrate how it works.
