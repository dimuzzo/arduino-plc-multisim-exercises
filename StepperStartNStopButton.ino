/*
  Demo Alessandro
  5^B - Automazione
  Compito per il 03.05.2022
  Es. 25.2:
  Aggiungere all'esercizio precedente due pulsanti di controllo 
  per lo start e per lo stop del motore. 
  Indicare lo stato del pulsante sulla Serial Monitor.
 */
#include <Stepper.h>
const int stepsPerRevolution = 1024;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
const int ledPin =  13;              
int giro = 0;
const int startButton = 3;
const int stopButton = 2;

void setup() {
  attachInterrupt(digitalPinToInterrupt(2), arresto, RISING);
  myStepper.setSpeed(15);
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(startButton, INPUT);
  pinMode(stopButton, INPUT);
  Serial.println("Pulsante start non premuto");
  Serial.println("Pulsante stop non premuto");
}

void loop() {
  if(digitalRead(startButton) == HIGH){
  Serial.println("Pulsante start premuto");
  Serial.println("Pulsante stop non premuto");   
  myStepper.step(stepsPerRevolution);
  tone(ledPin, 1000, 200);
  giro++;
  Serial.println("Giri compiuti:");
  Serial.print(giro);
  Serial.println("");
  }
}

void arresto() {
  Serial.println("Pulsante start non premuto");
  Serial.println("Pulsante stop premuto"); 
}