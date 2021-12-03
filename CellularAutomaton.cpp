#include <stdio.h> //Allows for use of printf.
#include <cstdlib> //For certain utility functions.
#include <string> //For using strings.
#include "CellularAutomaton.h" //Allows for 2DCA usage.
#include <math.h> //For use of floor.

using namespace std;

/**
 * Description: Randomizes the states of the cells in the CA.
 */
void CellularAutomaton::randomize() {
    int maxIndex = this->width * this->height;
    for(int i = 0; i < maxIndex; i++) {
        int random0or1 = rand() % 2;
        this->cadata[i] = random0or1;
    }
}

/**
 * Description: Initiates the CA by setting all cells to the quiescent state.
 */
void CellularAutomaton::initCA() {
    int maxIndex = this->width * this->height; //Stores the max index of the CA.
    for(int i = 0; i < maxIndex; i++) { //Go through each index of the cells.
        this->cadata[i] = this->quiescentState; //Set each cell to the quiescent state passed in.
    }
}

/**
 * Description: Sets the CA's size and gap based off of the value of m (see project specifications).
 */
void CellularAutomaton::setSizeAndGap() {
    int m = this->width > this->height ? this->width : this->height; //m per assignment specs.
    //The following thresholds were given in assignment specs.
    if(m > 1 && m <= 50) {
        this->size = 10;
        this->gap = 2;
    } else if (m > 50 && m <= 100) {
        this->size = 4;
        this->gap = 1;
    } else if (m > 100 && m <= 200) {
        this->size = 2;
        this->gap = 1;
    } else if (m > 200 && m <= 600) {
        this->size = 1;
        this->gap = 0;
    } else {
        printf("Error: Unsupported value for m.");
    }
}

/**
 * Description: Displays the state of the CA to the passed in GraphicsClient.
 * Parameter: gc - A pointer to a GraphicsClient object that the CA needs displayed to.
 */
void CellularAutomaton::displayCA(GraphicsClient* gc) {
    int maxIndex = this->width * this->height; 
    for(int i = 0; i < maxIndex; i++) { //For all cells within the CA.
        int x = i % width; //get the x coord.
        int y = floor(i/width); //get the y coord.
        if(this->cadata[i] == 1) {
            gc->fillRectangle(x*(this->size+this->gap), y*(this->size+this->gap), this->size, this->size);
        }
    }
}

/**
 * Description: Sets the value of a cell in the CA.
 * Parameter: index_x - The x coord of the cell that needs modified.
 * Parameter: index_y - The y coord of the cell that needs modified.
 * Parameter: charToSet - The char to set the value of the cell to.
 * Returns: integer - 0 if error, 1 if no error.
 */
int CellularAutomaton::set2DCACell(unsigned int index_x, unsigned int index_y, unsigned char charToSet) {
    int index = index_x+index_y*this->width; //converts the x and y index to it's index in the array.
    if(!(0 <= index && index <= (this->width*this->height)-1)) { //If the index is not within the bounds of the cells.
        printf("Error with set2DCACell usage - index out of bounds. The 2DCA was not modified.\n");
        return 0; //Return 0 because of error.
    } else {      //If the index is within the bounds of the 2DCA, we can set it.
        this->cadata[index] = charToSet; //Set the value at the index to the char passed in.
        return 1; //Return 1 because no error.
    }
}

/**
 * Description: Calculates the next state of the CA given a step function.
 * Parameter: ruleFunc - A pointer to a function that calculates the next state of a specific cell in the CA.
 */
void CellularAutomaton::step2DCA(unsigned char (*ruleFunc)(CellularAutomaton *tempCA, int index_x, int index_y)) {
    //The following code creates a temporary CA copy from the actual CA.
    CellularAutomaton *tempCA = new CellularAutomaton(*this);
    if(tempCA == NULL) { //Check to make sure the CA was created.
        printf("Error with create2DCA: Unable to allocate required memory for the temp 2DCA.\n");
        return;
    }
    //The following code goes through each cell of the actual 2DCA and calculates it's new value.
    for(int x = 0; x < this->width; x++) {
        for(int y = 0; y < this->height; y++) {
            int index = x+(y*width); //Converts the coords to an index.
            this->cadata[index] = ruleFunc(tempCA, x, y); //Calculates the new value via the rule.
        }
    }
    delete tempCA;
}

/**
 * Description: A constructor for a CA that doesn't use a file to create the initial state.
 * Parameter: width - The width of the new CA to create.
 * Parameter: height - The height of the new CA to create.
 * Parameter: quiescentState - The quiescent state (default state) of the new CA to create.
 * Parameter: shouldWrapFlag - Whether or not the CA should wrap (1 => yes, 0 => no)
 */
CellularAutomaton::CellularAutomaton(int width, int height, unsigned char quiescentState, unsigned char shouldWrapFlag) {
    this->quiescentState = quiescentState; //Set ca's quiescent state to the passed in quiescent state.
    this->width = width; //Set ca's width to the given width.
    this->height = height; //Set ca's height to the given height.
    this->setSizeAndGap(); //Calculate and set the size and gap for displaying the CA with GC.
    this->wrap = shouldWrapFlag; //Set ca's should wrap flag for access later.
    this->cadata = NULL;
    this->cadata = new unsigned char[width * height]; //Allocate memory on the heap for the cells array.
    if(this->cadata == NULL) {
        printf("Error with allocating memory for CA array.\n");
    } //Check to make sure the memory was allocated on the heap.
    initCA(); //Set all the values of the CA to the quiescentState.
}

/**
 * Description: A constructor for a CA that allows for a user to create the CA based off of a file and a quiescent state.
 * Parameter: fileName - A file path to a definition of a CA.
 * Parameter: quiescentState - The quiescent state (default state) of the new CA to create.
 */
CellularAutomaton::CellularAutomaton(string fileName, int quiescentState) {
    this->loadCAfromFile(fileName, quiescentState, 1); //Loads the CA in the file and saves it as this CA.
}

/**
 * Description: Loads a CA defined in a file into this CA.
 * Parameter: fileName - A file path to a definition of a CA.
 * Parameter: quiescentState - The quiescent state (default state) of the new CA to create.
 * Parameter: shouldSaveFileName - Whether or not the file being passed in should be saved to the CA's file name.
 */
void CellularAutomaton::loadCAfromFile(string fileName, int quiescentState, int shouldSaveFileName) {
    if(this->cadata != NULL) {
        delete this->cadata;
    }
    FILE *file; //Stores the file to be read.
    file = fopen(fileName.c_str(), "r"); //Reads the file passed in.
    if(!file) { //If the file is NULL then it wasn't read in properly.
        printf("Error: There was a problem opening the file '%s'.\n", fileName.c_str());
    }
    int rows, cols; //Will store the number of rows and number of columns.
    fscanf(file, "%d", &rows); //Scans the first int in the file and stores as the number of rows.
    fscanf(file, "%d", &cols); //Scans the second int in the file and stores as the number of cols.
    this->height = rows;
    this->width = cols;
    this->setSizeAndGap(); //Calculate and set the size and gap for displaying the CA with GC.
    this->quiescentState = quiescentState;
    this->wrap = 1;
    if(shouldSaveFileName) {
        this->fileName = fileName;
    }
    this->cadata = NULL;
    this->cadata = new unsigned char[width * height]; //Allocate memory on the heap for the cells array.
    if(this->cadata == NULL) {
        printf("Error with allocating memory for CA array.\n");
    } //Check to make sure the memory was allocated on the heap.
    for(int x = 0; x < rows; x++) {
        for(int y = 0; y < cols; y++) {
            int s = -1; //Will store the most recently read integer.
            fscanf(file, "%d", &s); //Read the next integer from the file and save to s.
            if(s == -1) { //If s isn't set to a different value than -1 then a value wasn't read.
                printf("Error: The file does not contain enough integers for a %dx%d 2DCA.\n", rows, cols);
            }
            if(s != 0 && s != 1) {
                printf("Error: The file contains a '%d' which is an unsupported character for Conway's Game of Life.", s);
            }
            set2DCACell(y, x, s); //Set the associated cell to the read in int. y and x are flipped due to having to ensure the file matches what will eventually be printed.
        }
    }
    int l = -1; //Will store the next int in the file.
    fscanf(file, "%d", &l); //Scans another int from the file.
    if(l != -1) { //At this point, if an int was read in, then there were too many ints because all ints should have been read in by now.
        printf("Error: The file contained too many integers for a %dx%d 2DCA.\n", rows, cols);
    }
    fclose(file); //Close the file.
}

/**
 * Description: A copy constructor for a CA.
 * Parameter: originalCA - The CA to create this new CA from.
 */
CellularAutomaton::CellularAutomaton(const CellularAutomaton& originalCA) {
    this->deepCopy(originalCA);
}

/**
 * Description: A deep copy method that copies the passed in CA into this CA.
 * Parameter: toCopyCA - The CA to deep copy into this CA.
 */
void CellularAutomaton::deepCopy(const CellularAutomaton& toCopyCA) {
    this->cadata = NULL;
    this->cadata = new unsigned char[toCopyCA.width * toCopyCA.height];
    if(this->cadata == NULL) {
        printf("Error with allocating memory for CA array.\n");
    } //Check to make sure the memory was allocated on the heap.
    this->height = toCopyCA.height;
    this->width = toCopyCA.width;
    this->size = toCopyCA.size;
    this->gap = toCopyCA.gap;
    this->wrap = toCopyCA.wrap;
    this->quiescentState = toCopyCA.quiescentState;
    //The following for loop copies the actual 2DCA's cells into the temporary 2DCA.
    for(int x = 0; x < this->width; x++) {
        for(int y = 0; y < this->height; y++) {
            int index = x+(y*this->width); //Converts the coords to an index.
            this->cadata[index] = toCopyCA.cadata[index]; //Copies actual value into temp.
        }
    }
}

/**
 * Description: A destructor for a CA.
 */
CellularAutomaton::~CellularAutomaton() {
    delete this->cadata; //Free the cells array that were put on the heap.
}

/**
 * Description: A copy assignment overload function for the CA.
 * Parameter: toCopyCA - The CA to create set the value of this to.
 */
CellularAutomaton& CellularAutomaton::operator=(const CellularAutomaton& toCopyCA) {
    if (this != &toCopyCA) {
        delete this->cadata;
        this->deepCopy(toCopyCA);
    }
    return *this;
}

/**
 * Description: A getter for the CA's quiescent state.
 * Returns: integer - The quiescent state of the CA.
 */
int CellularAutomaton::getQuiescentState() {
    return this->quiescentState;
}

/**
 * Description: A getter for the CA's width.
 * Returns: integer - The width of the CA.
 */
int CellularAutomaton::getWidth() {
    return this->width;
}

/**
 * Description: A getter for the CA's height.
 * Returns: integer - The height of the CA.
 */
int CellularAutomaton::getHeight() {
    return this->height;
}

/**
 * Description: A getter for the CA's cell size.
 * Returns: integer - The size of the CA.
 */
int CellularAutomaton::getSize() {
    return this->size;
}

/**
 * Description: A getter for the CA's cell gap.
 * Returns: integer - The gap of the CA.
 */
int CellularAutomaton::getGap() {
    return this->gap;
}

/**
 * Description: A getter for the CA's cell data.
 * Returns: unsigned char* (array) - The CA's cell data (values).
 */
unsigned char* CellularAutomaton::getCAdata() {
    return this->cadata;
}

/**
 * Description: A getter for the CA's wrap flag.
 * Returns: unsigned char - The wrap flag of the CA.
 */
unsigned char CellularAutomaton::getWrap() {
    return this->wrap;
}

/**
 * Description: A getter for the CA's file name.
 * Returns: string - The file name of the last loaded CA.
 */
string CellularAutomaton::getFileName() {
    return this->fileName;
}
