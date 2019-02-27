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
#define WHEEL_SPEED_OFFSET 53

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
  int distanceLeftFront = frontSensor.read();
  int distanceLeftLeft = leftSensor.read();
  int currentLeftSpeed = MIN_MOTOR_SPEED + WHEEL_SPEED_OFFSET;
  int currentRightSpeed = MIN_MOTOR_SPEED;
  int IRSensorDetect = digitalRead(IR_SENSOR);
  // put your main code here, to run repeatedly:
  
  if(IRSensorDetect == 1)
  {
    //There is no wall on my left
    //I want to make a left turn
    delay(500);
    IRSensorDetect = digitalRead(IR_SENSOR);
    if(IRSensorDetect == 1)
    {
      turnLeft(currentLeftSpeed, currentRightSpeed);
      Serial.println("I'm wanting to turn left");
    }
  }
  else if(distanceLeftFront > 10)
  {
    //There is no wall in front
    //Go forwards & follow the wall on my left
    if(distanceLeftLeft > 15){
      currentLeftSpeed -= 10;
      currentRightSpeed += 10;
      Serial.println("I'm following the wall on my left but heading towards it");
    }
    else if(distanceLeftLeft < 7) {
      currentLeftSpeed += 10;
      currentRightSpeed -= 10;
      Serial.println("I'm following the wall on my left but heading away from it");
    }
    else
    {
      currentLeftSpeed = MIN_MOTOR_SPEED + WHEEL_SPEED_OFFSET;
      currentRightSpeed = MIN_MOTOR_SPEED;
      Serial.println("I'm following the wall");
    }
  }
  else if(distanceLeftFront < 10 && distanceLeftLeft < 100 && distanceLeftLeft > 15)
  {
    //Make a right turn
    turnRight(currentLeftSpeed, currentRightSpeed);
    Serial.println("I want to make a right hand turn");
  }

  //If no wall on my left (IRSensorDetect == 1)
    //Make a left turn
  //If there is no wall in front
    //Go forwards
  //Otherwise
    //Turn right
    
  driveLeftMotor(currentLeftSpeed);
  driveRightMotor(currentRightSpeed);
}

void turnLeft(int &currentLeftSpeed, int &currentRightSpeed)
{
  driveLeftMotor(-MIN_MOTOR_SPEED - WHEEL_SPEED_OFFSET);
  driveRightMotor(MIN_MOTOR_SPEED);
  delay(350);
  driveLeftMotor(0);
  driveRightMotor(0);
  delay(1000);
  driveLeftMotor(MIN_MOTOR_SPEED + WHEEL_SPEED_OFFSET);
  driveRightMotor(MIN_MOTOR_SPEED);
  boolean continueForward = true;
  int noOfLoops = 0;
  while(continueForward)
  {
    delay(1);
    noOfLoops++;
    int distanceLeftFront = frontSensor.read();
    if(distanceLeftFront < 20 || noOfLoops >= 300)
    {
      continueForward = false;
    }
  }
}

void turnRight(int &currentLeftSpeed, int &currentRightSpeed)
{
  driveLeftMotor(MIN_MOTOR_SPEED);
  driveRightMotor(-MIN_MOTOR_SPEED - WHEEL_SPEED_OFFSET);
  delay(410);
  driveLeftMotor(0);
  driveRightMotor(0);
}

void driveLeftMotor(int speed)
{
  if (abs(speed) < MIN_MOTOR_SPEED) {
    analogWrite(L_MOTOR_ENABLE, speed);
    digitalWrite(L_MOTOR_1, LOW);
    digitalWrite(L_MOTOR_2, LOW);
  }
  else {
    analogWrite(L_MOTOR_ENABLE, abs(speed));
    if (speed > 0) {
      digitalWrite(L_MOTOR_1, HIGH);
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
  if (abs(speed) < MIN_MOTOR_SPEED) {
    analogWrite(R_MOTOR_ENABLE, speed);
    digitalWrite(R_MOTOR_1, LOW);
    digitalWrite(R_MOTOR_2, LOW);
  }
  else {
    analogWrite(R_MOTOR_ENABLE, abs(speed));
    if (speed > 0) {
      digitalWrite(R_MOTOR_1, LOW);
      digitalWrite(R_MOTOR_2, HIGH);
    }
    else {
      digitalWrite(R_MOTOR_1, HIGH);
      digitalWrite(R_MOTOR_2, LOW);
    }
  }
}
