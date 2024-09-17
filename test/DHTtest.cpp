/*
 * DHT Sensor Test Code for ESP8266
 * Author: Varad Chaskar
 * Description: This code is designed to test the DHT sensor (DHT11 or DHT22) 
 * connected to the ESP8266. It reads temperature and humidity data from the sensor 
 * and prints the values to the serial monitor.
 * Date: January 28, 2024
 */

#include <DHT.h>  // DHT sensor library

// Pin connected to the data pin of the DHT sensor
#define DHTPIN D5  // You can change this to the pin where your DHT sensor is connected

// Define the type of DHT sensor you're using (DHT11 or DHT22)
#define DHTTYPE DHT11  // Change to DHT22 if you're using a DHT22 sensor

// Create an instance of the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize serial communication at 115200 baud for debugging and monitoring
  Serial.begin(115200);

  // Print a startup message to the serial monitor
  Serial.println("DHT Sensor Test Starting...");

  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);

  // Read the temperature and humidity from the DHT sensor
  float humidity = dht.readHumidity();         // Read humidity in percentage
  float temperature = dht.readTemperature();   // Read temperature in Celsius

  // Check if any reads failed and exit the loop if there is a failure
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print the sensor readings to the serial monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
}
