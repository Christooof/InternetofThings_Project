
const int LEDred = 9;
const int LEDyellow = 6;
const int LEDgreen = 5;


void setup() {
  // put your setup code here, to run once:

  // initialize serial communication at 38400 bits per second:
  Serial.begin(38400);
  pinMode(LEDred, OUTPUT);
  pinMode(LEDyellow, OUTPUT);
  pinMode(LEDgreen, OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:

  // read the input on analog pin 0 and converting from 1023 to 5V:
  float millivolts = analogRead(A0) * (5000 / 1023);
  // 208 = 20 degress (we measured) and 10 mV per degree
  float temperature = 20 + (millivolts - 208) / 10;

    Serial.println(temperature);


  

    if (temperature <= 20.0) {
      digitalWrite(LEDgreen, HIGH);
      digitalWrite(LEDyellow, LOW);
      digitalWrite(LEDred, LOW);
    } else if (temperature > 20.0 && temperature <= 25.0) {
      digitalWrite(LEDgreen, LOW);
      digitalWrite(LEDyellow, HIGH);
      digitalWrite(LEDred, LOW);
    } else if (temperature > 25.0) {
      digitalWrite(LEDgreen, LOW);
      digitalWrite(LEDyellow, LOW);
      digitalWrite(LEDred, HIGH);
    }

  delay(500);




}


