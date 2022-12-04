#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver(2000,12,12,5);

const int IN1 = 7;
const int IN2 = 6;
const int IN3 = 5;
const int IN4 = 4;
const int SWITCH1 = 8;
int state1;
int state2;

const int ENA = 9;
const int ENB = 10;
int digitalSensorValue;

void setup()
{
  //Motor control pins
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (SWITCH1, INPUT_PULLUP);
  
  
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);

  //Radio receiver 
  Serial.begin(9600);  // Debugging only
  if (!driver.init())
        Serial.println("init failed");
}

void loop()
{
   

  //Radio Receiver
  uint8_t buf[12];
  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    int i;
    // Message with a good checksum received, dump it.
    Serial.print("Message: ");
    Serial.println((char*)buf);         
  }
    
  
  //Motor Control
  if (buf == "LEFT_LOWSPED"){
    digitalSensorValue = 60;
  }
  else if (buf == "LEFT_MEDSPED"){
    digitalSensorValue = 170;
  }
  else if (buf == "LEFT_HGHSPED"){
    digitalSensorValue = 230;
  }
  else{
    digitalSensorValue = 0;
  }
  // if(digitalRead(SWITCH1)==0)
  // {
  //   state1 = LOW;
  //   state2 = HIGH;
  //   //Serial.println("Rotation1");

    
  // }
  // else if (digitalRead(SWITCH1)==1)
  // {
  //   state1 = HIGH;
  //   state2 = LOW;
  //   //Serial.println("Rotation2");

  // }

  //L298N Pin states
  state1 = LOW;
  state2 = HIGH;
  analogWrite(ENA, digitalSensorValue);
  analogWrite(ENB, digitalSensorValue); 
  digitalWrite(IN1, state1);
  digitalWrite(IN2, state2);
  digitalWrite(IN3, state1);
  digitalWrite(IN4, state2);
  
  //Serial.println(digitalSensorValue);
  
  
    
}
