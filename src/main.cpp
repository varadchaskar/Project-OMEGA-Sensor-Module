#include <Arduino.h>
#include <WiFiManager.h>        // WiFiManager library for handling WiFi connections easily
#include <ESP8266WiFi.h>        // ESP8266 WiFi library for network communication
#include "ThingSpeak.h"         // ThingSpeak library for cloud communication (not used in this test)
#include <DHT.h> 

void setup() {

  // Initialize serial communication at 115200 baud for debugging and monitoring output
  Serial.begin(115200);

}

void loop() {
  // Nothing to do in the loop for this WiFiManager test
  // All actions are handled in the setup phase (connecting to WiFi and giving feedback)
}
