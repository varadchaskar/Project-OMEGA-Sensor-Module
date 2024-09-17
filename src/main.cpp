/*
 * ESP8266 Hydroponic Automation Sensor Module
 * 
 * Author: Varad Chaskar
 * Date: January 28, 2024
 * 
 * Description: 
 * This code is part of a hydroponic automation project using an ESP8266 microcontroller. 
 * It collects environmental data, such as temperature, humidity, light intensity, and water level,
 * and sends the data to the ThingSpeak IoT cloud platform for real-time monitoring and analysis.
 * 
 * Libraries Used:
 * 1. WiFiManager: Simplifies WiFi connection handling. It helps automatically connect the ESP8266
 *    to a known WiFi network or starts an access point (AP) for manual configuration if no known network is available.
 *    - Required for establishing a WiFi connection without hardcoding network credentials.
 * 
 * 2. ESP8266WiFi: Provides WiFi functionality for ESP8266. 
 *    - Used for establishing a WiFi connection and sending/receiving data.
 * 
 * 3. DHT: DHT sensor library used for interfacing with a DHT11 or DHT22 sensor.
 *    - Used to measure temperature and humidity.
 * 
 * 4. ThingSpeak: A library that provides seamless communication with the ThingSpeak IoT cloud platform.
 *    - Sends the environmental sensor data (temperature, humidity, light intensity, and water level) to ThingSpeak.
 * 
 * Functionality:
 * 1. Connects to WiFi using WiFiManager.
 * 2. Reads sensor data (temperature, humidity from the DHT sensor, light intensity from an LDR, and water level).
 * 3. Sends the sensor data to the ThingSpeak cloud for monitoring.
 */

// Include necessary libraries
#include <Arduino.h>
#include <WiFiManager.h>   // WiFiManager library for simplified WiFi connection handling
#include <ESP8266WiFi.h>   // ESP8266 WiFi library for network functionality
#include <DHT.h>           // DHT sensor library for temperature and humidity
#include "ThingSpeak.h"    // ThingSpeak library for sending data to the cloud

// Declare the WiFi client for ThingSpeak communication
WiFiClient client;

// ThingSpeak configuration
unsigned long myChannelNumber = 2384399;               // Your ThingSpeak channel number
const char *myWriteAPIKey = "ELW2NF5Q83OGB39G";        // Write API key for ThingSpeak channel
const char *myCounterReadAPIKey = "3D8NH4JCI0EDYMIU";  // (Optional) Read API key for ThingSpeak

// Pin connected to the data pin of the DHT sensor
#define DHTPIN D5  // You can change this to the pin where your DHT sensor is connected

// Define the type of DHT sensor you're using (DHT11 or DHT22)
#define DHTTYPE DHT11  // Change to DHT22 if you're using a DHT22 sensor

// Create an instance of the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Set up the built-in LED as an output for visual feedback
  pinMode(LED_BUILTIN, OUTPUT);  

  // Start serial communication for debugging
  Serial.begin(115200);
  
  // Create an instance of WiFiManager for WiFi connection management
  WiFiManager wm;

  // Try to connect to a saved WiFi network or start an access point named "ASAA" if no network is saved
  bool res;
  res = wm.autoConnect("ASAA"); // Connects to WiFi or creates an access point

  // Check if the connection was successful
  if (!res) {
    // Failed to connect to WiFi, provide visual feedback and restart the ESP8266
    Serial.println("Failed to connect to WiFi");
    digitalWrite(LED_BUILTIN, HIGH); // Turn on the built-in LED to indicate failure
    delay(1000);                     // Wait for 1 second
    digitalWrite(LED_BUILTIN, LOW);  // Turn off the LED
    delay(1000);                     // Blink again
    digitalWrite(LED_BUILTIN, HIGH);
    ESP.restart();                   // Restart the ESP8266 to retry connection
  } 
  else {
    // Successfully connected to WiFi, initialize ThingSpeak communication
    ThingSpeak.begin(client);         // Initialize ThingSpeak
    digitalWrite(LED_BUILTIN, LOW);   // Turn off the built-in LED to indicate success
    Serial.println("Connected to WiFi");

    // Initialize the DHT sensor (temperature and humidity)
    dht.begin();            // Set up the DHT sensor on the specified pin
  }
}

void loop() {
  // Turn off the built-in LED to indicate normal operation
  digitalWrite(LED_BUILTIN, LOW);

  // Read temperature and humidity data from the DHT sensor
  float temperature = dht.readTemperature(); // Get temperature in Celsius
  float humidity = dht.readHumidity();        // Get humidity in percentage

  // If the sensor fails to read values, print an error
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Read light intensity using the LDR sensor connected to the analog pin A0
  int ldrValue = analogRead(A0);  // Get the LDR value (0-1023 based on light intensity)

  // Simulate water level input by reading from a digital pin (e.g., connected to a water sensor)
  int waterLevel = digitalRead(D0);  // Read water level (0 = low, 1 = high)

  // Print the sensor values to the serial monitor for debugging
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Light Intensity (LDR): ");
  Serial.println(ldrValue);

  Serial.print("Water Level: ");
  Serial.println(waterLevel == HIGH ? "HIGH" : "LOW");

  // Send sensor data to the ThingSpeak cloud
  ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey);  // Field 1: Temperature
  ThingSpeak.writeField(myChannelNumber, 2, humidity, myWriteAPIKey);     // Field 2: Humidity
  ThingSpeak.writeField(myChannelNumber, 3, ldrValue, myWriteAPIKey);     // Field 3: Light intensity
  ThingSpeak.writeField(myChannelNumber, 4, waterLevel, myWriteAPIKey);   // Field 4: Water level
  
  // Wait for 20 seconds before the next update (ThingSpeak update limit: 15 seconds minimum)
  delay(20000);
}
