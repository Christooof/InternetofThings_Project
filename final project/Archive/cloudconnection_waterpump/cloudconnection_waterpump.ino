// Including the ESP8266 WiFi library
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <stdio.h> //for a NULL pointer


// Replace with your network details
const char* ssid = "OnePlus 8";
const char* password = "Hooksiel123";

WiFiClient client;


//update to our channel
unsigned long channelID = 2504191; //your channel
const char * myWriteAPIKey = "BTF16XM0P58SP8OL"; // your WRITE API key
const char* server = "api.thingspeak.com";


//initialisation to the sensor for watertank
int waterValue=1;
int *pointerWatertank=&waterValue;


// only runs once on boot
void setup() {
  // Initializing serial port for debugging purposes
  Serial.begin(115200);


  //initialisation of the pins

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

  //your code


  ThingSpeak.writeField(channelID, 1, *pointerWatertank, myWriteAPIKey);

  delay(100);
}
