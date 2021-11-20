
#include <stdio.h> //From socket code for input/output in C.
#include <stdlib.h> //From socket code.
#include <sys/socket.h> //From socket code
#include <arpa/inet.h> //From socket code
#include <unistd.h> //From socket code
#include <string> //For using strings.
#include <iostream> //input/output in C++ (not the same as stdio.h).
#include <sys/ioctl.h>
#include <math.h> //For use of floor.
#include "GraphicsClient.h" //Graphics client header.



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
const int repaint_btn_y = 10+(btn_gap*11);



using namespace std;


int GraphicsClient::getShouldReset() {
    return this->shouldReset;
}

void GraphicsClient::setShouldReset(int shouldReset) {
    this->shouldReset = shouldReset;
}

int GraphicsClient::getShouldRefresh() {
    return this->shouldRefresh;
}

void GraphicsClient::setShouldRefresh(int shouldRefresh) {
    this->shouldRefresh = shouldRefresh;
}

int GraphicsClient::getShouldExit() {
    return this->shouldExit;
}

void GraphicsClient::setShouldExit(int shouldExit) {
    this->shouldExit= shouldExit;
}

void GraphicsClient::clearGame() {
    this->setDrawingColor(0,0,0); //set to black
    this->fillRectangle(0, 0, 600, 800); //wipe playable screen. (black)
    this->setDrawingColor(0,200,20); //go back to green.
}

string GraphicsClient::clickEvent(int x, int y, CellularAutomaton* ca) {
    printf("click at: (%d, %d)", x, y);
    if(x > all_btn_x && x < all_btn_x + btn_w) {
        if(y > step_btn_y && y < step_btn_y + btn_h) {
            ca->stepAndDisplayCA(this);
            this->setShouldRefresh(0); //stop auto simulate.
        } else if(y > run_btn_y && y < run_btn_y + btn_h) {
            this->shouldRefresh = 1;
        } else if(y > pause_btn_y && y < pause_btn_y + btn_h) {
            this->shouldRefresh = 0;
        } else if(y > reset_btn_y && y < reset_btn_y + btn_h) {
            this->shouldReset = 1;
        } else if(y > random_btn_y && y < random_btn_y + btn_h) {
            ca->randomize();
            ca->displayCA(this);
        } else if(y > clear_btn_y && y < clear_btn_y + btn_h) {
            ca->initCA();
            ca->displayCA(this);
        } else if(y > load_btn_y && y < load_btn_y + btn_h) {
            this->requestFile();
        } else if(y > quit_btn_y && y < quit_btn_y + btn_h) {
            this->shouldExit = 1;
        } else if(y > size1_btn_y && y < size1_btn_y + btn_h) {
            return "./predefinedCAs/40by40.txt";
        } else if(y > size2_btn_y && y < size2_btn_y + btn_h) {
            return "./predefinedCAs/150by150.txt";
        } else if(y > size3_btn_y && y < size3_btn_y + btn_h) {
            return "./predefinedCAs/600by600.txt";
        } else if(y > repaint_btn_y && y < repaint_btn_y + btn_h) {
            this->repaint();
        }  
    }
    return "";
}

string GraphicsClient::getMessage(CellularAutomaton* ca) {
    int count; //number of bytes that can be read.
    ioctl(this->sockfd, FIONREAD, &count); 
    if(count == 0) { return ""; }
    char message[count];
    read(this->sockfd, message, count);
    for(int i = 0; i < count; i++) {
        if(message[i] == -1) {
            int len1 = message[i+1] << 12;//<< 12 //*4096
            int len2 = message[i+2] << 8;// << 8 //* 256
            int len3 = message[i+3] << 4; //<< 4 //* 16
            int len4 = message[i+4];
            int len = len1 + len2 + len3 + len4;
            printf("len: %d\n", len);
            if(message[i+5] == 0x03) { //click
                printf("click!\n");
                int x1 = message[i+7] << 12;
                int x2 = message[i+8] << 8;
                int x3 = message[i+9] << 4;
                int x4 = message[i+10];
                int y1 = message[i+11] << 12;
                int y2 = message[i+12] << 8;
                int y3 = message[i+13] << 4;
                int y4 = message[i+14];
                int x = x1 + x2 + x3 + x4;
                int y = y1 + y2 + y3 + y4;
                return this->clickEvent(x, y, ca);
            } else if(message[i+5] == 0x0A) { //file
                printf("file!\n");
                int filePathLen = (len-1)/2; //-1 to remove the file command and /2 since each char takes up 2 nibbles.
                string filePath = "";
                for(int j = 0; j < filePathLen; j++) {
                    int chr1 = message[i+6+(j*2)] << 4;
                    int chr2 = message[i+7+(j*2)];
                    int chr = chr1 + chr2;
                    filePath = filePath + (char)chr;
                }
                printf("\n");
                printf("string: '%s'\n", filePath.c_str());
                return filePath;
            }
            i = i + len; //skip over the read characters. 
        }
    }
    return "";
}

void GraphicsClient::drawGUI() {
    printf("drawing GUI\n");
    //green rectangle.
    this->setDrawingColor(0,200,20);
    this->fillRectangle(game_w,0,gui_w,game_h);
    //smaller black rectangle.
    this->setDrawingColor(0,0,0);
    this->fillRectangle(game_w+padding,padding,gui_w-(padding*2),game_h-(padding*2)); 
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
    this->drawButton(all_btn_x, repaint_btn_y, btn_w, btn_h, "REPAINT");
}

void GraphicsClient::drawButton(int x, int y, int w, int h, string name) {
    //green rectangle.
    this->setDrawingColor(0,200,20);
    this->fillRectangle(x,y,w,h);
    //smaller black rectangle.
    this->setDrawingColor(0,0,0);
    this->fillRectangle(x+padding,y+padding,w-(padding*2),h-(padding*2)); 
    //green text.
    this->setDrawingColor(0,200,20);
    this->drawstring((x+10),(y+20), name);
}

void GraphicsClient::requestFile() {
    char message[100]; //message on the stack
    message[0] = 0xFF;
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x00;
    message[4] = 0x01; //length 1
    message[5] = 0x0E; //request file
    send(sockfd, message, 6, 0);
}

/**
 * Description: A parameterized constructor for a GraphicsClient object.
 * Parameter: URL - The url address the GraphicsClient should connect to.
 * Parameter: port - The port the GraphicsClient should connect to.
 */
GraphicsClient::GraphicsClient(string URL, int port) {
    this->shouldExit = 0;
    this->shouldReset = 0;
    this->shouldRefresh = 0;
    this->URL = URL;
    this->port = port;
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "Error creating socket \n");
    }
    memset(&this->serv_addr, '0', sizeof(this->serv_addr));
    this->serv_addr.sin_family = AF_INET;
    this->serv_addr.sin_port = htons(this->port);
    if(inet_pton(AF_INET, URL.c_str(), &this->serv_addr.sin_addr) <= 0) {
        fprintf(stderr, "Invalid address/ Address not supported \n");
    }
    if (connect(this->sockfd, (struct sockaddr *)&this->serv_addr, sizeof(this->serv_addr)) < 0) {
        fprintf(stderr, "Connection Failed \n");
    }
}

/**
 * Description: A copy constructor for a GraphicsClient object.
 * Parameter: originalGC - The GraphicsClient object to base the newly created one off of.
 */
GraphicsClient::GraphicsClient(const GraphicsClient& originalGC) {
    this->shouldExit = originalGC.shouldExit;
    this->shouldReset = originalGC.shouldReset;
    this->shouldRefresh = originalGC.shouldRefresh;
    this->URL = originalGC.URL;
    this->port = originalGC.port;
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "Error creating socket \n");
    }
    memset(&this->serv_addr, '0', sizeof(this->serv_addr));
    this->serv_addr.sin_family = AF_INET;
    this->serv_addr.sin_port = htons(this->port);
    if(inet_pton(AF_INET, URL.c_str(), &this->serv_addr.sin_addr) <= 0) {
        fprintf(stderr, "Invalid address/ Address not supported \n");
    }
    if (connect(this->sockfd, (struct sockaddr *)&this->serv_addr, sizeof(this->serv_addr)) < 0) {
        fprintf(stderr, "Connection Failed \n");
    }
}

/**
 * Description: A destructor for a GraphicsClient object.
 */
GraphicsClient::~GraphicsClient() {
    close(sockfd);
}

/**
 * Description: A copy operator for a GraphicsClient object.
 * Parameter: toCopyGC - The GraphicsClient object to base the newly created one off of.
 */
GraphicsClient& GraphicsClient::operator=(const GraphicsClient& toCopyGC) {
    if (this != &toCopyGC) {
        close(this->sockfd); //close existing connection
        //Creates new connection with the parameters from RHS (toCopyGC).
        this->shouldExit = toCopyGC.shouldExit;
        this->shouldReset = toCopyGC.shouldReset;
        this->shouldRefresh = toCopyGC.shouldRefresh;
        this->URL = toCopyGC.URL;
        this->port = toCopyGC.port;
        this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            fprintf(stderr, "Error creating socket \n");
        }
        memset(&this->serv_addr, '0', sizeof(this->serv_addr));
        this->serv_addr.sin_family = AF_INET;
        this->serv_addr.sin_port = htons(this->port);
        if(inet_pton(AF_INET, URL.c_str(), &this->serv_addr.sin_addr) <= 0) {
            fprintf(stderr, "Invalid address/ Address not supported \n");
        }
        if (connect(this->sockfd, (struct sockaddr *)&this->serv_addr, sizeof(this->serv_addr)) < 0) {
            fprintf(stderr, "Connection Failed \n");
        }
    }
    return *this;
}

/**
 * Description: Sets the background color of the associated graphics display for the GraphicsClient object 
 *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
 * Parameter: r - The value of the red component of the RGB color (0-255) (higher bits of the int are ignored).
 * Parameter: g - The value of the green component of the RGB color (0-255).
 * Parameter: b - The value of the blue component of the RGB color (0-255).
 */
void GraphicsClient::setBackgroundColor(int r, int g, int b) {
    char message[100]; //message on the stack
    message[0] = 0xFF;
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x00;
    message[4] = 0x07; //length 7
    message[5] = 0x02; //set bg color
    message[6] = (char) ((r >> 4) & 0x0F); //get first 4 bits of r
    message[7] = (char) (r & 0x0F); //get next 4 bits of r
    message[8] = (char) ((g >> 4) & 0x0F);
    message[9] = (char) (g & 0x0F);
    message[10] = (char) ((b >> 4) & 0x0F);
    message[11] = (char) (b & 0x0F);
    send(sockfd, message, 12, 0);
}

/**
 * Description: Sets the drawing color of the associated graphics display for the GraphicsClient object 
 *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
 * Parameter: r - The value of the red component of the RGB color (0-255) (higher bits of the int are ignored).
 * Parameter: g - The value of the green component of the RGB color (0-255).
 * Parameter: b - The value of the blue component of the RGB color (0-255).
 */
void GraphicsClient::setDrawingColor(int r, int g, int b) {
    char message[100]; //message on the stack
    message[0] = 0xFF;
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x00;
    message[4] = 0x07; //length 7
    message[5] = 0x06; //set drawing color
    message[6] = (char) ((r >> 4) & 0x0F); //get first 4 bits
    message[7] = (char) (r & 0x0F); //
    message[8] = (char) ((g >> 4) & 0x0F);
    message[9] = (char) (g & 0x0F);
    message[10] = (char) ((b >> 4) & 0x0F);
    message[11] = (char) (b & 0x0F);
    send(sockfd, message, 12, 0);
}

/**
 * Description: Clears the associated graphics display for the GraphicsClient object 
 *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
 */
void GraphicsClient::clear() {
    char message[100];
    message[0] = 0xFF;
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x00;
    message[4] = 0x01; //length 1
    message[5] = 0x01; //clear, i.e. set all pixels to bg color.
    send(sockfd, message, 6, 0);
}

/**
 * Description: Sets the color of a pixel of the associated graphics display for the GraphicsClient object 
 *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
 * Parameter: x - The x coord of the pixel to set the color of.
 * Parameter: y - The y coord of the pixel to set the color of.
 * Parameter: r - The value of the red component of the RGB color (0-255) to set the pixel to
 *  (higher bits of the int are ignored).
 * Parameter: g - The value of the green component of the RGB color (0-255) to set the pixel to.
 * Parameter: b - The value of the blue component of the RGB color (0-255) to set the pixel to.
 */
void GraphicsClient::setPixel(int x, int y, int r, int g, int b) {
    char message[100]; //message on the stack
    message[0] = 0xFF;
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x00; //00010000
    message[4] = 0x0F; //length 16
    message[5] = 0x03; //set pixel command
    message[6] = (char) ((x >> 12) & 0x0F); //get first 4 bits
    message[7] = (char) ((x >> 8) & 0x0F); //get next 4 bits
    message[8] = (char) ((x >> 4) & 0x0F); //get next next 4 bits
    message[9] = (char) (x & 0x0F); //get last 4 bits
    message[10] = (char) ((y >> 12) & 0x0F); //get first 4 bits
    message[11] = (char) ((y >> 8) & 0x0F); //get next 4 bits
    message[12] = (char) ((y >> 4) & 0x0F); //get next next 4 bits
    message[13] = (char) (y & 0x0F); //
    message[14] = (char) ((r >> 4) & 0x0F); //get first 4 bits
    message[15] = (char) (r & 0x0F); //
    message[16] = (char) ((g >> 4) & 0x0F);
    message[17] = (char) (g & 0x0F);
    message[18] = (char) ((b >> 4) & 0x0F);
    message[19] = (char) (b & 0x0F);
    send(sockfd, message, 20, 0);
}

/**
 * Description: Draws an outline of a rectangle on the associated graphics display for the GraphicsClient object 
 *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
 * Parameter: x - The x coord of where the rectangle should start.
 * Parameter: y - The y coord of where the rectangle should start.
 * Parameter: w - The width (in pixels) of the rectangle to draw.
 * Parameter: h - The height (in pixels) of the rectangle to draw.
 */
void GraphicsClient::drawRectangle(int x, int y, int w, int h) {
    drawShapeHelper(0x07, x, y, w, h);
}

/**
 * Description: Draws a filled rectangle on the associated graphics display for the GraphicsClient object 
 *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
 * Parameter: x - The x coord of where the rectangle should start.
 * Parameter: y - The y coord of where the rectangle should start.
 * Parameter: w - The width (in pixels) of the rectangle to draw.
 * Parameter: h - The height (in pixels) of the rectangle to draw.
 */
void GraphicsClient::fillRectangle(int x, int y, int w, int h) {
    drawShapeHelper(0x08, x, y, w, h);
}

/**
 * Description: Draws a filled rectangle with the color of the background on the associated 
 *  graphics display for the GraphicsClient object by communicating to the GraphicsServer 
 *  based off of the project specifications and communication document provided.
 * Parameter: x - The x coord of where the rectangle should start.
 * Parameter: y - The y coord of where the rectangle should start.
 * Parameter: w - The width (in pixels) of the rectangle to draw.
 * Parameter: h - The height (in pixels) of the rectangle to draw.
 */
void GraphicsClient::clearRectangle(int x, int y, int w, int h) {
    drawShapeHelper(0x09, x, y, w, h);
}

/**
 * Description: Draws an outline of an oval on the associated graphics display for the GraphicsClient object 
 *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
 * Parameter: x - The x coord of where the oval should start.
 * Parameter: y - The y coord of where the oval should start.
 * Parameter: w - The width (in pixels) of the oval to draw.
 * Parameter: h - The height (in pixels) of the oval to draw.
 */
void GraphicsClient::drawOval(int x, int y, int w, int h) {
    drawShapeHelper(0x0A, x, y, w, h);
}

/**
 * Description: Draws an filled in an oval on the associated graphics display for the GraphicsClient object 
 *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
 * Parameter: x - The x coord of where the oval should start.
 * Parameter: y - The y coord of where the oval should start.
 * Parameter: w - The width (in pixels) of the oval to draw.
 * Parameter: h - The height (in pixels) of the oval to draw.
 */
void GraphicsClient::fillOval(int x, int y, int w, int h) {
    drawShapeHelper(0x0B, x, y, w, h);
}

/**
 * Description: Draws a line on the associated graphics display for the GraphicsClient object 
 *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
 * Parameter: x1 - The x coord of where the line should start.
 * Parameter: y1 - The y coord of where the line should start.
 * Parameter: x2 - The x coord of where the line should end.
 * Parameter: y2 - The y coord of where the line should end.
 */
void GraphicsClient::drawLine(int x1, int y1, int x2, int y2) {
    drawShapeHelper(0x0D, x1, y1, x2, y2);
}

/**
 * Description: Draws a shape on the associated graphics display for the GraphicsClient object 
 *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
 * Parameter: c - The code command (0-15) for drawing the desired shape found in the GraphicsServer communication document.
 * Parameter: x - The x coord of where the shape should start.
 * Parameter: y - The y coord of where the shape should start.
 * Parameter: w - The width (in pixels) of the shape to draw.
 * Parameter: h - The height (in pixels) of the shape to draw.
 */
void GraphicsClient::drawShapeHelper(int c, int x, int y, int w, int h) {
    char message[100]; //message on the stack
    message[0] = 0xFF;
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x01; //00010001
    message[4] = 0x01; //length 17
    message[5] = c; //command
    message[6] = (char) ((x >> 12) & 0x0F); //get first 4 bits
    message[7] = (char) ((x >> 8) & 0x0F); //get next 4 bits
    message[8] = (char) ((x >> 4) & 0x0F); //get next next 4 bits
    message[9] = (char) (x & 0x0F); //get last 4 bits
    message[10] = (char) ((y >> 12) & 0x0F); //get first 4 bits
    message[11] = (char) ((y >> 8) & 0x0F); //get next 4 bits
    message[12] = (char) ((y >> 4) & 0x0F); //get next next 4 bits
    message[13] = (char) (y & 0x0F); //get last 4 bits
    message[14] = (char) ((w >> 12) & 0x0F); //get first 4 bits
    message[15] = (char) ((w >> 8) & 0x0F); //get next 4 bits
    message[16] = (char) ((w >> 4) & 0x0F); //get next next 4 bits
    message[17] = (char) (w & 0x0F); //get last 4 bits
    message[18] = (char) ((h >> 12) & 0x0F); //get first 4 bits
    message[19] = (char) ((h >> 8) & 0x0F); //get next 4 bits
    message[20] = (char) ((h >> 4) & 0x0F); //get next next 4 bits
    message[21] = (char) (h & 0x0F); //get last 4 bits
    send(sockfd, message, 22, 0); 
}

/**
 * Description: Draws a string on the associated graphics display for the GraphicsClient object 
 *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
 * Parameter: x - The x coord of where the string should start.
 * Parameter: y - The y coord of where the string should start.
 * Parameter: stringToDraw - The string to draw on the graphics display.
 */
void GraphicsClient::drawstring(int x, int y, string stringToDraw) {
    int len = stringToDraw.length(); //get the length of the string to draw for message length calculation.
    if(len > 16535) { //16535 is max number of characters per message format protocol.
        printf("Error: Message has exceeded payload limit of 16,535 characters.");
        return;
    }
    char message[100+len*2]; //message on the stack, more than enough space created.
    int mesLen = 0x09 + (2*len);
    message[0] = 0xFF;
    message[1] = (char) ((mesLen >> 12) & 0x0F);
    message[2] = (char) ((mesLen >> 8) & 0x0F);
    message[3] = (char) ((mesLen >> 4) & 0x0F);
    message[4] = (char) (mesLen & 0x0F);
    message[5] = 0x05; //command to draw string
    message[6] = (char) ((x >> 12) & 0x0F); //get first 4 bits
    message[7] = (char) ((x >> 8) & 0x0F); //get next 4 bits
    message[8] = (char) ((x >> 4) & 0x0F); //get next next 4 bits
    message[9] = (char) (x & 0x0F); //get last 4 bits
    message[10] = (char) ((y >> 12) & 0x0F); //get first 4 bits
    message[11] = (char) ((y >> 8) & 0x0F); //get next 4 bits
    message[12] = (char) ((y >> 4) & 0x0F); //get next next 4 bits
    message[13] = (char) (y & 0x0F); //get last 4 bits
    for(int i = 0; i < len; i++) { //for each character to draw
        message[14+(i*2)] = (char) ((stringToDraw[i] >> 4) & 0x0F); //get first 4 bits
        message[15+(i*2)] = (char) (stringToDraw[i] & 0x0F); //get last 4 bits
    }
    send(sockfd, message, 0x09 + (2*len) + 5, 0); //9 for index 5-13, 5 for index 0-4, and 2*len for each char being split up into two nibbles.
}

/**
 * Description: Repaints (updates) the associated graphics display for the GraphicsClient object 
 *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
 */
void GraphicsClient::repaint() {
    char message[100]; //message on the stack
    message[0] = 0xFF;
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x00;
    message[4] = 0x01; //length 1
    message[5] = 0x0C; //repaint/update server code.
    send(sockfd, message, 6, 0);
}

