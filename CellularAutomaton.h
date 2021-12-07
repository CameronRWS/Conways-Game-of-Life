#include <string> //For using strings.
#include "GraphicsClient.h" //Graphics client header.

using namespace std; //Allows for 'std::' to be removed from certain lines.

#ifndef CA_HEADER
#define CA_HEADER

/** 
 * Description: Stores a CA in a convenient class with various methods to modify the CA.
 */
class CellularAutomaton {
    public:
        CellularAutomaton(string fileName, int quiescentState);
        CellularAutomaton(int width, int height, unsigned char quiescentState, unsigned char shouldWrapFlag);
        CellularAutomaton(const CellularAutomaton& originalGA);
        ~CellularAutomaton();
        CellularAutomaton& operator=(const CellularAutomaton& toCopyGA);
        void setSizeAndGap();
        void deepCopy(const CellularAutomaton& toCopyCA);
        void loadCAfromFile(string fileName, int quiescentState, int shouldSaveFileName);
        void initCA();
        void randomize();
        void displayCA(GraphicsClient* gc);
        int set2DCACell(unsigned int index_x, unsigned int index_y, unsigned char charToSet);
        void step2DCA(unsigned char (*ruleFunc)(CellularAutomaton *tempCA, int index_x, int index_y));
        int getQuiescentState();
        int getWidth();
        int getHeight();
        int getSize();
        int getGap();
        unsigned char* getCAdata();
        unsigned char getWrap();
        string getFileName();
    private:
        //Member/Field: int quiescentState - The quiescent (default) state of the CA.
        int quiescentState;
        //Member/Field: int width - The width of the CA.
        int width;
        //Member/Field: int height - The height of the CA.
        int height;
        //Member/Field: unsigned char *cadata - A pointer to the start of an array containing the cells of the CA.
        unsigned char *cadata;
        //Member/Field: unsigned char wrap - Stores if the CA should wrap or not.
        unsigned char wrap;
        //Member/Field: int size - The size of a displayed CA cell in pixels.
        int size;
        //Member/Field: int gap - The gap in between displayed CA cells in pixels.
        int gap; 
        //Member/Field: string fileName - The file name of the last loaded CA.
        string fileName;
};

#endif
