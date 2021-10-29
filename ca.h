
#ifndef CA_HEADER //If this has not been defined yet, define it.
#define CA_HEADER

/** 
 * Description: Stores a 1DCA in a convenient stuct.
 * Member/Field: unsigned char quiescentState - The quiescent (default) state of the 1DCA.
 * Member/Field: int numCells - The number of cells in the 1DCA.
 * Member/Field: unsigned char *cells - A pointer to the start of an array containing the 
 *      cells of the 1DCA.
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
 * Description: Initializes a 1DCA given a pointer to where the 1DCA is stored (struct ca_data).
 *      This function will set all values in the 1DCA to it's passed in quiescent state.
 * Parameter: struct ca_data *theDCA1D - A pointer to the 1DCA struct that will be initiated.
 * Parameter: int quiescentState - The quiescent state to set the cells in the 1DCA to.
 */
void initCA(struct ca_data *theDCA1D, int quiescentState);

/* 
 * Description: Displays a 1DCA given a pointer to where the 1DCA is stored (struct ca_data).
 *      It does so by iterating through each char of the 1DCA and printing each one
 *      individually with a space in between.
 * Parameter: struct ca_data *theDCA1D - A pointer to the 1DCA struct that will be displayed.
 */
void display1DCA(struct ca_data *theDCA1D);

/** 
 * Description: Sets the value of a 1DCA's cell given a pointer to the 1DCA (struct ca_data), 
 *      the index you want to set, and the char to set the cell to. 
 *      Checks that the passed in index is within bounds of the 1DCA.
 * Parameter: struct ca_data *theDCA1D - A pointer to the 1DCA struct whose cell will be set.
 * Parameter: int index - The index of the cell in the 1DCA you want to set the value of.
 * Parameter: unsigned char charToSet - The char to set the cell to.
 * Returns: Integer - returns 1 if no errors occured, 0 if an error occured.
 */
int set1DCACell(struct ca_data *theDCA1D, unsigned int index, unsigned char charToSet);

/** 
 * Description: Creates a 1DCA on the heap with the necessary memory space for the number of cells
 *      requested and also sets the value of each cell to the quiescent state. The number of cells
 *      and quiescent state is also stored in the created 1DCA for convenience.
 * Parameter: unsigned int numCells - The number of cells the 1DCA created should have.
 * Parameter: unsigned char quiescentState - The quiescent (default) state of the 1DCA.
 * Returns: struct ca_data* - The pointer to the new 1DCA. Also returns NULL if memory couldn't be allocated.
 */
struct ca_data* create1DCA(unsigned int numCells, unsigned char quiescentState, unsigned int shouldWrapFlag);

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
void step1DCA(struct ca_data *theDCA1D, unsigned char (*ruleFunc)(struct ca_data *tempDCA1D, int index));

/** 
 * Description: Calculates the next state of the indexed cell given the current state of the indexed cell
 *      and it's surrounding 2 cells (it's neighborhood). At this point the edge cases are already
 *      taken care of, and the client only asks for indices that have neighbors.
 * Parameter: struct ca_data *tempDCA1D - A pointer to the temporary 1DCA struct that holds the 
 *      original 1DCA along with the 2 extra cells (1 on each end) for edge cases.
 * Parameter: int index - The index of the cell that needs it's next state calculated.
 */
unsigned char rule110(struct ca_data *tempDCA1D, int index);





int set2DCACell(struct ca_data *theDCA1D, unsigned int index_x, unsigned int index_y, unsigned char charToSet);
void step2DCA(struct ca_data *theDCA1D, unsigned char (*ruleFunc)(struct ca_data *tempDCA1D, int index_x, int index_y));
struct ca_data* create2DCA(int width, int height, unsigned char quiescentState, unsigned int shouldWrapFlag);
void init1DCA(struct ca_data *theDCA1D, int quiescentState);


#endif