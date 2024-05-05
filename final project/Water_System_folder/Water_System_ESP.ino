/*
IoT Project, Green House. 
Code for ESP8622 (master in the I2C connection)

Description:
This code for the ESP8266 for the water system. 
The function of this code is to check if the water tank is empty, and if it is, 
send a message to the Arduino to stop the water pump via an I2C connection.
As well as sending an email alert to the user via a Thingsspeak server.
*/


// Including libraries related to connecting the ESP to the thingsspeak server and I/O operations
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <stdio.h>


// Including Wire library for I2C connection
#include <Wire.h>

// Defining Wifi for the ESP
const char* ssid = "Carla";
const char* password = "Emil2101";

// Create a WiFi client object to handle network communication
WiFiClient client;


//Thinksspeak server information
unsigned long channelID = 2504191;               //your channel
const char* myWriteAPIKey = "BTF16XM0P58SP8OL";  // your WRITE API key
const char* server = "api.thingspeak.com";


//initialisation to the sensor for watertank
int waterValue = 1;
int* pointerWatertank = &waterValue;

//Defining pins for the rain sensor (RS). A rain sensor is used in this setup.
const int RS_Power = D7;
const int RS_Read = D0;


void setup() {
  Wire.begin();  // join I2C bus

  Serial.begin(9600);  // Initializing serial port for debugging purposes

  pinMode(RS_Power, OUTPUT);  // defines RS_Power as OUTPUT
  pinMode(RS_Read, INPUT);    // defines RS_Read as OUTPUT

  delay(10);

  // Connecting to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  ThingSpeak.begin(client);
}


void loop() {
  digitalWrite(RS_Power, HIGH);  // turn the rain sensor's power ON
  delay(10);                     // wait 10 milliseconds to make sure that the sensor is ready
  waterValue = digitalRead(RS_Read);  // Read the sensor input
  ThingSpeak.writeField(channelID, 1, *pointerWatertank, myWriteAPIKey);  // Send data to the thingsspeak server
  digitalWrite(RS_Power, LOW);  // turn the rain sensor's power OFF

  if (waterValue == HIGH) {                // Enter this if condition if the water tank is empty
    Serial.println("Water NOT detected");  //for debugging

    while (waterValue == HIGH) {
      digitalWrite(RS_Power, HIGH);  // turn the rain sensor's power  ON
      delay(10);                     // wait 10 milliseconds to make sure that the sensor is ready
      ThingSpeak.writeField(channelID, 1, *pointerWatertank, myWriteAPIKey); // Send data to the thingsspeak server
      waterValue = digitalRead(RS_Read); // Read the sensor input

      digitalWrite(RS_Power, LOW);  // turn the rain sensor's power OFF
      Serial.println("The water tank is empty"); // for debugging
      delay(1000); // pause for 1 sec to avoid reading sensors frequently to prolong the sensor lifetime

      Wire.beginTransmission(4);  // transmit to Arduino via I2C connection with address #4
      Wire.write("x is ");        
      Wire.write(waterValue);     
      Wire.endTransmission();     // stop transmitting

      delay(500);
    }

  } else {
    Serial.println("The rain is detected"); // for debugging
  }

  delay(1000);  // pause for 1 sec to avoid reading sensors frequently to prolong the sensor lifetime
}