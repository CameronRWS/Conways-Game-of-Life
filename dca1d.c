/**
 * Author: Cameron Smith
 * Description: Store 3 functions for initializing, setting values of, and displaying a 1DCA. Also
 *      (for now) another purpose is to demo the 3 functions in the main method. See documentation
 *      for each function for more information.
 */

#include <stdio.h> //Allows for the ability to print to the console which is required for this part of the project.
#include "dca1d.h" //Lets main know the signature of the 3 functions being demo'd before they are declared.

/**
 * Description: At this point in the project, this main method's purpose is to show off the 3 
 *      functions created for this part by creating a 25 cell 1DCA, setting each odd indexed 
 *      cell to 1 and each even indexed cell to 2, then printing the 1DCA.
 * Note: This is a temporary location for the entry point of the program.
 */ 
int main(void) {
    int lengthOfAuto = 25; //We want 25 cells in our 1DCA per assignment instructions
    unsigned char dca1d[lengthOfAuto+1]; //Create the char array of length 25 + 1 (for \0)
    init1DCA(lengthOfAuto, dca1d); //Set all values in the 1DCA to 0 and add \0 to the end.
    for(int i = 0; i < lengthOfAuto; i++) { //For every index in the 1DCA
        if(i % 2 != 0) {                //If the index is odd
            set1DCACell(dca1d, i, '1'); //Set odd index to 1 per assignment instructions
        } else {                        //Otherwise (index is even)
            set1DCACell(dca1d, i, '2'); //Set even index to 2 per assignment instructions
        }
    }
    display1DCA(dca1d, lengthOfAuto); //Display the 1DCA per assignment requirements.
    return 0;
}

/** 
 * Description: Initializes a 1DCA given the number of cells the 1DCA should have and a 
 *      pointer to where the 1DCA is stored. This function will set all values in the 1DCA
 *      to it's quiescent state of 0.
 * Parameter: int numCellsToCreate - The number of cells you want the 1DCA to have.
 * Parameter: unsigned char *theDCA1D - A pointer to the start of the array that stores the 1DCA.
 */
void init1DCA(int numCellsToCreate, unsigned char *theDCA1D) {
    for(int i = 0; i < numCellsToCreate; i++) { //Go through each index and set the value to 0.
        theDCA1D[i] = '0'; //0 is the value of the quiescent state.
    }
    theDCA1D[numCellsToCreate] = '\0'; //Adds the string termination char to the end of our 1DCA.
}

/** 
 * Description: Sets the value of a 1DCA's cell given a pointer to the 1DCA, the index you want 
 *      to set, and the char to set the cell to. Checks for a non-negative integer before setting
 *      the value.
 * Parameter: unsigned char *theDCA1D - A pointer to the start of the array that stores the 1DCA.
 * Parameter: int index - The index in the array you want to set the value of.
 * Parameter: unsigned char charToSet - The char to set the cell to.
 */
void set1DCACell(unsigned char *theDCA1D, int index, unsigned char charToSet) {
    if(index < 0) { //If the passed in index is negative, then the index would be out of bounds.
        printf("Error with set1DCACell usage - index is negative. The 1DCA was not modified.\n");
    } else {        //If the index isn't negative then we can set the value.
        theDCA1D[index] = charToSet; //Set the value at the index to the char passed in.
    }
}

/* 
 * Description: Displays a 1DCA given a pointer to where the 1DCA is stored, and the length 
 *      of the 1DCA. It does so by iterating through each char of the 1DCA and printing each one
 *      individually with a space in between.
 * Parameter: unsigned char *theDCA1D - A pointer to the start of the array that stores the 1DCA.
 * Parameter: int numCells - The number of cells within the 1DCA.
 */
void display1DCA(unsigned char *theDCA1D, int numCells) {
    for(int i = 0; i < numCells - 1; i++) { //For all cells within the 1DCA except the last one.
        printf("%c ", theDCA1D[i]);         //Print the char at each index with a space after it.
    }
    printf("%c\n", theDCA1D[numCells - 1]); //Print last one without a space and adds a new line.
}