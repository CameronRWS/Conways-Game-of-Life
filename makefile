main: main.o ca.o;
	gcc main.o ca.o
	mv a.out odca.out 

main.o: main.c ca.h
	gcc -c main.c

ca.o: ca.c ca.h
	gcc -c ca.c

clean: 
	rm *.o
	rm *.out

run:
	./odca.out

mrun:
	make
	make run