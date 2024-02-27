/*
  Exercise 13: Catch the LED game
  Hand in: 03-03-2024
  Made by: Carla Soleta (s222824), Christof Haye s222577, and Emil Thomsen Øberg (s184164)

  PART C

/*

/*
Pins 2-6 are used for the 5 lamps. Thereby the middle lamp has to be attached to pin 4.
Pin 8 is used for the button. From the button on cable has to go to GND.
Pin 0, 1, 7,9,10,11,12,13 are used for 7 segment display
*/

//libary to use  rand() for exercise A
#include <stdlib.h>


//letters for pin input for 7 segement display - Excercise C
int a = 0;
int b = 1;
int c = 7; 
int d = 11; 
int e = 12; 
int f = 9; 
int g = 10; 
int dp = 13; 

//configuration of pins for different numbers on 7 segment display - Excericse C
//display number 1
void display1(void) 
{
  
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
} 
//display number2
void
  display2(void) 
{
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);

    digitalWrite(g,HIGH);
  digitalWrite(e,HIGH);
    digitalWrite(d,HIGH);
}
  
// display number3
void display3(void) 
{ 
    digitalWrite(a,HIGH);

    digitalWrite(b,HIGH);
    
  digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);

    digitalWrite(g,HIGH);
} 
// display number4
void display4(void) 
{
  
    digitalWrite(f,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(g,HIGH);

  digitalWrite(c,HIGH);
  
} 
// display number5
void display5(void)
  
{ 
    digitalWrite(a,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);

  digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
} 
// display number6
void
  display6(void) 
{ 
    digitalWrite(a,HIGH);
    digitalWrite(f,HIGH);

    digitalWrite(g,HIGH);
  digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
  
    digitalWrite(e,HIGH);  
} 
// display number7
void display7(void)
  
{   
   digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
}
  
// display number8
void display8(void) 
{ 
    digitalWrite(a,HIGH);

    digitalWrite(b,HIGH);
    digitalWrite(g,HIGH);
  digitalWrite(c,HIGH);

    digitalWrite(d,HIGH);  
    digitalWrite(e,HIGH);  
  digitalWrite(f,HIGH);
  
} 
void clearDisplay(void) 
{ 
    digitalWrite(a,LOW);
    digitalWrite(b,LOW);

    digitalWrite(g,LOW);
  digitalWrite(c,LOW);
    digitalWrite(d,LOW);  

    digitalWrite(e,LOW);  
  digitalWrite(f,LOW);  
} 
void display9(void)
  
{ 
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(g,HIGH);

  digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);  
  digitalWrite(f,HIGH);
  
} 
void display0(void) 
{ 
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);

  digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);  
    digitalWrite(e,HIGH);
  
  digitalWrite(f,HIGH);  
} 

// the setup function runs once when you press reset or power the board
void setup() {
  //pinMode initialisation for the lamps and 7 segment display
  int i;  
  for (i = 0; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
  //pinMode initialisation for the button
  pinMode(8,INPUT);
  digitalWrite(8,HIGH);

  Serial.begin(9600);
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
  
  //No matter if the button was pressed at the right time or not, the current Success counter is displayed on the Serial Monitor
  Serial.print("Success Counter: ");
  Serial.println(success_counter);

  //show success count on 7 digit 
  clearDisplay();
  switch (success_counter){
    case 0:
      clearDisplay();
      display0(); 
      break;

    case 1:
      clearDisplay();
      display1(); 
      break;

    case 2:
      clearDisplay();
      display2(); 
      break;

    case 3:
      clearDisplay();
      display3(); 
      break;

    case 4:
      clearDisplay();
      display4(); 
      break;

    case 5:
      clearDisplay();
      display5(); 
      break;

    case 6:
      clearDisplay();
      display6(); 
      break;

    case 7:
      clearDisplay();
      display7(); 
      break;

    case 8:
      clearDisplay();
      display8(); 
      break;

    case 9:
      clearDisplay();
      display9(); 
      break;
    
    case 10:
      clearDisplay();
      display0(); 
      break;
   
  }
}


 
