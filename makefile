main: main.o GraphicsClient.o CellularAutomaton.o;
	g++ main.o GraphicsClient.o CellularAutomaton.o
	mv a.out gol.out 

main.o: main.cpp GraphicsClient.h CellularAutomaton.h
	g++ -c main.cpp

GraphicsClient.o: GraphicsClient.cpp GraphicsClient.h CellularAutomaton.h
	g++ -c GraphicsClient.cpp

CellularAutomaton.o: CellularAutomaton.cpp CellularAutomaton.h GraphicsClient.h
	g++ -c CellularAutomaton.cpp

clean: 
	rm *.o
	rm *.out
