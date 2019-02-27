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

//Defining debug mode
#define DebugMode 1

//Defining the distances
#define min_front_distance 20 //20cm from the Wall in front
#define min_front_left_distance 20 //20cm from the Wall to the left
#define max_front_left_distance 40 //40cm from the Wall to the left

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
  printDebug("Distance Left Front:" + (String)distanceLeftFront);
  printDebug("Distance Left Left:" + (String)distanceLeftLeft);
  
  //Left range is 20 - 25

  //If Front Sensor Distance < 20 (Straight into wall)
  //  Spin Right until Left Sensor is within 20 - 40 range
  //Else
  //  Continue tracking wall

  if(goingStraightIntoAWall(&distanceLeftFront))
  {
    spinRight(&currentLeftSpeed,&currentRightSpeed);
  }
  else if(driftingAwayFromLeftWall(&distanceLeftLeft))
  {
    moveToLeft(&currentLeftSpeed,&currentRightSpeed);
  }
  else if(driftingTowardsLeftWall(&distanceLeftLeft))
  {
    moveToRight(&currentLeftSpeed,&currentRightSpeed);
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

void printDebug()
{
  if(DebugMode == 1)
  {
    Serial.println(text);
  }
  else if(DebugMode == 2)
  {
    
  }
}

boolean goingStraightIntoAWall(int DistanceLeftFront)
{
  if(DistanceLeftFront < min_front_distance)
  {
    return true;
  }
  else
  {
    return false;
  }
}

boolean driftingAwayFromLeftWall(int DistanceLeftLeft)
{
  if(DistanceLeftLeft > max_front_left_distance)
  {
    return true;
  }
  else
  {
    return false;
  }
}

boolean driftingTowardsLeftWall(int DistanceLeftLeft)
{
  if(DistanceLeftLeft < min_front_left_distance)
  {
    return true;
  }
  else 
  {
    return false;
  }
}

void spinRight(int CurrentLeftSpeed, int CurrentRightSpeed)
{
    CurrentLeftSpeed = MIN_MOTOR_SPEED;
    CurrentRightSpeed = -MIN_MOTOR_SPEED;
}

void moveToLeft(int CurrentLeftSpeed, int CurrentRightSpeed)
{
    CurrentLeftSpeed -= 15;
    CurrentRightSpeed += 15;
}

void moveToRight(int CurrentLeftSpeed, int CurrentRightSpeed)
{
    CurrentLeftSpeed += 15;
    CurrentRightSpeed -= 15;
}
