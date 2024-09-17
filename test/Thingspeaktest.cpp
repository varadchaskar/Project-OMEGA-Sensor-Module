/*
 * ThingSpeak Test Code for ESP8266 with WiFiManager
 * Author: Varad Chaskar
 * Description: This code tests ThingSpeak communication after connecting to WiFi using WiFiManager. 
 * It sends test data to a ThingSpeak channel.
 * Date: January 28, 2024
 */

#include <WiFiManager.h>        // WiFiManager library for handling WiFi connections easily
#include <ESP8266WiFi.h>        // ESP8266 WiFi library for network communication
#include "ThingSpeak.h"         // ThingSpeak library for cloud communication

WiFiClient client;              // WiFi client object to communicate with ThingSpeak

// ThingSpeak channel and API key (Replace with your actual channel number and API key)
unsigned long myChannelNumber = 2384399;  // Your ThingSpeak channel number
const char *myWriteAPIKey = "ELW2NF5Q83OGB39G";  // Your ThingSpeak write API key

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
  Serial.println("Starting WiFiManager for ThingSpeak Test...");

  // Attempt to connect to WiFi using saved credentials (auto-connect mode)
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

    // Initialize ThingSpeak communication with the WiFi client
    ThingSpeak.begin(client);
    Serial.println("ThingSpeak Initialized.");
  }
}

void loop() {
  // Test data to send to ThingSpeak
  float testValue = random(20, 30);  // Generate a random value between 20 and 30

  // Print the value being sent to ThingSpeak
  Serial.print("Sending test value: ");
  Serial.println(testValue);

  // Write the test value to field 1 of the ThingSpeak channel
  int responseCode = ThingSpeak.writeField(myChannelNumber, 1, testValue, myWriteAPIKey);

  // Check if data was sent successfully
  if (responseCode == 200) {
    Serial.println("Data sent successfully to ThingSpeak.");
  } else {
    Serial.print("Failed to send data to ThingSpeak. HTTP error code: ");
    Serial.println(responseCode);
  }

  // Wait for 20 seconds before sending the next data point (ThingSpeak allows updates every 15 seconds)
  delay(20000);
}
