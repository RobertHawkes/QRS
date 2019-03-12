#define MAX_MOTOR_SPEED 255
#define MIN_MOTOR_SPEED 130
#define L_MOTOR_ENABLE 6
#define R_MOTOR_ENABLE 5
#define R_MOTOR_1 7
#define R_MOTOR_2 8
#define L_MOTOR_1 9
#define L_MOTOR_2 11
#define LINE_FOLLOWING_A A1
#define LINE_FOLLOWING_B A2
#define LINE_FOLLOWING_C A3
#define MOTOR_SPEED_OFFSET 2
boolean foundLine = true;
int amountOfSearches = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(L_MOTOR_ENABLE, OUTPUT);
  pinMode(R_MOTOR_ENABLE, OUTPUT);
  pinMode(L_MOTOR_1, OUTPUT);
  pinMode(L_MOTOR_2, OUTPUT);
  pinMode(R_MOTOR_1, OUTPUT);
  pinMode(R_MOTOR_2, OUTPUT);
  pinMode(LINE_FOLLOWING_A, INPUT);
  pinMode(LINE_FOLLOWING_B, INPUT);
  pinMode(LINE_FOLLOWING_C, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int valueLeft = analogRead(LINE_FOLLOWING_A);
  int valueCenter = analogRead(LINE_FOLLOWING_B);
  int valueRight = analogRead(LINE_FOLLOWING_C);

  //If Left has lost the line, swivel to the right
  //If right has lost the line, swivel to the left
  //If center is on the line, go forward
  long noOfRecords = 0;
  long totalValueCenter += analogRead(LINE_FOLLOWING_B);
  
  if (foundLine) {
    //Serial.println("in the foundLine loop ---"+(String)valueCenter);
    if (valueCenter < 800) {
      foundLine = false;

    }
    else {
      driveLeftMotor(MIN_MOTOR_SPEED);
      driveRightMotor(MIN_MOTOR_SPEED + MOTOR_SPEED_OFFSET);

    }
  }

  if (!foundLine) {
    // Serial.println("in the !foundLine loop ");
    driveLeftMotor(0);
    driveRightMotor(0);
    delay(500);
    int maxLeft = 600;
    int currentLeftDelay = 0;
    while (currentLeftDelay < maxLeft) {
      driveLeftMotor(-MIN_MOTOR_SPEED);
      driveRightMotor(MIN_MOTOR_SPEED + MOTOR_SPEED_OFFSET);
      delay(20);
      currentLeftDelay += 20;
      if (analogRead(LINE_FOLLOWING_B) > 800) {
        foundLine = true;
        break;
      }
      driveLeftMotor(0);
      driveRightMotor(0);
      delay(30);
    }

    int maxRight = 950;
    int currentRightDelay = 0;
    while (currentRightDelay < maxRight) {
      driveLeftMotor(MIN_MOTOR_SPEED);
      driveRightMotor(-MIN_MOTOR_SPEED - MOTOR_SPEED_OFFSET);
      delay(20);
      currentRightDelay += 20;
      if (analogRead(LINE_FOLLOWING_B) > 800) {
        foundLine = true;
        break;
      }
      driveLeftMotor(0);
      driveRightMotor(0);
      delay(30);
    }

    //Swivel to the left
    //Have we found the line yet?
    //If yes, set foundLine to true and exit loop
    //If no, return to center, then begin swivel right
    //Have we found the line yet?
    //If no, re-loop!
  }
}

void driveLeftMotor(int speed)
{
  speed = -speed;
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
  speed = -speed;
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
