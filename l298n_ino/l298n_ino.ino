const int IN1 = 7;
const int IN2 = 6;
const int IN3 = 5;
const int IN4 = 4;
const int SWITCH1 = 8;
int state1;
int state2;

const int ENA = 9;
const int ENB = 10;


void setup() {

  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (SWITCH1, INPUT_PULLUP);
  
  Serial.begin(2400);  // Debugging only
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  
  float sensorValue = analogRead(A0);
  int digitalSensorValue = int(sensorValue/1024*255);
  

  if(digitalRead(SWITCH1)==0)
  {
    state1 = LOW;
    state2 = HIGH;
    //Serial.println("Rotation1");

    
  }
  else if (digitalRead(SWITCH1)==1)
  {
    state1 = HIGH;
    state2 = LOW;
    //Serial.println("Rotation2");

  }


  analogWrite(ENA, digitalSensorValue);
  analogWrite(ENB, digitalSensorValue); 
  digitalWrite(IN1, state1);
  digitalWrite(IN2, state2);
  digitalWrite(IN3, state1);
  digitalWrite(IN4, state2);
  
  Serial.println(digitalSensorValue);
  
  //Serial.println(digitalRead(SWITCH1));
  
      
  // put your main code here, to run repeatedly:

}
