#include <stdio.h> //Allows for use of printf.
#include <stdlib.h> //Allows for use of free and malloc.
#include "ca.h" //Allows for 1DCA and 2DCA usage.

/** 
 * Description: Initializes a CA given a pointer to where the CA is stored (struct ca_data).
 *      This function will set all values in the CA to it's passed in quiescent state.
 * Parameter: struct ca_data *theDCA1D - A pointer to the CA struct that will be initiated.
 * Parameter: int quiescentState - The quiescent state to set the cells in the CA to.
 */
void initCA(struct ca_data *theDCA1D, int quiescentState) {
    // printf("Got to init");
    // printf("Width: %d,", theDCA1D->width);
    // printf("Height: %d,", theDCA1D->height);
    int maxIndex = 0;
    if(theDCA1D->dimension == 1) {
        maxIndex = theDCA1D->width;
    } else {
        maxIndex = theDCA1D->width * theDCA1D->height;
    }
    // printf("%d,", maxIndex);
    for(int i = 0; i < maxIndex; i++) { //Go through each index of the cells.
        // printf("%d,", i);
        theDCA1D->cadata[i] = quiescentState; //Set each cell to the quiescent state passed in.
    }
}

/* 
 * Description: Displays a 1DCA given a pointer to where the 1DCA is stored (struct ca_data).
 *      It does so by iterating through each char of the 1DCA and printing each one
 *      individually with a space in between.
 * Parameter: struct ca_data *theDCA1D - A pointer to the 1DCA struct that will be displayed.
 */
void displayCA(struct ca_data *theDCA1D) {
    int maxIndex = theDCA1D->width * theDCA1D->height;
    for(int i = 0; i < maxIndex; i++) { //For all cells within the 1DCA except the last one.
        if(i % (theDCA1D->width) == 0 && i != 0) {
            printf("\n%d ", theDCA1D->cadata[i]); //Print the char at each index with a space after it.
        } else {
            printf("%d ", theDCA1D->cadata[i]); //Print the char at each index with a space after it.
        }
    }
    printf("\n");
}

/** 
 * Description: Sets the value of a 1DCA's cell given a pointer to the 1DCA (struct ca_data), 
 *      the index you want to set, and the char to set the cell to. 
 *      Checks that the passed in index is within bounds of the 1DCA.
 * Parameter: struct ca_data *theDCA1D - A pointer to the 1DCA struct whose cell will be set.
 * Parameter: int index - The index of the cell in the 1DCA you want to set the value of.
 * Parameter: unsigned char charToSet - The char to set the cell to.
 * Returns: Integer - returns 1 if no errors occured, 0 if an error occured.
 */
int set1DCACell(struct ca_data *theDCA1D, unsigned int index, unsigned char charToSet) {
    if(!(0 <= index && index <= theDCA1D->width-1)) { //If the index is not within the bounds of the cells.
        printf("Error with set1DCACell usage - index out of bounds. The 1DCA was not modified.\n");
        return 0; //Return 0 because of error.
    } else {      //If the index is within the bounds of the 1DCA, we can set it.
        theDCA1D->cadata[index] = charToSet; //Set the value at the index to the char passed in.
        return 1; //Return 1 because no error.
    }
}

int set2DCACell(struct ca_data *theDCA1D, unsigned int index_x, unsigned int index_y, unsigned char charToSet) {
    int index = index_x+index_y*theDCA1D->width;
    if(!(0 <= index && index <= (theDCA1D->width*theDCA1D->height)-1)) { //If the index is not within the bounds of the cells.
        printf("Error with set2DCACell usage - index out of bounds. The 2DCA was not modified.\n");
        return 0; //Return 0 because of error.
    } else {      //If the index is within the bounds of the 2DCA, we can set it.
        theDCA1D->cadata[index] = charToSet; //Set the value at the index to the char passed in.
        return 1; //Return 1 because no error.
    }
}

/** 
 * Description: Creates a 1DCA on the heap with the necessary memory space for the number of cells
 *      requested and also sets the value of each cell to the quiescent state. The number of cells
 *      and quiescent state is also stored in the created 1DCA for convenience.
 * Parameter: unsigned int numCells - The number of cells the 1DCA created should have.
 * Parameter: unsigned char quiescentState - The quiescent (default) state of the 1DCA.
 * Returns: struct ca_data* - The pointer to the new 1DCA. Also returns NULL if memory couldn't be allocated.
 */
struct ca_data* create1DCA(unsigned int numCells, unsigned char quiescentState, unsigned int shouldWrapFlag) {
    struct ca_data *ca = malloc(sizeof(struct ca_data)); //Allocate memory on the heap for the ca struct.
    if(ca == NULL) return NULL; //Check to make sure the memory was allocated on the heap.
    ca->quiescentState = quiescentState; //Set ca's quiescent state to the passed in quiescent state.
    ca->width = numCells; //Set ca's number of cells to the passed in number of cells.
    ca->height = 0; //1DCA should have height of 0, since its not 2D.
    ca->wrap = shouldWrapFlag; //Set ca's should wrap flag for access later.
    ca->dimension = 1; //Set to 1DCA because thats important to the CA we are creating.
    ca->cadata = malloc(sizeof(unsigned char) * numCells); //Allocate memory on the heap for the cells array.
    if(ca->cadata == NULL) return NULL; //Check to make sure the memory was allocated on the heap.
    initCA(ca, quiescentState); //Set all the values of the 1DCA to the quiescentState.
    return ca; //Return the pointer to the 1DCA that was created.
}

struct ca_data* create2DCA(int width, int height, unsigned char quiescentState, unsigned int shouldWrapFlag) {
    struct ca_data *ca = malloc(sizeof(struct ca_data)); //Allocate memory on the heap for the ca struct.
    if(ca == NULL) return NULL; //Check to make sure the memory was allocated on the heap.
    ca->quiescentState = quiescentState; //Set ca's quiescent state to the passed in quiescent state.
    ca->width = width; //Set ca's number of cells to the passed in number of cells.
    ca->height = height; //1DCA should have height of 0, since its not 2D.
    ca->wrap = shouldWrapFlag; //Set ca's should wrap flag for access later.
    ca->dimension = 2; //Set to 1DCA because thats important to the CA we are creating.
    ca->cadata = malloc((sizeof(unsigned char)) * width * height); //Allocate memory on the heap for the cells array.
    if(ca->cadata == NULL) return NULL; //Check to make sure the memory was allocated on the heap.
    initCA(ca, quiescentState); //Set all the values of the 1DCA to the quiescentState.
    return ca;
}

/** 
 * Description: Simulates one step of the 1DCA. It does this by creating a temporary 1DCA that
 *      has an additional 2 cells (one on each end of the original 1DCA) and copying the values
 *      from the original 1DCA into the temporary 1DCA (starting at index 1 and ending 1 cell before
 *      the end) and then depending on the value of flag it sets the starting and ending cell. 
 *      After creating this temporary 1DCA (for the purpose of being able to calculate the 
 *      neighborhood of the original 1DCA nicely), the function goes through each index of the 
 *      temporary 1DCA (starting at index 1 and ending 1 cell before the end) and using the 
 *      passed in rule function calculates the next state of indexed cell. It then frees the 
 *      temporary 1DCA's memory as it's no longer needed.
 * Parameter: struct ca_data *theDCA1D - A pointer to the 1DCA struct who needs simulated once.
 * Parameter: unsigned char (*ruleFunc)(struct ca_data *tempDCA1D, int index) - A pointer to a 
 *      function that will calculate the next state of each index.
 * Parameter: int flag - A variable for handling the edge cases of the 1DCA, 1 if 1DCA should wrap, 0 if not.
 */
void step1DCA(struct ca_data *theDCA1D, unsigned char (*ruleFunc)(struct ca_data *tempDCA1D, int index)) {
    int numCells = theDCA1D->width; //Store number of cells in the 1DCA for easy access (more readable code).
    //The following code creates a temporary 1DCA with 2 extra cells to better handle edge cases.
    struct ca_data *tempDCA1D = create1DCA(numCells+2, theDCA1D->quiescentState, theDCA1D->wrap);
    if(tempDCA1D == NULL) { //Check to make sure the 1DCA was created.
        printf("Error with create1DCA: Unable to allocate required memory for the temp 1DCA.\n");
        return;
    }
    //The following for loop copies the actual 1DCA's cells into the temporary 1DCA's inner cells (leaving the 1 cell on each end to be the quiescent state).
    for(int i = 0; i < numCells; i++) { //For every cell in the actual 1DCA.
        tempDCA1D->cadata[i+1] = theDCA1D->cadata[i]; //Copy the value into the temp 1DCA skipping the 1st cell.
    }
    //The following code ensures the edge cells (leading and ending) are properly set.
    //  Because the edge cells are by default set to the quiescent state, we don't need to do anything if the user specifies not to wrap.
    if(theDCA1D->wrap) { //If flag (should wrap) is true, set the edge cells to the wrapped values on the other side of the actual 1DCA.
        tempDCA1D->cadata[0] = tempDCA1D->cadata[numCells-1]; //Set leading cell to last cell in actual 1DCA.
        tempDCA1D->cadata[numCells+1] = tempDCA1D->cadata[1]; //Set ending cell to first cell in actual 1DCA.
    }
    //The following code goes through each cell of the actual 1DCA and calculates it's new value 
    //  based off of the rule function passed in and the index of the temp 1DCA offset by 1.
    for(int i = 0; i < numCells; i++) { //For each cell of the actual 1DCA.
        theDCA1D->cadata[i] = ruleFunc(tempDCA1D, i+1); //Set the new value using result of ruleFunc given the padded 1DCA and an index offset of 1.
    }
    free(tempDCA1D->cadata); //Free the temporary cells array.
    free(tempDCA1D); //Free the temporary 1DCA.
}

void step2DCA(struct ca_data *theDCA1D, unsigned char (*ruleFunc)(struct ca_data *tempDCA1D, int index_x, int index_y)) {
    //The following code creates a temporary 1DCA with 2 extra cells to better handle edge cases.
    struct ca_data *tempDCA1D = create2DCA(theDCA1D->width, theDCA1D->height, theDCA1D->quiescentState, theDCA1D->wrap);
    if(tempDCA1D == NULL) { //Check to make sure the 1DCA was created.
        printf("Error with create2DCA: Unable to allocate required memory for the temp 2DCA.\n");
        return;
    }
    //The following for loop copies the actual 2DCA's cells into the temporary 2DCA.
    for(int x = 0; x < theDCA1D->width; x++) {
        for(int y = 0; y < theDCA1D->height; y++) {
            int index = x+(y*theDCA1D->width);
            tempDCA1D->cadata[index] = theDCA1D->cadata[index];
        }
    }
    //The following code goes through each cell of the actual 2DCA and calculates it's new value.
    for(int y = 0; y < theDCA1D->height; y++) {
        for(int x = 0; x < theDCA1D->width; x++) {
            int index = x+(y*tempDCA1D->width);
            theDCA1D->cadata[index] = ruleFunc(tempDCA1D, x, y);
        }
    }
    free(tempDCA1D->cadata); //Free the temporary cells array.
    free(tempDCA1D); //Free the temporary 1DCA.
}

/** 
 * Description: Calculates the next state of the indexed cell given the current state of the indexed cell
 *      and it's surrounding 2 cells (it's neighborhood). At this point the edge cases are already
 *      taken care of, and the client only asks for indices that have neighbors.
 * Parameter: struct ca_data *tempDCA1D - A pointer to the temporary 1DCA struct that holds the 
 *      original 1DCA along with the 2 extra cells (1 on each end) for edge cases.
 * Parameter: int index - The index of the cell that needs it's next state calculated.
 */
unsigned char rule110(struct ca_data *tempDCA1D, int index) {
    unsigned char n1, n2, n3, r; //Stores the 3 neighbors of the neighborhood as well as the result.
    n1 = tempDCA1D->cadata[index-1]; //Gets the left neighbor.
    n2 = tempDCA1D->cadata[index]; //Gets the current state of the cell we need to calculate the new cell from.
    n3 = tempDCA1D->cadata[index+1]; //Gets the right neighbor.
    int rule[] = {0,1,1,0,1,1,1,0}; //Rule 110 encoded in the order of the possible permutations.
    //The following code goes through each permutation of the neighbors and sets the result
    //  based on the permutation. The rule array stores the results in order with the permutations.
    if       (n1 == 1 && n2 == 1 && n3 == 1) {
        r = rule[0];
    } else if(n1 == 1 && n2 == 1 && n3 == 0) {
        r = rule[1];
    } else if(n1 == 1 && n2 == 0 && n3 == 1) {
        r = rule[2];
    } else if(n1 == 1 && n2 == 0 && n3 == 0) {
        r = rule[3];
    } else if(n1 == 0 && n2 == 1 && n3 == 1) {
        r = rule[4];
    } else if(n1 == 0 && n2 == 1 && n3 == 0) {
        r = rule[5];
    } else if(n1 == 0 && n2 == 0 && n3 == 1) {
        r = rule[6];
    } else if(n1 == 0 && n2 == 0 && n3 == 0) {
        r = rule[7];
    } else { //this case shouldn't occur but I wanted to put something here just in case.
        r = tempDCA1D->quiescentState;
    }
    return r;
}

unsigned char ruleGameOfLife(struct ca_data *tempDCA1D, int x, int y) {
    unsigned char n1, n2, n3, n4, n5, n6, n7, n8, c;
    //Get neighbors.
    c = tempDCA1D->cadata[x+(y*tempDCA1D->width)];
    //return c+1;
    if(tempDCA1D->wrap) {
        n1 = tempDCA1D->cadata[(((x-1) + tempDCA1D->width) % tempDCA1D->width) + ((((y-1) + tempDCA1D->height) % tempDCA1D->height)*tempDCA1D->width)];
        n2 = tempDCA1D->cadata[(((x) + tempDCA1D->width) % tempDCA1D->width) + ((((y-1) + tempDCA1D->height) % tempDCA1D->height)*tempDCA1D->width)];
        n3 = tempDCA1D->cadata[(((x+1) + tempDCA1D->width) % tempDCA1D->width) + ((((y-1) + tempDCA1D->height) % tempDCA1D->height)*tempDCA1D->width)];
        n4 = tempDCA1D->cadata[(((x-1) + tempDCA1D->width) % tempDCA1D->width) + ((((y) + tempDCA1D->height) % tempDCA1D->height)*tempDCA1D->width)];
        n5 = tempDCA1D->cadata[(((x+1) + tempDCA1D->width) % tempDCA1D->width) + ((((y) + tempDCA1D->height) % tempDCA1D->height)*tempDCA1D->width)];
        n6 = tempDCA1D->cadata[(((x-1) + tempDCA1D->width) % tempDCA1D->width) + ((((y+1) + tempDCA1D->height) % tempDCA1D->height)*tempDCA1D->width)];
        n7 = tempDCA1D->cadata[(((x) + tempDCA1D->width) % tempDCA1D->width) + ((((y+1) + tempDCA1D->height) % tempDCA1D->height)*tempDCA1D->width)];
        n8 = tempDCA1D->cadata[(((x+1) + tempDCA1D->width) % tempDCA1D->width) + ((((y+1) + tempDCA1D->height) % tempDCA1D->height)*tempDCA1D->width)];
        //printf("Neighbors of: (%d, %d) i.e. %d -> (%d,%d,%d,%d,%d,%d,%d,%d)\n", x, y, c, n1, n2, n3, n4, n5, n6, n7, n8);
    } else {
        printf("Error: 2DCA's that do not wrap are not supported in Conway' Game of Life.\n");
        return c;
    }
    int nc = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
    if(c == 1) {
        if(nc == 2 || nc == 3) {
            return 1;
        } else {
            return 0;
        }
    } else if (c == 0) {
        if(nc == 3) {
            return 1;
        } else {
            return 0;
        }
    } else {
        printf("Error: Conway's Game of Life only supports cell values of 0 or 1. All cells that are not 0 or 1 are changed to 0.\n");
        return 0;
    }
}



