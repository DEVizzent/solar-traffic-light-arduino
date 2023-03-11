#ifndef EventReceiver_h
#define EventReceiver_h
#include "Arduino.h"
#include "Arduino_JSON.h"
class EventListener {
public:
  EventListener();
  void listen();
  bool hasEvent();
  JSONVar readEvent();
private:
  bool newEvent;
  byte numChars = 32;
  char * receivedChars[32];
};
#endif
