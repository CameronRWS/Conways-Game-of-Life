# COMS 327 - Project 1 Part A
This part of the project is the infrastructure for the sand painting project.

## Key Datastructures
- 1DCA (one-dimensional cellular automata) - An array of chars.
## Source Files
##### dca1d.c - Contains functions for initializing, setting values of, and displaying a 1DCA.
- int main(void) - Shows off the 3 functions created for this part by creating a 25 cell 1DCA, setting each odd indexed cell to 1 and each even indexed cell to 2, then printing the 1DCA.
- void init1DCA(int numCellsToCreate, unsigned char *theDCA1D) - Initializes a 1DCA given the number of cells the 1DCA should have and a pointer to where the 1DCA is stored. This function will set all values in the 1DCA to it's quiescent state of 0.
- void set1DCACell(unsigned char *theDCA1D, int index, unsigned char charToSet) - Sets the value of a 1DCA's cell given a pointer to the 1DCA, the index you want to set, and the char to set the cell to. Checks for a non-negative integer before setting the value.
- void display1DCA(unsigned char *theDCA1D, int numCells) - Displays a 1DCA given a pointer to where the 1DCA is stored, and the length of the 1DCA. It does so by iterating through each char of the 1DCA and printing each one individually with a space in between.

##### dca1d.h - Contains function signatures for dca1d.c. See dca1d.c for more a description on each function.

- void init1DCA(int numCellsToCreate, unsigned char *theDCA1D)
- void set1DCACell(unsigned char *theDCA1D, int index, unsigned char charToSet) 
- void display1DCA(unsigned char *theDCA1D, int numCells) 
