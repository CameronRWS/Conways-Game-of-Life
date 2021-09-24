#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ca.h"

int main(int argc, char **argv) {
    int quiescentState = 0;
    if(argc != 6) {
        printf("Error: You need to supply 5 integer parameters. You supplied %d.\n", argc);
        return 0;
    }
    int numCells = atoi(argv[1]); //10 to 100
    int numStates = atoi(argv[2]); //Labeled 0 to numStatesInput - 1.
    char *wrapText = argv[3]; //How to deal with edge cases.
    int initialState = atoi(argv[4]); //The intial state for the 1DCA.
    int numSteps = atoi(argv[5]); //Number of steps to simulate.
    //printf("Input: %d %d %d %d %d\n", numCells, numStates, shouldWrapFlag, quiescentState, numSteps);
    //make sure input is all ints
    
    if(!(10 <= numCells && numCells <= 100)) {
        printf("Error with 1st argument: Your 1DCA has to have a cell count between 10 and 100 (inclusive). You entered %d.\n", numCells);
        return 0;
    } else if(strcmp(wrapText, "wrap") && strcmp(wrapText, "nowrap")) {
        printf("Error with 3rd argument: Value must be 'wrap' or 'nowrap'. You entered '%s'.\n", wrapText);
        return 0;
    } else if(!(0 <= initialState && initialState <= numStates - 1) && initialState != -1) {
        printf("Error with 4nd argument: The initial state has to be between 0 and %d or set to -1. You entered %d.\n", numStates - 1, quiescentState);
        return 0;
    }
    //
    int shouldWrapFlag;
    if(!strcmp(wrapText, "wrap")) {
        shouldWrapFlag = 1;
    } else {
        shouldWrapFlag = 0;
    }
    //
    struct ca_data *ca = create1DCA(numCells, quiescentState);
    if(initialState != -1) {
        for(int i = 0; i < ca->numCells; i++) {
            set1DCACell(ca, i, initialState);
        }
    } else {
        time_t t;
        srand((unsigned) time(&t));
        for(int i = 0; i < ca->numCells; i++) {
            set1DCACell(ca, i, rand() % numStates); //random
        }
    }
    //
    display1DCA(ca);
    while(numSteps--) {
        stepCA(ca, &rule110, shouldWrapFlag);
        display1DCA(ca);
    }
}