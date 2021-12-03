#include <string> //For using strings.

using namespace std;

#ifndef GCM_HEADER
#define GCM_HEADER

class GCMessage {
    public:
        GCMessage(int messageType, string message);
        // GCMessage(const GCMessage& originalGCM);
        // ~GCMessage();
        // GCMessage& operator=(const GCMessage& toCopyGCM);
        int getMessageType();
        string getMessage();
    private:
        int messageType; //1 => click, 2 => file
        string message; //1 => "x,y", 2 => fileName
};

#endif