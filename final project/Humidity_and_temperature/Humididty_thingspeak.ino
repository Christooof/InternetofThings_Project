#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <LiquidCrystal.h>
#include <ThingSpeak.h>


#define DHTPIN 21      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11  // DHT 11
#define LEDPIN 23

LiquidCrystal lcd(27, 14, 26, 25, 33, 32);

WiFiClient client;

const char *ssid = "<REDACTED>";
const char *password = "<REDACTED>";

const char *server = "api.thingspeak.com";

// We use 2 thingspeak channels, 1 for displaying sensor data, and one for controlling sensors.
// Displaying server
int dataChannelID = 2496158;
const char * dataAPIWriteKey = "REDACTED";

// Controlling server
int controlChannelID = 2504240; 
const char * controlAPIWriteKey = "REDACTED"; 
const char * controlAPIReadKey = "REDACTED";

// Initialisation of the variable to chose the program and the corresponding pointer
int selected_program=0;
int *pointerProgram=&selected_program;

int brightness = 0;
int *pointerBrightness=&brightness;

long currentMS=0;
long *currentMillis=&currentMS;

int lamp_state=0;
int *pointerLamp=&lamp_state;

float humidity;
float temperature;

// Timers for when to update and read from thingspeak
long int updateThingspeak;

long int readFromThingspeak;

// Temperature and Humidity sensor 
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(230400);
  delay(100);

  dht.begin();

  // Connect to WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Connected to WiFi");

  // Enable LCD
  lcd.begin(16,2);

  pinMode(LEDPIN, OUTPUT);

  ThingSpeak.begin(client);

  updateThingspeak, readFromThingspeak = millis();


  // Initial reading from humidity and temperature sensor
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
}

void loop() {
  // Read from ThingSpeak every second
  if(millis() - readFromThingspeak > 1000){
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    // Read from DHT11 sensor 
    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor!");
      delay(1000);
      return;
    }

    // Print humid and temp to serial monitor for debugging
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C");

    // Write temp and humid to lcd screen
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: " + String(temperature));
    lcd.setCursor(0, 1);
    lcd.print("Humi: " + String(humidity));
  }

  // Send data to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {

    if(millis() - readFromThingspeak > 1000){
      readFromThingspeak = millis();
      // Read from control dashboard
      *pointerProgram = ThingSpeak.readIntField(controlChannelID, 2, controlAPIReadKey);
      *pointerBrightness = ThingSpeak.readIntField(controlChannelID, 1, controlAPIReadKey);
    }

    if(millis() - updateThingspeak > 15000){
      updateThingspeak = millis();
      // Multifield update for thingspeak data dashboard
      ThingSpeak.setField(1, humidity);
      ThingSpeak.setField(2, temperature);
      ThingSpeak.setField(3, lamp_state);
      ThingSpeak.setField(4, selected_program);
      ThingSpeak.setField(5, brightness);
      ThingSpeak.writeFields(dataChannelID, dataAPIWriteKey);
    }

  } else {
    Serial.println("WiFi Disconnected!");
  }
  
  executeRhythm();
  delay(100);
}