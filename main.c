#include <stdio.h>
#include "ca.h"

int main(void) {
    struct ca_data ca = { .numCells = 3};
    //printf("%d\n", ca.numCells);
    init1DCA(&ca, 0);
    display1DCA(&ca);

}