
unsigned long duration;
bool measuring = true;
const int pwmaPin =3; //control motor speed
const int ain2Pin =4;//control motor direction
const int ain1Pin =5;//control motor direction
const int stbyPin =6; //enable /disenable the driver
const int bin1Pin =7;//control motor direction
const int bin2Pin =8;//control motor direction
const int pwmbPin =9; //control motor speed
const int trigPin =10; //output in arduino perpective
const int echoPin =11; //input in arduino perpective

// function prototypes
void testMotorA();
void testMotorB();
void stopMotorA();
void stopMotorB();
void moveForward();
void stopMotor();


void setup() {
  pinMode(trigPin,OUTPUT); // send the trig signal
  pinMode(pwmaPin,OUTPUT);
  pinMode(pwmbPin,OUTPUT);
  pinMode(ain1Pin,OUTPUT);
  pinMode(ain2Pin,OUTPUT);
  pinMode(bin1Pin,OUTPUT);
  pinMode(bin2Pin,OUTPUT);
  pinMode(echoPin,INPUT); // recive the eacho signal
  pinMode(stbyPin,OUTPUT);
  digitalWrite(stbyPin,LOW);
  analogWrite(pwmaPin,0);
  analogWrite(pwmbPin,0);
  digitalWrite(ain1Pin,LOW);
  digitalWrite(ain2Pin,LOW);
  digitalWrite(bin1Pin,LOW);
  digitalWrite(bin2Pin,LOW);

  Serial.begin(9600);
}

void loop() {

  // check the input from the serial monitor
  //imput 'p' to puase the sensor, 'r to resume the sensor
  if (Serial.available() > 0) 
  {
    char command = Serial.read();
    if(command =='p')
    {
      measuring=false;
      stopMotor();
    }else if(command =='r')
    {
      measuring =true;
    }
  }
  
  //running the sensor only if the measuring is true
  if(measuring)
  {
    //set TRIG LOW briefly
    digitalWrite(trigPin,LOW);
    delayMicroseconds(2);
    // set TRIG HIGH for 10 microseconds
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(10);
    // set TRIG LOW again
    digitalWrite(trigPin,LOW);
  
    //read echo signal
    duration = pulseIn(echoPin, HIGH, 30000);
    if(duration ==0) // if no echo before 30 ms
    {
      Serial.println("no echo detacted!");
      stopMotor();
    }else{
      float distance =(0.0343*duration)/2; //distance calculation
      Serial.print("distance: ");
      Serial.print(distance);
      Serial.println(" cm ");

      if (distance <=20)
      {
      //obstacle detected, stop
      Serial.println("obstacle detected! STOP");
      stopMotor();

      }else{
       Serial.println("Path clear! Move forward");
       moveForward();
       }
    }

    delay(100); //100ms

    
     

  }


}
void testMotorA()
{
  // moving forward ain1 = LOW, ain2 =HIGH
  digitalWrite(ain1Pin,LOW);
  digitalWrite(ain2Pin,HIGH);
  analogWrite(pwmaPin,128);
}
void testMotorB()
{
  //// moving forward bin1 = HIGH, ain2 =LOW
  digitalWrite(bin1Pin,HIGH);
  digitalWrite(bin2Pin,LOW);
  analogWrite(pwmbPin,128);
}
// Make motor a coast a stop, not a brake
void stopMotorA()
{
  analogWrite(pwmaPin,0);
  digitalWrite(ain1Pin,LOW);
  digitalWrite(ain2Pin,LOW);
}
void stopMotorB()
{
  analogWrite(pwmbPin,0);
  digitalWrite(bin1Pin,LOW);
  digitalWrite(bin2Pin,LOW);
}
void moveForward()
{
  digitalWrite(stbyPin, HIGH);
  testMotorA();
  testMotorB();
}
void stopMotor()
{
  stopMotorA();
  stopMotorB();
  digitalWrite(stbyPin, LOW);

}


