#ifndef TrafficLight_h
#define TrafficLight_h
#include "Arduino.h"
#include "arduino-timer.h"
class TrafficLight {
public:
  TrafficLight(int green, int yellow, int red, Timer<> timer);
  void green();
  void yellow();
  void red();
  void off();
  void toggleColor(int color);
  int greenPin();
  int yellowPin();
  int redPin();
private:
  Timer<> _timer;
  int _green;
  int _yellow;
  int _red;
  void _high(int led);
};
#endif
