#include <Ultrasonic.h>

Ultrasonic leftSensor(12, 10, 10000UL);
Ultrasonic frontSensor(A5, A4, 10000UL);

#define L_MOTOR_ENABLE 6
#define R_MOTOR_ENABLE 5
#define R_MOTOR_1 7
#define R_MOTOR_2 8
#define L_MOTOR_1 9
#define L_MOTOR_2 11

//Motor speed range
#define MAX_MOTOR_SPEED 255
#define MIN_MOTOR_SPEED 130

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(L_MOTOR_1, OUTPUT);
  pinMode(L_MOTOR_2, OUTPUT);
  pinMode(R_MOTOR_1, OUTPUT);
  pinMode(R_MOTOR_2, OUTPUT);
  pinMode(L_MOTOR_ENABLE, OUTPUT);
  pinMode(R_MOTOR_ENABLE, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int distanceLeftFront = frontSensor.read();
  int distanceLeftLeft = leftSensor.read();
  int currentLeftSpeed = MIN_MOTOR_SPEED+20;
  int currentRightSpeed = MIN_MOTOR_SPEED+20;
  //Serial.println("Distance Left Front:" + distanceLeftFront);
  //Serial.println("Distance Left Left:" + (String)distanceLeftLeft);
  
  //Left range is 20 - 25

  //If Front Sensor Distance < 20 (Straight into wall)
  //  Spin Right until Left Sensor is within 20 - 40 range
  //Else
  //  Continue tracking wall
  
  if(distanceLeftFront < 20){
    currentLeftSpeed = MIN_MOTOR_SPEED;
    currentRightSpeed = -MIN_MOTOR_SPEED;
    Serial.println("Spinning right");
  }
  else if(distanceLeftLeft > 40){
    currentLeftSpeed -= 15;
    currentRightSpeed += 15;
    Serial.println("I'm going towards the wall on my left");
  }
  else if(distanceLeftLeft < 20) {
    currentLeftSpeed += 15;
    currentRightSpeed -= 15;
    Serial.println("I'm going away from the wall on my left");
  }
    
//  if(distanceLeftFront < 15){
//    currentLeftSpeed = 0;
//    currentRightSpeed = 0;
//    Serial.println("Heading straight into a wall. I want to spin right");
//  }
//  else { 
//    currentLeftSpeed = MIN_MOTOR_SPEED;
//    currentRightSpeed = MIN_MOTOR_SPEED + 2;
//  }
//    else if(distanceLeftLeft > 40){
//      currentLeftSpeed -= 15;
//      currentRightSpeed += 15;
//      Serial.println("I'm going towards the wall on my left");
//    }
//    else if(distanceLeftLeft < 20) {
//      currentLeftSpeed += 15;
//      currentRightSpeed -= 15;
//      Serial.println("I'm going away from the wall on my left");
//    }
//    else {
//      currentLeftSpeed = MIN_MOTOR_SPEED + 20;
//      currentRightSpeed = MIN_MOTOR_SPEED + 17;
//      Serial.println("Just right");
//    }
//  }

  driveLeftMotor(currentLeftSpeed);
  driveRightMotor(currentRightSpeed);
}

void driveLeftMotor(int speed)
{
  if(abs(speed) < MIN_MOTOR_SPEED){
    analogWrite(L_MOTOR_ENABLE, speed);
    digitalWrite(L_MOTOR_1, LOW);
    digitalWrite(L_MOTOR_2, LOW);
  }
  else {
    analogWrite(L_MOTOR_ENABLE, abs(speed));
    if (speed > 0) {
      digitalWrite(L_MOTOR_1,HIGH);
      digitalWrite(L_MOTOR_2, LOW);
    }
    else {
      digitalWrite(L_MOTOR_1, LOW);
      digitalWrite(L_MOTOR_2, HIGH);
    }
  }
}

void driveRightMotor(int speed)
{
  if(abs(speed) < MIN_MOTOR_SPEED){
    analogWrite(R_MOTOR_ENABLE, speed);
    digitalWrite(R_MOTOR_1, LOW);
    digitalWrite(R_MOTOR_2, LOW);
  }
  else {
    analogWrite(R_MOTOR_ENABLE, abs(speed));
    if (speed > 0) {
      digitalWrite(R_MOTOR_1,LOW);
      digitalWrite(R_MOTOR_2, HIGH);
    }
    else {
      digitalWrite(R_MOTOR_1, HIGH);
      digitalWrite(R_MOTOR_2, LOW);
    }
  }
}
