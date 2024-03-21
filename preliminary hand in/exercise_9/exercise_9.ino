void setup() {
  // put your setup code here, to run once:

  // initialize serial communication at 38400 bits per second:
  Serial.begin(38400);

}

void loop() {
  // put your main code here, to run repeatedly:

  // read the input on analog pin 0 and converting from 1023 to 5V:
  float millivolts = analogRead(A0) * (5000 / 1023);
  // 208 = 20 degress (we measured) and 10 mV per degree
  float temperature = 20 + (millivolts - 208) / 10;

  Serial.println(millivolts);
  Serial.println(temperature);


  delay(500);




}
