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
        printf("%d ", theDCA1D->cells[i]); //Print the char at each index with a space after it.
    }
    printf("%d\n", theDCA1D->cells[theDCA1D->numCells - 1]); //Print last one without a space and add a new line.
}

int set1DCACell(struct ca_data *theDCA1D, unsigned int index, unsigned char charToSet) {
    if(!(0 <= index && index <= theDCA1D->numCells-1)) {
        printf("Error with set1DCACell usage - index out of bounds. The 1DCA was not modified.\n");
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

void stepCA(struct ca_data *theDCA1D, unsigned char (*ruleFunc)(struct ca_data *theDCA1D, int index), int flag) {
    int numCells = theDCA1D->numCells;
    struct ca_data *tempDCA1D = create1DCA(numCells+2, theDCA1D->quiescentState);
    for(int i = 1; i < theDCA1D->numCells + 1; i++) {
        tempDCA1D->cells[i] = theDCA1D->cells[i-1];
    }
    if(flag) { 
        tempDCA1D->cells[0] = tempDCA1D->cells[numCells-1];
        tempDCA1D->cells[numCells+1] = tempDCA1D->cells[1];
    }
    for(int i = 1; i < theDCA1D->numCells + 1; i++) {
        theDCA1D->cells[i-1] = ruleFunc(tempDCA1D, i);
    }
}

unsigned char rule110(struct ca_data *theDCA1D, int index) {
    unsigned char n1, n2, n3, r; //neighbors and result
    n1 = theDCA1D->cells[index-1];
    n2 = theDCA1D->cells[index];
    n3 = theDCA1D->cells[index+1];
    if       (n1 == 1 && n2 == 1 && n3 == 1) {
        r = 0;
    } else if(n1 == 1 && n2 == 1 && n3 == 0) {
        r = 1;
    } else if(n1 == 1 && n2 == 0 && n3 == 1) {
        r = 1;
    } else if(n1 == 1 && n2 == 0 && n3 == 0) {
        r = 0;
    } else if(n1 == 0 && n2 == 1 && n3 == 1) {
        r = 1;
    } else if(n1 == 0 && n2 == 1 && n3 == 0) {
        r = 1;
    } else if(n1 == 0 && n2 == 0 && n3 == 1) {
        r = 1;
    } else if(n1 == 0 && n2 == 0 && n3 == 0) {
        r = 0;
    } else {
        r = theDCA1D->quiescentState;
    }
    //printf("%d|%d|%d => r: %d\n", n1, n2, n3, r);
    return r;
}

