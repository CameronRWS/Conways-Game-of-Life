
#include "CAGraphicSimulator.h" 
#include "GraphicsClient.h" 
#include "CellularAutomaton.h" 
#include <math.h> //For use of floor.

const int padding = 4; //padding for GUI.
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
const int quit_btn_y   = 10+(btn_gap*7);
const int size1_btn_y  = 10+(btn_gap*8);
const int size2_btn_y  = 10+(btn_gap*9);
const int size3_btn_y  = 10+(btn_gap*10);
const int drawing_color_r = 0; //light green
const int drawing_color_g = 200; //light green
const int drawing_color_b = 20; //light green

unsigned char ruleGameOfLife(CellularAutomaton *tempCA, int x, int y); 

CAGraphicSimulator::CAGraphicSimulator(GraphicsClient* gc, CellularAutomaton* ca) {
    this->gc = gc;
    this->ca = ca;
    this->shouldExit = 0;
    this->shouldRefresh = 0;
}

void CAGraphicSimulator::displayCA() {
    this->clearGame();
    this->ca->displayCA(this->gc);
    this->gc->repaint();
}

void CAGraphicSimulator::checkForMessages() {
    list<GCMessage*> listOfGCM = this->gc->checkForMessages();
    for (list<GCMessage*>::iterator it = listOfGCM.begin(); it != listOfGCM.end(); ++it) {
        string message = (*it)->getMessage();
        if((*it)->getMessageType() == 1) {
            string x_str = message.substr(0, message.find(","));
            string y_str = message.substr(message.find(",")+1, message.length());
            this->clickEvent(stoi(x_str), stoi(y_str));
        } else if ((*it)->getMessageType() == 2) {
            this->ca->loadCAfromFile(message, this->ca->getQuiescentState(), 1);
            this->displayCA();
        }
    }
}

int CAGraphicSimulator::getShouldRefresh() {
    return this->shouldRefresh;
}

int CAGraphicSimulator::getShouldExit() {
    return this->shouldExit;
}

void CAGraphicSimulator::clearGame() {
    this->gc->setDrawingColor(0,0,0); //set to black
    this->gc->fillRectangle(0, 0, 600, 800); //wipe playable screen. (black)
    this->gc->setDrawingColor(drawing_color_r,drawing_color_g,drawing_color_b);
}

void CAGraphicSimulator::stepAndDisplayCA() {
    this->ca->step2DCA(&ruleGameOfLife);
    this->displayCA();
}

void CAGraphicSimulator::clickEvent(int x, int y) {
    if(x > all_btn_x && x < all_btn_x + btn_w) { //if click was within button area.
        if(y > step_btn_y && y < step_btn_y + btn_h) {
            this->stepAndDisplayCA();
            this->shouldRefresh = 0; //stop auto simulate.
        } else if(y > run_btn_y && y < run_btn_y + btn_h) {
            this->shouldRefresh = 1; //enable auto simulate.
        } else if(y > pause_btn_y && y < pause_btn_y + btn_h) {
            this->shouldRefresh = 0;
        } else if(y > reset_btn_y && y < reset_btn_y + btn_h) {
            this->ca->loadCAfromFile(ca->getFileName(), ca->getQuiescentState(), 0);
            this->shouldRefresh = 0; //stop auto simulate.
            this->displayCA();
        } else if(y > random_btn_y && y < random_btn_y + btn_h) {
            this->ca->randomize();
            this->shouldRefresh = 0; //stop auto simulate.
            this->displayCA();
        } else if(y > clear_btn_y && y < clear_btn_y + btn_h) {
            this->ca->initCA();
            this->shouldRefresh = 0; //stop auto simulate.
            this->displayCA();
        } else if(y > load_btn_y && y < load_btn_y + btn_h) {
            this->shouldRefresh = 0; //stop auto simulate.
            this->gc->requestFile();
        } else if(y > quit_btn_y && y < quit_btn_y + btn_h) {
            this->shouldExit = 1;
        } else if(y > size1_btn_y && y < size1_btn_y + btn_h) {
            this->ca->loadCAfromFile("./predefinedCAs/40by40.txt", ca->getQuiescentState(), 0);
            this->shouldRefresh = 0; //stop auto simulate.
            this->displayCA();
        } else if(y > size2_btn_y && y < size2_btn_y + btn_h) {
            this->ca->loadCAfromFile("./predefinedCAs/150by150.txt", ca->getQuiescentState(), 0);
            this->shouldRefresh = 0; //stop auto simulate.
            this->displayCA();
        } else if(y > size3_btn_y && y < size3_btn_y + btn_h) {
            this->ca->loadCAfromFile("./predefinedCAs/600by600.txt", ca->getQuiescentState(), 0);
            this->shouldRefresh = 0; //stop auto simulate.
            this->displayCA();
        }
    } else { //Click wasn't in the button area.
        this->checkForCAClick(x, y);
    }
}


void CAGraphicSimulator::checkForCAClick(int x, int y) {
    int displayedCAwidth = this->ca->getWidth()*this->ca->getSize() + (this->ca->getWidth()-1)*this->ca->getGap();
    int displayedCAheight = this->ca->getHeight()*this->ca->getSize() + (this->ca->getHeight()-1)*this->ca->getGap();
    if(x < displayedCAwidth && y < displayedCAheight) { //if the CA was clicked.
        //I could have checked if they clicked a gap or not, but with the supported CA sizes this made the smaller CA sizes harder to toggle cells.
        int ca_x = floor(x/(this->ca->getSize()+this->ca->getGap())); //x coord in the ca.
        int ca_y = floor(y/(this->ca->getSize()+this->ca->getGap())); //y coord in the ca.
        int index = (ca_y*this->ca->getWidth() + ca_x); //index in the ca.
        if(this->ca->getCAdata()[index] == 1) {
            this->ca->set2DCACell(ca_x, ca_y, 0);
            this->displayCA();
        } else {
            this->ca->set2DCACell(ca_x, ca_y, 1);
            this->displayCA();
        }
    }
}

void CAGraphicSimulator::drawGUI() {
    //green rectangle.
    this->gc->setDrawingColor(drawing_color_r,drawing_color_g,drawing_color_b);
    this->gc->fillRectangle(game_w,0,gui_w,game_h);
    //smaller black rectangle.
    this->gc->setDrawingColor(0,0,0);
    this->gc->fillRectangle(game_w+padding,padding,gui_w-(padding*2),game_h-(padding*2)); 
    //draw buttons.
    this->drawButton(all_btn_x, step_btn_y, btn_w, btn_h, "STEP");
    this->drawButton(all_btn_x, run_btn_y, btn_w, btn_h, "RUN");
    this->drawButton(all_btn_x, pause_btn_y, btn_w, btn_h, "PAUSE");
    this->drawButton(all_btn_x, reset_btn_y, btn_w, btn_h, "RESET");
    this->drawButton(all_btn_x, random_btn_y, btn_w, btn_h, "RANDOM");
    this->drawButton(all_btn_x, clear_btn_y, btn_w, btn_h, "CLEAR");
    this->drawButton(all_btn_x, load_btn_y, btn_w, btn_h, "LOAD");
    this->drawButton(all_btn_x, quit_btn_y, btn_w, btn_h, "QUIT");
    this->drawButton(all_btn_x, size1_btn_y, btn_w, btn_h, "SIZE 1");
    this->drawButton(all_btn_x, size2_btn_y, btn_w, btn_h, "SIZE 2");
    this->drawButton(all_btn_x, size3_btn_y, btn_w, btn_h, "SIZE 3");
}

void CAGraphicSimulator::drawButton(int x, int y, int w, int h, string name) {
    //green rectangle.
    this->gc->setDrawingColor(drawing_color_r,drawing_color_g,drawing_color_b);
    this->gc->fillRectangle(x,y,w,h);
    //smaller black rectangle.
    this->gc->setDrawingColor(0,0,0);
    this->gc->fillRectangle(x+padding,y+padding,w-(padding*2),h-(padding*2)); 
    //green text.
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
