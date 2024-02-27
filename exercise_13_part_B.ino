/*
  Exercise 13: Catch the LED game
  Hand in: 03-03-2024
  Made by: Carla Soleta (s222824), Christof Haye s222577, and Emil Thomsen Øberg (s184164)

  PART B

*/

/*
Pins 2-6 are used for the 5 lamps. Thereby the middle lamp has to be attached to pin 4.
Pin 8 is used for the button. From the button on cable has to go to GND.

The LCD circut:
RS pin to pin 0
Enable pin to pin 1
D4 pin to pin 7
D5 pin to pin 9
D6 pin to pin 10
D7 pin to pin 11

*/

//libary to use rand()
#include <stdlib.h>

// include the library for LCD:
#include <LiquidCrystal.h>

// LiquidCrystal lcd() initialisation (LCD interface pins linked to Arduino I/O pins)
const int rs = 0, en = 1, d4 = 7, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// the setup function runs once when you press reset or power the board
void setup() {
  // Defines the number of columns and rows for the LCD
  lcd.begin(16, 2);

  //Prints the heading for the dislpay. This does not change, so the code is in setup() so it only runs once
  lcd.print("Success Counter:");
  
  //pinMode initialisation for the lamps
  int i;  
  for (i = 2; i < 7; i++) {
    pinMode(i, OUTPUT);
  }
  //pinMode initialisation for the button
  pinMode(8,INPUT);
  digitalWrite(8,HIGH);
}

//int success_counter=0;
// the loop function runs over and over again forever
void loop() {

  //initialisation of the success_counter
  //the success_counter is a static variable, so the variable is not initialised again after each loop
  int static success_counter=0;

  int time=2000-175*success_counter; //after each successful round the lamps blink shorter
  int lamp; //the port of the lamp
  
  //during the first 8 rounds the lamps blinking in order. 
  //Furthermore, the button is not pressed.
  while(digitalRead(8)==1 && success_counter<8){    
    for (lamp=2;lamp<7;lamp++){
      digitalWrite(lamp, HIGH); 
      delay(time);                   
      digitalWrite(lamp, LOW);  
      //if the button is pressed, the lamps not blink anymore and the program continues to the next step
      if (digitalRead(8) == 0) {
        break;
      }
    }
  }

  //for the last two rounds, the lamps are blinking randomly. The power of the pins are randomly turned on
  while(digitalRead(8)==1 && success_counter >=8 && success_counter<10){
      lamp=rand() % 6 + 2;
      digitalWrite(lamp, HIGH);
      delay(300);                      
      digitalWrite(lamp, LOW); 
  }


  //this section contains the evaluation, if the player can jump to the next round or not

  //if the middle lamp is selected, all lamps blink 5 times, and the counter is raised
  if (lamp==4){
    for (int blink=1;blink<5;blink++){
      for (int lamp=2;lamp<7;lamp++){
        digitalWrite(lamp, HIGH); 
      }
      delay(300);
      for (int lamp=2;lamp<7;lamp++){
        digitalWrite(lamp, LOW);
      }
      delay(300);
    }
    //the success counter is not increased further, after the game was won
    if(success_counter<10){
      success_counter=success_counter+1;
    }
  }

  //if the false lamp is selected, all LEDs are turned off for 3 seconds, and the success counter does not increased
  else{
    for (int lamp=2;lamp<7;lamp++){
        digitalWrite(lamp, LOW);
      }
      delay(3000);
  }
  
  //No matter if the button was pressed at the right time or not, the current Success counter is displayed on the LCD
  // Setting the LCD cursor to first colum (colum 0) and second line (line 1)
  lcd.setCursor(0, 1);
  // Print the current Succes Counter:
  lcd.print(success_counter);
}


 


