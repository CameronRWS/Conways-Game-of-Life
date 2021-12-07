#include <string> //For using strings.

using namespace std; //Allows for 'std::' to be removed from certain lines.

#ifndef GCM_HEADER
#define GCM_HEADER

/** 
 * Description: Stores a Graphics Client message.
 */
class GCMessage {
    public:
        /**
         * Description: A parameterized constructor for a GCMessage object.
         * Parameter: messageType - The type of the message contained.
         * Parameter: message - The message information.
         */
        GCMessage(int messageType, string message);
        //The following lines are for the GCM's copy constructor (the default), equals operator (the default), and destructor (the default).
        GCMessage(const GCMessage&) = default;
        GCMessage& operator=(const GCMessage&) = default;
        ~GCMessage() = default;
        /**
         * Description: A getter for the GCMessages's message type.
         * Returns: int - The message type of the GCMessage.
         */
        int getMessageType();
        /**
         * Description: A getter for the GCMessages's message.
         * Returns: string - The message of the GCMessage.
         */
        string getMessage();
    private:
        //Member/Field: int messageType - The type of information stored in the message.
        int messageType;
        //Member/Field: string message - The contents of the message.
        string message;
};

#endif