OBJS=bin/objs/Node.o bin/objs/HuffmanTree.o bin/objs/BinarySearchTree.o

CC=g++

DEBUG=-Wextra -g3 -Og -fno-optimize-sibling-calls -fno-ipa-icf -fno-omit-frame-pointer -fno-common -fsanitize=address -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=undefined -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=unreachable -fsanitize=vla-bound -fsanitize=null -fsanitize=return -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=bounds-strict -fsanitize=alignment -fsanitize=object-size -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=bool -fsanitize=enum -fsanitize=vptr -fsanitize=pointer-overflow -fsanitize=builtin -fno-sanitize-recover=all -fsanitize-address-use-after-scope -fstack-protector-all

CFLAGS=-Wall -c ${DEBUG} 

LFLAGS=-Wall ${DEBUG}

huffman.exe: ${OBJS} 
	${CC} ${LFLAGS} ${OBJS} ./src/main.cpp -o ./bin/huffman.exe

bin/objs/HuffmanTree.o: include/HuffmanTree.h src/HuffmanTree.cpp include/Node.h src/Node.cpp
	${CC} ${CFLAGS} src/HuffmanTree.cpp -o bin/objs/HuffmanTree.o

bin/objs/BinarySearchTree.o: include/BinarySearchTree.h src/BinarySearchTree.cpp include/Node.h src/Node.cpp
	${CC} ${CFLAGS} src/BinarySearchTree.cpp -o bin/objs/BinarySearchTree.o

bin/objs/Node.o: include/Node.h src/Node.cpp
	${CC} ${CFLAGS} src/Node.cpp -o bin/objs/Node.o

clean:
	rm bin/huffman.exe bin/obs/*.0

