
#include <Bridge.h>
#include <ApiClient.h>
#include <KeenClient.h>
#include <keys.h>

const int totalAnlgSensors = 5;
const String collectionName = "readings"

KeenClient keen;

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Bridge.begin();
  digitalWrite(13, LOW);
  keenSetup();
}

void loop() {
  float sensorValues[totalAnlgSensors];
  String jsonWriteString;
  
  readAnalogSensors(&sensorValues);
  
  convertArrayValues(&sensorValues);
  
  jsonWriteString = compileJSON(&sensorValues);
  
  keenWrite(collectionName, jsonWriteString);
  
  delay(30000);
}

void keenSetup() {
  keen.setApiVersion(F("3.0"));
  keen.setProjectId(F(KEENPROJECTID));
  keen.setWriteKey(F(KEENWRITEKEY));
}

void readAnalogSensors(float *psensorValues){
  for (int i=0; i<totalAnlgSensors; i++){
    psensorValues[i] = analogRead(i);
  }
}

void convertArrayValues(float *psensorValues){
  for (int i=0; i<totalAnlgSensors; i++){
    psensorValues[i] = convertValue(psensorValues[i]);
  }
}

float convertValue(float sensorValue){
  float voltageValue;
  float temperature;
  voltageValue = sensorValue * (5000/1024); //5000 for 5V, 3300 for 3.3V
  temperature = (voltageValue - 500)/10;
  return temperature;
}

String compileJSON(float *psensorValues){
  String jsonString = "{";
  for (int i=0; i<5; i++){
    jsonString = jsonString + "\"s"+ i + "\": " + psensorValues[i] + ",";
  }
  jsonString.remove((jsonString.length() - 1));
  jsonString = jsonString + "}";
  return jsonString;
}

void keenWrite(String collection, String jsonString) {
  keen.addEvent(collection, jsonString);
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

