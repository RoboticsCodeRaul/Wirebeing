#include <Ultrasonic.h>
#include <SoftwareSerial.h>

#define redPin A1
#define greenPin A3
#define bluePin A2

#define motorEsq1 6
#define motorEsq2 7
#define motorEsqVel 5

#define motorDir1 8
#define motorDir2 9
#define motorDirVel 10
#define TRIGGER_PIN 2
#define ECHO_PIN 3

Ultrasonic ultrasonic (TRIGGER_PIN, ECHO_PIN);

SoftwareSerial mySerial(A5, A4); // RX, TX
char opcao;
float cmMsec;
long randNum, microsec;

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(motorEsq1, OUTPUT);
  pinMode(motorEsq2, OUTPUT);
  pinMode(motorEsqVel, OUTPUT);

  pinMode(motorDir1, OUTPUT);
  pinMode(motorDir2, OUTPUT);
  pinMode(motorDirVel, OUTPUT);

  Serial.begin(9600);
  mySerial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(redPin, 255);
  analogWrite(greenPin, 222);
  analogWrite(bluePin, 246);

  if (mySerial.available() > 0) {
    opcao = mySerial.read();
    Serial.println(opcao);
    switch (opcao) {
      case 'F':
        setSpeedM(255, 255);
        moveF();
        break;
      case 'S':
        setSpeedM(0, 0);
        moveStop();
        break;
      case 'L':
        setSpeedM(0, 255);
        moveL();
        break;
      case 'R':
        setSpeedM(255, 0);
        moveR();
        break;
      case 'B':
        setSpeedM(255, 255);
        moveB();
        break;
      case 'X':
        do {
          autonomo();
          Serial.println("ola");
          opcao = mySerial.read();
        } while (opcao != 'F' && opcao != 'B' && opcao != 'L' && opcao && 'R');
        break;
    }
  }

}

void moveF () {

  digitalWrite(motorEsq1, HIGH);
  digitalWrite(motorEsq2, LOW);
  digitalWrite(motorDir1, HIGH);
  digitalWrite(motorDir2, LOW);

}

void moveB () {

  digitalWrite(motorEsq1, LOW);
  digitalWrite(motorEsq2, HIGH);
  digitalWrite(motorDir1, LOW);
  digitalWrite(motorDir2, HIGH);
}

void moveR () {

  digitalWrite(motorEsq1, HIGH);
  digitalWrite(motorEsq2, LOW);
  digitalWrite(motorDir1, LOW);
  digitalWrite(motorDir2, LOW);

}

void moveL () {

  digitalWrite(motorEsq1, LOW);
  digitalWrite(motorEsq2, LOW);
  digitalWrite(motorDir1, HIGH);
  digitalWrite(motorDir2, LOW);
}

void moveStop() {
  digitalWrite(motorEsq1, LOW);
  digitalWrite(motorEsq2, LOW);
  digitalWrite(motorDir1, LOW);
  digitalWrite(motorDir2, LOW);
}

void autonomo() {

  microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  Serial.println(cmMsec);

  moveF();
  setSpeedM(150, 150);

  if (cmMsec < 35) {
    moveStop();
    setSpeedM(0, 0);
    delay(500);
    randNum = random(0, 2);
    if (randNum == 0)
    {
      moveB();
      setSpeedM(150, 150);
      delay(1000);
      moveL();
      setSpeedM(0, 150);
      delay(900);

    } else {
      moveB();
      setSpeedM(150, 150);
      delay(1000);
      moveR();
      setSpeedM(150, 0);
      delay(900);
    }
  }
}

void setSpeedM(int speedl, int speedr) {
  analogWrite(motorEsqVel, speedl);
  analogWrite(motorDirVel, speedr);
}
