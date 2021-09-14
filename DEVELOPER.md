# COMS 327 - Project 1 Part A
This part of the project is the infrastructure for the sand painting project.

## Key Datastructures
- 1DCA (one-dimensional cellular automata) - An array of chars.
## Source Files
##### dca1d.c - Contains key functions for initializing, setting, and printing a 1DCA.
- int main(void) - Temporary location for the entry point of the program.
- void init1DCA(int numCellsToCreate, unsigned char *theDCA1D) - Initializes a 1DCA given the number of cells the 1DCA should have and a pointer to where the 1DCA is stored.
- void set1DCACell(unsigned char *theDCA1D, int index, unsigned char charToSet) - Sets the value of a 1DCA's cell given a pointer to the 1DCA, the index you want to set, and the char to set the cell to.
- void display1DCA(unsigned char *theDCA1D, int numCells) - Displays a 1DCA given a pointer to where the 1DCA is stored, and the length of the 1DCA.

##### dca1d.h - Contains key function headers for dca1d.c