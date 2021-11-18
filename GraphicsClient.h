#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
using namespace std;

#ifndef GC_HEADER
#define GC_HEADER

class GraphicsClient {
    public:
        /**
         * Description: A parameterized constructor for a GraphicsClient object.
         * Parameter: URL - The url address the GraphicsClient should connect to.
         * Parameter: port - The port the GraphicsClient should connect to.
         */
        GraphicsClient(string URL, int port);
        /**
         * Description: A copy constructor for a GraphicsClient object.
         * Parameter: originalGC - The GraphicsClient object to base the newly created one off of.
         */
        GraphicsClient(const GraphicsClient& originalGC);
        /**
         * Description: A destructor for a GraphicsClient object.
         */
        ~GraphicsClient();
        /**
         * Description: A copy operator for a GraphicsClient object.
         * Parameter: toCopyGC - The GraphicsClient object to base the newly created one off of.
         */
        GraphicsClient& operator=(const GraphicsClient& toCopyGC);
        /**
         * Description: Sets the background color of the associated graphics display for the GraphicsClient object 
         *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
         * Parameter: r - The value of the red component of the RGB color (0-255) (higher bits of the int are ignored).
         * Parameter: g - The value of the green component of the RGB color (0-255).
         * Parameter: b - The value of the blue component of the RGB color (0-255).
         */
        void setBackgroundColor(int r, int g, int b);
        /**
         * Description: Sets the drawing color of the associated graphics display for the GraphicsClient object 
         *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
         * Parameter: r - The value of the red component of the RGB color (0-255) (higher bits of the int are ignored).
         * Parameter: g - The value of the green component of the RGB color (0-255).
         * Parameter: b - The value of the blue component of the RGB color (0-255).
         */
        void setDrawingColor(int r, int g, int b);
        /**
         * Description: Clears the associated graphics display for the GraphicsClient object 
         *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
         */
        void clear();
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
        void setPixel(int x, int y, int r, int g, int b);
        /**
         * Description: Draws an outline of a rectangle on the associated graphics display for the GraphicsClient object 
         *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
         * Parameter: x - The x coord of where the rectangle should start.
         * Parameter: y - The y coord of where the rectangle should start.
         * Parameter: w - The width (in pixels) of the rectangle to draw.
         * Parameter: h - The height (in pixels) of the rectangle to draw.
         */
        void drawRectangle(int x, int y, int w, int h);
        /**
         * Description: Draws a filled rectangle on the associated graphics display for the GraphicsClient object 
         *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
         * Parameter: x - The x coord of where the rectangle should start.
         * Parameter: y - The y coord of where the rectangle should start.
         * Parameter: w - The width (in pixels) of the rectangle to draw.
         * Parameter: h - The height (in pixels) of the rectangle to draw.
         */
        void fillRectangle(int x, int y, int w, int h);
        /**
         * Description: Draws a filled rectangle with the color of the background on the associated 
         *  graphics display for the GraphicsClient object by communicating to the GraphicsServer 
         *  based off of the project specifications and communication document provided.
         * Parameter: x - The x coord of where the rectangle should start.
         * Parameter: y - The y coord of where the rectangle should start.
         * Parameter: w - The width (in pixels) of the rectangle to draw.
         * Parameter: h - The height (in pixels) of the rectangle to draw.
         */
        void clearRectangle(int x, int y, int w, int h);
        /**
         * Description: Draws an outline of an oval on the associated graphics display for the GraphicsClient object 
         *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
         * Parameter: x - The x coord of where the oval should start.
         * Parameter: y - The y coord of where the oval should start.
         * Parameter: w - The width (in pixels) of the oval to draw.
         * Parameter: h - The height (in pixels) of the oval to draw.
         */
        void drawOval(int x, int y, int w, int h);
        /**
         * Description: Draws an filled in an oval on the associated graphics display for the GraphicsClient object 
         *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
         * Parameter: x - The x coord of where the oval should start.
         * Parameter: y - The y coord of where the oval should start.
         * Parameter: w - The width (in pixels) of the oval to draw.
         * Parameter: h - The height (in pixels) of the oval to draw.
         */
        void fillOval(int x, int y, int w, int h);
        /**
         * Description: Draws a line on the associated graphics display for the GraphicsClient object 
         *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
         * Parameter: x1 - The x coord of where the line should start.
         * Parameter: y1 - The y coord of where the line should start.
         * Parameter: x2 - The x coord of where the line should end.
         * Parameter: y2 - The y coord of where the line should end.
         */
        void drawLine(int x1, int y1, int x2, int y2);
        /**
         * Description: Draws a string on the associated graphics display for the GraphicsClient object 
         *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
         * Parameter: x - The x coord of where the string should start.
         * Parameter: y - The y coord of where the string should start.
         * Parameter: stringToDraw - The string to draw on the graphics display.
         */
        void drawstring(int x, int y, string stringToDraw);
        /**
         * Description: Repaints (updates) the associated graphics display for the GraphicsClient object 
         *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
         */
        void repaint();
        /**
         * Description: Draws a shape on the associated graphics display for the GraphicsClient object 
         *  by communicating to the GraphicsServer based off of the project specifications and communication document provided.
         * Parameter: c - The code command (0-15) for drawing the desired shape found in the GraphicsServer communication document.
         * Parameter: x - The x coord of where the shape should start.
         * Parameter: y - The y coord of where the shape should start.
         * Parameter: w - The width (in pixels) of the shape to draw.
         * Parameter: h - The height (in pixels) of the shape to draw.
         */
        void drawShapeHelper(int c, int x, int y, int w, int h);
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