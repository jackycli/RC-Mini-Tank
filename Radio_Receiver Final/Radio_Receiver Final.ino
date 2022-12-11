#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

//Pin assignment
const int IN4 = 7;
const int IN3 = 6;
const int IN2 = 5;
const int IN1 = 4;

//PWM assignment
const int ENA = 3;
const int ENB = 11;

//Both using pin 12, on transmitter and receiver
RH_ASK driver(2000,12,12,5);

//Create data structure to be received over radio, 8 bytes long
struct dataStruct{
  unsigned int left_Speed; 
  unsigned int left_Direction;
  unsigned int right_Speed;
  unsigned int right_Direction;
}radioBuf;

void setup() {
  
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  
  Serial.begin(9600);  // Debugging only
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);

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
    Serial.print("    Right Direction");
    Serial.println(radioBuf.left_Direction);
  }


  //analogWrite(ENA, 255);
  analogWrite(ENB, radioBuf.right_Speed); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);


}
