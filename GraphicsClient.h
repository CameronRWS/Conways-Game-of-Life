#include <stdio.h> //From socket code for input/output in C.
#include <stdlib.h> //From socket code.
#include <sys/socket.h> //From socket code.
#include <arpa/inet.h> //From socket code.
#include <unistd.h> //From socket code.
#include <string> //For using strings.
#include <iostream> //input/output in C++ (not the same as stdio.h).
#include <list> //For using lists, specifically for messages.
#include "GCMessage.h" //Allows for GCM usage.

using namespace std; //Allows for 'std::' to be removed from certain lines.

#ifndef GC_HEADER
#define GC_HEADER

/**
 * Description: Convenient class for communicating with a graphics server via various drawing methods. 
 *  This class encapsulates what a window created by the graphics server is.
 */
class GraphicsClient {
    public:
        GraphicsClient(string URL, int port);
        GraphicsClient(const GraphicsClient& originalGC);
        ~GraphicsClient();
        GraphicsClient& operator=(const GraphicsClient& toCopyGC);
        void connectToAddress(string URL, int port);
        void setBackgroundColor(int r, int g, int b);
        void setDrawingColor(int r, int g, int b);
        void clear();
        void setPixel(int x, int y, int r, int g, int b);
        void drawRectangle(int x, int y, int w, int h);
        void fillRectangle(int x, int y, int w, int h);
        void clearRectangle(int x, int y, int w, int h);
        void drawOval(int x, int y, int w, int h);
        void fillOval(int x, int y, int w, int h);
        void drawLine(int x1, int y1, int x2, int y2);
        void drawstring(int x, int y, string stringToDraw);
        void repaint();
        void drawShapeHelper(int c, int x, int y, int w, int h);
        list<GCMessage> checkForMessages();
        void requestFile();
    private:
        //Member/Field: string URL - The URL to the GraphicsClient connects to.
        string URL;
        //Member/Field: int port - The port the GraphicsClient connects to.
        int port;
        //Member/Field: int sockfd - The socket to send messages to.
        int sockfd;
        //Member/Field: sockaddr_in serv_addr - The server address the GraphicsClient connects to.
        struct sockaddr_in serv_addr;
};

#endif