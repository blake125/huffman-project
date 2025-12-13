#!/bin/bash

path="/home/blake/huffman-project/"

#clean build
cd ${path} && make clean; make 

#remove test 1 if it already happened
rm ./tests/output/diff.txt ./tests/output/test1.txt.huff ./tests/output/test1.txt.test

#generate the random python files
cd ${path} && ./tests/generate_files.py

#create the file
cd ${path} && ./bin/huffman -f ./tests/output/test1.txt -e

#decode the file
cd ${path} && ./bin/huffman -f ./tests/output/test1.txt.huff -d

#compare the diffs of the expected and actual output.
cd ${path} && diff -u ./tests/output/test1.txt ./tests/output/test1.txt.test > ./tests/output/diff.txt

#cat the diff output to make it easier to read
cat ./tests/output/diff.txt
