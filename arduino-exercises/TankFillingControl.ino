/*
  Sistema di controllo di un forno industriale
  Alessandro Demo
  4^B - AUTOMAZIONE
  10/12/2020
*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);//definisci i bus dati per comunicare con i pin del display lcd

int LEDTMax = 10;     
int LEDTMin = 9;      
int LEDAvvio = 8;     
int buzzer = 13;       
int PulsanteAvvio = 3;
int PulsanteErrore = 2;
int misure[10];
float media = 0.0;
int trimmerval;          
int trimmervalprecedente; 
int valore;        
float temperatura; 
int TMax;
int TMin = TMax - 2;
int tempolcd;              
unsigned long temposec;
int errore;
int stato = 0;

void setup() 
{
  lcd.begin(16, 2);
  Serial.begin(9600); 
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(3, INPUT);
  pinMode(2, INPUT);
  analogReference(INTERNAL);
}

void loop() 
{
  switch (stato) 
  {
    case 0:
      SelezioneTemperatura();
      break;

    case 1:
      SelezioneTempo();
      break;

    case 2:
      FornoInFunzione();
      break;

    case 3:
      Errore();
      break;
  }
}

void SelezioneTemperatura() 
{
  lcd.setCursor(0, 0);
  lcd.print("Impostare con");
  lcd.setCursor(0, 1);
  lcd.print("il trimmer A0");
  delay(1000);
  trimmerval = analogRead(A0);
  TMax = map(trimmerval, 0, 1023, 0, 300);
  Serial.println(TMax);
  Serial.println(TMin);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temperatura Max:");
  lcd.setCursor(0, 1);
  lcd.print(TMax);
  lcd.setCursor(5, 1);
  lcd.print("Celsius");

  if (digitalRead(PulsanteAvvio) == 1) 
  {
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Temperatura Min:");
    lcd.setCursor(0, 1);
    lcd.print(TMin);
    lcd.setCursor(3, 1);
    lcd.setCursor(5, 1);
    lcd.print("Celsius");
    delay(1000);
    stato = 1;
  }
  else 
  {
    stato = 0;
  }
}

void SelezioneTempo() 
{
  trimmerval = analogRead(A0);
  tempolcd = map(trimmerval, 0, 1023, 0, 60);
  temposec = tempolcd * 1000;
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Imposta durata:");
  lcd.setCursor(0, 1);
  lcd.print(tempolcd);
  lcd.setCursor(3, 1);
  lcd.print("secondi");
  delay(200);
  if (digitalRead(PulsanteAvvio) == 1) 
  {
    stato = 2;
  }
  else 
  {
    stato = 1;
  }
}

void FornoInFunzione() 
{
  digitalWrite(8, HIGH);
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  MisurazioneTemperatura();
  for (int i = tempolcd; i >= 0; i--) 
  {
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Tempo rimenante:");
    lcd.setCursor(0, 1);
    lcd.print(i);
    lcd.setCursor(3, 1);
    lcd.print("secondi");
    delay(1000);
    if (digitalRead(PulsanteErrore) == 1) 
    {
      errore = 0;
      tempolcd = 0;
      i = 0;
      stato = 3;
    }
    if (media > TMax) 
    {
      errore = 1;
      tempolcd = 0;
      i = 0;
      stato = 3;
    }

    if (media < TMin) 
    {
      errore = 2;
      tempolcd = 0;
      i = 0;
      stato = 3;
    }
  }
}

void MisurazioneTemperatura() 
{
  for (int i = 0; i < 10; i++) 
  {
    misure[i] = analogRead(A1);
  }
  for (int i = 0; i < 10; i++) 
  {
    media += misure[i];
  }
  media = media / 10.0;
  Serial.println(media);
}

lcd.begin(16, 2);
lcd.setCursor(0, 0);
lcd.print("Fusione");
lcd.setCursor(0, 1);
//lcd.print("completata");
delay(1000);
trimmervalprecedente = analogRead(A0);
if (trimmervalprecedente != trimmerval) 
{
  stato = 0;
}

void Errore() 
{
  lcd.clear();
  lcd.begin(16, 2);
  switch (errore) 
  {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("CHIUDERE");
      lcd.setCursor(0, 1);
      lcd.print("IL FORNO!");
      digitalWrite(13, HIGH);
      delay(1000);
      digitalWrite(13, LOW);
      int stato = 0;
      break;

    case 1:
      lcd.setCursor(0, 0);
      lcd.print("Temperatura Max");
      lcd.setCursor(0, 1);
      lcd.print("superata");
      digitalWrite(13, HIGH);
      delay(1000);
      digitalWrite(13, LOW);
      int stato = 0;
      break;

    case 2:
      lcd.setCursor(0, 0);
      lcd.print("Temperatura Min");
      lcd.setCursor(0, 1);
      lcd.print("superata");
      digitalWrite(13, HIGH);
      delay(1000);
      digitalWrite(13, LOW);
      int stato = 0;
      break;
  }
}