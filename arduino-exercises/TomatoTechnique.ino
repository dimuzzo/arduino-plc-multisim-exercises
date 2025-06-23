/*
 * Demo Alessandro
 * 4B - Automazione
 * Compito per il 17.11.2020
 * Misuratore con pomodoro technique
 */
#define Lavoro 0
#define PausaBreve 1
#define PausaLunga 2

int stato = Lavoro;             // variabile di stato iniziale
int counter = 0;                // variabile di conteggio

const int buttonPin = 8;        // pin a cui é collegato il pulsante
const int buzzerPin = 13;       // pin a cui é collegato il buzzer
const int PeriodoLavoroLED = 7; // pin a cui é collegato il LED del periodo di lavoro
const int PausaBreveLED = 6;    // pin a cui é collegato il LED del periodo di pausa breve
const int PausaLungaLED  =  5;  // pin a cui é collegato il LED del periodo di pausa lunga

// pin a cui sono collegati i LED pomodoro
const int pom1LED =   12;
const int pom2LED =   11;
const int pom3LED =   10;
const int pom4LED =   9;

void setup() {
  pinMode(buttonPin, INPUT);         // pulsante inizializzato come input
  pinMode(buzzerPin, OUTPUT);        // buzzer inizializzato come output
  pinMode(PeriodoLavoroLED, OUTPUT); // LED del periodo di lavoro inizializzato come output
  pinMode(PausaBreveLED, OUTPUT);    // LED del periodo di pausa breve inizializzato come output
  pinMode(PausaLungaLED, OUTPUT);    // LED del periodo di pausa lunga inizializzato come output

  // LED pomodoro inizializzati come output
  pinMode(pom1LED, OUTPUT);
  pinMode(pom2LED, OUTPUT);
  pinMode(pom3LED, OUTPUT);
  pinMode(pom4LED, OUTPUT);

  // premere il pulsante per iniziare il ciclo di lavoro e pause
  while (digitalRead(buttonPin) == HIGH);
}

void loop() {
  switch (stato) {       // se lo stato ha:
    case 0:              // valore 0
      Lavorare();        // eseguire la funzione Lavorare
      break;             // interrompere la funzione
 
    case 1:              // valore 1
      FarePausaBreve();  // eguire la funzione FarePausaBreve
      break;             // interrompere la funzione

    case 2:              // valore 2
      FarePausaLunga();  // eguire la funzione FarePausaLunga
      break;             // interrompere la funzione
  }
}

void Lavorare() {
  statoPomodoro();     // leggere gli stati dei pomodori

  digitalWrite(PeriodoLavoroLED, HIGH); // il LED del periodo di lavoro é acceso
  digitalWrite(PausaBreveLED, LOW);     // il LED del periodo di pausa breve é spento
  digitalWrite(PausaLungaLED, LOW);     // il LED del periodo di pausa lunga é spento

  delay(25000);        // durata di un pomodoro pari a 25 secondi(si possono impostare anche 25 minuti reali)
  counter++;           // aggiungere 1 alla variabile di conteggio dopo un pomodoro

  // se il conteggio é minore o uguale a 3
  if (counter <= 3) {
    stato = PausaBreve;      // passare allo stato di pausa breve
  }

  // se il conteggio é uguale a 4
  if (counter == 4) {
    stato = PausaLunga;      // passare allo stato di pausa lunga
  }
}

void FarePausaBreve() {
  statoPomodoro();     // leggere gli stati dei pomodori

  digitalWrite(PeriodoLavoroLED, LOW); // il LED del periodo di lavoro é spento
  digitalWrite(PausaBreveLED, HIGH);   // il LED del periodo di pausa breve é acceso
  digitalWrite(PausaLungaLED, LOW);    // il LED del periodo di pausa lunga é spento
  digitalWrite(buzzerPin, HIGH);       // il buzzer emette un suono accendendosi
  delay(1000);                         // aspettare un secondo
  digitalWrite(buzzerPin, LOW);        // il buzzer si spegne

  delay(5000);         // durata della pausa breve  pari a 5 secondi(si possono impostare anche 5 minuti reali)
  digitalWrite(buzzerPin, HIGH);       // il buzzer emette un suono accendendosi
  delay(1000);                         // aspettare un secondo
  digitalWrite(buzzerPin, LOW);        // il buzzer si spegne

  if (counter <= 3) {        // se il conteggio é ancora minore o uguale a 3
    stato = Lavoro;          // passare allo stato di lavoro
  }
}

void FarePausaLunga() {
  statoPomodoro();     // leggere gli stati dei pomodori

  digitalWrite(PeriodoLavoroLED, LOW);  // il LED del periodo di lavoro é spento
  digitalWrite(PausaBreveLED, LOW);     // il LED del periodo di pausa breve é spento
  digitalWrite(PausaLungaLED, HIGH);    // il LED del periodo di pausa lunga é acceso
  digitalWrite(buzzerPin, HIGH);        // il buzzer emette un suono accendendosi
  delay(1000);                          // aspettare un secondo
  digitalWrite(buzzerPin, LOW);         // il buzzer si spegne

  delay(20000);         // durata della pausa lunga pari a 20 secondi(si possono impostare anche 20 minuti reali)
  digitalWrite(buzzerPin, HIGH);       // il buzzer emette un suono accendendosi
  delay(1000);                         // aspettare un secondo
  digitalWrite(buzzerPin, LOW);        // il buzzer si spegne

  // si accendono tutti e 7 i led per indicare la fine di un ciclo di lavoro e pause
  digitalWrite(PeriodoLavoroLED, HIGH);
  digitalWrite(PausaBreveLED, HIGH);
  digitalWrite(PausaLungaLED, HIGH);
  delay(2000);       // aspettare 2 secondi

  // i 7 led si spengono per cominciare un nuovo ciclo di lavoro e pause
  digitalWrite(PeriodoLavoroLED, LOW);
  digitalWrite(PausaBreveLED, LOW);
  digitalWrite(PausaLungaLED, LOW);
  digitalWrite(pom1LED, LOW);
  digitalWrite(pom2LED, LOW);
  digitalWrite(pom3LED, LOW);
  digitalWrite(pom4LED, LOW);

  // premere nuovamente il pulsante se si vuole inizare un nuovo ciclo
  while (digitalRead(buttonPin) == HIGH);

  // resettare tutte le impostazioni da zero
  counter = 0;
  stato = Lavoro;

}

void statoPomodoro() {
  if (counter == 0) {             // se il conteggio é uguale a 0
    // tutti e 4 i LED pomodoro sono spenti
    digitalWrite(pom1LED, LOW);   
    digitalWrite(pom2LED, LOW);   
    digitalWrite(pom3LED, LOW);   
    digitalWrite(pom4LED, LOW);   
  }

  if (counter == 1) {             // se il conteggio é uguale a 1
    digitalWrite(pom1LED, HIGH);  // solo il LED pomodoro 1 é acceso
  }

  if (counter == 2) {             // se il conteggio é uguale a 2
    digitalWrite(pom1LED, HIGH);  // il LED pomodoro 1 é acceso
    digitalWrite(pom2LED, HIGH);  // il LED pomodoro 2 é acceso
  }

  if (counter == 3) {             // se il conteggio é uguale a 3
    digitalWrite(pom1LED, HIGH);  // il LED pomodoro 1 é acceso
    digitalWrite(pom2LED, HIGH);  // il LED pomodoro 2 é acceso
    digitalWrite(pom3LED, HIGH);  // il LED pomodoro 3 é acceso
  }

  if (counter == 4) {             // se il conteggio é uguale a 4
    // tutti e 4 i LED pomodoro sono accesi
    digitalWrite(pom1LED, HIGH);  
    digitalWrite(pom2LED, HIGH);  
    digitalWrite(pom3LED, HIGH);  
    digitalWrite(pom4LED, HIGH);  
  }
}