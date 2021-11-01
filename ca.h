
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

void initCA(struct ca_data *theCA, int quiescentState);
void displayCA(struct ca_data *theCA);
int set1DCACell(struct ca_data *theCA, unsigned int index, unsigned char charToSet);
int set2DCACell(struct ca_data *theCA, unsigned int index_x, unsigned int index_y, unsigned char charToSet);
void step1DCA(struct ca_data *theCA, unsigned char (*ruleFunc)(struct ca_data *tempCA, int index));
void step2DCA(struct ca_data *theCA, unsigned char (*ruleFunc)(struct ca_data *tempCA, int index_x, int index_y));
struct ca_data* create1DCA(unsigned int numCells, unsigned char quiescentState, unsigned int shouldWrapFlag);
struct ca_data* create2DCA(int width, int height, unsigned char quiescentState, unsigned int shouldWrapFlag);
unsigned char rule110(struct ca_data *tempCA, int index);
unsigned char ruleGameOfLife(struct ca_data *tempCA, int x, int y);

#endif