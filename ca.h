
#ifndef CA_HEADER //If this has not been defined yet, define it.
#define CA_HEADER

typedef struct ca_data {
    int numCells;
    unsigned char cells[];
} ca_data;

void init1DCA(struct ca_data *theDCA1D, int quiescentState);
void display1DCA(struct ca_data *theDCA1D);

#endif
