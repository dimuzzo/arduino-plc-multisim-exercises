/*
  Demo Alessandro
  5^B - Automazione
  Compito per il 03.05.2022
  Es. 25.5:
  All’avvio del programma sulla Serial Monitor inserire due valori che identificano:
  il numero di passi utilizzati per incrementare e il numero di passi per decrementare.
  In questo esercizio si desidera impostare due valori che possono essere anche diversi
  per l’incremento e il decremento dei passi del motore.
  Stampare sulla Serial Monitor il valore totale dei passi compiuti dallo stepper.
*/
#include <Stepper.h>
const int stepsPerRevolution = 1024;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
int P1 = 4;
int P2 = 3;
int stepsForward = 0;
int stepsBackward = 0;
int pressionP1 = 0;
int pressionP2 = 0;
int state = 0;

void setup() {
  myStepper.setSpeed(15);
  Serial.begin(9600);
  pinMode(P1, INPUT);
  pinMode(P2, INPUT);
  Serial.println("Scrivere i passi da compiere in avanti sulla seriale");
}

void loop() {
  switch (state) {
    case 0:
      if (Serial.available() > 0) {
        stepsForward = Serial.parseInt();
        Serial.println(stepsForward);
        Serial.println("Scrivere i passi da compiere all'indietro sulla seriale");
        state = 1;
      }
      break;
    case 1:
      if (Serial.available() > 0) {
        delay(3000);
        stepsBackward = Serial.parseInt();
        Serial.println(stepsBackward);
        Serial.println("Premere un pulsante");
        state = 2;
      }
      break;
    case 2:
      if (digitalRead(P1) == HIGH) {
        pressionP1++;
        myStepper.step(stepsForward);
        Serial.print("Avanzamento di ");
        Serial.print(stepsForward);
        Serial.println(" passi");
        Serial.print("I passi totali fatti in avanti sono ");
        int totalStepsForward = stepsForward * pressionP1;
        Serial.println(totalStepsForward);
        Serial.print("I passi totali fatti all'indietro sono ");
        int totalStepsBackward = stepsBackward * pressionP2;
        Serial.println(totalStepsBackward);
      }
      if (digitalRead(P2) == HIGH) {
        pressionP2++;
        myStepper.step(-stepsBackward);
        Serial.print("Indietreggiamento di ");
        Serial.print(stepsBackward);
        Serial.println(" passi");
        Serial.print("I passi totali fatti in avanti sono ");
        int totalStepsForward = stepsForward * pressionP1;
        Serial.println(totalStepsForward);
        Serial.print("I passi totali fatti all'indietro sono ");
        int totalStepsBackward = stepsBackward * pressionP2;
        Serial.println(totalStepsBackward);
      }
      break;
  }
}