all: 1a

1a: 1a.o
	gcc -g -m32 -Wall -o 1a 1a.o
1a.o: 1a.c
	gcc -m32 -g -Wall -ansi -c -Iinclude -o 1a.o 1a.c
.PHONY: clean

clean:
	rm -f *.o 1a