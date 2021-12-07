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
        /** 
         * Description: Constructs a CAGraphicsSimulator object.
         * Parameter: gc - A pointer to the GC object that the CA will be displayed on.
         * Parameter: ca - A pointer to the CA object that will be simulated graphically.
         */
        CAGraphicsSimulator(GraphicsClient* gc, CellularAutomaton* ca);
        //The following lines are for the CAGS's copy constructor (not allowed), equals operator (not allowed), and destructor (the default).
        CAGraphicsSimulator(const CAGraphicsSimulator&) = delete;
        CAGraphicsSimulator& operator=(const CAGraphicsSimulator&) = delete;
        ~CAGraphicsSimulator() = default;
        /** 
         * Description: Simulates the CA on the Graphics Window with interative buttons.
         */
        void simulate();
        /** 
         * Description: Draws a button on the Graphics Window.
         * Parameter: x - The x coord of where the button should start (top left).
         * Parameter: y - The y coord of where the button should start (top left).
         * Parameter: w - The width the button should be in pixels.
         * Parameter: h - The height the button should be in pixels.
         * Parameter: name - The label the button should receive.
         */
        void drawButton(int x, int y, int w, int h, string name);
        /** 
         * Description: Displays the CA on the Graphics Window.
         */
        void displayCA();
        /** 
         * Description: Check the Graphics Client for messages and executes them if they exist.
         */
        void checkForAndExecuteMessages();
        /** 
         * Description: Gets this object's shouldStep field.
         * Returns: int - Whether or not the simulated CA should step to the next state.
         */
        int getShouldStep();
        /** 
         * Description: Gets this object's shouldExit field.
         * Returns: int - Whether or not the simulation should stop and exit.
         */
        int getShouldExit();
        /** 
         * Description: Clears the game area (600x600 CA area).
         */
        void clearGame();
        /** 
         * Description: Steps the CA forward (calculate the next state) and display it graphically.
         */
        void stepAndDisplayCA();
        /** 
         * Description: Handles when the user clicks on the Graphics Client.
         * Parameter: x - The x coord of where the user clicked.
         * Parameter: y - The y coord of where the user clicked.
         */
        void clickEvent(int x, int y);
        /** 
         * Description: Checks to see if the user clicked on a CA cell, and if so flips the cell state.
         * Parameter: x - The x coord of where the user clicked.
         * Parameter: y - The y coord of where the user clicked.
         */
        void checkForCAClick(int x, int y);
        /** 
         * Description: Draws the GUI and it's buttons on the Graphics Window.
         * Parameter: x - The x coord of where the user clicked.
         * Parameter: y - The y coord of where the user clicked.
         */
        void drawGUI();
        /** 
         * Description: Saves the displayed CA as the text representation.
         */
        void saveCAToFile();
        /** 
         * Description: Logs text graphically in the corner of the Graphics Window.
         */
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