
#ifndef CA_HEADER //If this has not been defined yet, define it.
#define CA_HEADER

/** 
 * Description: Stores a CA in a convenient stuct.
 * Member/Field: unsigned char quiescentState - The quiescent (default) state of the CA.
 * Member/Field: int width - The width of the CA.
 * Member/Field: int height - The height of the CA. 0 if it's a 1DCA.
 * Member/Field: unsigned char *cells - A pointer to the start of an array containing the 
 *      cells of the CA.
 * Member/Field: unsigned char wrap - Stores if the CA should wrap or not.
 * Member/Field: unsigned char dimension - Stores if the CA is 1D or 2D.
 */
typedef struct ca_data {
    unsigned char quiescentState;
    int width;
    int height;
    unsigned char *cadata;
    unsigned char wrap;
    unsigned char dimension;
} ca_data;

/** 
 * Description: Initializes a CA given a pointer to where the CA is stored (struct ca_data).
 *      This function will set all values in the CA to it's passed in quiescent state.
 * Parameter: struct ca_data *theCA - A pointer to the CA struct that will be initiated.
 * Parameter: int quiescentState - The quiescent state to set the cells in the CA to.
 */
void initCA(struct ca_data *theCA, int quiescentState);

/* 
 * Description: Displays a CA given a pointer to where the CA is stored (struct ca_data).
 *      It does so by iterating through each char of the CA and printing each one
 *      individually with a space in between.
 * Parameter: struct ca_data *theCA - A pointer to the CA struct that will be displayed.
 */
void displayCA(struct ca_data *theCA);

/** 
 * Description: Sets the value of a CA's cell given a pointer to the CA (struct ca_data), 
 *      the index you want to set, and the char to set the cell to. 
 *      Checks that the passed in index is within bounds of the CA.
 * Parameter: struct ca_data *theCA - A pointer to the CA struct whose cell will be set.
 * Parameter: unsigned int index - The index of the cell in the CA you want to set the value of.
 * Parameter: unsigned char charToSet - The char to set the cell to.
 * Returns: Integer - returns 1 if no errors occured, 0 if an error occured.
 */
int set1DCACell(struct ca_data *theCA, unsigned int index, unsigned char charToSet);

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
int set2DCACell(struct ca_data *theCA, unsigned int index_x, unsigned int index_y, unsigned char charToSet);

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
void step1DCA(struct ca_data *theCA, unsigned char (*ruleFunc)(struct ca_data *tempCA, int index));

/** 
 * Description: Simulates one step of the 2DCA. It does this by creating a temporary CA that
 *      has the values of the original CA that gets used to calculate the values for the next
 *      step of the CA. No need for any padding cells in this 2DCA.
 * Parameter: struct ca_data *theCA - A pointer to the CA struct who needs simulated once.
 * Parameter: unsigned char (*ruleFunc)(struct ca_data *tempCA, int index_x, int index_y) - A pointer to a 
 *      function that will calculate the next state of each index (x and y position).
 */
void step2DCA(struct ca_data *theCA, unsigned char (*ruleFunc)(struct ca_data *tempCA, int index_x, int index_y));

/** 
 * Description: Creates a 1DCA on the heap with the necessary memory space for the number of cells
 *      requested and also sets the value of each cell to the quiescent state. The number of cells,
 *      quiescent state, and should wrap flag is also stored in the created 1DCA for convenience.
 * Parameter: unsigned int numCells - The number of cells the 1DCA created should have. Could also be thought of as the width.
 * Parameter: unsigned char quiescentState - The quiescent (default) state of the 1DCA.
 * Parameter: unsigned int shouldWrapFlag - Whether or not the 1DCA wraps.
 * Returns: struct ca_data* - The pointer to the new 1DCA. Also returns NULL if memory couldn't be allocated.
 */
struct ca_data* create1DCA(unsigned int numCells, unsigned char quiescentState, unsigned int shouldWrapFlag);

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
struct ca_data* create2DCA(int width, int height, unsigned char quiescentState, unsigned int shouldWrapFlag);

/** 
 * Description: Calculates the next state of the indexed cell given the current state of the indexed cell
 *      and it's surrounding 2 cells (it's neighborhood). At this point the edge cases are already
 *      taken care of, and the client only asks for indices that have neighbors.
 * Parameter: struct ca_data *tempCA - A pointer to the temporary CA struct that holds the 
 *      original CA along with the 2 extra cells (1 on each end) for edge cases.
 * Parameter: int index - The index of the cell that needs it's next state calculated.
 */
unsigned char rule110(struct ca_data *tempCA, int index);

/** 
 * Description: Calculates the next state of the indexed cell given the current state of the indexed cell
 *      and it's surrounding 8 cells (it's neighborhood). Rule is based off of Conway's Game of Life.
 * Parameter: struct ca_data *tempCA - A pointer to the temporary CA struct that holds the 
 *      original CA along with the 2 extra cells (1 on each end) for edge cases.
 * Parameter: int x - The x position of the cell that needs it's next state calculated.
 * Parameter: int y - The y position of the cell that needs it's next state calculated.
 */
unsigned char ruleGameOfLife(struct ca_data *tempCA, int x, int y);

#endif