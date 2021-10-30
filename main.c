#include <stdio.h> //Allows for printing to the console (printf).
#include <stdlib.h> //Allows for getting user input as an integer (atoi), Seeding the random method (srand), and getting a random integer (rand).
#include <time.h> //Allows for getting a good random seed (time) and accessing time_t type.
#include <string.h> //Allows for comparing strings (strcmp).
#include "ca.h" //Allows for 1DCA usage.

int main(int argc, char **argv) {
    FILE *file;
    file = fopen("textInput.txt", "r");
    int rows, cols, s;
    fscanf(file, "%d", &rows);
    fscanf(file, "%d", &cols);
    struct ca_data *ca; //Declare the 2DCA.
    unsigned char qState = 0;
    int shouldWrap = 1;
    ca = create2DCA(cols, rows, qState, shouldWrap);
    for(int y = 0; y < rows; y++) {
        for(int x = 0; x < cols; x++) {
            fscanf(file, "%d", &s);
            set2DCACell(ca, x, y, s);
        }
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
}