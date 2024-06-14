#include <SoftwareSerial.h>
#include<Wire.h>
#include <Adafruit_PWMServoDriver.h>

SoftwareSerial myBluetooth(2, 3);  // RX, TX

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

int angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   return pulse;
}

char command = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  myBluetooth.begin(9600);
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(myBluetooth.available() > 0){
    command = myBluetooth.read();
    Serial.println(command);
    if(command ==  'r'){
      pwm.setPWM(0, 0, angleToPulse(180));
    }else if(command == 'l'){
      pwm.setPWM(0, 0, angleToPulse(0));
    }
    else if(command == 'U'){
      pwm.setPWM(1, 0, angleToPulse(0));
    }
    else if(command == 'D'){
      pwm.setPWM(1, 0, angleToPulse(30));
    }
    else if(command == 'O'){
      pwm.setPWM(1, 0, angleToPulse(0));
    }
    else if(command == 'C'){
      pwm.setPWM(1, 0, angleToPulse(30));
    }
    else if(command == 'F'){
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
    }
     else if(command == 'B'){
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
    }
     else if(command == 'R'){
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
    }
     else if(command == 'L'){
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
    }
    else{
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
    }
  }
}
