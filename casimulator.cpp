#include <string> //Allows for string usage (the file passed in)
#include "CAGraphicsSimulator.h" //Allows for CAGS usage.
#include "GraphicsClient.h" //Allows for GC usage.
#include "CellularAutomaton.h" //Allows for CA usage.

using namespace std; //Allows for 'std::' to be removed from certain lines.

/**
 * Description: The main method and entry point of this program. It gets a file from the command 
 * line parameters and uses it to simulate a Cellular Automaton on a graphics window.
 * Parameter: argc - The amount of command line parameters.
 * Parameter: argv - An array of pointers to the values passed into the program.
 * Returns: int - Indicates whether or not the program failed.
 */
int main(int argc, char **argv) {
    //Checks to make sure the user entered in the correct number of arguments.
    if(argc != 2) { //If the argument count is not 2 (the first is the function name).
        printf("Error: You need to supply only 1 parameter. You supplied %d.\n", argc-1);
        return 1; //Return 1 since there is an error.
    }
    string fileName = argv[1]; //Get the file name from command line input.
    GraphicsClient gc("127.0.0.1", 7777); //Create a GC on the stack.
    CellularAutomaton ca(fileName, 0); //Create a CA on the stack.
    CAGraphicsSimulator cags(&gc, &ca); //Create a CAGS on the stack.
    cags.simulate(); //Simulate the CA on the graphics window.
    return 0;
}
