/*
  Demo Alessandro
  5^B - Automazione
  Compito per il 03.05.2022
  Es. 25.6:
  Mediante un sensore ad ultrasuoni realizzare un programma che
  nell’intervallo tra 3 cm e 19 cm avvicinando un ostacolo,
  per ogni centimetro il sensore incrementa di 128 passi e
  allontanandosi dall’ostacolo per ogni centimetro il numero di passi decremento di 128 passi.
*/
#include <Stepper.h>
const int stepsPerRevolution = 1024;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
const int triggerPort = 4;
const int echoPort = 3;
int totalStepsForward = 0;
int totalStepsBackward = 0;

void setup() {
  pinMode(triggerPort, OUTPUT);
  pinMode(echoPort, INPUT);
  myStepper.setSpeed(15);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(triggerPort, LOW);
  digitalWrite(triggerPort, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPort, LOW);
  long duration = pulseIn(echoPort, HIGH);
  long distance = 0.034 * duration / 2;
  long lastDistance = 0;
  Serial.print("distanza: ");
  Serial.println(distance);
  if (distance >= 3 && distance <= 19) {
    if (distance > lastDistance) {
      totalStepsForward = 128 * (distance - lastDistance );
      myStepper.step(totalStepsForward);
      Serial.println(totalStepsForward);
    }
    if (distance < lastDistance) {
      totalStepsBackward = -128 * (distance - lastDistance);
      myStepper.step(totalStepsBackward);
      Serial.println(totalStepsBackward);
    }
  }
}