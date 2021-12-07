#include <string> //For using strings.
#include "GCMessage.h" //Allows for GCM usage.

using namespace std; //Allows for 'std::' to be removed from certain lines.

/**
 * Description: A parameterized constructor for a GCMessage object.
 * Parameter: messageType - The type of the message contained.
 * Parameter: message - The message information.
 */
GCMessage::GCMessage(int messageType, string message) {
    this->messageType = messageType;
    this->message = message;
}

/**
 * Description: A getter for the GCMessages's message type.
 * Returns: int - The message type of the GCMessage.
 */
int GCMessage::getMessageType() {
    return this->messageType;
}

/**
 * Description: A getter for the GCMessages's message.
 * Returns: string - The message of the GCMessage.
 */
string GCMessage::getMessage() {
    return this->message;
}