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
int t1=0;
int t2=0;
int t3=0;
int t4=0;
int a1=0;
int a2=0;
int a3=0;
int a4=0;
//Función para encender leds
void leds(bool t1, bool t2, bool t3, bool t4){
  digitalWrite(md1,t1);
  digitalWrite(md2,t2);
  digitalWrite(md3,t3);
  digitalWrite(md4,t4);
}
//Función para movimiento de servos segun grado 
void servos(int a1, int a2, int a3, int a4){
    Servom1.write(a1);
    Servom2.write(a2);
    Servom3.write(a3);
    Servom4.write(a4);
}


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
    leds(t1, t2, t3, t5);
    servos(a1, a2, a3, a4);
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
                leds(0,0,0,0);
                servos(0,68,127,180);
                break;

            case 1:
                leds(1,0,0,0);
                servos(0,148,94,134);
                break;

            case 2:
                leds(0,1,0,0);
                servos(0,148,94,180);              
                break;

            case 3:
                leds(0,0,1,0);
                servos(0,68,127,180);              
                break;

            case 4:
                leds(0,0,0,1);
                servos(180,96,156,134);
                break;

            case 5:
                leds(1,0,0,1);
                servos(180,96,156,134);
                break;

            case 6:
                leds(1,1,0,1);
                servos(90,73,102,180);
                break;
    }
  }
}
