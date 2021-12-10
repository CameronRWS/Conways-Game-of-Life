# COMS 327 - Project 2 Part B
This part of the project is an implementation of Conway's Game of Life displayed on a graphics window with the ability for user interaction.

## Key Datastructures

- CellularAutomaton.h - Stores a CA in a convenient class with various methods to modify the CA.
- GraphicsClient.h - Convenient class for communicating with a graphics server/window via various drawing methods. This class encapsulates what a window created by the graphics server is.
- GCMessage.h - Stores a Graphics Client message.
- CAGraphicsSimulator.h - Simulates a Cellular Automaton graphically. Handles all of the logic that is unique to simulating the Cellular Automaton using the Graphics Client without having to modify what the CA and GC class do.

## Source Files
##### casimulator.cpp - The entry point for the program. Connects to a Graphics Window and simulates a Cellular Automaton.

##### CAGraphicsSimulator.cpp - Simulates a Cellular Automaton graphically. Handles all of the logic that is unique to simulating the Cellular Automaton using the Graphics Client without having to modify what the CA and GC class do. Also contains a function for calculating the next state of a cell in a Cellular Automaton. This step function is based on Conway's Game of Life.

- CAGraphicsSimulator::CAGraphicsSimulator(GraphicsClient* gc, CellularAutomaton* ca) -> Constructs a CAGraphicsSimulator object.

- void CAGraphicsSimulator::simulate() -> Simulates the CA on the Graphics Window with interative buttons.

- void CAGraphicsSimulator::drawButton(int x, int y, int w, int h, string name) -> Draws a button on the Graphics Window.

- void CAGraphicsSimulator::displayCA() -> Displays the CA on the Graphics Window.

- void CAGraphicsSimulator::checkForAndExecuteMessages() -> Check the Graphics Client for messages and executes them if they exist.

- int CAGraphicsSimulator::getShouldStep() -> Gets this object's shouldStep field.

- int CAGraphicsSimulator::getShouldExit() -> Gets this object's shouldExit field.

- void CAGraphicsSimulator::clearGame() -> Clears the game area (600x600 CA area).

- void CAGraphicsSimulator::stepAndDisplayCA() -> Steps the CA forward (calculate the next state) and display it graphically.
- void CAGraphicsSimulator::clickEvent(int x, int y) -> Handles when the user clicks on the Graphics Client.

- void CAGraphicsSimulator::checkForCAClick(int x, int y) -> Checks to see if the user clicked on a CA cell, and if so flips the cell state.

- void CAGraphicsSimulator::drawGUI() -> Draws the GUI and it's buttons on the Graphics Window.

- void CAGraphicsSimulator::saveCAToFile() -> Saves the displayed CA as the text representation.

- void CAGraphicsSimulator::logEvent(string text) -> Logs text graphically in the corner of the Graphics Window.

##### CAGraphicsSimulator.h - Contains the class definition of a Cellular Automaton Graphics Simulator.

##### CellularAutomaton.cpp - Contains the implementation of a Cellular Automaton. Includes the various functions for working with a Cellular Automaton per assignment specifications.

- CellularAutomaton::CellularAutomaton(string fileName, int quiescentState) -> A constructor for a CA that allows for a user to create the CA based off of a file and a quiescent state.

- CellularAutomaton::CellularAutomaton(int width, int height, unsigned char quiescentState, unsigned char shouldWrapFlag) -> A constructor for a CA that doesn't use a file to create the initial state.

- CellularAutomaton::CellularAutomaton(const CellularAutomaton& originalCA) : cadata(NULL) -> A copy constructor for a CA.

- CellularAutomaton::~CellularAutomaton() -> A destructor for a CA.

- CellularAutomaton& CellularAutomaton::operator=(const CellularAutomaton& toCopyCA) -> A copy assignment overload function for the CA.

- void CellularAutomaton::setSizeAndGap() -> Sets the CA's size and gap based off of the value of m (see project specifications).

- void CellularAutomaton::deepCopy(const CellularAutomaton& toCopyCA) -> A deep copy method that copies the passed in CA into this CA.

- void CellularAutomaton::loadCAfromFile(string fileName, int quiescentState, int shouldSaveFileName) -> Loads a CA defined in a file into this CA.

- void CellularAutomaton::initCA() -> Initiates the CA by setting all cells to the quiescent state.

- void CellularAutomaton::randomize() -> Randomizes the states of the cells in the CA.

- void CellularAutomaton::displayCA(GraphicsClient* gc) -> Displays the state of the CA to the passed in GraphicsClient.

- int CellularAutomaton::set2DCACell(unsigned int index_x, unsigned int index_y, unsigned char charToSet) -> Sets the value of a cell in the CA.

- void CellularAutomaton::step2DCA(unsigned char (*ruleFunc)(CellularAutomaton *tempCA, int index_x, int index_y)) -> Calculates the next state of the CA given a step function.

- int CellularAutomaton::getQuiescentState() -> A getter for the CA's quiescent state.

- int CellularAutomaton::getWidth() -> A getter for the CA's width.

- int CellularAutomaton::getHeight() -> A getter for the CA's height.

- int CellularAutomaton::getSize() -> A getter for the CA's cell size.

- int CellularAutomaton::getGap() -> A getter for the CA's cell gap.

- unsigned char* CellularAutomaton::getCAdata() -> A getter for the CA's cell data.

- unsigned char CellularAutomaton::getWrap() -> A getter for the CA's wrap flag.

- string CellularAutomaton::getFileName() -> A getter for the CA's file name.

##### CellularAutomaton.h - Contains the class definition of a Cellular Automaton.

##### GraphicsClient.cpp - Contains the implementation for a Graphics Client. Includes the various functions for working with a Graphics Client per assignment specifications.

- GraphicsClient::GraphicsClient(string URL, int port) -> A parameterized constructor for a GraphicsClient object.

- GraphicsClient::GraphicsClient(const GraphicsClient& originalGC) -> A copy constructor for a GraphicsClient object.

- GraphicsClient::~GraphicsClient() -> A destructor for a GraphicsClient object.

- GraphicsClient& GraphicsClient::operator=(const GraphicsClient& toCopyGC) -> A copy operator for a GraphicsClient object.

- void GraphicsClient::connectToAddress(string URL, int port) -> Connects this GraphicsClient to an address.

- void GraphicsClient::setBackgroundColor(int r, int g, int b) -> Sets the background color of the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::setDrawingColor(int r, int g, int b) -> Sets the drawing color of the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::clear() -> Clears the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::setPixel(int x, int y, int r, int g, int b) -> Sets the color of a pixel of the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::drawRectangle(int x, int y, int w, int h) -> Draws an outline of a rectangle on the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::fillRectangle(int x, int y, int w, int h) -> Draws a filled rectangle on the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::clearRectangle(int x, int y, int w, int h) -> Draws a filled rectangle with the color of the background on the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::drawOval(int x, int y, int w, int h) -> Draws an outline of an oval on the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::fillOval(int x, int y, int w, int h) -> Draws an filled in an oval on the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided. 

- void GraphicsClient::drawLine(int x1, int y1, int x2, int y2) -> Draws a line on the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::drawstring(int x, int y, string stringToDraw) -> Draws a string on the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::repaint() -> Repaints (updates) the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- void GraphicsClient::drawShapeHelper(int c, int x, int y, int w, int h) -> Draws a shape on the associated graphics display for the GraphicsClient object by communicating to the GraphicsServer based off of the project specifications and communication document provided.

- list<GCMessage> GraphicsClient::checkForMessages() -> Checks to see if there are messages from the Graphics Window. If so this returns the messages.

- void GraphicsClient::requestFile() -> Tells the Graphics Window prompt the user for a file to load.

##### GraphicsClient.h - Contains the class definition of a Graphics Client.

##### GCMessage.cpp - Contains the implementation for a Graphics Client Message. Includes the various functions for working with a Graphics Client Message.

- GCMessage::GCMessage(int messageType, string message) -> A parameterized constructor for a GCMessage object.

- int GCMessage::getMessageType() -> A getter for the GCMessages's message type.

- string GCMessage::getMessage() -> A getter for the GCMessages's message.

##### GCMessage.h - Contains the class definition of a Graphics Client.
