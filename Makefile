all:
	gcc -g -c Reader.c Xorer.c
	gcc -o Xorer Xorer.o
	gcc -o Reader Reader.o
	rm Xorer.o Reader.o
