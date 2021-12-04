CXXFLAGS += -std=c++11
CXX=g++

gol: casimulator.o CAGraphicsSimulator.o CellularAutomaton.o GraphicsClient.o GCMessage.o;
	g++ -o $@ $^

casimulator.o: casimulator.cpp CAGraphicsSimulator.h GraphicsClient.h CellularAutomaton.h

GraphicsClient.o: GraphicsClient.cpp GraphicsClient.h GCMessage.h

CellularAutomaton.o: CellularAutomaton.cpp CellularAutomaton.h GraphicsClient.h

GCMessage.o: GCMessage.cpp GCMessage.h

CAGraphicsSimulator.o: CAGraphicsSimulator.cpp CAGraphicsSimulator.h GraphicsClient.h CellularAutomaton.h

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean: 
	-rm *.o
	-rm gol

.PHONY: clean run