#include <stdio.h>
#include <stdlib.h>
#include "ca.h"

int main(void) {
    // struct ca_data ca = { .numCells = 3};
    // int quiescentState = 3;
    // init1DCA(&ca, quiescentState);
    // set1DCACell(&ca, 2, 4);
    // display1DCA(&ca);
    struct ca_data *ca = create1DCA(5, 1);
    display1DCA(ca);
    stepCA(ca, &rule110, 1);
    display1DCA(ca);


}