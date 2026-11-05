

const int trigPin =9; //output in arduino perpective
const int echoPin =10; ////input in arduino perpective
unsigned long duration;
bool measuring = true;

void setup() {
  pinMode(trigPin,OUTPUT); // send the trig signal
  pinMode(echoPin,INPUT); // recive the eacho signal
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
    }else
    {
      float distance =(0.0343*duration)/2; //distance calculation
      Serial.print("distance: ");
      Serial.print(distance);
      Serial.println(" cm ");

      if (distance <=20)
      {
      //obstacle detected, stop
      Serial.println("obstacle detected! STOP");

      }else{
       Serial.println("Path clear! Move forward");
       }
    }



    delay(100);

    
     
    


  }

 



}
