
// Define connection pins:
int pirPin = 8;
int ledPin = 13;

//reminder: adjust the two yellow crosses on Motion dector accoridng to sensibility (distance of detection & how long delay is)
//right one (closer to black roll): distance between 1-7 meters
//left one (lengths of bliking of lamp): time delay (5 sec)
//high and low on motion detector: 
//High (measures all the time motion - resets timer whenever new motion detected, : how can you switch, my sensor is missing something
//low only measure once, runs timer and in that time new motion detection is blocked)

// Create variables:
int val = 0;
bool motionState = false; // We start with no motion detected.

void setup() {
  // Configure the pins as input or output:
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  digitalWrite(ledPin,LOW); //ensure LED is off when started

  // Begin serial communication at a baud rate of 9600:
  Serial.begin(9600);
}

void loop() {
  // Read out the pirPin and store as val:
  val = digitalRead(pirPin);

  // If motion is detected (pirPin = HIGH), do the following:
  if (val == HIGH) {
    digitalWrite(ledPin, HIGH); // Turn on the on-board LED.

    // Change the motion state to true (motion detected):
    if (motionState == false) {
      Serial.println("Motion detected!");
      motionState = true;
    }
  }

  // If no motion is detected (pirPin = LOW), do the following:
  else {
    digitalWrite(ledPin, LOW); // Turn off the on-board LED.

    // Change the motion state to false (no motion):
    if (motionState == true) {
      Serial.println("Motion ended!");
      motionState = false;
    }
  }
}