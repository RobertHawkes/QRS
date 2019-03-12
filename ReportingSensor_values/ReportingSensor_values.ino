#define LINE_FOLLOW_B A2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LINE_FOLLOW_B, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:


  double  total =  0;

  int Delay = 20;
  for (int i = 0; i < Delay; i++)
  {

    //Use a compound assignment operator to total up the LDR values
    //We read the analogue signal from the Analogue input pins specified in the global variable
    total += analogRead(LINE_FOLLOW_B);


    //We delay each iteration in order to get values from a range of time as processing speed
    //would mean that the for loop would get it in a shorter time duration
    delay(1);
  }
  double average =  (total/(double)Delay);
  Serial.println((average));
}
