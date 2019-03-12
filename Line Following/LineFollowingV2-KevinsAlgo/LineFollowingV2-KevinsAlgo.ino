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
  int valueCenter = analogRead(LINE_FOLLOWING_B);

  long total = 0;

  int Delay = 20;
  //For loop to collect the LDR's values
  for (int i = 0; i < Delay; i++)
  {

    total += analogRead(LINE_FOLLOWING_B);


    delay(1);
  }


  int avg = total / Delay;

  if (avg < 750) {
    driveLeftMotor(MAX_MOTOR_SPEED + 20);
    driveRightMotor(0);
    delay(10);
    driveLeftMotor(0);
  }
  else if (avg > 850) {
    driveLeftMotor(0);
    driveRightMotor(MAX_MOTOR_SPEED + 20);
    delay(10);
    driveRightMotor(0);
  }
  else {
    driveLeftMotor(MAX_MOTOR_SPEED);
    driveRightMotor(MAX_MOTOR_SPEED);
    delay(10);
    driveRightMotor(0);
    driveLeftMotor(0);
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
