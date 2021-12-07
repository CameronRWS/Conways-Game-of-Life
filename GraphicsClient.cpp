
#include <stdio.h> //From socket code for input/output in C.
#include <stdlib.h> //From socket code.
#include <sys/socket.h> //From socket code.
#include <arpa/inet.h> //From socket code.
#include <unistd.h> //From socket code.
#include <string> //For using strings.
#include <iostream> //input/output in C++ (not the same as stdio.h).
#include <sys/ioctl.h> //To read from the socket.
#include <math.h> //For use of floor.
#include <list> //For getting messages.
#include "GraphicsClient.h" //Graphics client header.
#include "GCMessage.h" //Allows for GCM usage.

using namespace std; //Allows for 'std::' to be removed from certain lines.

//A constant that represents when a message is a click message.
const int message_type_click = 1;
//A constant that represents when a message is a file message.
const int message_type_file = 2;

/**
 * Description: A parameterized constructor for a GraphicsClient object.
 * Parameter: URL - The url address the GraphicsClient should connect to.
 * Parameter: port - The port the GraphicsClient should connect to.
 */
GraphicsClient::GraphicsClient(string URL, int port) {
    this->URL = URL;
    this->port = port;
    this->connectToAddress(URL, port);
}

/**
 * Description: A copy constructor for a GraphicsClient object.
 * Parameter: originalGC - The GraphicsClient object to base the newly created one off of.
 */
GraphicsClient::GraphicsClient(const GraphicsClient& originalGC) {
    this->URL = originalGC.URL;
    this->port = originalGC.port;
    this->connectToAddress(URL, port);
}

/**
 * Description: A destructor for a GraphicsClient object.
 */
GraphicsClient::~GraphicsClient() {
    close(this->sockfd);
    this->sockfd = -1;
}

/**
 * Description: A copy operator for a GraphicsClient object.
 * Parameter: toCopyGC - The GraphicsClient object to base the newly created one off of.
 */
GraphicsClient& GraphicsClient::operator=(const GraphicsClient& toCopyGC) {
    if (this != &toCopyGC) {
        close(this->sockfd);
        this->sockfd = -1;
        this->URL = toCopyGC.URL;
        this->port = toCopyGC.port;
        this->connectToAddress(URL, port);
    }
    return *this;
}

/**
 * Description: Connects this GraphicsClient to an address.
 * Parameter: URL - The url address the GraphicsClient should connect to.
 * Parameter: port - The port the GraphicsClient should connect to.
 */
void GraphicsClient::connectToAddress(string URL, int port) {
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sockfd < 0) {
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
    char message[100]; //Message on the stack.
    message[0] = 0xFF;
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x00;
    message[4] = 0x07; //Message length 7/
    message[5] = 0x06; //Set drawing color command.
    message[6] = (char) ((r >> 4) & 0x0F); //get first 4 bits
    message[7] = (char) (r & 0x0F);
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
    message[4] = 0x01; //Message length 1.
    message[5] = 0x01; //Clear, i.e. set all pixels to bg color.
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
    char message[100]; //Message on the stack.
    message[0] = 0xFF;
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x00; //00010000
    message[4] = 0x0F; //Message length 16.
    message[5] = 0x03; //Set pixel command.
    message[6] = (char) ((x >> 12) & 0x0F); //get first 4 bits
    message[7] = (char) ((x >> 8) & 0x0F); //get next 4 bits
    message[8] = (char) ((x >> 4) & 0x0F); //get next next 4 bits
    message[9] = (char) (x & 0x0F); //get last 4 bits
    message[10] = (char) ((y >> 12) & 0x0F); //get first 4 bits
    message[11] = (char) ((y >> 8) & 0x0F); //get next 4 bits
    message[12] = (char) ((y >> 4) & 0x0F); //get next next 4 bits
    message[13] = (char) (y & 0x0F); //get last 4 bits
    message[14] = (char) ((r >> 4) & 0x0F);
    message[15] = (char) (r & 0x0F); 
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
    message[5] = 0x05; //Command to draw string.
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
    char message[100]; //Message on the stack.
    message[0] = 0xFF;
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x00;
    message[4] = 0x01; //Message length 1.
    message[5] = 0x0C; //Repaint/update server code.
    send(sockfd, message, 6, 0);
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
    char message[100]; //Message on the stack.
    message[0] = 0xFF;
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x01; //00010001
    message[4] = 0x01; //Message length 17.
    message[5] = c; //Passed in command.
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
 * Description: Checks to see if there are messages from the Graphics Window. If so this returns the messages.
 * Returns: list<GCMessage> - A list of messages read from the GraphicsClient.
 */
list<GCMessage> GraphicsClient::checkForMessages() {
    list<GCMessage> listOfGCM; //A list of the messages send from the Graphics Server.
    int count; //Number of bytes that can be read.
    ioctl(this->sockfd, FIONREAD, &count); //Gets the number of bytes ready to be read.
    if(count == 0) { return listOfGCM; } //If there are no messages, then return the list empty.
    char message[count]; //Declare an array of chars that will hold the messages from the Graphics Server.
    read(this->sockfd, message, count); //Read the message bytes into the message variable.
    for(int i = 0; i < count; i++) { //For each byte in the message.
        if(message[i] == -1) { //If we are at the start of a message.
            int len = (message[i+1] << 12) + (message[i+2] << 8) + (message[i+3] << 4) + message[i+4]; //Get the length of the message.
            if(message[i+5] == 0x01) { //If the message sent is a click message.
                //The following lines of code read the next 8 nibbles and gets x and y values.
                int x = (message[i+7] << 12) + (message[i+8] << 8) + (message[i+9] << 4) + (message[i+10]);
                int y = (message[i+11] << 12) + (message[i+12] << 8) + (message[i+13] << 4) + (message[i+14]);
                //Create GCMessage for this click and add to list of messages to send to client.
                GCMessage gcm = GCMessage(message_type_click, to_string(x) + "," + to_string(y));
                listOfGCM.push_back(gcm);
            } else if(message[i+5] == 0x0A) { //If the message sent is a file message.
                int filePathLen = (len-1)/2; //"len-1" to remove the file command from message length and "/2" since each char takes up 2 nibbles.
                string filePath = ""; //Declare an empty string where the file path will eventually go.
                for(int j = 0; j < filePathLen; j++) { //For each char in the file path part of the message.
                    //The following lines gets the char in the message and appends to the end of the filePath variable.
                    int chr = (message[i+6+(j*2)] << 4) + message[i+7+(j*2)];
                    filePath = filePath + (char)chr;
                }
                //Create GCMessage for this file and add to list of messages to send to client.
                GCMessage gcm = GCMessage(message_type_file, filePath);
                listOfGCM.push_back(gcm);
            }
            i = i + len; //Skip over the read characters in our message array since they were just read.
        }
    }
    return listOfGCM;
}

/**
 * Description: Tells the Graphics Window prompt the user for a file to load.
 */
void GraphicsClient::requestFile() {
    char message[100]; //Message on the stack.
    message[0] = 0xFF;
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x00;
    message[4] = 0x01; //Message length 1.
    message[5] = 0x0E; //Request file command.
    send(sockfd, message, 6, 0);
}

