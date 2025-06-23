/*
  Demo Alessandro
  4^B - Automazione
  Compito per il 25.02.2021

  Esercizio numero 1:
  Sensore di temperatura digitale DS18B20 utilizzo in modalità singola:
  - Rilevare ogni 2 secondi 10 misurazioni, memorizzare questi valori in un Array;
  - Visualizzare la temperatura minima, media e massima ogni 10 secondi su un display 16×2 I2C;
  - Se la temperatura scende sotto il valore minimo o supera il valore massimo impostati viene emesso un allarme
  (messaggio su display, emissione di un suono, accensione di un LED rosso per il superamento del valore massimo, azzurro se la temperatura scende al di sotto del valore minimo impostato).
*/

// include le librerie di funzionamento del sensore e del display LCD
#include <OneWire.h>           //includi la libreria OneWire.h (sonda DS18B20)
#include <DallasTemperature.h> //includi la libreria DallasTemperature (sonda DS18B20)
#include <LiquidCrystal.h>     //includi la libreria LiquidCrystal (display)

// inizializzazione dei pin del display LCD 16x2
LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

// Pin Arduino a cui colleghiamo il pin DQ del sensore
#define ONE_WIRE_BUS 2

// variabili dei LED collegate ai pin di essi
int LEDTsup = 9;   // variabile del LED, collegato al pin 9 che si accende in caso venga superata la temperatura massima
int LEDTinf = 8;   // variabile del LED, collegato al pin 8 che si accende in caso la temperatura sia al di sotto della temperatura minima
int buzzerPin = 7; // variabile del buzzer, collegato al pin 7
int Tmax = 30;     //temperaratura massima impostata
int Tmin = 20;     //temperatura minima impostata

float Temp[10];       // variabile della temperatura, si fanno 10 misurazioni di essa
float TempMax = 0;    // variabile della temperatura massima
float TempMin = 1023; // variabile della temperatura minima
float media;          // variabile della media
int somma = 0;        // variabile di somma per la media

OneWire oneWire(ONE_WIRE_BUS);       // imposta la connessione OneWire
DallasTemperature sensore(&oneWire); // dichiarazione dell'oggetto sensore

void setup() {
  pinMode(LEDTsup, OUTPUT); // inizializzazione LED temperatura superiore come OUTPUT
  pinMode(LEDTinf, OUTPUT); // inizializzazione LED temperatura inferiore come OUTPUT
  pinMode(buzzerPin, OUTPUT); // inizializzazione buzzer come OUTPUT

  Serial.begin(9600);// inizializzazione della serial monitor
  sensore.begin();   // inizializzazione del sensore
  lcd.begin(16, 2);  // inizializzazione colonne e righe del display LCD 16x2
  // Stampa del messaggio di avvio
  Serial.println("Temperatura rilevata dal sensore DS18B20");//stampa i caratteri
  Serial.println("----------------------------------------");//stampa i caratteri
  digitalWrite(LEDTsup, LOW); // il LED é spento
  digitalWrite(LEDTinf, LOW); // il LED é spento
  noTone(buzzerPin);          // il buzzer é spento
  delay(1000);
}

void loop() {
  sensore.requestTemperatures(); // richiesta lettura temperatura

  // valore massimo della temperatura
  for (int i = 0; i < 10; i++)  // ciclo for per cui viene fatta la comparazione tra le temperature
  {
    sensore.requestTemperatures();        // richiesta lettura temperatura
    Temp[i] = sensore.getTempCByIndex(0); //l'array delle temperature ha i valori di Celsius rilevati dal sensore
    if (Temp[i] > TempMax)  // se il valore di i nella temperatura é maggiore della temperatura massima
    {
      TempMax = Temp[i];    // la temperatura massima é pari al valore di i della sequenza voti
      lcd.setCursor(0, 0);  // posizionare il cursore su 0,0
      lcd.print("Temp");    // stampa sul display i caratteri
      lcd.setCursor(0, 1);  // posizionare il cursore su 0,1
      lcd.print(Temp[i]);   // stampa sul display la temperatura
      lcd.clear();          // pulisci il display
    }
  }

  // valore minimo della temperatura
  for (int i = 0; i < 10; i++)  // ciclo for per cui viene fatta la comparazione tra le temperature
  {
    sensore.requestTemperatures();        // richiesta lettura temperatura
    Temp[i] = sensore.getTempCByIndex(0);//l'array delle temperature ha i valori di Celsius rilevati dal sensore
    if (Temp[i] < TempMin)  // se il valore di i nella temperatura é maggiore della temperatura massima
    {
      TempMin = Temp[i];    // la temperatura minima é pari al valore di i della temperatura
      lcd.setCursor(0, 0);  // posizionare il cursore su 0,0
      lcd.print("TempMin"); // stampa sul display la frase
      lcd.setCursor(0, 1);  // posizionare il cursore su 0,1
      lcd.print(TempMin);   // stampa sul display la temperatura minima
      lcd.clear();          // pulisci il display
    }
  }

  // valore medio della temperatura
  for (int i = 0; i < 10; i++) {
    Temp[i] = sensore.getTempCByIndex(0);//l'array delle temperature ha i valori di Celsius rilevati dal sensore
    somma = somma + Temp[i]; //la variabile somma è uguale alla somma di valore iniziale 0 + l'array che contiene tutte le temperature
    media = somma / 10;      //la media è uguale alla somma dei 10 valori diviso 10
    lcd.setCursor(0, 0);  // posizionare il cursore su 0,0
    lcd.print("Media");   // stampa sul display la frase
    lcd.setCursor(0, 1);  // posizionare il cursore su 0,1
    lcd.print(media);     // stampa sul display la media della temperatura
    lcd.clear();          // pulisci il display
  }
  //condizione di allarme superiore
  if (sensore.getTempCByIndex(0) > Tmax) {//se la media delle temperature è maggiore alla TempMax esegui
    digitalWrite(LEDTinf, LOW);//mantieni spento il led di allarme inferiore
    digitalWrite(LEDTsup , HIGH);//accendi il led di allarme superiore
    tone(buzzerPin, 660);//genera un'onda quadra di frequenza = 660Hz dul pin del buzzer
    delay(500);//attendi 500ms
    noTone(buzzerPin);//interrompi l'onda quadra sul pin del buzzer
  }

  //condizione di allarme inferiore
  if (sensore.getTempCByIndex(0) < Tmin) {//se la media delle temperature è minore alla TempMin esegui
    digitalWrite(LEDTinf, HIGH);//accendi il led di allarme inferiore
    digitalWrite(LEDTsup , LOW);//mantieni spento il led di allarme superiore
    tone(buzzerPin, 660);//genera un'onda quadra di frequenza = 660Hz dul pin del buzzer
    delay(300);//attendi 500ms
    noTone(buzzerPin);//interrompi l'onda quadra sul pin del buzzer
  }
}
