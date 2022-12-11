#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <string.h>

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


void setup()
{
  //Motor control pins
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  // pinMode (SWITCH1, INPUT_PULLUP);
  
  
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);

  //Radio receiver 
  Serial.begin(9600);  // Debugging only
  if (!driver.init())
        Serial.println("init failed");
}

void loop()
{
   
  int digitalSensorValue = 0;
  //Radio Receiver
  uint8_t buf[8];
  uint8_t buflen = sizeof(buf);
  
  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    int i;
    
    String x = ((String)(char*)buf);  
    
    Serial.println(x+ " :"+x.length());  
  }
  // //Motor Control
  
  // // if (x == "LEFT_LOWSPED"){
  // //   digitalSensorValue = 60;
  // //   // Serial.println("1");
  // // }
  // // else if (x == "LEFT_MEDSPED"){
  // //   digitalSensorValue = 170;
  // //   // Serial.println("2");
  // // }
  // // else if (x == "LEFT_HGHSPED"){
  // //   digitalSensorValue = 230;
  // //   // Serial.println("3");
  // // }
  // // else{
  // //   digitalSensorValue = 170;
    
  // //   // Serial.println("-");
  // // }
  //  //Serial.println(digitalSensorValue);
  // // if(digitalRead(SWITCH1)==0)
  // // {
  // //   state1 = LOW;
  // //   state2 = HIGH;
  // //   //Serial.println("Rotation1");

    
  // // }
  // // else if (digitalRead(SWITCH1)==1)
  // // {
  // //   state1 = HIGH;
  // //   state2 = LOW;
  // //   //Serial.println("Rotation2");

  // // }
  
    
  // }
  
  //L298N Pin states
  int state1 = LOW;
  int state2 = HIGH;
  //Serial.println(state1+" "+state2 );   
  analogWrite(ENA, 170);
  analogWrite(ENB, 170); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
    
}
