/* Demo Alessandro
 * 4^B-Automazione
 * Es.1 Stepper
 * Consegna 03.11.2020
 */
 
// inclusione della libreria AccelStepper
#include <AccelStepper.h>

// funzionamento:

// in fullstep  impostare 4

// in halfstemp impostare 8
#define FULLSTEP 4

// variabile massima velocita`
int max_speed;

// variabile accelerazione
int acc;

// variabile velocita` iniziale
int in_speed;

// variabile numero di passi da compiere
int n_steps;

// variabile degli stati 
int stato = 0;

// creazione dell'istanza della classe mioStepper
/*
   IN1 -> 8

   IN2 -> 9

   IN3 -> 10

   IN4 -> 11

*/
AccelStepper stepper(FULLSTEP, 8, 10, 9, 11);

void setup() {

   Serial.begin(9600); // inizializza il monitor seriale
   Serial.println("Benvenuto nel monitor seriale, imposta i valori dello stepper come richiesto."); // inserisce la frase nel monitor seriale
   Serial.println(""); // inserisce una riga vuota nel monitor seriale
   

   for(int i = 1; i>0; i++)
   {

      switch(stato)
      {
         case 0:
            Serial.println("imposta velocita` massima:");
            stato = 1;
            break;

         case 1:
            if (Serial.available()) 
            { 
               String a = Serial.readString();
               max_speed = a.toInt();
               Serial.print("velocita` massima =");
               Serial.print(max_speed);
               Serial.println("");
               stato = 2;
               Serial.println("imposta accelerazione:");
            }
            break;

         case 2:
            if (Serial.available()) 
            {
               String b = Serial.readString();
               acc = b.toInt();
               Serial.print("accelerazione = ");
               Serial.print(acc);
               Serial.println("");
               stato = 3;
               Serial.println("imposta velocita` iniziale:");
            }
            break;

         case 3:
            if (Serial.available()) 
            {
               String c = Serial.readString();
               in_speed = c.toInt();
               Serial.print("velocita` iniziale = ");
               Serial.print(in_speed);
               Serial.println("");
               stato = 4;
               Serial.println("imposta numero di passi da compiere:");
            }
            break;

         case 4:
            if (Serial.available()) 
            {
               String d = Serial.readString();
               n_steps = d.toInt();
               Serial.print("numero di passi =");
               Serial.print(n_steps);
               stato = 5;
            }
            break;

         case 5:  
            stepper.setMaxSpeed(max_speed);
            stepper.setAcceleration(acc);
            stepper.setSpeed(in_speed);
            stepper.moveTo(n_steps);
            stepper.run();
            stato = 6;
            break;

         case 6:
            rotazione();
            break;
      }
   }
}


void rotazione()
{
   for(int y=1; y>0; y++){
      if(stepper.distanceToGo()==0){
         stepper.moveTo(-stepper.currentPosition());
      }
      stepper.run();
   }
}

void loop() {}