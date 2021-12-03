main: main.o CAGraphicsSimulator.o CellularAutomaton.o GraphicsClient.o GCMessage.o;
	g++ main.o CAGraphicsSimulator.o CellularAutomaton.o GraphicsClient.o GCMessage.o
	mv a.out gol.out 

main.o: main.cpp CAGraphicsSimulator.h GraphicsClient.h CellularAutomaton.h
	g++ -c main.cpp 

GraphicsClient.o: GraphicsClient.cpp GraphicsClient.h GCMessage.h
	g++ -c GraphicsClient.cpp

CellularAutomaton.o: CellularAutomaton.cpp CellularAutomaton.h GraphicsClient.h
	g++ -c CellularAutomaton.cpp

GCMessage.o: GCMessage.cpp GCMessage.h
	g++ -c GCMessage.cpp

CAGraphicsSimulator.o: CAGraphicsSimulator.cpp CAGraphicsSimulator.h GraphicsClient.h CellularAutomaton.h
	g++ -c CAGraphicsSimulator.cpp

clean: 
	rm *.o
	rm *.out
