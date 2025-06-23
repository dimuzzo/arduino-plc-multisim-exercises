int A = 0;
int B = 0;
int C = 0;
int stato = 0;

void setup() {
  Serial.begin(9600);
  Serial.print("Digita il valore di A: ");
}

void loop() {
  if(Serial.available() > 0){
    switch(stato){
      case 0:
        A = Serial.parseInt();
        Serial.println(A, DEC);
        Serial.print("Digita il valore di B: ");
        stato = 1;
        break;
          
      case 1:
        B = Serial.parseInt();
        Serial.println(B, DEC);
        Serial.print("Il valore di C e`: ");
        C = A + B;
        stato = 2;
        break;
      
      case 2:
        Serial.println(C, DEC);
        stato = 0;
        break;
    }
  }
}