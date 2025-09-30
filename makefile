#Default target: builds the final executable
all: escape


escape: escape.o fileimport.o color.o
	gcc -o escape escape.o fileimport.o color.o


escape.o: escape.c escape.h fileimport.h
	gcc -Wall -ansi -pedantic -c escape.c


fileimport.o: fileimport.c fileimport.h color.h
	gcc -Wall -ansi -pedantic -c fileimport.c


color.o: color.c color.h
	gcc -Wall -ansi -pedantic -c color.c

clean:
	rm -f escape escape.o fileimport.o color.o
