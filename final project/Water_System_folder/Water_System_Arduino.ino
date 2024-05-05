/*
IoT Project, Green House. 
Code for Arduino (Slave in the I2C connection)

Description:
This code for the Arduino for the water system. 
The function of this code is to check if the water tank for the herbs is empty, and if it is, 
start pumping water from the additional water tank until the water level reaches maximum.
*/

// Including Wire library for I2C connection
#include <Wire.h>

const int WS_L_Power = 5; // defining the lower water sensor to pin 5
const int WS_L_Read = A0; // defining the lower water sensor measure to A0

const int WS_H_Power = 3; // defining the higher water sensor to pin 3
const int WS_H_Read = A1; // defining the higher water sensor measure to A1

int waterValueLow = 0;    // defining the constant waterValueLow
int waterValueHigh = 0;   // defining the constant waterValueHigh

const int WP_Power = 6;   // defining the water pump to pin 6

int WATER_MIN = 10;       // defining the minimum value for the water sensors

void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event

  Serial.begin(9600);           // start serial for debugging

  pinMode(WS_L_Power, OUTPUT);  // defines WS_L_Power as OUTPUT
  pinMode(WS_H_Power, OUTPUT);  // defines WS_H_Power as OUTPUT
  pinMode(WP_Power, OUTPUT);    // defines WP_Power as OUTPUT

  digitalWrite(WS_L_Power, LOW);  // turns the  water sensor OFF
  digitalWrite(WS_H_Power, LOW);  // turns the  water sensor OFF
  digitalWrite(WP_Power, LOW);    // turns the water pump OFF
}


void loop()
{
  delay(1000); // pause for 1 sec to avoid reading sensors frequently to prolong the sensor lifetime
  
  // SENSOR LOW measuring:
  digitalWrite(WS_L_Power, HIGH);  // turn the sensor ON
  delay(10);  // wait 10 milliseconds to make sure that the sensor is ready
  waterValueLow = analogRead(WS_L_Read); // read the analog value from sensor
  digitalWrite(WS_L_Power, LOW);   // turn the sensor OFF
    
  if (WATER_MIN >= waterValueLow) { // Enter the if condition if the herbs are out of water
    
    digitalWrite(WP_Power, HIGH); // turn the water pump ON
    
    while(waterValueHigh < WATER_MIN) { // Pump untill the water level reaches maximum (higher water sensor)
      // SENSOR HIGH is measuring
      digitalWrite(WS_H_Power, HIGH);  // turn the sensor ON
      delay(10);  // wait 10 milliseconds to make sure that the sensor is ready               
      waterValueHigh = analogRead(WS_H_Read); // read the analog value from sensor
      digitalWrite(WS_H_Power, LOW);   // turn the sensor OFF

      
      delay(500); // pause for 0,5 sec to avoid reading sensors frequently to prolong the sensor lifetime
    }

    digitalWrite(WP_Power, LOW); // turn the water pump OFF
  }

  // Reset sensor values
  waterValueLow = 0;
  waterValueHigh = 0;
}

// Function that will interrupt if the ESP measures that the extra water tank is empty via I2C connection
// The function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // Read data from ESP
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer

  if (x == 1) { //if water tank is empty
    
    digitalWrite(WP_Power, LOW); // turn the water pump OFF

    while(x == 1) { // infinite loop, waits for the user to press the reset button to indicate that the tank is refilled
      delay(5000);
    }
  }
}