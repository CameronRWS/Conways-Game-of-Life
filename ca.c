#include "ca.h"

void init1DCA(struct ca_data *theDCA1D, int quiescentState) {
    for(int i = 0; i < theDCA1D->numCells; i++) { //Go through each index.
        theDCA1D->cells[i] = quiescentState; //Set each cell to the quiescent state.
    }
}

void display1DCA(struct ca_data *theDCA1D) {
    for(int i = 0; i < theDCA1D->numCells - 1; i++) { //For all cells within the 1DCA except the last one.
        printf("%c ", theDCA1D->cells[i]); //Print the char at each index with a space after it.
    }
    printf("%c\n", theDCA1D[theDCA1D->numCells - 1]); //Print last one without a space and add a new line.
}

