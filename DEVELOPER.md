# COMS 327 - Project 2 Part B
This part of the project is an implementation of Conway's Game of Life displayed on a graphics window with the ability for user interaction.

## Key Datastructures

- CellularAutomaton.h - Stores a CA in a convenient class with various methods to modify the CA.
- GraphicsClient.h - Convenient class for communicating with a graphics server/window via various drawing methods. This class encapsulates what a window created by the graphics server is.
- GCMessage.h - Stores a Graphics Client message.
- CAGraphicsSimulator.h - Simulates a Cellular Automaton graphically. Handles all of the logic that is unique to simulating the Cellular Automaton using the Graphics Client without having to modify what the CA and GC class do.

## Source Files
##### casimulator.cpp - Connects to a Graphics Window and simulates a Cellular Automaton.

- Also contains a function for calculating the next state of a cell in a Cellular Automaton. This step function is based on Conway's Game of Life.

##### CellularAutomaton.cpp - Contains the implementation of a Cellular Automaton. Includes the various functions for working with a Cellular Automaton per assignment specifications.

- void CellularAutomaton::initCA() -> Initiates the CA by setting all cells to the quiescent state.

- void CellularAutomaton::displayCAToConsole() -> Displays the state of the CA to the console (like in project 1 part c). This mezthod is used for debugging.

- void CellularAutomaton::displayCA(GraphicsClient* gc) -> Displays the state of the CA to the passed in GraphicsClient.

- int CellularAutomaton::set2DCACell(unsigned int index_x, unsigned int index_y, unsigned char charToSet) -> Sets the value of a cell in the CA.

- void CellularAutomaton::step2DCA(unsigned char (*ruleFunc)(CellularAutomaton *tempCA, int index_x, int index_y)) -> Calculates the next state of the CA given a step function.

- CellularAutomaton::CellularAutomaton(int width, int height, unsigned char quiescentState, unsigned char shouldWrapFlag) -> A constructor for a CA that doesn't use a file to create the initial state.

- CellularAutomaton::CellularAutomaton(string fileName, int quiescentState) -> A constructor for a CA that doesn't use a file to create the initial state.

- CellularAutomaton::CellularAutomaton(const CellularAutomaton& originalCA) -> A copy constructor for a CA.

- CellularAutomaton::~CellularAutomaton() -> A destructor for a CA.

- CellularAutomaton& CellularAutomaton::operator=(const CellularAutomaton& toCopyCA) -> A copy assignment overload function for the CA.

- int CellularAutomaton::getQuiescentState() -> A getter for the CA's quiescent state.

- int CellularAutomaton::getWidth() -> A getter for the CA's width.

- int CellularAutomaton::getHeight() -> A getter for the CA's height.

- unsigned char* CellularAutomaton::getCAdata() -> A getter for the CA's cell data.

- unsigned char CellularAutomaton::getWrap() -> A getter for the CA's wrap flag.

##### CellularAutomaton.h - Contains the class definition of a Cellular Automaton.

##### GraphicsClient.cpp - Contains the implementation for a Graphics Client. Includes the various functions for working with a Graphics Client per assignment specifications.

- GraphicsClient::GraphicsClient(string URL, int port) -> A parameterized constructor for a GraphicsClient object.

- GraphicsClient::GraphicsClient(const GraphicsClient& originalGC) -> A copy constructor for a GraphicsClient object.

- GraphicsClient::~GraphicsClient() -> A destructor for a GraphicsClient object.

- GraphicsClient& GraphicsClient::operator=(const GraphicsClient& toCopyGC) -> A copy operator for a GraphicsClient object.

- void GraphicsClient::setBackgroundColor(int r, int g, int b) -> Sets the background color of the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::setDrawingColor(int r, int g, int b) -> Sets the drawing color of the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::clear() -> Clears the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::setPixel(int x, int y, int r, int g, int b) -> Sets the color of a pixel of the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::drawRectangle(int x, int y, int w, int h)  -> Draws an outline of a rectangle on the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::fillRectangle(int x, int y, int w, int h) -> Draws a filled rectangle on the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::clearRectangle(int x, int y, int w, int h) -> Draws a filled rectangle with the color of the background on the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::drawOval(int x, int y, int w, int h) -> Draws an outline of an oval on the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::fillOval(int x, int y, int w, int h) -> Draws an filled in an oval on the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::drawLine(int x1, int y1, int x2, int y2) -> Draws a line on the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::drawShapeHelper(int c, int x, int y, int w, int h) -> Draws a shape on the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::drawstring(int x, int y, string stringToDraw) -> Draws a string on the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::repaint() -> Repaints (updates) the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

##### GraphicsClient.h - Contains the class definition of a Graphics Client.
