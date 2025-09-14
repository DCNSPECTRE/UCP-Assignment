# NOTE : This makefile is a supplementary file for demonstration purposes, hence it only consists of simple rules.
#        When you write the makefile for your assignment, please make sure it has complete rules,
#        prerequisites, all the necessary variables, and clean rules to get full mark on makefile category.
#	     (Depending on the assignment requirement, you might even have to write CONDITIONAL COMPILATION)

demo: demoChangeColor.o color.o
	gcc demoChangeColor.o color.o -o demo

demoChangeColor.o: demoChangeColor.c color.h
	gcc -Wall -ansi -pedantic demoChangeColor.c -c

color.o: color.c color.h
	gcc -Wall -ansi -pedantic color.c -c

clean:
	rm demo demoChangeColor.o color.o	