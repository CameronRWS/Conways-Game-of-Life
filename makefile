main: main.o
	gcc main.o
	mv a.out odca.out 

main.o: main.c ca.o ca.h
	gcc -c main.c

ca.o: ca.c ca.h
	gcc -c ca.c

clean: 
	rm *.o
	rm *.out