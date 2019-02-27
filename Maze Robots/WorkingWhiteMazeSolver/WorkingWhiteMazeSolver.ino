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
}

void loop() {
  // put your main code here, to run repeatedly:
  int currentLeftSpeed = MIN_MOTOR_SPEED + 20;
  int currentRightSpeed = MIN_MOTOR_SPEED + 20;
 


  if (digitalRead(IR_SENSOR) == 1)
  {
    turnLeft(currentLeftSpeed, currentRightSpeed);

  }
  else if (distanceLeftFront < 20) 
  {

    turnRight(currentLeftSpeed, currentRightSpeed);

  }

  drivingCorrections( currentLeftSpeed, currentRightSpeed);





}
void turnLeft(int currentLeftSpeed, int currentRightSpeed)
{
  delay(60);
  if (digitalRead(IR_SENSOR) == 1)
  {
    waitASec();

    if (frontSensor.read() < 30)
    {

      while (frontSensor.read() > 13 || frontSensor.read() < 10)
      {
        while (frontSensor.read() > 13)
        {
          currentLeftSpeed = MIN_MOTOR_SPEED;
          currentRightSpeed = MIN_MOTOR_SPEED;
          driveLeftMotor(currentLeftSpeed);
          driveRightMotor(currentRightSpeed);

        }
        while (frontSensor.read() < 10)
        {
          currentLeftSpeed = -MIN_MOTOR_SPEED;
          currentRightSpeed = -MIN_MOTOR_SPEED;
          driveLeftMotor(currentLeftSpeed);
          driveRightMotor(currentRightSpeed);

        }
      }
    }

    waitASec();

    if (digitalRead(IR_SENSOR) == 1) {


      currentLeftSpeed = -MIN_MOTOR_SPEED;
      currentRightSpeed = MIN_MOTOR_SPEED;
      driveLeftMotor(currentLeftSpeed);
      driveRightMotor(currentRightSpeed);
      delay(230);


      currentLeftSpeed = MIN_MOTOR_SPEED;
      currentRightSpeed = MIN_MOTOR_SPEED;
      driveLeftMotor(currentLeftSpeed);
      driveRightMotor(currentRightSpeed);
      delay(500);

      waitASec();
    }
  }
}


void turnRight(int currentLeftSpeed, int currentRightSpeed) {

  waitASec();
  while (frontSensor.read() > 10 || frontSensor.read() < 5)
  {
    while (frontSensor.read() > 10)
    {
      currentLeftSpeed = MIN_MOTOR_SPEED;
      currentRightSpeed = MIN_MOTOR_SPEED;
      driveLeftMotor(currentLeftSpeed);
      driveRightMotor(currentRightSpeed);

    }
    while (frontSensor.read() < 5)
    {
      currentLeftSpeed = -MIN_MOTOR_SPEED;
      currentRightSpeed = -MIN_MOTOR_SPEED;
      driveLeftMotor(currentLeftSpeed);
      driveRightMotor(currentRightSpeed);

    }
  }

  currentLeftSpeed = MIN_MOTOR_SPEED;
  currentRightSpeed = -MIN_MOTOR_SPEED;
  driveLeftMotor(currentLeftSpeed);
  driveRightMotor(currentRightSpeed);
  delay(240);
  currentLeftSpeed = MIN_MOTOR_SPEED;
  currentRightSpeed = MIN_MOTOR_SPEED;
  driveLeftMotor(currentLeftSpeed);
  driveRightMotor(currentRightSpeed);
  delay(30);

  waitASec();
}
void drivingCorrections(int currentLeftSpeed, int currentRightSpeed)
{
  if (distanceLeftLeft > 30) {
    currentLeftSpeed -= 10;
    currentRightSpeed += 10;
    //Serial.println("I'm going towards the wall on my left");
  }
  else if (distanceLeftLeft < 15) {
    currentLeftSpeed += 10;
    currentRightSpeed -= 10;
    //  Serial.println("I'm going away from the wall on my left");
  }

  driveLeftMotor(currentLeftSpeed);
  driveRightMotor(currentRightSpeed);
}
void waitASec()
{
  driveLeftMotor(0);
  driveRightMotor(0);
  delay(666);
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
