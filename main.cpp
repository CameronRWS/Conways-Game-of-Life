#include <string>
#include <iostream>
#include "CAGraphicsSimulator.h" 
#include "GraphicsClient.h" 
#include "CellularAutomaton.h" 
using namespace std;

int main(int argc, char **argv) {
    //Checks to make sure the user entered in the correct number of arguments.
    if(argc != 2) { //If the argument count is not 2 (the first is the function name).
        printf("Error: You need to supply only 1 parameter. You supplied %d.\n", argc-1);
        return 1; //Return 1 since there is an error.
    }
    string fileName = argv[1]; //Get the file name from command line input.
    GraphicsClient gc = GraphicsClient("127.0.0.1", 7777);
    CellularAutomaton ca = CellularAutomaton(fileName, 0);
    CAGraphicsSimulator cags = CAGraphicsSimulator(&gc, &ca);
    cags.simulate();
    return 0;
}
