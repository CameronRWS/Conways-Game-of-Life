
#include <stdio.h>
#include <string.h>


void init1DCA(int numCellsToCreate, unsigned char *startOfString) {
    for(int i = 0; i < numCellsToCreate - 1; i++) {
        startOfString[i] = '0';
    }
    startOfString[numCellsToCreate-1] = '\0';
}

int main(void) {
    int lengthOfAuto = 32;
    unsigned char dca1d[lengthOfAuto];
    init1DCA(lengthOfAuto, dca1d);
    printf("%s\n", dca1d);
    return 0;
}