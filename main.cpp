#include "GraphicsClient.h"
#include <string>
#include <iostream>
#include <chrono>
#include <sys/time.h>
#include <ctime>
using namespace std;

int main(int argc, char **argv) {
    //Checks to make sure the user entered in the correct number of arguments.
    if(argc != 2) { //If the argument count is not 2 (the first is the function name).
        printf("Error: You need to supply only 1 parameter. You supplied %d.\n", argc-1);
        return 1; //Return 1 since there is an error.
    }
    string fileName = argv[1]; //Get the file name from command line input.
    GraphicsClient gc = GraphicsClient("127.0.0.1", 7777);
    gc.setBackgroundColor(0, 0, 0);
    CellularAutomaton ca = CellularAutomaton(fileName, 0);
    int shouldExit = 0; //Will store if the while loop should exit or not. Done for readability.
    char input; //Stores the char the user enters into the console.
    gc.drawGUI();
    ca.displayCA(&gc);
    while(!shouldExit) { //While the loop shouldn't exit.
        gc.checkForMessages(&ca);
        if(gc.getShouldRefresh()) {
            ca.stepAndDisplayCA(&gc);
        }
        if(gc.getShouldExit()) {
            shouldExit = 1;
        }
        nanosleep((const struct timespec[]){{0, 100000000L}}, NULL);
    }
    printf("Program has exited!\n");
    return 0;
}
