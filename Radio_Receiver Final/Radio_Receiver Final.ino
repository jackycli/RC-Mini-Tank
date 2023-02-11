#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

//Pin assignment
const int IN4 = 7;
const int IN3 = 6;
const int IN2 = 5;
const int IN1 = 4;

//PWM pin assignment
const int ENA = 3;
const int ENB = 11;

//Both using pin 12, on transmitter and receiver
RH_ASK driver(2000,12,12,5);

//Create data structure to be received over radio, 8 bytes long
struct radioBuf{
  unsigned int left_Speed; 
  unsigned int left_Direction;
  unsigned int right_Speed;
  unsigned int right_Direction;
}radioBuf;

int l_State1, l_State2, r_State1, r_State2;

void setup() {
  
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);

  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  
  Serial.begin(9600);  // Debugging only
  if (!driver.init())
         Serial.println("init failed");

}

void loop() {

  //Allows receiver to receive max length messages
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);
  
  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    int i;
    // Message with a good checksum received, dump it.
    driver.printBuffer("Got:", buf, buflen);
    memcpy(&radioBuf, buf, sizeof(radioBuf));
    Serial.print("Right Speed");
    Serial.print(radioBuf.right_Speed);
    Serial.print("    Right Direction");
    Serial.print(radioBuf.right_Direction);
    Serial.print("    Left Speed");
    Serial.print(radioBuf.left_Speed);
    Serial.print("    Left Direction");
    Serial.println(radioBuf.left_Direction);
  }
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

  analogWrite(ENA, radioBuf.right_Speed);
  analogWrite(ENB, radioBuf.left_Speed); 
  digitalWrite(IN1, r_State1);
  digitalWrite(IN2, r_State2);
  digitalWrite(IN3, l_State1);
  digitalWrite(IN4, l_State2);
 

}
