all: hexaprint

hexaprint: hexaprint.o
	gcc -g -m32 -Wall -o hexaprint hexaprint.o
hexaprint.o: hexaPrint.c
	gcc -m32 -g -Wall -ansi -c -Iinclude -o hexaprint.o hexaPrint.c
.PHONY: clean

clean:
	rm -f *.o hexaprint