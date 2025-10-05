COMPILER=gcc
CFLAGS=-Wall -ansi -pedantic -c
CLEANUP=rm -f escape escape.o fileimport.o color.o terminal.o gamemech.o
ALL=escape.o fileimport.o color.o terminal.o gamemech.o
ESCAPE=escape.c escape.h fileimport.h
FILEIMPORT=fileimport.c fileimport.h color.h
COLOR=color.c color.h
TERMINAL=terminal.c terminal.h
GAMEMECH=gamemech.c gamemech.h
MEMORYCHECK=valgrind --leak-check=full -s ./escape map.txt

escape: $(ALL)
	$(COMPILER) -o escape escape.o fileimport.o color.o terminal.o gamemech.o

escape.o: $(ESCAPE)
	$(COMPILER) $(CFLAGS) escape.c

fileimport.o: $(FILEIMPORT)
	$(COMPILER) $(CFLAGS) fileimport.c

color.o: $(COLOR)
	$(COMPILER) $(CFLAGS) color.c

terminal.o: $(TERMINAL)
	$(COMPILER) $(CFLAGS) terminal.c

gamemech.o: $(GAMEMECH)
	$(COMPILER) $(CFLAGS) gamemech.c

antonisnightmare: escape
	$(MEMORYCHECK)

clean:
	$(CLEANUP)
