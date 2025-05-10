#include <Servo.h>
int cambio = 2;
int ledA = 8;
int ledB = 5;

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

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    Servom1.attach(motor1);
    Servom2.attach(motor2);
    Servom3.attach(motor3);
    Servom4.attach(motor4);
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
