build:
	g++ -g elfinfo.cpp -o elfinfo

run:
	./elfinfo ./elfinfo

build_hello64:
	nasm -f elf64 hello.asm
	ld -o hello hello.o
	./hello

build_hello32:
	gcc -g -static -m32 -o hello hello.c

build_load:
	gcc -g ./load.c -o load