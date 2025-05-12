# huffman-project
My implementation of a Huffman encoder/decoder in C++.

Currently, the encoder only supports one byte UTF-8 characters.

Since the frequency tables are developed locally, smaller files
actually end up getting expanded rather than decoded.

To clone, use the command
    "git clone "https://github.com/blake125/huffman-project""

Here is the usage of the program:
    "./bin/huffman -f [FILENAME] [-e(ncode) || -d(ecode)]"

I've included a "make test" shortcut that will encode and decode
this README. However, since the file size is so small, the encoder
doesn't actually get to show off.

Features in development:
    -Full UTF-8 encoding (multibyte)
    -Global frequency analysis option (improves smaller file compression)
