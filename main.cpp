#include "GraphicsClient.h"
#include "CellularAutomaton.h"
#include <string>
#include <iostream>
using namespace std;

unsigned char ruleGameOfLife(CellularAutomaton *tempCA, int x, int y);

int main(int argc, char **argv) {
    //Checks to make sure the user entered in the correct number of arguments.
    if(argc != 2) { //If the argument count is not 2 (the first is the function name).
        printf("Error: You need to supply only 1 parameter. You supplied %d.\n", argc-1);
        return 1; //Return 1 since there is an error.
    }
    char *fileName = argv[1]; //Get the file name from command line input.
    GraphicsClient gc = GraphicsClient("127.0.0.1", 7777);
    gc.setBackgroundColor(0,0,0);
    gc.setDrawingColor(0,200,20);
    CellularAutomaton ca = CellularAutomaton(fileName, 0);
    int shouldExit = 0; //Will store if the while loop should exit or not. Done for readability.
    char input; //Stores the char the user enters into the console.
    while(!shouldExit) { //While the loop shouldn't exit.
        fflush(stdin);
        gc.clear();
        ca.displayCA(&gc); //Display the current state of the CA.
        //ca.displayCAToConsole();
        gc.repaint();
        input = getchar(); //Get the next char in the console.
        if(input == '\n') { //If the char put in the console is the return char, simulate the CA once.
            ca.step2DCA(&ruleGameOfLife);
        } else { //If the user enters any other char, then the program exits.
            shouldExit = 1; //Allows for the loop to exit, in a nice readable way.
        }
    }
    printf("Program has exited!\n");
    return 0;
}

// int main() {
//     CellularAutomaton ca = CellularAutomaton("./examples/blinker.txt", 0);
//     CellularAutomaton ca2 = CellularAutomaton("./examples/stable.txt", 0);
//     ca.displayCAToConsole();
//     printf("\n");
//     ca2.displayCAToConsole();
//     printf("\n");
//     //ca2 = ca;
//     ca2.displayCAToConsole();

//     printf("Program has exited!\n");
//     return 0;
// }

/** 
 * Description: Calculates the next state of the indexed cell given the current state of the indexed cell
 *      and it's surrounding 8 cells (it's neighborhood). Rule is based off of Conway's Game of Life.
 * Parameter: CellularAutomaton *tempCA - A pointer to the temporary CA object that holds the 
 *      original CA.
 * Parameter: int x - The x position of the cell that needs it's next state calculated.
 * Parameter: int y - The y position of the cell that needs it's next state calculated.
 */
unsigned char ruleGameOfLife(CellularAutomaton *tempCA, int x, int y) {
    //The following variables will store the various neighbors (8) and the current cell (c).
    unsigned char n1, n2, n3, n4, n5, n6, n7, n8, c;
    //Stores the value of the current cell.
    c = tempCA->getCAdata()[x+(y*tempCA->getWidth())];
    if(tempCA->getWrap()) {
        //The following 8 lines get the various neighbors (surronding 8 cells) of the current cell.
        //  In order to ensure the index's wrap properly, each x position gets width cells added to it then
        //  the position is modulo the width. Similarily with y position but with the height instead.
        //  For example, (0,0) with a width and height of 5 would mean n1 = (-1,-1) is ((-1+5)%5,(-1+5)%5) which is (4,4).
        n1 = tempCA->getCAdata()[(((x-1) + tempCA->getWidth()) % tempCA->getWidth()) + ((((y-1) + tempCA->getHeight()) % tempCA->getHeight())*tempCA->getWidth())];
        n2 = tempCA->getCAdata()[(((x) + tempCA->getWidth()) % tempCA->getWidth()) + ((((y-1) + tempCA->getHeight()) % tempCA->getHeight())*tempCA->getWidth())];
        n3 = tempCA->getCAdata()[(((x+1) + tempCA->getWidth()) % tempCA->getWidth()) + ((((y-1) + tempCA->getHeight()) % tempCA->getHeight())*tempCA->getWidth())];
        n4 = tempCA->getCAdata()[(((x-1) + tempCA->getWidth()) % tempCA->getWidth()) + ((((y) + tempCA->getHeight()) % tempCA->getHeight())*tempCA->getWidth())];
        n5 = tempCA->getCAdata()[(((x+1) + tempCA->getWidth()) % tempCA->getWidth()) + ((((y) + tempCA->getHeight()) % tempCA->getHeight())*tempCA->getWidth())];
        n6 = tempCA->getCAdata()[(((x-1) + tempCA->getWidth()) % tempCA->getWidth()) + ((((y+1) + tempCA->getHeight()) % tempCA->getHeight())*tempCA->getWidth())];
        n7 = tempCA->getCAdata()[(((x) + tempCA->getWidth()) % tempCA->getWidth()) + ((((y+1) + tempCA->getHeight()) % tempCA->getHeight())*tempCA->getWidth())];
        n8 = tempCA->getCAdata()[(((x+1) + tempCA->getWidth()) % tempCA->getWidth()) + ((((y+1) + tempCA->getHeight()) % tempCA->getHeight())*tempCA->getWidth())];
        //printf("Neighbors of: (%d, %d) i.e. %d -> (%d,%d,%d,%d,%d,%d,%d,%d)\n", x, y, c, n1, n2, n3, n4, n5, n6, n7, n8);
    } else {
        printf("Error: 2DCA's that do not wrap are not supported in Conway' Game of Life.\n");
        return c;
    }
    //Since the CA only has 0 and 1, you can calculate how many number of neighbors have a
    //  value of 1 by simply adding them together.
    int nc = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
    if(c == 1) { //If the current cell is alive,
        if(nc == 2 || nc == 3) { //and the number of neighbors alive is 2 or 3,
            return 1; //then the resulting cell is alive.
        } else { //and the number of neighbors alive is not 2 or 3,
            return 0; //then the cell dies (under-population or over-population).
        }
    } else if (c == 0) { //If the current cell is dead,
        if(nc == 3) { //and the number of neighbors alive is 3,
            return 1; //then the resulting cell is alive, by population.
        } else { //and the number of neighbors alive is not 3,
            return 0; //then the resulting cell is dead.
        }
    } else { //The current cell is not 0 or 1, that is not allowed.
        printf("Error: Conway's Game of Life only supports cell values of 0 or 1. All cells that are not 0 or 1 are changed to 0.\n");
        return 0;
    }
}

