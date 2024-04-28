//https://se.mathworks.com/help/thingspeak/read-and-post-temperature-data.html
//https://thingspeak.com/channels/2501766/private_show
//https://api.thingspeak.com/update?api_key=XBN4EDNPJ9VA7&Field2=4

// Including the ESP8266 WiFi library
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <stdio.h> //for a NULL pointer

//const int potPin = A0;    // Analog pin for potentiometer
const int ledPin1 = D2;     // Digital pin for LED
const int ledPin2 = D3;     // Digital pin for LED


// Replace with your network details
const char* ssid = "OnePlus 8";
const char* password = "Hooksiel123";

WiFiClient client;

int counter =0;

unsigned long channelID = 2501766; //your channel
const char * myWriteAPIKey = "XBN4EDNPJ9VA7MWM"; // your WRITE API key
const char * myReadAPIKey = "VLH4594QOOH4SUQH"; // your Read API key
const char* server = "api.thingspeak.com";


//initialisation of the variable to chose the program and the corresponding pointer
int selected_program=0;
int *pointerProgram=&selected_program;

int brightness = 0;
int *pointerBrightness=&brightness;

long currentMS=0;
long *currentMillis=&currentMS;

int lamp_state=0;
int *pointerLamp=&lamp_state;


// only runs once on boot
void setup() {
  // Initializing serial port for debugging purposes
  Serial.begin(115200);
  pinMode(ledPin1, OUTPUT); // Set LED pin as an output
  pinMode(ledPin2, OUTPUT); // Set LED pin as an output
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

  *currentMillis = millis();  // Get the current time

  /*if(*currentMillis%1500==0){
    ThingSpeak.writeField(channelID, 1, counter, myWriteAPIKey);
    //Serial.println(*pointerProgram);
    Serial.println(*currentMillis);
  }
  */

  // put your main code here, to run repeatedly:
  //data=thingSpeakRead(channelID,myWriteAPIKey);
  ThingSpeak.writeField(channelID, 1, *pointerLamp, myWriteAPIKey);
  *pointerProgram = ThingSpeak.readIntField(channelID, 2, myWriteAPIKey);
  *pointerBrightness = ThingSpeak.readIntField(channelID, 3, myWriteAPIKey);
  //Serial.println(data);

  executeRhythm();

  delay(100);
}
