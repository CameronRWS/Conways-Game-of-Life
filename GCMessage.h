#include <string> //For using strings.

using namespace std;

#ifndef GCM_HEADER
#define GCM_HEADER

class GCMessage {
    public:
        GCMessage(int messageType, string message);
        GCMessage(const GCMessage&) = default;
        GCMessage& operator=(const GCMessage&) = default;
        ~GCMessage() = default;
        int getMessageType();
        string getMessage();
    private:
        //Member/Field: int messageType - The type of information stored in the message.
        int messageType;
        //Member/Field: string message - The contents of the message.
        string message;
};

#endif