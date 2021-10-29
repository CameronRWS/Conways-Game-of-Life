#include <stdio.h> //Allows for printing to the console (printf).
#include <stdlib.h> //Allows for getting user input as an integer (atoi), Seeding the random method (srand), and getting a random integer (rand).
#include <time.h> //Allows for getting a good random seed (time) and accessing time_t type.
#include <string.h> //Allows for comparing strings (strcmp).
#include "ca.h" //Allows for 1DCA usage.

int main(int argc, char **argv) {
    struct ca_data *ca; //Declare the 1DCA.
    int width = 10;
    int height = 10;
    ca = create2DCA(width, height, '0', 1);
    int i = 0;
    int j = 0;
    printf("%c\n", ca->cadata[(i*height)+j]);
    i = 1;
    j = 0;
    printf("%c\n", ca->cadata[(i*height)+j]);
    i = 9;
    j = 9;
    printf("%c\n", ca->cadata[(i*height)+j]);
    
    return 1;
    
    // //Checks to make sure the user entered in the correct number of arguments.
    // if(argc != 6) { //If the argument count is not 6 (the first is the function name).
    //     printf("Error: You need to supply 5 parameters. You supplied %d.\n", argc-1);
    //     return 1;
    // }
    // //The following 5 lines parse the user input.
    // int numCells = atoi(argv[1]); //The number of cells the 1DCA should have. Must be between 10 and 100 (inclusive).
    // int numStates = atoi(argv[2]); //The number of states the 1DCA has. Labeled 0 to numStates - 1. For example, if 2 then the valid states are 0 and 1.
    // char *wrapText = argv[3]; //How to deal with edge cases when evaluating neighborhood of 1DCA cells. Must be 'wrap' or 'nowrap'.
    // int quiescentState = atoi(argv[4]); //The quiescent state for the 1DCA and how the 1DCA should be initialized. Must be between 0 and numStates-1 or -1 if initial states should be randomly initialized.
    // int numSteps = atoi(argv[5]); //Number of steps to simulate.
    // //The following if block validates the user input.
    // if(!(10 <= numCells && numCells <= 100)) { //If numCells is not within 10 and 100 (inclusive)
    //     printf("Error with 1st argument: Your 1DCA has to have a cell count between 10 and 100 (inclusive). You entered %d.\n", numCells);
    //     return 1;
    // } else if(!(numStates > 0)) { //If numStates is not positive.
    //     printf("Error with 2nd argument: The number of states needs to be a positive integer. You entered %d.\n", numStates);
    //     return 1;
    // } else if(strcmp(wrapText, "wrap") && strcmp(wrapText, "nowrap")) { //If wrapText is not 'nowrap' or 'wrap'.
    //     printf("Error with 3rd argument: Value must be 'wrap' or 'nowrap'. You entered '%s'.\n", wrapText);
    //     return 1;
    // } else if(!(0 <= quiescentState && quiescentState <= numStates - 1) && quiescentState != -1) { //If quiescentState is not with 0 and numStates-1 or quiescentState is not -1.
    //     printf("Error with 4th argument: The quiescent state has to be between 0 and %d or set to -1. You entered %d.\n", numStates - 1, quiescentState);
    //     return 1;
    // } else if(!(numSteps > 0)) { //If numSteps is not positive.
    //     printf("Error with 5th argument: The number of steps needs to be a positive integer. You entered %d.\n", numSteps);
    //     return 1;
    // }
    // //The following code takes the wrapText and turns it into its associated shouldWrapFlag value.
    // int shouldWrapFlag; //Value is set to 1 if the 1DCA neighborhood should wrap, 0 if not.
    // if(!strcmp(wrapText, "wrap")) { //If wrapText is equal to "wrap" Then
    //     shouldWrapFlag = 1;         //1 means 1DCA neighborhood should wrap.
    // } else {
    //     shouldWrapFlag = 0;         //0 means 1DCA neighborhood should not wrap.
    // }
    // //The following code initializes the 1DCA depending on the user input.
    // struct ca_data *ca; //Declare the 1DCA.
    // if(quiescentState != -1) { //If quiscentState is not -1, then the 1DCA shouldn't be randomly initialized.
    //     ca = create1DCA(numCells, quiescentState, shouldWrapFlag); //Initialize the 1DCA to the quiescentState and allocate memory.
    //     if(ca == NULL) { //Check to make sure the 1DCA was created.
    //         printf("Error with create1DCA: Unable to allocate required memory for the 1DCA.\n");
    //         return 1;
    //     }
    // } else {
    //     quiescentState = 0; //When quiescentState input is -1, the quiescentState should be 0 per piazza post.
    //     time_t t; //Declare a variable to store a time.
    //     srand((unsigned) time(&t)); //Seed our random number with the time. This ensures a random set of integers.
    //     ca = create1DCA(numCells, quiescentState, shouldWrapFlag); //Initialize the 1DCA to the quiescentState and allocate memory.
    //     if(ca == NULL) { //Check to make sure the 1DCA was created.
    //         printf("Error with create1DCA: Unable to allocate required memory for the 1DCA.\n");
    //         return 1;
    //     }
    //     for(int i = 0; i < ca->width; i++) { //For each cell in the 1DCA
    //         set1DCACell(ca, i, rand() % numStates); //Set the cell to a random state.
    //     }
    // }
    // //The following code simulates the 1DCA.
    // display1DCA(ca); //Display the current state of the 1DCA.
    // while(numSteps--) { //Simulate the 1DCA for the requested number of steps.
    //     step1DCA(ca, &rule110); //Simulate one step of the 1DCA using rule 110.
    //     display1DCA(ca); //Display the current state of the 1DCA.
    // }
    // return 0;
}