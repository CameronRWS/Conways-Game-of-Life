# COMS 327 - Project 1 Part B
This part of the project is to expand on what was written in part A but using a structure to represent the 1DCA and also now simulate the 1DCA.

## Key Datastructures

- struct ca_data -> A structure for storing a 1DCA (one-dimensional cellular automata) - Contains a member/field for the number of cells the 1DCA has, the quiescent state of the 1DCA, and an array representing the cells of the 1DCA. More details in ca.h

## Source Files
##### main.c - Prompts the user for input then simulates the 1DCA.

##### ca.c - Contains functions for initializing, setting values of, displaying, creating, and simulating a 1DCA. As well as a stand alone function for calculating the next state of a cell in a 1DCA (rule110).

- void init1DCA(struct ca_data *theDCA1D, int quiescentState) -> Initializes a 1DCA given a pointer to where the 1DCA is stored (struct ca_data). This function will set all values in the 1DCA to it's passed in quiescent state.

- void display1DCA(struct ca_data *theDCA1D) -> Displays a 1DCA given a pointer to where the 1DCA is stored (struct ca_data). It does so by iterating through each char of the 1DCA and printing each one individually with a space in between.

- int set1DCACell(struct ca_data *theDCA1D, unsigned int index, unsigned char charToSet) -> Sets the value of a 1DCA's cell given a pointer to the 1DCA (struct ca_data), the index you want to set, and the char to set the cell to. Checks that the passed in index is within bounds of the 1DCA.

- struct ca_data* create1DCA(unsigned int numCells, unsigned char quiescentState) -> Creates a 1DCA on the heap with the necessary memory space for the number of cells requested and also sets the value of each cell to the quiescent state. The number of cells and quiescent state is also stored in the created 1DCA for convenience.

- void stepCA(struct ca_data *theDCA1D, unsigned char (*ruleFunc)(struct ca_data *tempDCA1D, int index), int flag) -> Simulates one step of the 1DCA. It does this by creating a temporary 1DCA that has an additional 2 cells (one on each end of the original 1DCA) and copying the values from the original 1DCA into the temporary 1DCA (starting at index 1 and ending 1 cell before the end) and then depending on the value of flag it sets the starting and ending cell. After creating this temporary 1DCA (for the purpose of being able to calculate the neighborhood of the original 1DCA nicely), the function goes through each index of the temporary 1DCA (starting at index 1 and ending 1 cell before the end) and using the passed in rule function calculates the next state of indexed cell. It then frees the temporary 1DCA's memory as it's no longer needed.

- unsigned char rule110(struct ca_data *tempDCA1D, int index) -> Calculates the next state of the indexed cell given the current state of the indexed cell and it's surrounding 2 cells (it's neighborhood). At this point the edge cases are already taken care of, and the client only asks for indices that have neighbors.

##### ca.h - Contains function signatures for ca.c. See ca.c for a description of each function.

- void init1DCA(struct ca_data *theDCA1D, int quiescentState) 

- void display1DCA(struct ca_data *theDCA1D)

- int set1DCACell(struct ca_data *theDCA1D, unsigned int index, unsigned char charToSet)

- struct ca_data* create1DCA(unsigned int numCells, unsigned char quiescentState)

- void stepCA(struct ca_data *theDCA1D, unsigned char (*ruleFunc)(struct ca_data *tempDCA1D, int index), int flag) 

- unsigned char rule110(struct ca_data *tempDCA1D, int index)
