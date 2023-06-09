#include "TrafficLight.h"

TrafficLight::TrafficLight(int green, int yellow, int red) {
  _green = green;
  _yellow = yellow;
  _red = red;
  pinMode(_green, OUTPUT);
  pinMode(_yellow, OUTPUT);
  pinMode(_red, OUTPUT); 
}

void TrafficLight::green() {
  _high(_green);
}

void TrafficLight::yellow() {
  _high(_yellow);
}

void TrafficLight::red() {
  _high(_red);
}

int TrafficLight::greenPin() {
  return _green;
}

int TrafficLight::yellowPin() {
  return _yellow;
}

int TrafficLight::redPin() {
  return _red;
}

void TrafficLight::off() {
  _high(0);
}

void TrafficLight::toggleColor(int color) {
  if (digitalRead(color) == HIGH) {
    _high(0);
    return;
  }
  _high(color);
  return;
}

void TrafficLight::_high(int led) {
  digitalWrite(_green, (led == _green)? HIGH : LOW);
  digitalWrite(_yellow, (led == _yellow)? HIGH : LOW);
  digitalWrite(_red, (led == _red)? HIGH : LOW);
}
