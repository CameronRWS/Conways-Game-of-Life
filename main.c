#include <stdio.h> //Allows for printing to the console (printf).
#include <stdlib.h> //Allows for getting user input as an integer (atoi).
#include "ca.h" //Allows for 1DCA and 2DCA usage.

int main(int argc, char **argv) {
    //Checks to make sure the user entered in the correct number of arguments.
    if(argc != 3) { //If the argument count is not 3 (the first is the function name).
        printf("Error: You need to supply 2 parameters. You supplied %d.\n", argc-1);
        return 1; //Return 1 since there is an error.
    }
    int dim = atoi(argv[1]); //Get the requested CA dimension from command line input.
    char *fileName = argv[2]; //Get the file name from command line input.
    if(dim != 2) { //If the dimension isn't 2 then exit per piazza post.
        printf("Error: Conway's Game of Life is meant to be simulated in 2 dimensions. You requested a 1DCA.\n");
        return 1; //Return 1 since there is an error.
    }
    FILE *file; //Stores the file to be read.
    file = fopen(fileName, "r"); //Reads the file passed in.
    if(!file) { //If the file is NULL then it wasn't read in properly.
        printf("Error: There was a problem opening the file '%s'.\n", fileName);
        return 1; //Return 1 since there is an error.
    }
    int rows, cols; //Will store the number of rows and number of columns.
    fscanf(file, "%d", &rows); //Scans the first int in the file and stores as the number of rows.
    fscanf(file, "%d", &cols); //Scans the second int in the file and stores as the number of cols.
    struct ca_data *ca; //Declare the 2DCA.
    unsigned char qState = 0; //CGOL states 0 is default state.
    int shouldWrap = 1; //CGOL wraps by definition.
    ca = create2DCA(cols, rows, qState, shouldWrap); //Initiates an empty 2DCA with the requested dimensions.
    for(int x = 0; x < rows; x++) {
        for(int y = 0; y < cols; y++) {
            int s = -1; //Will store the most recently read integer.
            fscanf(file, "%d", &s); //Read the next integer from the file and save to s.
            if(s == -1) { //If s isn't set to a different value than -1 then a value wasn't read.
                printf("Error: The file does not contain enough integers for a %dx%d 2DCA.\n", rows, cols);
                return 1; //Return 1 since there is an error.
            }
            if(s != 0 && s != 1) {
                printf("Error: The file contains a '%d' which is an unsupported character for Conway's Game of Life.", s);
                return 1; //Return 1 since there is an error.
            }
            set2DCACell(ca, y, x, s); //Set the associated cell to the read in int. y and x are flipped due to having to ensure the file matches what will eventually be printed.
        }
    }
    int l = -1; //Will store the next int in the file.
    fscanf(file, "%d", &l); //Scans another int from the file.
    if(l != -1) { //At this point, if an int was read in, then there were too many ints because all ints should have been read in by now.
        printf("Error: The file contained too many integers for a %dx%d 2DCA.\n", rows, cols);
        return 1; //Return 1 since there is an error.
    }
    int shouldExit = 0; //Will store if the while loop should exit or not. Done for readability.
    char input; //Stores the char the user enters into the console.
    //int sim = 0; //number of steps simulated.
    while(!shouldExit) { //While the loop shouldn't exit.
        //printf("Steps: %d\n", sim++);
        displayCA(ca); //Display the current state of the CA.
        input = getchar(); //Get the next char in the console.
        if(input == '\n') { //If the char put in the console is the return char, simulate the CA once.
            step2DCA(ca, &ruleGameOfLife);
        } else { //If the user enters any other char, then the program exits.
            shouldExit = 1; //Allows for the loop to exit, in a nice readable way.
        }
    }
    fclose(file); //Close the file.
}