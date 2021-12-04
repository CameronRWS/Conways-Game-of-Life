
#include "CAGraphicsSimulator.h" 
#include "GraphicsClient.h" 
#include "CellularAutomaton.h" 
#include <iostream> //For creating file.
#include <fstream> //For creating file.
#include <math.h> //For use of floor.
#include <time.h> //For use of nanosleep.
#include <sstream> //For converting date to string.
#include <iomanip> //For use of put_time. 

using namespace std;

const int padding = 4; //padding for GUI.
const int screen_w = 800;
const int gui_w = 200;
const int game_w = 600;
const int game_h = 600;
const int btn_w = 80;
const int btn_h = 40;
const int all_btn_x = game_w+60;
const int btn_gap = 45;
const int step_btn_y   = 10+(btn_gap*0);
const int run_btn_y    = 10+(btn_gap*1);
const int pause_btn_y  = 10+(btn_gap*2);
const int reset_btn_y  = 10+(btn_gap*3);
const int random_btn_y = 10+(btn_gap*4);
const int clear_btn_y  = 10+(btn_gap*5);
const int load_btn_y   = 10+(btn_gap*6);
const int save_btn_y   = 10+(btn_gap*7);
const int quit_btn_y   = 10+(btn_gap*8);
const int size1_btn_y  = 10+(btn_gap*9);
const int size2_btn_y  = 10+(btn_gap*10);
const int size3_btn_y  = 10+(btn_gap*11);
const int drawing_color_r = 255;
const int drawing_color_g = 200;
const int drawing_color_b = 20;
const int bg_color_r = 40;
const int bg_color_g = 40;
const int bg_color_b = 40;

/** 
 * Description: Calculates the next state of the indexed cell given the current state of the indexed cell
 *      and it's surrounding 8 cells (it's neighborhood). Rule is based off of Conway's Game of Life.
 * Parameter: CellularAutomaton *tempCA - A pointer to the temporary CA object that holds the 
 *      original CA.
 * Parameter: int x - The x position of the cell that needs it's next state calculated.
 * Parameter: int y - The y position of the cell that needs it's next state calculated.
 */
unsigned char ruleGameOfLife(CellularAutomaton *tempCA, int x, int y); 

void CAGraphicsSimulator::saveCAToFile() {
    //The following lines gets the current time for the file name.
    time_t theTime = time(nullptr);
    tm theLocalTime = *localtime(&theTime);
    std::ostringstream oss;
    oss << put_time(&theLocalTime, "%m-%d-%y_%I-%M-%S");
    //The following lines create a file with the following name.
    ofstream theFile("./savedCAs/savedCA_" + oss.str() + ".txt");
    //The following lines prints the CA to the file.
    int maxIndex = this->ca->getWidth() * this->ca->getHeight(); 
    theFile << this->ca->getWidth() << " " << this->ca->getHeight() << "\n"; //Put the dimensions at the top.
    for(int i = 0; i < maxIndex; i++) { //For all cells within the CA.
        if(i % (this->ca->getWidth()) == 0 && i != 0) { //If i is at the end of a row, create a new line.
            theFile << "\n" << (int)this->ca->getCAdata()[i] << " "; //Print the return char then the char with a space after it.
        } else {
            theFile << (int)this->ca->getCAdata()[i] << " "; //Print the char with a space after it.
        }
    }
    theFile.close(); //Close file.
}

/** 
 * Description: Constructs a CAGraphicsSimulator object.
 * Parameter: GraphicsClient *gc - A pointer to the GC object that the CA will be displayed on.
 * Parameter: CellularAutomaton *ca - A pointer to the CA object that will be simulated graphically.
 */
CAGraphicsSimulator::CAGraphicsSimulator(GraphicsClient* gc, CellularAutomaton* ca) {
    this->gc = gc;
    this->ca = ca;
    this->shouldExit = 0;
    this->shouldStep = 0;
}

/** 
 * Description: Simulates the CA on the Graphics Window with interative buttons.
 */
void CAGraphicsSimulator::simulate() {
    this->drawGUI(); //Draw the GUI on the right of the screen.
    this->displayCA(); //Display the initial state of the CA.
    while(!this->getShouldExit()) { //While the loop shouldn't exit.
        this->checkForAndExecuteMessages(); //Check for messages from Graphics Window and do what they say.
        if(this->getShouldStep()) { //If the CA should calculate the next step.
            this->stepAndDisplayCA(); //Step the CA and update the displayed CA.
        }
        nanosleep((const struct timespec[]){{0, 100000000L}}, NULL); //Halt the program for 0.1 seconds.
    }
    printf("Program has exited!\n");
}

/** 
 * Description: Displays the CA on the Graphics Window.
 */
void CAGraphicsSimulator::displayCA() {
    this->clearGame(); //Clear the outdated CA from the game screen.
    this->ca->displayCA(this->gc); //Put the CA on the Graphics Window.
    this->gc->repaint(); //Update the screen to display the newly drawn CA.
}

/** 
 * Description: Check the Graphics Client for messages and executes them if they exist.
 */
void CAGraphicsSimulator::checkForAndExecuteMessages() { 
    list<GCMessage> listOfGCM = this->gc->checkForMessages(); //Get the messages to execute.
    //Execute the messages if there are any.
    for (list<GCMessage>::iterator it = listOfGCM.begin(); it != listOfGCM.end(); ++it) { //For each message.
        string message = it->getMessage();
        if(it->getMessageType() == 1) {
            string x_str = message.substr(0, message.find(","));
            string y_str = message.substr(message.find(",")+1, message.length());
            this->clickEvent(stoi(x_str), stoi(y_str));
        } else if (it->getMessageType() == 2) {
            this->ca->loadCAfromFile(message, this->ca->getQuiescentState(), 1);
            this->displayCA();
        }
    }
}

/** 
 * Description: Gets this object's shouldStep field.
 * Returns: int - Whether or not the simulated CA should step to the next state.
 */
int CAGraphicsSimulator::getShouldStep() {
    return this->shouldStep;
}

/** 
 * Description: Gets this object's shouldExit field.
 * Returns: int - Whether or not the simulation should stop and exit.
 */
int CAGraphicsSimulator::getShouldExit() {
    return this->shouldExit;
}

/** 
 * Description: Clears the game area (600x600 CA area).
 */
void CAGraphicsSimulator::clearGame() {
    this->gc->setDrawingColor(bg_color_r,bg_color_g,bg_color_b); //Set drawing color to background temporarily.
    this->gc->fillRectangle(0, 0, game_w, game_h); //Wipe playable screen.
    this->gc->setDrawingColor(drawing_color_r,drawing_color_g,drawing_color_b); //Set the drawing color back to normal.
}

/** 
 * Description: Steps the CA forward (calculate the next state) and display it graphically.
 */
void CAGraphicsSimulator::stepAndDisplayCA() {
    this->ca->step2DCA(&ruleGameOfLife); //Step the CA using the game of life rule.
    this->displayCA(); //Display the CA graphically.
}

/** 
 * Description: Handles when the user clicks on the Graphics Client.
 * Parameter: int x - The x coord of where the user clicked.
 * Parameter: int y - The y coord of where the user clicked.
 */
void CAGraphicsSimulator::clickEvent(int x, int y) {
    if(x > all_btn_x && x < all_btn_x + btn_w) { //If the click was within the x button area.
        if(y > step_btn_y && y < step_btn_y + btn_h) { //If the step button was clicked.
            this->stepAndDisplayCA(); //Step and display the CA.
            this->shouldStep = 0; //Stop auto simulate.
        } else if(y > run_btn_y && y < run_btn_y + btn_h) {
            this->shouldStep = 1; //Enable auto simulate.
        } else if(y > pause_btn_y && y < pause_btn_y + btn_h) {
            this->shouldStep = 0; //Stop auto simulate.
        } else if(y > reset_btn_y && y < reset_btn_y + btn_h) {
            this->ca->loadCAfromFile(ca->getFileName(), ca->getQuiescentState(), 0); //Reload the CA and don't save the file name (since it didn't change).
            this->shouldStep = 0; //Stop auto simulate.
            this->displayCA(); //Display the CA graphically.
        } else if(y > random_btn_y && y < random_btn_y + btn_h) {
            this->ca->randomize(); //Set all cells in the CA to 0 or 1 randomly.
            this->shouldStep = 0; //Stop auto simulate.
            this->displayCA(); //Display the CA graphically.
        } else if(y > clear_btn_y && y < clear_btn_y + btn_h) {
            this->ca->initCA(); //Set all cells in the CA to 0 (the quiescent state for CGOL).
            this->shouldStep = 0; //Stop auto simulate.
            this->displayCA(); //Display the CA graphically.
        } else if(y > load_btn_y && y < load_btn_y + btn_h) {
            this->shouldStep = 0; //Stop auto simulate.
            this->gc->requestFile(); //Tell the GC to prompt the user for a file to load.
        } else if(y > save_btn_y && y < save_btn_y + btn_h) {
            this->saveCAToFile();
        } else if(y > quit_btn_y && y < quit_btn_y + btn_h) {
            this->shouldExit = 1; //Exit the program.
        } else if(y > size1_btn_y && y < size1_btn_y + btn_h) {
            this->ca->loadCAfromFile("./predefinedCAs/40by40.txt", ca->getQuiescentState(), 0); //Load the 40x40 CA and don't save the file name.
            this->shouldStep = 0; //Stop auto simulate.
            this->displayCA(); //Display the CA graphically.
        } else if(y > size2_btn_y && y < size2_btn_y + btn_h) {
            this->ca->loadCAfromFile("./predefinedCAs/150by150.txt", ca->getQuiescentState(), 0); //Load the 150x150 CA and don't save the file name.
            this->shouldStep = 0; //Stop auto simulate.
            this->displayCA(); //Display the CA graphically.
        } else if(y > size3_btn_y && y < size3_btn_y + btn_h) {
            this->ca->loadCAfromFile("./predefinedCAs/600by600.txt", ca->getQuiescentState(), 0); //Load the 600x600 CA and don't save the file name.
            this->shouldStep = 0; //Stop auto simulate.
            this->displayCA(); //Display the CA graphically.
        }
    } else { //If the click wasn't in the button area.
        this->checkForCAClick(x, y); //Check to see if the CA was clicked.
    }
}

/** 
 * Description: Checks to see if the user clicked on a CA cell, and if so flips the cell state.
 * Parameter: int x - The x coord of where the user clicked.
 * Parameter: int y - The y coord of where the user clicked.
 */
void CAGraphicsSimulator::checkForCAClick(int x, int y) {
    //The following lines calculates the width and height of the CA in pixels.
    int displayedCAwidth = this->ca->getWidth()*this->ca->getSize() + (this->ca->getWidth()-1)*this->ca->getGap();
    int displayedCAheight = this->ca->getHeight()*this->ca->getSize() + (this->ca->getHeight()-1)*this->ca->getGap();
    if(x < displayedCAwidth && y < displayedCAheight) { //If the CA was clicked.
        //I could have checked if they clicked a gap or not, but with the supported CA sizes this made the smaller CA sizes harder to toggle cells.
        int ca_x = floor(x/(this->ca->getSize()+this->ca->getGap())); //Get x coord in the CA.
        int ca_y = floor(y/(this->ca->getSize()+this->ca->getGap())); //Get y coord in the CA.
        int index = (ca_y*this->ca->getWidth() + ca_x); //Calculated index of the cell clicked.
        if(this->ca->getCAdata()[index] == 1) { //If the cell was on.
            this->ca->set2DCACell(ca_x, ca_y, 0); //Turn the cell off.
            this->displayCA(); //Display the CA graphically.
        } else { //If the cell was off.
            this->ca->set2DCACell(ca_x, ca_y, 1); //Turn the cell on.
            this->displayCA(); //Display the CA graphically.
        }
    }
}

/** 
 * Description: Draws the GUI and it's buttons on the Graphics Window.
 * Parameter: int x - The x coord of where the user clicked.
 * Parameter: int y - The y coord of where the user clicked.
 */
void CAGraphicsSimulator::drawGUI() {
    //Outline drawing color rectangle.
    this->gc->setDrawingColor(drawing_color_r,drawing_color_g,drawing_color_b);
    this->gc->fillRectangle(game_w,0,gui_w,game_h);
    //Smaller background color rectangle.
    this->gc->setDrawingColor(bg_color_r,bg_color_g,bg_color_b);
    this->gc->fillRectangle(game_w+padding,padding,gui_w-(padding*2),game_h-(padding*2)); 
    //Draw all buttons for the GUI.
    this->drawButton(all_btn_x, step_btn_y, btn_w, btn_h, "STEP");
    this->drawButton(all_btn_x, run_btn_y, btn_w, btn_h, "RUN");
    this->drawButton(all_btn_x, pause_btn_y, btn_w, btn_h, "PAUSE");
    this->drawButton(all_btn_x, reset_btn_y, btn_w, btn_h, "RESET");
    this->drawButton(all_btn_x, random_btn_y, btn_w, btn_h, "RANDOM");
    this->drawButton(all_btn_x, clear_btn_y, btn_w, btn_h, "CLEAR");
    this->drawButton(all_btn_x, load_btn_y, btn_w, btn_h, "LOAD");
    this->drawButton(all_btn_x, save_btn_y, btn_w, btn_h, "SAVE");
    this->drawButton(all_btn_x, quit_btn_y, btn_w, btn_h, "QUIT");
    this->drawButton(all_btn_x, size1_btn_y, btn_w, btn_h, "SIZE 1");
    this->drawButton(all_btn_x, size2_btn_y, btn_w, btn_h, "SIZE 2");
    this->drawButton(all_btn_x, size3_btn_y, btn_w, btn_h, "SIZE 3");
}

/** 
 * Description: Draws a button on the Graphics Window.
 * Parameter: int x - The x coord of where the button should start (top left).
 * Parameter: int y - The y coord of where the button should start (top left).
 * Parameter: int w - The width the button should be in pixels.
 * Parameter: int h - The height the button should be in pixels.
 * Parameter: string name - The label the button should receive.
 */
void CAGraphicsSimulator::drawButton(int x, int y, int w, int h, string name) {
    //Outline drawing color rectangle.
    this->gc->setDrawingColor(drawing_color_r,drawing_color_g,drawing_color_b);
    this->gc->fillRectangle(x,y,w,h);
    //Smaller background color rectangle.
    this->gc->setDrawingColor(bg_color_r,bg_color_g,bg_color_b);
    this->gc->fillRectangle(x+padding,y+padding,w-(padding*2),h-(padding*2)); 
    //Drawing color text for button label.
    this->gc->setDrawingColor(drawing_color_r,drawing_color_g,drawing_color_b);
    this->gc->drawstring((x+10),(y+20), name);
}

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
