odca: dca1d.o
	gcc dca1d.o

dca1d.o: dca1d.c dca1d.h
	gcc -c dca1d.c