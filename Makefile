OBJS=bin/objs/HuffmanTree.o bin/objs/BinarySearchTree.o bin/objs/HuffFileMaker.o

CC=g++

DEBUG=-Wextra -g3 -Og -fno-optimize-sibling-calls -fno-ipa-icf -fno-omit-frame-pointer -fno-common -fsanitize=address -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=undefined -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=unreachable -fsanitize=vla-bound -fsanitize=null -fsanitize=return -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=bounds-strict -fsanitize=alignment -fsanitize=object-size -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=bool -fsanitize=enum -fsanitize=vptr -fsanitize=pointer-overflow -fsanitize=builtin -fno-sanitize-recover=all -fsanitize-address-use-after-scope -fstack-protector-all

CFLAGS=-Wall -c ${DEBUG} 

LFLAGS=-Wall ${DEBUG}

huffman: ${OBJS} 
	${CC} ${LFLAGS} ${OBJS} ./src/main.cpp -o ./bin/huffman

bin/objs/HuffFileMaker.o: include/HuffFileMaker.h src/HuffFileMaker.cpp include/HuffmanTree.h src/HuffmanTree.cpp include/BinarySearchTree.h src/BinarySearchTree.cpp
	${CC} ${CFLAGS} src/HuffFileMaker.cpp -o bin/objs/HuffFileMaker.o

bin/objs/HuffmanTree.o: include/HuffmanTree.h src/HuffmanTree.cpp include/Node.h
	${CC} ${CFLAGS} src/HuffmanTree.cpp -o bin/objs/HuffmanTree.o

bin/objs/BinarySearchTree.o: include/BinarySearchTree.h src/BinarySearchTree.cpp include/Node.h 
	${CC} ${CFLAGS} src/BinarySearchTree.cpp -o bin/objs/BinarySearchTree.o

clean:
	rm bin/huffman bin/objs/*.o *.huff *.test 

remake:
	make clean; make

test:
	make remake; ./bin/huffman -f README.md -e; ./bin/huffman -f README.md.huff -d
