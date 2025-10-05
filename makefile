COMPILER=gcc
CFLAGS=-Wall -ansi -pedantic -c
CLEANUP=rm -f escape escape.o fileimport.o color.o terminal.o gamemech.o linkedlist.o
ALL=escape.o fileimport.o color.o terminal.o gamemech.o linkedlist.o
ESCAPE=escape.c escape.h fileimport.h
FILEIMPORT=fileimport.c fileimport.h color.h
COLOR=color.c color.h
TERMINAL=terminal.c terminal.h
GAMEMECH=gamemech.c gamemech.h
LLIST=linkedlist.c linkedlist.h
COMPLIEEVERYTHING= -o escape escape.o fileimport.o color.o terminal.o gamemech.o linkedlist.o

escape: $(ALL)
	$(COMPILER) $(COMPLIEEVERYTHING)

escape.o: $(ESCAPE)
	$(COMPILER) $(CFLAGS) escape.c

fileimport.o: $(FILEIMPORT)
	$(COMPILER) $(CFLAGS) fileimport.c

color.o: $(COLOR)
	$(COMPILER) $(CFLAGS) color.c

terminal.o: $(TERMINAL)
	$(COMPILER) $(CFLAGS) terminal.c

linkedlist.o: $(LLIST)
	$(COMPILER) $(CFLAGS) linkedlist.c

gamemech.o: $(GAMEMECH)
	$(COMPILER) $(CFLAGS) gamemech.c


antonisnightmare: escape
	valgrind --leak-check=full ./escape map.txt

clean:
	$(CLEANUP)
