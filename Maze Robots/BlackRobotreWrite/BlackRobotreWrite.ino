#include <Ultrasonic.h>
#include <Encoder.h>

Ultrasonic leftSensor(12, 10, 10000UL);
Ultrasonic frontSensor(A5, A4, 10000UL);

Encoder rightEncoder(3, A2);
Encoder leftEncoder(2, 4);

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
#define wheelSpeedOffset 53


#define diameterOfWheel 129
#define radiusOfWheel diamaterOfWheel / 2;

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
  int currentLeftSpeed = MIN_MOTOR_SPEED + wheelSpeedOffset;
  int currentRightSpeed = MIN_MOTOR_SPEED;
  int IRSensorDetect = digitalRead(IR_SENSOR);
  int ableToFollowLeftWall = wallToLeftAbleToFollow(distanceLeftLeft, currentLeftSpeed, currentRightSpeed);
  Serial.println((String)IRSensorDetect);
  if(noWallToLeft)
  {
    //We need to make a left turn
    delay(5000);
    makeALeftTurn(currentLeftSpeed, currentRightSpeed);
  }
  else if (ableToFollowLeftWall == 1) {
    //Go forth!
    goForward(currentLeftSpeed, currentRightSpeed);
  }
  else if (ableToFollowLeftWall == 2)
  {
    moveRight(currentLeftSpeed, currentRightSpeed);
  }
  else if (ableToFollowLeftWall == 3)
  {
    moveLeft(currentLeftSpeed, currentRightSpeed);
  }
  else
  {
    makeARightTurn(currentLeftSpeed, currentRightSpeed);
  }

  driveLeftMotor(currentLeftSpeed);
  driveRightMotor(currentRightSpeed);
}

void makeALeftTurn(int &currentLeftSpeed, int &currentRightSpeed)
{
  turn(90);
}

void makeARightTurn(int &currentLeftSpeed, int &currentRightSpeed)
{
  turn(-90);
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

void turn(int deg)
{
  driveLeftMotor(0);
  driveRightMotor(0);
  delay(200);
  if (deg > 0) {
    driveLeftMotor(-MIN_MOTOR_SPEED - wheelSpeedOffset);
    driveRightMotor(MIN_MOTOR_SPEED);
  }
  else
  {
    driveLeftMotor(MIN_MOTOR_SPEED + wheelSpeedOffset);
    driveRightMotor(-MIN_MOTOR_SPEED);
  }

  delay((abs(deg) * 95) / 36);

  driveLeftMotor(0);
  driveRightMotor(0);
  delay(200);
}

bool noWallToLeft(int &IRSensorDetect)
{
  if (IRSensorDetect == 1)
  {
      return true;
  }

  return false;

}

int wallToLeftAbleToFollow(int &distanceLeftLeft, int &currentLeftSpeed, int &currentRightSpeed)
{
  const int minimumWallDistance = 10;
  const int maximumWallDistance = 20;

  if (distanceLeftLeft < maximumWallDistance && distanceLeftLeft > minimumWallDistance)
  {
    //We are within the acceptable range, go forth!
    return 1;
  }
  else if (distanceLeftLeft < minimumWallDistance)
  {
    //We want to go away from the wall to maintain our boundary
    return 2;
  }
  else if (distanceLeftLeft > maximumWallDistance)
  {
    //We want to go towards the wall to maintain our boundary
    return 3;
  }
}

void moveLeft(int &currentLeftSpeed, int &currentRightSpeed)
{
  currentLeftSpeed -= 10;
  currentRightSpeed += 10;
}

void moveRight(int &currentLeftSpeed, int &currentRightSpeed)
{
  currentLeftSpeed += 10;
  currentRightSpeed -= 10;
}

void goForward(int &currentLeftSpeed, int &currentRightSpeed)
{
  currentLeftSpeed = MIN_MOTOR_SPEED + wheelSpeedOffset;
  currentRightSpeed = MIN_MOTOR_SPEED;
}
