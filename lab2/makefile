all: add sub

add: add.o
	ld -o add add.o

add.o: add.s
	as -g -o add.o add.s

sub: sub.o
	ld -o sub sub.o

sub.o: sub.s
	as -g -o sub.o sub.s
