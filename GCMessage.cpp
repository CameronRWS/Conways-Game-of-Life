#include <string> //For using strings.
#include "GCMessage.h" //Allows for GCM usage.

GCMessage::GCMessage(int messageType, string message) {
    this->messageType = messageType;
    this->message = message;
}

GCMessage::GCMessage(const GCMessage& originalGCM) {
    this->message = originalGCM.message;
    this->messageType = originalGCM.messageType;
}

GCMessage::~GCMessage() {

}

GCMessage& GCMessage::operator=(const GCMessage& toCopyGCM) {
    if (this != &toCopyGCM) {
        this->message = toCopyGCM.message;
        this->messageType = toCopyGCM.messageType;
    }
    return *this;
}


int GCMessage::getMessageType() {
    return this->messageType;
}

string GCMessage::getMessage() {
    return this->message;
}