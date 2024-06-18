#include <SoftwareSerial.h>
#include <Servo.h>

#define boMotor01 10
#define boMotor02 11
#define boMotor03 12
#define boMotor04 13

Servo servo01;
Servo servo02;
Servo servo03;

SoftwareSerial myBluetooth(2, 3);  // RX, TX

int servo1Pos, servo2Pos, servo3Pos;

void setup() {
  servo01.attach(5);
  servo02.attach(6);
  servo03.attach(7);
  pinMode(boMotor01, OUTPUT);
  pinMode(boMotor02, OUTPUT);
  pinMode(boMotor03, OUTPUT);
  pinMode(boMotor04, OUTPUT);

  myBluetooth.begin(9600);
  Serial.begin(9600);

  servo1Pos = 90;
  servo01.write(servo1Pos);
  servo2Pos = 0;
  servo02.write(servo2Pos);
  servo3Pos = 0;
  servo03.write(servo3Pos);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(myBluetooth.available() > 0){
    char command = myBluetooth.read();
    Serial.println(command);
    
    if(command >= 'A' && command <= 'Z'){
      controlCar(command);
    }else if(command >= 'a' && command <= 'z'){
      controlPickAndPlace(command);
    }
  }
}

void controlCar(char command) {
  switch (command) {
    case 'F':
      moveForward();
      break;
    case 'B':
      moveBackward();
      break;
    case 'L':
      turnLeft();
      break;
    case 'R':
      turnRight();
      break;
    case 'N':
      stopCar();
      break;
  }
}

void controlPickAndPlace(char command) {
  switch (command) {
    case 'l': 
      servo01.write(180); 
      break;
    case 'r':
      servo01.write(0);
      break;
    case 'u': 
      servo02.write(0);
      break;
    case 'd': 
      servo02.write(45);
      break;
    case 'o': 
      servo03.write(90);
      break;
    case 'c': 
      servo03.write(0);
      break;
    default:
      servo01.write(90);
      servo02.write(0); 
      servo03.write(0); 
      break;
  }
}

void moveForward() {
  digitalWrite(boMotor01, HIGH);
  digitalWrite(boMotor02, LOW);
  digitalWrite(boMotor03, HIGH);
  digitalWrite(boMotor04, LOW);
}
void moveBackward() {
  digitalWrite(boMotor01, LOW);
  digitalWrite(boMotor02, HIGH);
  digitalWrite(boMotor03, LOW);
  digitalWrite(boMotor04, HIGH);
}

void turnLeft() {
  digitalWrite(boMotor01, LOW);
  digitalWrite(boMotor02, HIGH);
  digitalWrite(boMotor03, HIGH);
  digitalWrite(boMotor04, LOW);
}

void turnRight() {
  digitalWrite(boMotor01, HIGH);
  digitalWrite(boMotor02, LOW);
  digitalWrite(boMotor03, LOW);
  digitalWrite(boMotor04, HIGH);
}

void stopCar() {
  digitalWrite(boMotor01, LOW);
  digitalWrite(boMotor02, LOW);
  digitalWrite(boMotor03, LOW);
  digitalWrite(boMotor04, LOW);
}
   

