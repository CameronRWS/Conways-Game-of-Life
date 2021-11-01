# COMS 327 - Project 1 Part C
This part of the project is an implementation of Conway's Game of Life.

## Key Datastructures

- struct ca_data -> A structure for storing a CA (cellular automata) - Contains a member/field for the quiescent state, width, height, should wrap flag, dimension, and array of cells. More details in ca.h

## Source Files
##### main.c - Prompts the user for input then simulates the CA.

##### ca.c - Contains functions for initializing, setting values of, displaying, creating, and simulating both 1DCA's and 2DCA's. As well as 2 stand alone function for calculating the next state of a cell in a 1DCA (rule110) or 2DCA (ruleGameOfLife).

- void initCA(struct ca_data *theCA, int quiescentState) -> Initializes a CA given a pointer to where the CA is stored (struct ca_data). This function will set all values in the CA to it's passed in quiescent state.

- void displayCA(struct ca_data *theCA) -> Displays a CA given a pointer to where the CA is stored (struct ca_data). It does so by iterating through each char of the CA and printing each one individually with a space in between.

- int set1DCACell(struct ca_data *theCA, unsigned int index, unsigned char charToSet) -> Sets the value of a CA's cell given a pointer to the CA (struct ca_data), the index you want to set, and the char to set the cell to. Checks that the passed in index is within bounds of the CA.

- int set2DCACell(struct ca_data *theCA, unsigned int index_x, unsigned int index_y, unsigned char charToSet) -> Sets the value of a CA's cell given a pointer to the CA (struct ca_data), the index you want to set (the x and y position), and the char to set the cell to. Checks that the passed in index is within bounds of the CA.

- void step1DCA(struct ca_data *theCA, unsigned char (*ruleFunc)(struct ca_data *tempCA, int index)) -> Simulates one step of the 1DCA. It does this by creating a temporary CA that has an additional 2 cells (one on each end of the original CA) and copying the values from the original CA into the temporary CA (starting at index 1 and ending 1 cell before the end) and then depending on the value of flag it sets the starting and ending cell. After creating this temporary CA (for the purpose of being able to calculate the neighborhood of the original CA nicely), the function goes through each index of the temporary CA (starting at index 1 and ending 1 cell before the end) and using the passed in rule function calculates the next state of indexed cell. It then frees the temporary CA's memory as it's no longer needed.

- void step2DCA(struct ca_data *theCA, unsigned char (*ruleFunc)(struct ca_data *tempCA, int index_x, int index_y)) -> Simulates one step of the 2DCA. It does this by creating a temporary CA that has the values of the original CA that gets used to calculate the values for the next step of the CA. No need for any padding cells in this 2DCA.

- struct ca_data* create1DCA(unsigned int numCells, unsigned char quiescentState, unsigned int shouldWrapFlag) -> Creates a 1DCA on the heap with the necessary memory space for the number of cells requested and also sets the value of each cell to the quiescent state. The number of cells, quiescent state, and should wrap flag is also stored in the created 1DCA for convenience.

- struct ca_data* create2DCA(int width, int height, unsigned char quiescentState, unsigned int shouldWrapFlag) -> Creates a 2DCA on the heap with the necessary memory space for the number of cells requested and also sets the value of each cell to the quiescent state. The width, height, quiescent state, and should wrap flag is also stored in the created 2DCA for convenience.

- unsigned char rule110(struct ca_data *tempCA, int index) -> Calculates the next state of the indexed cell given the current state of the indexed cell and it's surrounding 2 cells (it's neighborhood). At this point the edge cases are already taken care of, and the client only asks for indices that have neighbors.

- unsigned char ruleGameOfLife(struct ca_data *tempCA, int x, int y) -> Calculates the next state of the indexed cell given the current state of the indexed cell and it's surrounding 8 cells (it's neighborhood). Rule is based off of Conway's Game of Life.

##### ca.h - Contains function signatures for ca.c. See ca.c for a description of each function.

- void displayCA(struct ca_data *theCA)

- int set1DCACell(struct ca_data *theCA, unsigned int index, unsigned char charToSet)

- int set2DCACell(struct ca_data *theCA, unsigned int index_x, unsigned int index_y, unsigned char charToSet)

- void initCA(struct ca_data *theCA, int quiescentState)

- void step1DCA(struct ca_data *theCA, unsigned char (*ruleFunc)(struct ca_data *tempCA, int index))

- void step2DCA(struct ca_data *theCA, unsigned char (*ruleFunc)(struct ca_data *tempCA, int index_x, int index_y))

- struct ca_data* create1DCA(unsigned int numCells, unsigned char quiescentState, unsigned int shouldWrapFlag)

- struct ca_data* create2DCA(int width, int height, unsigned char quiescentState, unsigned int shouldWrapFlag)

- unsigned char rule110(struct ca_data *tempCA, int index)

- unsigned char ruleGameOfLife(struct ca_data *tempCA, int x, int y)