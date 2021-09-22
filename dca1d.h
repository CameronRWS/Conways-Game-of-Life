/**
 * Author: Cameron Smith
 * Description: Stores the signatures for 3 functions for initializing, setting values of, 
 *      and displaying a 1DCA.
 */

#ifndef DCA1D_HEADER //If this has not been defined yet, define it.
#define DCA1D_HEADER

/** 
 * Description: Initializes a 1DCA given the number of cells the 1DCA should have and a 
 *      pointer to where the 1DCA is stored. This function will set all values in the 1DCA
 *      to it's quiescent state of 0.
 * Parameter: int numCellsToCreate - The number of cells you want the 1DCA to have.
 * Parameter: unsigned char *theDCA1D - A pointer to the start of the array that stores the 1DCA.
 */
void init1DCA(int numCellsToCreate, unsigned char *theDCA1D);

/** 
 * Description: Sets the value of a 1DCA's cell given a pointer to the 1DCA, the index you want 
 *      to set, and the char to set the cell to. Checks for a non-negative integer before setting
 *      the value.
 * Parameter: unsigned char *theDCA1D - A pointer to the start of the array that stores the 1DCA.
 * Parameter: int index - The index in the array you want to set the value of.
 * Parameter: unsigned char charToSet - The char to set the cell to.
 */
void set1DCACell(unsigned char *theDCA1D, int index, unsigned char charToSet);

/* 
 * Description: Displays a 1DCA given a pointer to where the 1DCA is stored, and the length 
 *      of the 1DCA. It does so by iterating through each char of the 1DCA and printing each one
 *      individually with a space in between.
 * Parameter: unsigned char *theDCA1D - A pointer to the start of the array that stores the 1DCA.
 * Parameter: int numCells - The number of cells within the 1DCA.
 */
void display1DCA(unsigned char *theDCA1D, int numCells);

#endif