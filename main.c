#include <stdio.h> //Allows for printing to the console (printf).
#include <stdlib.h> //Allows for getting user input as an integer (atoi), Seeding the random method (srand), and getting a random integer (rand).
#include <time.h> //Allows for getting a good random seed (time) and accessing time_t type.
#include <string.h> //Allows for comparing strings (strcmp).
#include "ca.h" //Allows for 1DCA usage.

int main(int argc, char **argv) {
    //Checks to make sure the user entered in the correct number of arguments.
    if(argc != 3) { //If the argument count is not 3 (the first is the function name).
        printf("Error: You need to supply 2 parameters. You supplied %d.\n", argc-1);
        return 1;
    }
    int dim = atoi(argv[1]);
    char *fileName = argv[2];
    if(dim != 2) {
        printf("Error: Conway's Game of Life is meant to be simulated in 2 dimensions. You requested a 1DCA.\n");
        return 1;
    }
    FILE *file;
    file = fopen(fileName, "r");
    if(!file) {
        printf("Error: There was a problem opening the file '%s'.\n", fileName);
        return 1;
    }
    int rows, cols;
    fscanf(file, "%d", &rows);
    fscanf(file, "%d", &cols);
    struct ca_data *ca; //Declare the 2DCA.
    unsigned char qState = 0;
    int shouldWrap = 1;
    ca = create2DCA(cols, rows, qState, shouldWrap);
    for(int x = 0; x < rows; x++) {
        for(int y = 0; y < cols; y++) {
            int s = -1;
            fscanf(file, "%d", &s);
            if(s == -1) {
                printf("Error: The file does not contain enough integers for a %dx%d 2DCA.\n", rows, cols);
                return 1;
            }
            set2DCACell(ca, y, x, s);
        }
    }
    int l = -1;
    fscanf(file, "%d", &l);
    if(l != -1) {
        printf("Error: The file contained too many integers for a %dx%d 2DCA.\n", rows, cols);
        return 1;
    }
    int shouldExit = 0;
    char input;
    while(!shouldExit) {
        displayCA(ca);
        input = getchar();
        if(input == '\n') {
            step2DCA(ca, &ruleGameOfLife);
        } else {
            shouldExit = 1;
        }
    }
    fclose(file);
}