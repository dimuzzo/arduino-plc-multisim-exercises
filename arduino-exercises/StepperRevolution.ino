/*
  Demo Alessandro
  5^B - Automazione
  Compito per il 03.05.2022
  Es. 25.1:
  Fare ruotare in modo continuo l’albero dello stepper, 
  ad ogni rivoluzione accendere un LED per 200 ms. 
  Visualizzare sulla serial monitor il contatore di rivoluzioni.
 */
#include <Stepper.h>
const int stepsPerRevolution = 1024;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
const int ledPin =  13;             
int giro = 0;

void setup() {
  myStepper.setSpeed(15);
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  myStepper.step(stepsPerRevolution);
  tone(ledPin, 1000, 200);
  giro++;
  Serial.println("Giri compiuti:");
  Serial.print(giro);
  Serial.println("");
}