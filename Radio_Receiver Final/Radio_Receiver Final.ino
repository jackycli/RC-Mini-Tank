#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

const int IN1 = 7;
const int IN2 = 6;
const int IN3 = 5;
const int IN4 = 4;

int state1;
int state2;

const int ENA = 9;
const int ENB = 10;
int y;

RH_ASK driver(2000,12,12,5);


void setup() {

  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  
  
  Serial.begin(9600);  // Debugging only
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  // put your setup code here, to run once:

  if (!driver.init())
         Serial.println("init failed");

}

void loop() {
  state1 = HIGH;
  state2 = LOW;
  uint8_t buf[8];
  uint8_t buflen = sizeof(buf);
  
  
  

  analogWrite(ENA, y);
  analogWrite(ENB, y); 
  digitalWrite(IN1, state1);
  digitalWrite(IN2, state2);
  digitalWrite(IN3, state1);
  digitalWrite(IN4, state2);

  //Serial.println(digitalSensorValue);
   
  // put your main code here, to run repeatedly:

}
