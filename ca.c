#include <stdio.h>
#include <stdlib.h>
#include "ca.h"

void init1DCA(struct ca_data *theDCA1D, int quiescentState) {
    for(int i = 0; i < theDCA1D->numCells; i++) { //Go through each index.
        theDCA1D->cells[i] = quiescentState; //Set each cell to the quiescent state.
    }
}

void display1DCA(struct ca_data *theDCA1D) {
    for(int i = 0; i < theDCA1D->numCells - 1; i++) { //For all cells within the 1DCA except the last one.
        //printf("%d", theDCA1D->cells[i]); //Print the char at each index with a space after it.
        printf("(%d: %u) - ", i, theDCA1D->cells[i]); //DEBUG CODE

    }
    //printf("%d\n", theDCA1D->cells[theDCA1D->numCells - 1]); //Print last one without a space and add a new line.
    printf("(%d: %u)\n", theDCA1D->numCells - 1, theDCA1D->cells[theDCA1D->numCells - 1]); //DEBUG CODE
}

int set1DCACell(struct ca_data *theDCA1D, unsigned int index, unsigned char charToSet) {
    if(index < 0) { //If the passed in index is negative, then the index would be out of bounds.
        printf("Error with set1DCACell usage - index is negative. The 1DCA was not modified.\n");
        return 0; //Return 0 because of error.
    } else {        //If the index isn't negative then we can set the value.
        theDCA1D->cells[index] = charToSet; //Set the value at the index to the char passed in.
        return 1; //Return 1 because no error.
    }
}

struct ca_data* create1DCA(unsigned int numCells, unsigned char quiescentState) {
    struct ca_data *ca = malloc(sizeof(struct ca_data));
    ca->quiescentState = quiescentState;
    ca->numCells = numCells;
    ca->cells = malloc(sizeof(unsigned char) * numCells);
    init1DCA(ca, quiescentState);
    return ca;
}

void stepCA(struct ca_data *theDCA1D, unsigned char (*ruleFunc)(struct ca_data *theDCA1D, int index, int flag), int flag) {
    unsigned char arrTemp[theDCA1D->numCells];
    for(int i = 0; i < theDCA1D->numCells; i++) {
        arrTemp[i] = theDCA1D->cells[i];
    }
    for(int i = 0; i < theDCA1D->numCells - 1; i++) {
        //printf("value of i in stepCA: %d\n", i);
        arrTemp[i] = ruleFunc(theDCA1D, i, flag);
    }
    theDCA1D->cells = arrTemp;
}

unsigned char rule110(struct ca_data *theDCA1D, int index, int flag) {
    unsigned char n1, n2, n3;
    n2 = theDCA1D->cells[index];
    //printf("value of n2: %u\n", n2);
    int maxIndex = theDCA1D->numCells;
    if(flag) { //if should wrap
        if(index == 0) {
            n1 = theDCA1D->cells[maxIndex];
            n3 = theDCA1D->cells[index+1];
        } else if(index == maxIndex) {
            n1 = theDCA1D->cells[index-1];
            n3 = theDCA1D->cells[0];
        } else {
            n1 = theDCA1D->cells[index-1];
            n3 = theDCA1D->cells[index+1];
        }
    } else { //if shouldn't wrap
        if(index == 0) {
            n1 = theDCA1D->quiescentState;
            n3 = theDCA1D->cells[index+1];
        } else if(index == maxIndex) {
            n1 = theDCA1D->cells[index-1];
            n3 = theDCA1D->quiescentState;
        } else {
            n1 = theDCA1D->cells[index-1];
            n3 = theDCA1D->cells[index+1];
        }
    }
    if(n1 == 1 && n2 == 1 && n3 == 1) {
        return 0;
    } else {
        return 1;
    }
}

