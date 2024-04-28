void executeRhythm(char selected_program, int brightness) {  
  unsigned long currentMillis = millis();  // Get the current time

  //depending from the selected program different "Day-Night Rhythms" are selected
  switch (selected_program) {
    case '2':
      if(((currentMillis/1000)%4)<2){
        analogWrite(ledPin1, brightness);  // Set LED brightness using PWM
        analogWrite(ledPin2, brightness);  // Set LED brightness using PWM       
      }else{
        analogWrite(ledPin1, 0);
        analogWrite(ledPin2, 0);
      }  
      break;
    case '5':
      if(((currentMillis/1000)%4)<2){
        //Serial.println((currentMillis/1000));
        analogWrite(ledPin1, brightness);  // Set LED brightness using PWM
        analogWrite(ledPin2, brightness);  // Set LED brightness using PWM      
      }else{
        analogWrite(ledPin1, 0);
        analogWrite(ledPin2, 0);
      } 
    case '8':
      if(((currentMillis/1000)%8)<4){
        analogWrite(ledPin1, brightness);  // Set LED brightness using PWM
        analogWrite(ledPin2, brightness);  // Set LED brightness using PWM       
      }else{
        analogWrite(ledPin1, 0);
        analogWrite(ledPin2, 0);
      } 
      break;

    default:
     break;
  }
}




