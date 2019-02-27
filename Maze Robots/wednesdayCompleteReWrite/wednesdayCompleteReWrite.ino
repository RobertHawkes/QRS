#include <Ultrasonic.h>


Ultrasonic leftSensor(12, 10, 10000UL);
Ultrasonic frontSensor(A5, A4, 10000UL);

#define L_MOTOR_ENABLE 6
#define R_MOTOR_ENABLE 5
#define R_MOTOR_1 7
#define R_MOTOR_2 8
#define L_MOTOR_1 9
#define L_MOTOR_2 11
#define IR_SENSOR A0

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
  pinMode(IR_SENSOR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int distanceLeftFront = frontSensor.read();
  int distanceLeftLeft = leftSensor.read();
  int currentLeftSpeed = MIN_MOTOR_SPEED+53;
  int currentRightSpeed = MIN_MOTOR_SPEED;
  int IRSensorDetect = digitalRead(IR_SENSOR);

  if(IRSensorDetect == 1)
  {
    delay(100);
    IRSensorDetect = digitalRead(IR_SENSOR);
    if(IRSensorDetect == 1)
    {
      driveLeftMotor(0);
      driveRightMotor(0);
      delay(5000);
      currentLeftSpeed = MIN_MOTOR_SPEED;
      currentRightSpeed = -MIN_MOTOR_SPEED;
      driveLeftMotor(currentLeftSpeed);
      driveLeftMotor(currentRightSpeed);
      delay(500);
      driveLeftMotor(0);
      driveRightMotor(0);
      delay(5000);
      currentLeftSpeed = MIN_MOTOR_SPEED;
      currentRightSpeed = MIN_MOTOR_SPEED;
      driveLeftMotor(currentLeftSpeed);
      driveRightMotor(currentRightSpeed);
      delay(500);
    }
  }
  else if(distanceLeftFront < 20){
    currentLeftSpeed = MIN_MOTOR_SPEED;
    currentRightSpeed = -MIN_MOTOR_SPEED;
  }
  else if(distanceLeftLeft > 20){
    currentLeftSpeed -= 15;
    currentRightSpeed += 15;
  }
  else if(distanceLeftLeft < 10) {
    currentLeftSpeed += 15;
    currentRightSpeed -= 15;
  }

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
