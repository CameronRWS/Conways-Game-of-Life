
#include <string>

using namespace std;

#ifndef CA_HEADER
#define CA_HEADER
#include "GraphicsClient.h" //Graphics client header.
/** 
 * Description: Stores a CA in a convenient class with various methods to modify the CA.
 */
class GraphicsClient;
class CellularAutomaton {
    public:
        /**
         * Description: A constructor for a CA that doesn't use a file to create the initial state.
         * Parameter: fileName - A file path to a definition of a CA.
         * Parameter: quiescentState - The quiescent state (default state) of the new CA to create.
         */
        CellularAutomaton(string fileName, int quiescentState);
        /**
         * Description: A constructor for a CA that doesn't use a file to create the initial state.
         * Parameter: width - The width of the new CA to create.
         * Parameter: height - The height of the new CA to create.
         * Parameter: quiescentState - The quiescent state (default state) of the new CA to create.
         * Parameter: shouldWrapFlag - Whether or not the CA should wrap (1 => yes, 0 => no)
         */
        CellularAutomaton(int width, int height, unsigned char quiescentState, unsigned char shouldWrapFlag);
        /**
         * Description: A copy constructor for a CA.
         * Parameter: originalCA - The CA to create this new CA from.
         */
        CellularAutomaton(const CellularAutomaton& originalGA);
        /**
         * Description: A destructor for a CA.
         */
        ~CellularAutomaton();
        /**
         * Description: A copy assignment overload function for the CA.
         * Parameter: toCopyCA - The CA to create set the value of this to.
         */
        CellularAutomaton& operator=(const CellularAutomaton& toCopyGA);
        /**
         * Description: Initiates the CA by setting all cells to the quiescent state.
         */
        void initCA();
        /**
         * Description: Displays the state of the CA to the console (like in project 1 part c). This
         *  method is used for debugging.
         */
        void displayCA(GraphicsClient* gc);
        /**
         * Description: Sets the value of a cell in the CA.
         * Parameter: index_x - The x coord of the cell that needs modified.
         * Parameter: index_y - The y coord of the cell that needs modified.
         * Parameter: charToSet - The char to set the value of the cell to.
         * Returns: integer - 0 if error, 1 if no error.
         */
        int set2DCACell(unsigned int index_x, unsigned int index_y, unsigned char charToSet);
        /**
         * Description: Calculates the next state of the CA given a step function.
         * Parameter: ruleFunc - A pointer to a function that calculates the next state of a specific cell in the CA.
         */
        void step2DCA(unsigned char (*ruleFunc)(CellularAutomaton *tempCA, int index_x, int index_y));
        /**
         * Description: A getter for the CA's quiescent state.
         * Returns: integer - The quiescent state of the CA.
         */
        int getQuiescentState();
        /**
         * Description: A getter for the CA's width.
         * Returns: integer - The width of the CA.
         */
        int getWidth();
        /**
         * Description: A getter for the CA's height.
         * Returns: integer - The height of the CA.
         */
        int getHeight();
        /**
         * Description: A getter for the CA's cell data.
         * Returns: unsigned char* (array) - The CA's cell data (values).
         */
        unsigned char* getCAdata();
        /**
         * Description: A getter for the CA's wrap flag.
         * Returns: unsigned char - The wrap flag of the CA.
         */
        unsigned char getWrap();

        string getFileName();

        void stepAndDisplayCA(GraphicsClient* gc);
        void randomize();
        void checkForCAClick(int x, int y, GraphicsClient* gc);
        void setSizeAndGap();
        void deepCopy(const CellularAutomaton& toCopyCA);
        void loadCAfromFile(string fileName, int quiescentState);
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
        int size; //size of the ca cell pixel to display.
        int gap; //how big the gap in ca cells.
        string fileName;
};

#endif
