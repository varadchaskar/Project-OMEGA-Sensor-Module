<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>

<h1>Project OMEGA Sensor Module</h1>
<h2>Part of the Hydroponics Based Precision Farming with Feature Optimization Project</h2>

<p>
    <strong>Author:</strong> Varad Chaskar<br>
    <strong>Date:</strong> January 28, 2024
</p>

<h3>Project Description</h3>
<p>
    The <strong>Project OMEGA Sensor Module</strong> is a key component of the larger project titled 
    "<strong>Hydroponics Based Precision Farming with Feature Optimization</strong>." This project aims to automate and optimize
    the farming process in hydroponic systems using the ESP8266 microcontroller. The OMEGA Sensor Module focuses on gathering 
    critical environmental data, including temperature, humidity, light intensity, and water levels, to monitor and maintain 
    optimal growing conditions in real-time.
</p>

<h3>Purpose</h3>
<p>
    The primary objective of this module is to collect real-time sensor data and transmit it to the <strong>ThingSpeak</strong> 
    cloud platform, enabling remote monitoring and analysis of environmental conditions in a hydroponic system. The data collected 
    is essential for making informed decisions to enhance crop yield and optimize resource usage in a controlled environment.
</p>

<h3>Hardware Used</h3>
<ul>
    <li><strong>Wemos D1 Mini:</strong> The main microcontroller board (based on ESP8266) used to collect and transmit sensor data.</li>
    <li><strong>DHT11 Sensor:</strong> Used for measuring temperature and humidity inside the hydroponic environment.</li>
    <li><strong>Water Level Sensor:</strong> Monitors the water levels in the hydroponic reservoir, providing feedback to prevent water shortage or overflow.</li>
    <li><strong>LDR (Light Dependent Resistor):</strong> Measures the light intensity, ensuring that plants receive adequate lighting for photosynthesis.</li>
</ul>

<h3>Software and Libraries</h3>
<p>The project is developed using <strong>PlatformIO</strong> and includes the following libraries:</p>
<ul>
    <li><strong>WiFiManager:</strong> Simplifies the WiFi connection process, automatically connecting to saved networks or starting an access point for manual setup.</li>
    <li><strong>ESP8266WiFi:</strong> Provides WiFi functionality for the ESP8266 microcontroller to establish network connections.</li>
    <li><strong>DHT:</strong> Used to interface with the DHT11 sensor to retrieve temperature and humidity data.</li>
    <li><strong>ThingSpeak:</strong> Enables seamless communication with the ThingSpeak cloud platform to transmit sensor data for real-time monitoring.</li>
</ul>

<h3>Key Features of the Code</h3>
<ul>
    <li>Automatically connects to a WiFi network using <strong>WiFiManager</strong> or starts an AP for manual configuration.</li>
    <li>Reads temperature and humidity data from the <strong>DHT11</strong> sensor and checks for reading errors.</li>
    <li>Monitors light intensity using the <strong>LDR</strong> sensor connected to the analog pin A0.</li>
    <li>Detects water levels using the <strong>Water Level Sensor</strong> connected to a digital pin.</li>
    <li>Transmits all the collected data to the <strong>ThingSpeak</strong> cloud for real-time monitoring and analysis.</li>
    <li>Built-in LED provides visual feedback on WiFi connection status and data transmission.</li>
</ul>

<h3>ThingSpeak Setup</h3>
<p>
    To view the data from this module on ThingSpeak:
</p>
<ul>
    <li>Create a ThingSpeak account and set up a new channel.</li>
    <li>Configure fields to receive the following data:
        <ul>
            <li>Field 1: Temperature (in Celsius)</li>
            <li>Field 2: Humidity (in %)</li>
            <li>Field 3: Light Intensity (from LDR)</li>
            <li>Field 4: Water Level (0 for low, 1 for high)</li>
        </ul>
    </li>
    <li>Use the provided API key to send data to ThingSpeak.</li>
</ul>

<h3>Future Work</h3>
<p>
    This module is an early prototype of a larger hydroponic farming automation system. Future iterations of this project will involve:
</p>
<ul>
    <li>Adding automated nutrient dosing and pH adjustment based on sensor feedback.</li>
    <li>Implementing predictive analytics using historical data from ThingSpeak to optimize growing conditions.</li>
    <li>Extending support for additional sensors and actuators to further automate the farming process.</li>
</ul>

</body>
</html>
