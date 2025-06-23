/*
  Demo Alessandro
  5^B - Automazione
  Compito per il 03.05.2022
  Es. 25.3:
  Alla pressione del pulsante P1 il motore avanza di 512 passi 
  alla pressione del pulsante P2 il motore torna indietro di 512 passi.
 */
#include <Stepper.h>
const int stepsPerRevolution = 1024;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);           
const int P1 = 4;
const int P2 = 3;

void setup() {
  myStepper.setSpeed(15);
  Serial.begin(9600);
  pinMode(P1, INPUT);
  pinMode(P2, INPUT);
  Serial.println("Premere un pulsante");
}

void loop() {
  if(digitalRead(P1) == HIGH){
  myStepper.step(512);
  Serial.println("Avanza di 512 passi");  
  }
  if(digitalRead(P2) == HIGH){
  myStepper.step(-512);
  Serial.println("Indietreggia di 512 passi");  
  }
}