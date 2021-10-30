
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

void displayCA(struct ca_data *theDCA1D);
int set1DCACell(struct ca_data *theDCA1D, unsigned int index, unsigned char charToSet);
int set2DCACell(struct ca_data *theDCA1D, unsigned int index_x, unsigned int index_y, unsigned char charToSet);
int set2DCACellDebug(struct ca_data *theDCA1D, unsigned int index, unsigned char charToSet);
void initCA(struct ca_data *theDCA1D, int quiescentState);
void step1DCA(struct ca_data *theDCA1D, unsigned char (*ruleFunc)(struct ca_data *tempDCA1D, int index));
void step2DCA(struct ca_data *theDCA1D, unsigned char (*ruleFunc)(struct ca_data *tempDCA1D, int index_x, int index_y));
struct ca_data* create1DCA(unsigned int numCells, unsigned char quiescentState, unsigned int shouldWrapFlag);
struct ca_data* create2DCA(int width, int height, unsigned char quiescentState, unsigned int shouldWrapFlag);
unsigned char rule110(struct ca_data *tempDCA1D, int index);
unsigned char ruleGameOfLife(struct ca_data *tempDCA1D, int x, int y);

#endif