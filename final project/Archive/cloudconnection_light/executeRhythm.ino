void executeRhythm() {  
  

  //depending from the selected program different "Day-Night Rhythms" are selected
  switch (*pointerProgram) {
    case 2:
      if(((*currentMillis/1000)%20)<10){
        analogWrite(ledPin1, *pointerBrightness);  // Set LED brightness using PWM
        analogWrite(ledPin2, *pointerBrightness);  // Set LED brightness using PWM  
        *pointerLamp=1;
      }else{
        analogWrite(ledPin1, 0);
        analogWrite(ledPin2, 0);
        *pointerLamp=0;
      }  
      break;
    case 5:
      if(((*currentMillis/1000)%4)<2){
        //Serial.println((currentMillis/1000));
        analogWrite(ledPin1, *pointerBrightness);  // Set LED brightness using PWM
        analogWrite(ledPin2, *pointerBrightness);  // Set LED brightness using PWM   
        *pointerLamp=1;   
      }else{
        analogWrite(ledPin1, 0);
        analogWrite(ledPin2, 0);
        *pointerLamp=0;
      } 
    case 8:
      if(((*currentMillis/1000)%8)<4){
        analogWrite(ledPin1, *pointerBrightness);  // Set LED brightness using PWM
        analogWrite(ledPin2, *pointerBrightness);  // Set LED brightness using PWM       
        *pointerLamp=1;
      }else{
        analogWrite(ledPin1, 0);
        analogWrite(ledPin2, 0);
        *pointerLamp=0;
      } 
      break;

    default:
     break;
  }
}




