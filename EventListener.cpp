#include "EventListener.h"
#ifndef START_EVENT_MARK
#define START_EVENT_MARK '{'
#define END_EVENT_MARK '}'
#endif
EventListener::EventListener() {
  newEvent = false;
}

void EventListener::listen() {
    static boolean recvInProgress = false;
    static byte ndx = 1;
    char rc;
 
    while (Serial.available() > 0 && newEvent == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
                Serial.println(rc);
            if (rc != END_EVENT_MARK) {
                Serial.println(rc);
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = rc + '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newEvent = true;
            }
        }
        else if (rc == START_EVENT_MARK) { 
            receivedChars[0] = rc;
            recvInProgress = true;
        }
    }
}

bool EventListener::hasEvent() {
  return newEvent;
}

JSONVar EventListener::readEvent() {
  char * castedReceivedChars = (char*)receivedChars;
    Serial.println(castedReceivedChars);
  JSONVar event = JSON.parse(castedReceivedChars);
  if (JSON.typeof(event) == "undefined") {
    return;
  }
  Serial.println("Json formatted");
  return event;
}
