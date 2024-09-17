/*
 * WiFiManager Test Code for ESP8266
 * Author: Varad Chaskar
 * Description: This code is designed to test the WiFiManager functionality on an ESP8266 board. 
 * It tries to connect to a WiFi network using the WiFiManager library, providing an easy-to-use 
 * interface for managing WiFi connections.
 * Date: January 28, 2024
 */

#include <Arduino.h>
#include <WiFiManager.h>        // WiFiManager library for handling WiFi connections easily
#include <ESP8266WiFi.h>        // ESP8266 WiFi library for network communication      

// Create a WiFiClient object for potential future communication
WiFiClient client;

// Pin configuration for built-in LED on the ESP8266 board
const int LED_PIN = LED_BUILTIN; 

void setup() {
  // Configure the built-in LED as an output to provide visual feedback on connection status
  pinMode(LED_PIN, OUTPUT);

  // Initialize serial communication at 115200 baud for debugging and monitoring output
  Serial.begin(115200);

  // Create an instance of WiFiManager to handle the WiFi connection process
  WiFiManager wm;

  // Print message to serial console for debugging and tracking progress
  Serial.println("Starting WiFiManager Test...");

  // Attempt to connect to WiFi using saved credentials (auto-connect mode)
  // If no credentials are saved, it will start an access point (AP) named "ASAA" for manual WiFi configuration
  bool connected = wm.autoConnect("ASAA");

  // Check if WiFi connection was successful
  if (!connected) {
    // If connection fails, print an error message to the serial monitor
    Serial.println("Failed to connect to WiFi.");

    // Blink the built-in LED to visually indicate connection failure
    digitalWrite(LED_PIN, HIGH);  // Turn LED on
    delay(1000);                  // Wait for 1 second
    digitalWrite(LED_PIN, LOW);   // Turn LED off
    delay(1000);                  // Wait for 1 second
    digitalWrite(LED_PIN, HIGH);  // Turn LED on again

    // Restart the ESP8266 after a failed connection attempt to retry WiFi setup
    ESP.restart();  
  } else {
    // If successfully connected to WiFi, print a success message to the serial monitor
    Serial.println("Connected to WiFi!");

    // Turn off the built-in LED to indicate successful WiFi connection
    digitalWrite(LED_PIN, LOW);  
  }

}

void loop() {
  // Nothing to do in the loop for this WiFiManager test
  // All actions are handled in the setup phase (connecting to WiFi and giving feedback)
}
