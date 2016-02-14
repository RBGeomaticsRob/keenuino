
#include <Bridge.h>
#include <ApiClient.h>
#include <KeenClient.h>
#include "keys.h"

int sensorValue = 0;
float voltageValue = 0.0;
float temperature = 0.0;
String jsonString = "{";

KeenClient keen;

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Bridge.begin();
  digitalWrite(13, LOW);
  keenSetup();
}

void loop() {
  readTemps();
  keenWrite();
  delay(30000);
}

void keenSetup() {
  keen.setApiVersion(F("3.0"));
  keen.setProjectId(F(KEENPROJECTID));
  keen.setWriteKey(F(KEENWRITEKEY));
}

void readTemps() {
  jsonString = "{";
  for (int i=0; i<5; i++) {
    sensorValue = analogRead(i);
    voltageValue = sensorValue * (5000/1024);
    temperature = (voltageValue - 500)/10;
    jsonString = jsonString + "\"s"+ i + "\": " + temperature + ",";
  }
  jsonString.remove((jsonString.length() - 1));
  jsonString = jsonString + "}";
}

void keenWrite() {
  keen.addEvent("readings", jsonString);
  ledFlash();
}

void ledFlash() {
  for (int i=0; i<5; i++) {
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  }
}

