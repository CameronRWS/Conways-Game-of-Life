
#ifndef CA_HEADER //If this has not been defined yet, define it.
#define CA_HEADER

typedef struct ca_data {
    unsigned char quiescentState;
    int numCells;
    unsigned char *cells;
} ca_data;

void init1DCA(struct ca_data *theDCA1D, int quiescentState);
void display1DCA(struct ca_data *theDCA1D);
int set1DCACell(struct ca_data *theDCA1D, unsigned int index, unsigned char charToSet);
struct ca_data* create1DCA(unsigned int numCells, unsigned char quiescentState);
//void stepCA(struct ca_data *theDCA1D, unsigned char (*ruleFunc)(struct ca_data *theDCA1D, int index), int flag) ;
void stepCA(struct ca_data *theDCA1D, unsigned char (*ruleFunc)(struct ca_data *theDCA1D, int index, int flag), int flag);
unsigned char rule110(struct ca_data *theDCA1D, int index, int flag);
#endif