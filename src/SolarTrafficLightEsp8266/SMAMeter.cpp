#include "SMAMeter.h"

#ifndef SMAMETER_LOGIN_URL
#define SMAMETER_PORT 443
#define SMAMETER_LOGIN_URI "/dyn/login.json"
#define SMAMETER_GET_VALUES_URI  "/dyn/getValues.json"
#endif

SMAMeter::SMAMeter() {
  Serial.println("SMA created");
}
void SMAMeter::init(BearSSL::WiFiClientSecure wClient, String host) {
  _host = host;
  _wClient = wClient; 
  _wClient.setInsecure();
}
void SMAMeter::login(String password){
    String body = String("{\"right\":\"usr\",\"pass\":\"") + password + String("\"}");
    String responseBody = call(SMAMETER_LOGIN_URI, body);
    JSONVar jsonResponse = JSON.parse(responseBody);
    if (JSON.typeof(jsonResponse) == "undefined") {
      Serial.println("Parsing input failed!");
      return;
    }
    _token = String((const char*) jsonResponse["result"]["sid"]);
}

int SMAMeter::readValue(){
  String body = "{\"destDev\":[],\"keys\":[\"6100_40263F00\"]}";
  String getValuesUri = SMAMETER_GET_VALUES_URI + String("?sid=") + _token; 
  String responseBody = call(getValuesUri, body);
  JSONVar jsonResponse = JSON.parse(responseBody);
  if (JSON.typeof(jsonResponse) == "undefined") {
    Serial.println("Parsing input failed!");
    return -1;
  }
  int retorno = readResponseValue(jsonResponse);
  return retorno;
}

int SMAMeter::readResponseValue(JSONVar jsonResponse){
  for (int x = 0; x < jsonResponse.keys().length(); x++) {
    if ((JSON.typeof(jsonResponse[jsonResponse.keys()[x]])).equals("object") || (JSON.typeof(jsonResponse[jsonResponse.keys()[x]])).equals("array")) {
      return readResponseValue(jsonResponse[jsonResponse.keys()[x]]);
    }
    if (JSON.typeof(jsonResponse[jsonResponse.keys()[x]]).equals("number")) {
      return (int) jsonResponse[jsonResponse.keys()[x]];
    }
  }
  if (JSON.typeof(jsonResponse).equals("array")) {
    return readResponseValue(jsonResponse[0]);
  }
  if (JSON.typeof(jsonResponse).equals("number")) {
    return (int) jsonResponse;
  }
  return -1;
}
String SMAMeter::call(String uri, String body) {
  if (_httpClient.begin(_wClient, _host, SMAMETER_PORT, uri)) {
    _httpClient.addHeader("Content-Type", "application/json");
    int httpResponseCode = _httpClient.POST(body);
    if (httpResponseCode > 0) {
        if (httpResponseCode == HTTP_CODE_OK) {
            return _httpClient.getString();
        }
    } else {
        Serial.print("Http Error Code is :  ");
        Serial.println(httpResponseCode);
        Serial.println(_httpClient.errorToString(httpResponseCode));
    }
  } 
  return String("");
}
