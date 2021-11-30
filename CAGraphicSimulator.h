#include <string> //For using strings.
#include "CellularAutomaton.h" 
#include "GraphicsClient.h" 

using namespace std;

#ifndef CAGS_HEADER
#define CAGS_HEADER

class CAGraphicSimulator {
    public:
        CAGraphicSimulator(GraphicsClient* gc, CellularAutomaton* ca);
        void drawButton(int x, int y, int w, int h, string name);
        int getShouldRefresh();
        int getShouldExit();
        void clearGame();
        void clickEvent(int x, int y);
        void drawGUI();
        void displayCA();
        void checkForMessages();
        void stepAndDisplayCA();
        void checkForCAClick(int x, int y);
    private:
        GraphicsClient* gc;
        CellularAutomaton* ca;
        int shouldRefresh;
        int shouldExit;
};

#endif