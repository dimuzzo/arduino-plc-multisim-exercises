/*
 Demo Alessandro
 4^B - Automazione
 LED RGB es.3:
 Utilizzando la Serial Monitor come unico strumento per inviare comandi ad Arduino, 
 realizzare un menù di selezione che permette di impostare le funzionalità dell’esercizio 01 e dell’esercizio 03.
 Compito per il 07.01.2021
*/

// tempo di dissolvenza tra i colori
#define tempoRitardo 10
// per stampare una sola volta il messaggio sulla Serial Monitor
bool abilitaMessaggio = 0;
const byte PinRosso = 11;     // variabile in byte costante collegata al pin rosso
const byte PinBlu = 10;       // variabile in byte costante collegata al pin blu
const byte PinVerde = 9;      // variabile in byte costante collegata al pin verde
int stato;                    // variabile dello stato

// definizione di variabili
int valoreRosso;
int valoreVerde;
int valoreBlu;

void setup()
{
 Serial.begin(9600);           // inizializza il monitor seriale a 9600 baud
 pinMode(PinRosso, OUTPUT);    // inizializza il pin rosso come output
 pinMode(PinBlu, OUTPUT);      // inizializza il pin blu come output
 pinMode(PinVerde, OUTPUT);    // inizializza il pin verde come output
 stato = 0;                    // il numero di stato attuale é lo 0
}

void loop()
{
  stato = Serial.read();
  switch(stato){
    case 'a':                          // stato a
 // Impostazioni variabili per avere partire con LED:
 // ROSSO accesso, VERDE spento, BLU spento.
     valoreRosso = 255;
     valoreVerde = 0;
     valoreBlu = 0;
// partendo dal ROSSO si sfuma al VERDE pieno quando i = 255
     for (int i = 0; i < 255; i += 1){
      valoreRosso -= 1;
      valoreVerde += 1;
// L'intensità del ROSSO viene diminuita ad ogni ciclo, mentre
// l'intensità del VERDE viene aumentata ad ogni ciclo
      analogWrite(PinRosso, valoreRosso);
      analogWrite(PinVerde, valoreVerde);
      delay(tempoRitardo);
    }
// Impostazioni variabili per avere partire con LED:
// ROSSO spento, VERDE acceso, BLU spento.
      valoreRosso = 0;
      valoreVerde = 255;
      valoreBlu = 0;
// partendo dal VERDE si sfuma al BLU pieno quando i = 255
    for (int i = 0; i < 255; i += 1){
      valoreVerde -= 1;
      valoreBlu += 1;
// L'intensità del VERDE viene diminuita ad ogni ciclo, mentre
// l'intensità del BLU viene aumentata ad ogni ciclo
      analogWrite(PinVerde, valoreVerde);
      analogWrite(PinBlu, valoreBlu);
      delay(tempoRitardo);
    }
// Impostazioni variabili per avere partire con LED:
// ROSSO spento, VERDE spento, BLU acceso.
      valoreRosso = 0;
      valoreVerde = 0;
      valoreBlu = 255;
// partendo dal BLU si sfuma al ROSSO pieno quando i = 255
    for (int i = 0; i < 255; i += 1){
      valoreBlu -= 1;
      valoreRosso += 1;
// L'intensità del BLU viene diminuita ad ogni ciclo, mentre
// l'intensità del ROSSO viene aumentata ad ogni ciclo
      analogWrite(PinBlu, valoreBlu);
      analogWrite(PinRosso, valoreRosso);
      delay(tempoRitardo);
    }
      Serial.print("stato numero:"); // stampa la frase
      Serial.println(stato);         // stampa il valore dello stato
    break;                           // lo stato a viene chiuso
    
    case 'b':                        // stato 1
// consente di visualizzare sulla Serial Monitor
// una sola stampa delle stringa
  if (abilitaMessaggio == 0) {
// ritardo che evita la doppia stampa del messaggio
    delay(200);
    Serial.print("Inserisci i valori R G B (es. 125, 50, 255): ");
    abilitaMessaggio = 1;
  }
   if (Serial.available()) {
// memorizzazione dei colori nelle variabili
    int rosso = Serial.parseInt();
    int verde = Serial.parseInt();
    int blu = Serial.parseInt();
    Serial.print(rosso);
    Serial.print(", ");
    Serial.print(verde);
    Serial.print(", ");
    Serial.println(blu);
    Serial.println("-------------------------------------------");
// impostazione del PWM
    analogWrite(PinRosso, rosso);
    analogWrite(PinVerde, verde);
    analogWrite(PinBlu, blu);
// abilita alla stampa di una nuova stringa:
// "Inserisci il ritardo in millisecondi: "
    abilitaMessaggio = 0;
  }
      Serial.print("stato numero:"); // stampa la frase
      Serial.println(stato);         // stampa il valore dello stato
    break;                           // lo stato b viene chiuso
    }
}
