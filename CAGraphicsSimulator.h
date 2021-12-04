#include <string> //For using strings.
#include "CellularAutomaton.h" 
#include "GraphicsClient.h" 

using namespace std;

#ifndef CAGS_HEADER
#define CAGS_HEADER

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
    private:
        GraphicsClient* gc;
        CellularAutomaton* ca;
        int shouldStep;
        int shouldExit;
};

#endif