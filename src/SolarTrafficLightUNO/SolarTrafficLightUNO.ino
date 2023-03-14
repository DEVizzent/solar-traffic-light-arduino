#include "TrafficLight.h"
#include "EventListener.h"
#include "arduino-timer.h"
auto timer = timer_create_default();
TrafficLight traffic = TrafficLight(8,9,10);
EventListener eventListener;
JSONVar event;
void setup() {
  Serial.begin(115200);
}

void loop() {
  eventListener.listen();
  if (eventListener.hasEvent()) {
    event = eventListener.readEvent();
    if (event.hasOwnProperty("b")) {
      updateTrafficLight((int)event["b"]);
    }
  }
  timer.tick();
}

void updateTrafficLight(int balance) {
  timer.cancel();
  if (balance <= 0) {
    traffic.red();
    return;
  }
  if (balance < 500) {
    timer.every(200, toggle_yellow);
    return;
  }
  if (balance < 1000) {
    traffic.yellow();
    return;
  }
    traffic.green();
}

bool toggle_yellow(void *) {
  traffic.toggleColor(traffic.yellowPin());
  return true;
}
