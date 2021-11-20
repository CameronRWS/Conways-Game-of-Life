#include "GraphicsClient.h"
#include <string>
#include <iostream>
#include <chrono>
#include <sys/time.h>
#include <ctime>
using namespace std;
using namespace chrono;

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
    int shouldUpdateScreen = 1;
    milliseconds lastUpdate = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    milliseconds currentTime;
    //gc.requestFile();
    gc.drawGUI();
    ca.displayCA(&gc);
    while(!shouldExit) { //While the loop shouldn't exit.
        currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        string newFileName = gc.getMessage(&ca);
        if(newFileName != "") {
            fileName = newFileName;
            gc.setShouldReset(1);
            printf("%s\n", fileName.c_str());
        }
        if(currentTime.count() - lastUpdate.count() > 500) {
            if(gc.getShouldRefresh()) {
                ca.stepAndDisplayCA(&gc);
            }
            if(gc.getShouldReset()) {
                ca = CellularAutomaton(fileName, 0);
                gc.clearGame();
                ca.displayCA(&gc);
                gc.setShouldReset(0);
                gc.setShouldRefresh(0);
            }
            if(gc.getShouldExit()) {
                shouldExit = 1;
            }
            lastUpdate = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        }
    }
    printf("Program has exited!\n");
    return 0;
}
