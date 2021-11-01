#include <stdio.h> //Allows for use of printf.
#include <stdlib.h> //Allows for use of free and malloc.
#include "ca.h" //Allows for 1DCA and 2DCA usage.

/** 
 * Description: Initializes a CA given a pointer to where the CA is stored (struct ca_data).
 *      This function will set all values in the CA to it's passed in quiescent state.
 * Parameter: struct ca_data *theCA - A pointer to the CA struct that will be initiated.
 * Parameter: int quiescentState - The quiescent state to set the cells in the CA to.
 */
void initCA(struct ca_data *theCA, int quiescentState) {
    int maxIndex = 0; //Stores the max index of the CA.
    //The following lines determine the max index of the CA.
    if(theCA->dimension == 1) { //If dim is 1, the max index is w (width).
        maxIndex = theCA->width;
    } else { //If not 1, then defaults to 2 where max index is w*h.
        maxIndex = theCA->width * theCA->height;
    }
    for(int i = 0; i < maxIndex; i++) { //Go through each index of the cells.
        theCA->cadata[i] = quiescentState; //Set each cell to the quiescent state passed in.
    }
}

/* 
 * Description: Displays a CA given a pointer to where the CA is stored (struct ca_data).
 *      It does so by iterating through each char of the CA and printing each one
 *      individually with a space in between.
 * Parameter: struct ca_data *theCA - A pointer to the CA struct that will be displayed.
 */
void displayCA(struct ca_data *theCA) {
    int maxIndex = theCA->width * theCA->height; 
    for(int i = 0; i < maxIndex; i++) { //For all cells within the CA.
        if(i % (theCA->width) == 0 && i != 0) { //If i is at the end of a row, create a new line.
            printf("\n%d ", theCA->cadata[i]); //Print the return char then the char with a space after it.
        } else {
            printf("%d ", theCA->cadata[i]); //Print the char with a space after it.
        }
    }
    printf("\n");
}

/** 
 * Description: Sets the value of a CA's cell given a pointer to the CA (struct ca_data), 
 *      the index you want to set, and the char to set the cell to. 
 *      Checks that the passed in index is within bounds of the CA.
 * Parameter: struct ca_data *theCA - A pointer to the CA struct whose cell will be set.
 * Parameter: unsigned int index - The index of the cell in the CA you want to set the value of.
 * Parameter: unsigned char charToSet - The char to set the cell to.
 * Returns: Integer - returns 1 if no errors occured, 0 if an error occured.
 */
int set1DCACell(struct ca_data *theCA, unsigned int index, unsigned char charToSet) {
    if(!(0 <= index && index <= theCA->width-1)) { //If the index is not within the bounds of the cells.
        printf("Error with set1DCACell usage - index out of bounds. The 1DCA was not modified.\n");
        return 0; //Return 0 because of error.
    } else {      //If the index is within the bounds of the CA, we can set it.
        theCA->cadata[index] = charToSet; //Set the value at the index to the char passed in.
        return 1; //Return 1 because no error.
    }
}

/** 
 * Description: Sets the value of a CA's cell given a pointer to the CA (struct ca_data), 
 *      the index you want to set (the x and y position), and the char to set the cell to. 
 *      Checks that the passed in index is within bounds of the CA.
 * Parameter: struct ca_data *theCA - A pointer to the CA struct whose cell will be set.
 * Parameter: unsigned int index_x - The x position of the cell in the CA you want to set the value of.
 * Parameter: unsigned int index_y - The y position of the cell in the CA you want to set the value of.
 * Parameter: unsigned char charToSet - The char to set the cell to.
 * Returns: Integer - returns 1 if no errors occured, 0 if an error occured.
 */
int set2DCACell(struct ca_data *theCA, unsigned int index_x, unsigned int index_y, unsigned char charToSet) {
    int index = index_x+index_y*theCA->width; //converts the x and y index to it's index in the array.
    if(!(0 <= index && index <= (theCA->width*theCA->height)-1)) { //If the index is not within the bounds of the cells.
        printf("Error with set2DCACell usage - index out of bounds. The 2DCA was not modified.\n");
        return 0; //Return 0 because of error.
    } else {      //If the index is within the bounds of the 2DCA, we can set it.
        theCA->cadata[index] = charToSet; //Set the value at the index to the char passed in.
        return 1; //Return 1 because no error.
    }
}

/** 
 * Description: Simulates one step of the 1DCA. It does this by creating a temporary CA that
 *      has an additional 2 cells (one on each end of the original CA) and copying the values
 *      from the original CA into the temporary CA (starting at index 1 and ending 1 cell before
 *      the end) and then depending on the value of flag it sets the starting and ending cell. 
 *      After creating this temporary CA (for the purpose of being able to calculate the 
 *      neighborhood of the original CA nicely), the function goes through each index of the 
 *      temporary CA (starting at index 1 and ending 1 cell before the end) and using the 
 *      passed in rule function calculates the next state of indexed cell. It then frees the 
 *      temporary CA's memory as it's no longer needed.
 * Parameter: struct ca_data *theCA - A pointer to the CA struct who needs simulated once.
 * Parameter: unsigned char (*ruleFunc)(struct ca_data *tempCA, int index) - A pointer to a 
 *      function that will calculate the next state of each index.
 */
void step1DCA(struct ca_data *theCA, unsigned char (*ruleFunc)(struct ca_data *tempCA, int index)) {
    int numCells = theCA->width; //Store number of cells in the CA for easy access (more readable code).
    //The following code creates a temporary CA with 2 extra cells to better handle edge cases.
    struct ca_data *tempCA = create1DCA(numCells+2, theCA->quiescentState, theCA->wrap);
    if(tempCA == NULL) { //Check to make sure the CA was created.
        printf("Error with create1DCA: Unable to allocate required memory for the temp CA.\n");
        return;
    }
    //The following for loop copies the actual CA's cells into the temporary CA's inner cells (leaving the 1 cell on each end to be the quiescent state).
    for(int i = 0; i < numCells; i++) { //For every cell in the actual CA.
        tempCA->cadata[i+1] = theCA->cadata[i]; //Copy the value into the temp CA skipping the 1st cell.
    }
    //The following code ensures the edge cells (leading and ending) are properly set.
    //  Because the edge cells are by default set to the quiescent state, we don't need to do anything if the user specifies not to wrap.
    if(theCA->wrap) { //If flag (should wrap) is true, set the edge cells to the wrapped values on the other side of the actual CA.
        tempCA->cadata[0] = tempCA->cadata[numCells-1]; //Set leading cell to last cell in actual CA.
        tempCA->cadata[numCells+1] = tempCA->cadata[1]; //Set ending cell to first cell in actual CA.
    }
    //The following code goes through each cell of the actual CA and calculates it's new value 
    //  based off of the rule function passed in and the index of the temp CA offset by 1.
    for(int i = 0; i < numCells; i++) { //For each cell of the actual CA.
        theCA->cadata[i] = ruleFunc(tempCA, i+1); //Set the new value using result of ruleFunc given the padded CA and an index offset of 1.
    }
    free(tempCA->cadata); //Free the temporary cells array.
    free(tempCA); //Free the temporary CA.
}

/** 
 * Description: Simulates one step of the 2DCA. It does this by creating a temporary CA that
 *      has the values of the original CA that gets used to calculate the values for the next
 *      step of the CA. No need for any padding cells in this 2DCA.
 * Parameter: struct ca_data *theCA - A pointer to the CA struct who needs simulated once.
 * Parameter: unsigned char (*ruleFunc)(struct ca_data *tempCA, int index_x, int index_y) - A pointer to a 
 *      function that will calculate the next state of each index (x and y position).
 */
void step2DCA(struct ca_data *theCA, unsigned char (*ruleFunc)(struct ca_data *tempCA, int index_x, int index_y)) {
    //The following code creates a temporary CA.
    struct ca_data *tempCA = create2DCA(theCA->width, theCA->height, theCA->quiescentState, theCA->wrap);
    if(tempCA == NULL) { //Check to make sure the CA was created.
        printf("Error with create2DCA: Unable to allocate required memory for the temp 2DCA.\n");
        return;
    }
    //The following for loop copies the actual 2DCA's cells into the temporary 2DCA.
    for(int x = 0; x < theCA->width; x++) {
        for(int y = 0; y < theCA->height; y++) {
            int index = x+(y*theCA->width); //Converts the coords to an index.
            tempCA->cadata[index] = theCA->cadata[index]; //Copies actual value into temp.
        }
    }
    //The following code goes through each cell of the actual 2DCA and calculates it's new value.
    for(int x = 0; x < theCA->width; x++) {
        for(int y = 0; y < theCA->height; y++) {
            int index = x+(y*tempCA->width); //Converts the coords to an index.
            theCA->cadata[index] = ruleFunc(tempCA, x, y); //Calculates the new value via the rule.
        }
    }
    free(tempCA->cadata); //Free the temporary cells array.
    free(tempCA); //Free the temporary CA.
}

/** 
 * Description: Creates a 1DCA on the heap with the necessary memory space for the number of cells
 *      requested and also sets the value of each cell to the quiescent state. The number of cells,
 *      quiescent state, and should wrap flag is also stored in the created 1DCA for convenience.
 * Parameter: unsigned int numCells - The number of cells the 1DCA created should have. Could also be thought of as the width.
 * Parameter: unsigned char quiescentState - The quiescent (default) state of the 1DCA.
 * Parameter: unsigned int shouldWrapFlag - Whether or not the 1DCA wraps.
 * Returns: struct ca_data* - The pointer to the new 1DCA. Also returns NULL if memory couldn't be allocated.
 */
struct ca_data* create1DCA(unsigned int numCells, unsigned char quiescentState, unsigned int shouldWrapFlag) {
    struct ca_data *ca = malloc(sizeof(struct ca_data)); //Allocate memory on the heap for the ca struct.
    if(ca == NULL) return NULL; //Check to make sure the memory was allocated on the heap.
    ca->quiescentState = quiescentState; //Set ca's quiescent state to the passed in quiescent state.
    ca->width = numCells; //Set ca's width to the number of cells requested.
    ca->height = 0; //CA should have height of 0, since its not 2D.
    ca->wrap = shouldWrapFlag; //Set ca's should wrap flag for access later.
    ca->dimension = 1; //Set to 1DCA because thats important to the CA we are creating.
    ca->cadata = malloc(sizeof(unsigned char) * numCells); //Allocate memory on the heap for the cells array.
    if(ca->cadata == NULL) return NULL; //Check to make sure the memory was allocated on the heap.
    initCA(ca, quiescentState); //Set all the values of the CA to the quiescentState.
    return ca; //Return the pointer to the CA that was created.
}

/** 
 * Description: Creates a 2DCA on the heap with the necessary memory space for the number of cells
 *      requested and also sets the value of each cell to the quiescent state. The width, height,
 *      quiescent state, and should wrap flag is also stored in the created 2DCA for convenience.
 * Parameter: int width - The width the 2DCA created should have.
 * Parameter: int height - The height the 2DCA created should have.
 * Parameter: unsigned char quiescentState - The quiescent (default) state of the 2DCA.
 * Parameter: unsigned int shouldWrapFlag - Whether or not the 2DCA wraps.
 * Returns: struct ca_data* - The pointer to the new 2DCA. Also returns NULL if memory couldn't be allocated.
 */
struct ca_data* create2DCA(int width, int height, unsigned char quiescentState, unsigned int shouldWrapFlag) {
    struct ca_data *ca = malloc(sizeof(struct ca_data)); //Allocate memory on the heap for the ca struct.
    if(ca == NULL) return NULL; //Check to make sure the memory was allocated on the heap.
    ca->quiescentState = quiescentState; //Set ca's quiescent state to the passed in quiescent state.
    ca->width = width; //Set ca's width to the given width.
    ca->height = height; //Set ca's height to the given height.
    ca->wrap = shouldWrapFlag; //Set ca's should wrap flag for access later.
    ca->dimension = 2; //Set to 2DCA because thats important to the CA we are creating.
    ca->cadata = malloc((sizeof(unsigned char)) * width * height); //Allocate memory on the heap for the cells array.
    if(ca->cadata == NULL) return NULL; //Check to make sure the memory was allocated on the heap.
    initCA(ca, quiescentState); //Set all the values of the CA to the quiescentState.
    return ca;
}

/** 
 * Description: Calculates the next state of the indexed cell given the current state of the indexed cell
 *      and it's surrounding 2 cells (it's neighborhood). At this point the edge cases are already
 *      taken care of, and the client only asks for indices that have neighbors.
 * Parameter: struct ca_data *tempCA - A pointer to the temporary CA struct that holds the 
 *      original CA along with the 2 extra cells (1 on each end) for edge cases.
 * Parameter: int index - The index of the cell that needs it's next state calculated.
 */
unsigned char rule110(struct ca_data *tempCA, int index) {
    unsigned char n1, n2, n3, r; //Stores the 3 neighbors of the neighborhood as well as the result.
    n1 = tempCA->cadata[index-1]; //Gets the left neighbor.
    n2 = tempCA->cadata[index]; //Gets the current state of the cell we need to calculate the new cell from.
    n3 = tempCA->cadata[index+1]; //Gets the right neighbor.
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
        r = tempCA->quiescentState;
    }
    return r;
}

/** 
 * Description: Calculates the next state of the indexed cell given the current state of the indexed cell
 *      and it's surrounding 8 cells (it's neighborhood). Rule is based off of Conway's Game of Life.
 * Parameter: struct ca_data *tempCA - A pointer to the temporary CA struct that holds the 
 *      original CA along with the 2 extra cells (1 on each end) for edge cases.
 * Parameter: int x - The x position of the cell that needs it's next state calculated.
 * Parameter: int y - The y position of the cell that needs it's next state calculated.
 */
unsigned char ruleGameOfLife(struct ca_data *tempCA, int x, int y) {
    //The following variables will store the various neighbors (8) and the current cell (c).
    unsigned char n1, n2, n3, n4, n5, n6, n7, n8, c;
    //Stores the value of the current cell.
    c = tempCA->cadata[x+(y*tempCA->width)];
    if(tempCA->wrap) {
        //The following 8 lines get the various neighbors (surronding 8 cells) of the current cell.
        //  In order to ensure the index's wrap properly, each x position gets width cells added to it then
        //  the position is modulo the width. Similarily with y position but with the height instead.
        //  For example, (0,0) with a width and height of 5 would mean n1 = (-1,-1) is ((-1+5)%5,(-1+5)%5) which is (4,4).
        n1 = tempCA->cadata[(((x-1) + tempCA->width) % tempCA->width) + ((((y-1) + tempCA->height) % tempCA->height)*tempCA->width)];
        n2 = tempCA->cadata[(((x) + tempCA->width) % tempCA->width) + ((((y-1) + tempCA->height) % tempCA->height)*tempCA->width)];
        n3 = tempCA->cadata[(((x+1) + tempCA->width) % tempCA->width) + ((((y-1) + tempCA->height) % tempCA->height)*tempCA->width)];
        n4 = tempCA->cadata[(((x-1) + tempCA->width) % tempCA->width) + ((((y) + tempCA->height) % tempCA->height)*tempCA->width)];
        n5 = tempCA->cadata[(((x+1) + tempCA->width) % tempCA->width) + ((((y) + tempCA->height) % tempCA->height)*tempCA->width)];
        n6 = tempCA->cadata[(((x-1) + tempCA->width) % tempCA->width) + ((((y+1) + tempCA->height) % tempCA->height)*tempCA->width)];
        n7 = tempCA->cadata[(((x) + tempCA->width) % tempCA->width) + ((((y+1) + tempCA->height) % tempCA->height)*tempCA->width)];
        n8 = tempCA->cadata[(((x+1) + tempCA->width) % tempCA->width) + ((((y+1) + tempCA->height) % tempCA->height)*tempCA->width)];
        //printf("Neighbors of: (%d, %d) i.e. %d -> (%d,%d,%d,%d,%d,%d,%d,%d)\n", x, y, c, n1, n2, n3, n4, n5, n6, n7, n8);
    } else {
        printf("Error: 2DCA's that do not wrap are not supported in Conway' Game of Life.\n");
        return c;
    }
    //Since the CA only has 0 and 1, you can calculate how many number of neighbors have a
    //  value of 1 by simply adding them together.
    int nc = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
    if(c == 1) { //If the current cell is alive,
        if(nc == 2 || nc == 3) { //and the number of neighbors alive is 2 or 3,
            return 1; //then the resulting cell is alive.
        } else { //and the number of neighbors alive is not 2 or 3,
            return 0; //then the cell dies (under-population or over-population).
        }
    } else if (c == 0) { //If the current cell is dead,
        if(nc == 3) { //and the number of neighbors alive is 3,
            return 1; //then the resulting cell is alive, by population.
        } else { //and the number of neighbors alive is not 3,
            return 0; //then the resulting cell is dead.
        }
    } else { //The current cell is not 0 or 1, that is not allowed.
        printf("Error: Conway's Game of Life only supports cell values of 0 or 1. All cells that are not 0 or 1 are changed to 0.\n");
        return 0;
    }
}



