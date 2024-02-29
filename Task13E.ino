/*
Similarities: 
There are no similarities in the code
Differences: 
ChatGPt does not use any for loops for intializing or blinking of the LEDs that would have shorten the code
ChatGPT created its own functin fo flashing the lights outside of main loop and just calls it inside (good- let the code look more tidy)

Did the AI generated code make any mistakes or
did it come up with some (partial) solutions that inspired you? 
Chat Gpt implements a different way to not increase the success_counter, by "while (true); // Loop indefinitely, game over"
Solution inspired: partly yes of having some of the loops outside of main loop function as seperate functions

Did you have any difficulties
in making the AI engine write propper code?
The first try, it created more LED pins than needed, because it did not consider that pin 4 is the success LED. So it created single pin ports 8,9 as success and failure LED, 
so it did not work as intended

*/



#define LED_PIN_1 2
#define LED_PIN_2 3
#define LED_PIN_3 4
#define LED_PIN_4 5
#define LED_PIN_5 6
#define BUTTON_PIN 8

#define SUCCESS_LED LED_PIN_3

int successCounter = 0;
const long interval = 500;

void setup() {
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);
  pinMode(LED_PIN_5, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pinMode(SUCCESS_LED, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  flashLEDs();
  
  if (digitalRead(BUTTON_PIN) == LOW) {
    if (successCounter < 10) {
      if (successCounter == 8) {
        flashRandom();
      } else {
        digitalWrite(SUCCESS_LED, HIGH);
        delay(interval); // Blink success LED with a delay
        digitalWrite(SUCCESS_LED, LOW);
        successCounter++;
        Serial.println("Success! Counter: " + String(successCounter));
      }
    } else {
      Serial.println("Game Over! Success Counter reached 10.");
      while (true); // Loop indefinitely, game over
    }
  } else {
    digitalWrite(SUCCESS_LED, LOW);
    Serial.println("Incorrect answer!");
  }

  delay(1000);
}

void flashLEDs() {
  digitalWrite(LED_PIN_1, HIGH);
  delay(100);
  digitalWrite(LED_PIN_1, LOW);
  digitalWrite(LED_PIN_2, HIGH);
  delay(100);
  digitalWrite(LED_PIN_2, LOW);
  digitalWrite(LED_PIN_3, HIGH);
  delay(100);
  digitalWrite(LED_PIN_3, LOW);
  digitalWrite(LED_PIN_4, HIGH);
  delay(100);
  digitalWrite(LED_PIN_4, LOW);
  digitalWrite(LED_PIN_5, HIGH);
  delay(100);
  digitalWrite(LED_PIN_5, LOW);
}

void flashRandom() {
  for (int i = 0; i < 10; i++) {
    int randomLED = random(2, 7); // Random pin between 2 and 6
    digitalWrite(randomLED, HIGH);
    delay(100);
    digitalWrite(randomLED, LOW);
  }
}
