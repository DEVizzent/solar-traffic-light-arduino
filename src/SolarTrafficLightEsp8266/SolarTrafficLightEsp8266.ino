#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266HTTPClient.h>
#include "SMAMeter.h"
#include "Config.h"
#include "arduino-timer.h"

ESP8266WiFiMulti WiFiMulti;
SMAMeter meter;
int balance;
auto timer = timer_create_default();
char eventBuffer[32];

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  BearSSL::WiFiClientSecure client;
  meter.init(client, SMAMETER_HOST);
  meter.login(SMAMETER_PASSWORD);
  delay(500);
  timer.every(5000, writeBalance);
}


void loop() {
  timer.tick();
}

bool writeBalance(void *) {
  balance = meter.readValue();
  sprintf(eventBuffer, "{\"b\":%d}", balance);
  Serial.write(eventBuffer);
  memset( eventBuffer, 0, 32);
  return true;
}
