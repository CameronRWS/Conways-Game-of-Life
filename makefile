odca: dca1d.o
	gcc dca1d.o
	mv a.out odca.out 

dca1d.o: dca1d.c dca1d.h
	gcc -c dca1d.c

clean: 
	rm *.o
	rm *.out