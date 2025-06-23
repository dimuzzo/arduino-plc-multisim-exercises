/*
  Demo Alessandro
  5^B - Automazione
  Compito per il 03.05.2022
  Es. 25.7:
  Costruire un sistema costituito da 3 pulsanti che controllano la rotazione del motore:
  P1: numero passi in avanti
  P2: numero di passi indietro
  P3: avvio
  - Ogni pressione di P1 equivale ad un giro del motore in avanti
  - Ogni pressione di P2 equivale ad un giro del motore in indietro
   All'avvio del sistema bisognerà impostare il numero di giri in avanti e
   indietro con i pulsanti P1 e P2. Il pulsante P3 permetterà di avviare la sequenza.
*/
#include <Stepper.h>
const int stepsPerRevolution = 1024;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
int P1 = 4;
int P2 = 3;
int P3 = 2;
int pressionP1 = 0;
int pressionP2 = 0;
int state = 0;
int totalSteps = totalStepsForward + totalStepsBackward;

void setup() {
  myStepper.setSpeed(15);
  Serial.begin(9600);
  pinMode(P1, INPUT);
  pinMode(P2, INPUT);
  pinMode(P3, INPUT);
  Serial.println("Premere i pulsanti P1 e P2");
}

void loop() {
  switch (state) {
    case 0:
      if (digitalRead(P1) == HIGH) {
        pressionP1++;
        Serial.print("I passi totali da fare in avanti sono ");
        int totalStepsForward = stepsPerRevolution * pressionP1;
        Serial.println(totalStepsForward);
        state = 1;
      }
      break;
    case 1:
      if (digitalRead(P2) == HIGH) {
        pressionP2++;
        Serial.print("I passi totali da fare all'indietro sono ");
        int totalStepsBackward = -stepsPerRevolution * pressionP2;
        Serial.println(totalStepsBackward);
        Serial.println("Premere il pulsante P3 per avviare il motore");
        state = 2;
      }
      break;
    case 2:
      if (digitalRead(P3) == HIGH) {
        Serial.print("I passi totali da fare sono ");
        Serial.println(totalSteps);
        myStepper.step(totalSteps);
      }
      break;
  }
}
