#ifndef SMAMeter_h
#define SMAMeter_h
#include "Arduino.h"
#include "Arduino_JSON.h"
#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
class SMAMeter {
public:
  SMAMeter();
  void init(BearSSL::WiFiClientSecure wClient, String host);
  void login(String password);
  int readValue();
  void test();
private:
  BearSSL::WiFiClientSecure _wClient;
  HTTPClient _httpClient;
  String _host;
  String _token;
  String call(String uri, String body);
  int readResponseValue(JSONVar jsonResponse);
};
#endif
