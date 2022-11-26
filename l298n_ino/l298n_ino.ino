const int IN1 = 7;
const int IN2 = 6;
const int IN3 = 5;
const int IN4 = 4;
const int SWITCH1 = 8;
int State1;
int State2;

//const int ENA = 9;
//const int ENB = 3;


void setup() {

  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (SWITCH1, INPUT_PULLUP);
  
  Serial.begin(2400);  // Debugging only
  //pinMode (ENA, OUTPUT);
  //pinMode (ENB, OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  //analogWrite(ENA, 255);
  //analogWrite(ENB, 255); 
  if(digitalRead(SWITCH1)==0)
  {
    State1 = LOW;
    State2 = HIGH;
    //Serial.println("Rotation1");

    
  }
  else if (digitalRead(SWITCH1)==1)
  {
    State1 = HIGH;
    State2 = LOW;
    //Serial.println("Rotation2");

  }
  Serial.print("State1: ");
  Serial.println(State1);
  Serial.print("State2: ");
  Serial.println(State2);
  digitalWrite(IN1, State1);
  digitalWrite(IN2, State2);
  digitalWrite(IN3, State1);
  digitalWrite(IN4, State2);
  
  Serial.println(digitalRead(SWITCH1));
  
      
  // put your main code here, to run repeatedly:

}
