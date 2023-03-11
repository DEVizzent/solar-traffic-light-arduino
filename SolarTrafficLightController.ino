#include "TrafficLight.h"
#include "EventListener.h"
#include "arduino-timer.h"
auto timer = timer_create_default();
TrafficLight traffic = TrafficLight(8,9,10,timer);
EventListener eventListener;
void setup() {
  Serial.begin(9600);
  Serial.println("Empezamos");
  delay(200);
  timer.every(200, toggle_yellow);
}

// the loop function runs over and over again forever
void loop() {
  eventListener.listen();
  if (eventListener.hasEvent()) {
    Serial.println("Event Recived");
    JSONVar event = eventListener.readEvent();
    if (event.hasOwnProperty("b")) {
      updateTrafficLight((int)event["b"]);
    }
    delay(500);
  }
  timer.tick();
}

void updateTrafficLight(int balance) {
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
  return true; // repeat? true
}
