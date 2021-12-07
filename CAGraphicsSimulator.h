#include <string> //For using strings.
#include "CellularAutomaton.h" //For using CA.
#include "GraphicsClient.h" //For using GC.

using namespace std; //Allows for 'std::' to be removed from certain lines.

#ifndef CAGS_HEADER
#define CAGS_HEADER

/** 
 * Description: Simulates a Cellular Automaton graphically. Handles all of the logic that is unique to 
 *  simulating the Cellular Automaton using the Graphics Client without having to modify what the 
 *  CA and GC class do.
 */
class CAGraphicsSimulator {
    public:
        CAGraphicsSimulator(GraphicsClient* gc, CellularAutomaton* ca);
        CAGraphicsSimulator(const CAGraphicsSimulator&) = delete;
        CAGraphicsSimulator& operator=(const CAGraphicsSimulator&) = delete;
        ~CAGraphicsSimulator() = default;
        void drawButton(int x, int y, int w, int h, string name);
        int getShouldStep();
        int getShouldExit();
        void clearGame();
        void clickEvent(int x, int y);
        void drawGUI();
        void displayCA();
        void checkForAndExecuteMessages();
        void stepAndDisplayCA();
        void checkForCAClick(int x, int y);
        void simulate();
        void saveCAToFile();
        void logEvent(string text);
    private:
        //Member/Field: GraphicsClient* gc - A reference to the Graphics Client to allow for displaying the CA graphically.
        GraphicsClient* gc;
        //Member/Field: CellularAutomaton* ca - A reference to the Cellular Automaton to display and modify.
        CellularAutomaton* ca;
        //Member/Field: int shouldStep - Whether or not the CA should step to it's next state when the graphics window refreshes.
        int shouldStep;
        //Member/Field: int shouldExit - Whether or not the program should exit.
        int shouldExit;
};

#endif