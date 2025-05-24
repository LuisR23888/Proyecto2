#include <Servo.h>
int cambio = 13;
int ledA = 2;
int ledB = 3;

Servo Servom1;
int pot1 = A0;
int res1 = 0;
int motor1 = 11;
int mp1 = 0;

Servo Servom2;
int pot2 = A1;
int res2 = 0;
int motor2 = 10;
int mp2 = 0;

Servo Servom3;
int pot3 = A2;
int res3 = 0;
int motor3 = 9;
int mp3 = 0;

Servo Servom4;
int pot4 = A3;
int res4 = 0;
int motor4 = 6;
int mp4 = 0;

int md1 = 12;
int md2 = 8;
int md3 = 7;
int md4 = 4;
int av = A4;
int ret = A5;

int cont = 0;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    Servom1.attach(motor1);
    Servom2.attach(motor2);
    Servom3.attach(motor3);
    Servom4.attach(motor4);
    pinMode(ledA, OUTPUT);
    pinMode(ledB, OUTPUT);
    pinMode(md1, OUTPUT);
    pinMode(md2, OUTPUT);
    pinMode(md3, OUTPUT);
    pinMode(md4, OUTPUT);
    pinMode(av, INPUT);
    pinMode(ret, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    bool modo = digitalRead(cambio);

    if (modo == HIGH) {
        // Modo manual
        digitalWrite(ledA, HIGH);
        digitalWrite(ledB, LOW);

        cont=0;
        
        res1 = analogRead(pot1);
        mp1 = map(res1, 0, 1023, 0, 180);
        Servom1.write(mp1);

        res2 = analogRead(pot2);
        mp2 = map(res2, 0, 1023, 0, 180);
        Servom2.write(mp2);

        res3 = analogRead(pot3);
        mp3 = map(res3, 0, 1023, 0, 180);
        Servom3.write(mp3);

        res4 = analogRead(pot4);
        mp4 = map(res4, 0, 1023, 0, 180);
        Servom4.write(mp4);
    }
    else {
      // Modo automático con contador
      digitalWrite(ledB, HIGH);
      digitalWrite(ledA, LOW);

      // Transición con debounce
        if (digitalRead(av) == HIGH && digitalRead(ret) == LOW) {
            delay(10);  // Espera inicial para debounce
            if (digitalRead(av) == HIGH) {  // Verificación después del delay
                cont = (cont + 1);
                // Reiniciar contador si es mayor a 5
                if (cont > 6) {
                    cont = 0;
                    }
            while (digitalRead(av) == HIGH) {}  // Espera a que se suelte el botón
            delay(50);  // Debounce final
            }
        } 
        else if (digitalRead(ret) == HIGH && digitalRead(av) == LOW) {
            delay(10);
            if (digitalRead(ret) == HIGH) {
                cont = (cont - 1);
            // Reiniciar contador si es menor a 0
                if (cont < 0) {
                    cont = 0;
                    }
            while (digitalRead(ret) == HIGH) {}
            delay(50);
        }
    }
      
      switch (cont) {
            case 0:
                Servom1.write(0);
                Servom2.write(68);
                Servom3.write(127);
                Servom4.write(180);
                
                digitalWrite(md1, LOW);
                digitalWrite(md2, LOW);
                digitalWrite(md3, LOW);
                digitalWrite(md4, LOW);

                break;

            case 1:
                Servom1.write(0);
                Servom2.write(148);
                Servom3.write(94);
                Servom4.write(134);
                
                digitalWrite(md1, HIGH);
                digitalWrite(md2, LOW);
                digitalWrite(md3, LOW);
                digitalWrite(md4, LOW);
                break;

            case 2:
                Servom1.write(0);
                Servom2.write(148);
                Servom3.write(94);
                Servom4.write(180);
              
                digitalWrite(md1, LOW);
                digitalWrite(md2, HIGH);
                digitalWrite(md3, LOW);
                digitalWrite(md4, LOW);
                break;

            case 3:
                Servom1.write(0);
                Servom2.write(68);
                Servom3.write(127);
                Servom4.write(180);
              
                digitalWrite(md1, LOW);
                digitalWrite(md2, LOW);
                digitalWrite(md3, HIGH);
                digitalWrite(md4, LOW);
                break;

            case 4:
                Servom1.write(180);
                Servom2.write(96);
                Servom3.write(156);
                Servom4.write(134);
              
                digitalWrite(md1, LOW);
                digitalWrite(md2, LOW);
                digitalWrite(md3, LOW);
                digitalWrite(md4, HIGH);
                break;

            case 5:
                Servom1.write(180);
                Servom2.write(96);
                Servom3.write(156);
                Servom4.write(134);
              
                digitalWrite(md1, HIGH);
                digitalWrite(md2, LOW);
                digitalWrite(md3, LOW);
                digitalWrite(md4, HIGH);
                break;

            case 6:
                Servom1.write(90);
                Servom2.write(73);
                Servom3.write(102);
                Servom4.write(180);
              
                digitalWrite(md1, HIGH);
                digitalWrite(md2, HIGH);
                digitalWrite(md3, LOW);
                digitalWrite(md4, HIGH);
                break;
    }
  }
}
