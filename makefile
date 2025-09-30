CC = gcc
CFLAGS = -Wall -ansi -pedantic
EXEC = escapeGame

$(EXEC): fileimport.o color.o escape.o
	$(CC) escape.o color.o escape.o -o $(EXEC)

fileimport.o: fileimport.c fileimport.h
	$(CC) $(CFLAGS) fileimport.c -c

color.o: color.c color.h
	$(CC) $(CFLAGS) color.c -c

clean:
	rm escape.o color.o fileimport.o escapeGame