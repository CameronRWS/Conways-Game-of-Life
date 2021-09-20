#include <stdio.h>
#include "dca1d.h"

//Temporary location for the entry point of the program.
int main(void) {
    int lengthOfAuto = 25; //We want 25 cells in our 1DCA.
    unsigned char dca1d[lengthOfAuto+1]; //Create the char array of length 25 + 1 (for \0)
    init1DCA(lengthOfAuto, dca1d); //Set all values in the 1DCA to 0 and add \0 to the end.
    for(int i = 0; i < lengthOfAuto; i++) {
        if(i % 2 != 0) {
            set1DCACell(dca1d, i, '1'); //Set odd index to 1
        } else {
            set1DCACell(dca1d, i, '2'); //Set even index to 2
        }
    }
    display1DCA(dca1d, lengthOfAuto); //Display the 1DCA per assignment requirements.
    return 0;
}

//Initializes a 1DCA given the number of cells the 1DCA should have and a pointer to where the 1DCA is stored.
void init1DCA(int numCellsToCreate, unsigned char *theDCA1D) {
    for(int i = 0; i < numCellsToCreate - 1; i++) {
        theDCA1D[i] = '0';
    }
    theDCA1D[numCellsToCreate-1] = '\0';
}

//Sets the value of a 1DCA's cell given a pointer to the 1DCA, the index you want to set, and the char to set the cell to.
void set1DCACell(unsigned char *theDCA1D, int index, unsigned char charToSet) {
    if(index < 0) {
        printf("Error with set1DCACell - index is negative.");
    }
    theDCA1D[index] = charToSet;
}

//Displays a 1DCA given a pointer to where the 1DCA is stored, and the length of the 1DCA.
void display1DCA(unsigned char *theDCA1D, int numCells) {
    for(int i = 0; i < numCells - 1; i++) {
        printf("%c ", theDCA1D[i]);
    }
    printf("%c\n", theDCA1D[numCells - 1]); //the last one without a space at the end.
}