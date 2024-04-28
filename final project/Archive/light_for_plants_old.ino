#include <Keypad.h>
#include <stdio.h> //for a NULL pointer

//setup for dimmer
const int potPin = A0;    // Analog pin for potentiometer
const int ledPin1 = 10;     // Digital pin for LED
const int ledPin2 = 11;     // Digital pin for LED

//setup for keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//Create an object of keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup() {
  Serial.begin(9600);     // Initialize serial communication
  pinMode(ledPin1, OUTPUT); // Set LED pin as an output
  pinMode(ledPin2, OUTPUT); // Set LED pin as an output
  pinMode(potPin, INPUT); // Set POT pin as an input
}

//initialisation of the variable to chose the program and the corresponding pointer
char selected_program=0;
char *pointerProgram=&selected_program;

void loop() {

  int potValue = analogRead(potPin);  // Read analog value from potentiometer
  int brightness = (float) potValue * 255 / 1023; // The PWM modulation only have an 8bit depth, so the 10bit depth ADC reading has to be remapped to 8bit resolution

  char key = keypad.getKey();// Read the key

  //save the selected program and show it in the Serial Monitor
  if (key){
    *pointerProgram=key;
    Serial.print("Program : ");
    Serial.println(*pointerProgram);
  }
  
  //depending from the selected program different "Day-Night Rhythms" are selected
  switch (*pointerProgram) {
    case '2':
      analogWrite(ledPin1, brightness);  // Set LED brightness using PWM
      analogWrite(ledPin2, brightness);  // Set LED brightness using PWM
      delay(1000);
      analogWrite(ledPin1, 0);
      analogWrite(ledPin2, 0);
      delay(1000);
      break;
    case '5':
      analogWrite(ledPin1, brightness);  // Set LED brightness using PWM
      analogWrite(ledPin2, brightness);  // Set LED brightness using PWM
      delay(2000);
      analogWrite(ledPin1, 0);
      analogWrite(ledPin2, 0);
      delay(2000);
      break;
    case '8':
      analogWrite(ledPin1, brightness);  // Set LED brightness using PWM
      analogWrite(ledPin2, brightness);  // Set LED brightness using PWM
      delay(3000);
      analogWrite(ledPin1, 0);
      analogWrite(ledPin2, 0);
      delay(3000);
      break;

    default:
     break;
  }
}




