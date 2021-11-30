main: main.o CAGraphicSimulator.o CellularAutomaton.o GraphicsClient.o GCMessage.o;
	g++ main.o CAGraphicSimulator.o CellularAutomaton.o GraphicsClient.o GCMessage.o
	mv a.out gol.out 

main.o: main.cpp CAGraphicSimulator.h GraphicsClient.h CellularAutomaton.h
	g++ -c main.cpp 

GraphicsClient.o: GraphicsClient.cpp GraphicsClient.h GCMessage.h
	g++ -c GraphicsClient.cpp

CellularAutomaton.o: CellularAutomaton.cpp CellularAutomaton.h GraphicsClient.h
	g++ -c CellularAutomaton.cpp

GCMessage.o: GCMessage.cpp GCMessage.h
	g++ -c GCMessage.cpp

CAGraphicSimulator.o: CAGraphicSimulator.cpp CAGraphicSimulator.h GraphicsClient.h CellularAutomaton.h
	g++ -c CAGraphicSimulator.cpp

clean: 
	rm *.o
	rm *.out
