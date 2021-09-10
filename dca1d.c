
#include <stdio.h>
#include <string.h>
#include "dca1d.h"

int main(void) {
    int lengthOfAuto = 25;
    unsigned char dca1d[lengthOfAuto];
    init1DCA(lengthOfAuto, dca1d);
    for(int i = 0; i < lengthOfAuto; i++) {
        if(i % 2 != 0) {
            set1DCACell(dca1d, i, '1'); //set odd to 1
        } else {
            set1DCACell(dca1d, i, '2'); //set even to 2
        }
    }
    display1DCA(dca1d, lengthOfAuto);
    return 0;
}

void init1DCA(int numCellsToCreate, unsigned char *theDCA1D) {
    for(int i = 0; i < numCellsToCreate - 1; i++) {
        theDCA1D[i] = '0';
    }
    theDCA1D[numCellsToCreate-1] = '\0';
}

void set1DCACell(unsigned char *theDCA1D, int index, unsigned char charToSet) {
    if(index < 0) {
        printf("Error with set1DCACell - index is negative.");
    }
    theDCA1D[index] = charToSet;
}

void display1DCA(unsigned char *theDCA1D, int numCells) {
    for(int i = 0; i < numCells - 1; i++) {
        printf("%c ", theDCA1D[i]);
    }
    printf("%c\n", theDCA1D[numCells - 1]); //the last one without a space at the end.
}