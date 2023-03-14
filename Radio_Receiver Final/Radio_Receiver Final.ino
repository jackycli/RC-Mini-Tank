//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


//Pin assignment
const int IN4 = 6;
const int IN3 = 5;
const int IN2 = 4;
const int IN1 = 3;

//PWM pin assignment
const int ENA = 9;
const int ENB = 10;

//create an RF24 object
RF24 radio(7,8);  // CSN,mCE

//address through which two modules communicate.
const byte address[6] = "ABCDE";

//Create data structure to be received over radio, 8 bytes long
struct radioBuf{
  unsigned int left_Speed; 
  unsigned int left_Direction;
  unsigned int right_Speed;
  unsigned int right_Direction;
}radioBuf;

//Direction states for High and Low
int l_State1, l_State2, r_State1, r_State2;

void setup() {
  //Pin assignment
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);

  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  
  Serial.begin(9600);  // Debugging only

  //Begin radio
  radio.begin();
   
  //set the address
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_HIGH);

  //Set module as transmitter
  radio.startListening();
}

void loop() {
  //Allows receiver to receive max length messages
  uint8_t buf[32] = "";
  
  if (radio.available()) // If message to be received
  {
    int i;

    //Read
    radio.read(buf,sizeof(buf));

    //Copies data received from radio into RadioBuf Structure
    memcpy(&radioBuf, buf, sizeof(radioBuf));

    Serial.print("Left Speed");
    Serial.print(radioBuf.left_Speed);
    Serial.print("    Left Direction");
    Serial.print(radioBuf.left_Direction);
    Serial.print("    Right Speed");
    Serial.print(radioBuf.right_Speed);
    Serial.print("    Right Direction");
    Serial.println(radioBuf.right_Direction);
  }

  //Assigning HIGH LOW based on direction received 
  if (radioBuf.right_Direction == 0){
    r_State1 = HIGH;
    r_State2 = LOW;
  }
  else if (radioBuf.right_Direction == 1){
    r_State1 = LOW;
    r_State2 = HIGH;
  }

  if (radioBuf.left_Direction == 0){
    l_State1 = HIGH;
    l_State2 = LOW;
  }
  else if (radioBuf.left_Direction == 1){
    l_State1 = LOW;
    l_State2 = HIGH;
  }

  //Rounding to reduce motor whine at low PWM
  if(radioBuf.right_Speed<50){
    radioBuf.right_Speed = 0;
  }
  if(radioBuf.left_Speed<50){
    radioBuf.left_Speed = 0;
  }

  //Assigning IO and PWM states
  analogWrite(ENB, radioBuf.left_Speed);
  analogWrite(ENA, radioBuf.right_Speed); 
  digitalWrite(IN3, l_State1);
  digitalWrite(IN4, l_State2);
  digitalWrite(IN1, r_State1);
  digitalWrite(IN2, r_State2);
}
