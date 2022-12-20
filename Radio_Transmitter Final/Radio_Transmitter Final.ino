#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile


//Both using pin 12, on transmitter and receiver
RH_ASK driver(2000,12,12,5);

//Pin Assignment
//const int right_Switch = 8;
//const int left_Switch = 9;
//Counter to delay radio tramsit
unsigned int counter;

//Data to be saved
float raw_right_Speed;
int raw_right_Direction;
float raw_left_Speed;
int raw_left_Direction;

//Create data structure to be sent over radio, 8 bytes long
struct dataStruct{
  unsigned int left_Speed; 
  unsigned int left_Direction;
  unsigned int right_Speed;
  unsigned int right_Direction;
}radioBuf;

//Used to turn int data into binary to transmit
byte tx_buf[sizeof(radioBuf)] = {0};

void setup()
{
  //Direction pin
  // pinMode (right_Switch, INPUT_PULLUP);
  // pinMode (left_Switch, INPUT_PULLUP);
            
  // Debugging only
  Serial.begin(9600);    
  if (!driver.init())
        Serial.println("init failed");
  
  
  

}

void loop()
{
    //Get analog data from pot
    //raw_right_Speed = analogRead(A0);
    raw_right_Speed = analogRead(A0);
    if (raw_right_Speed>=1023) raw_right_Speed =1024;
    if (raw_right_Speed>=500 && raw_right_Speed<=524) {
      radioBuf.right_Speed = 0;
    }
    else if (raw_right_Speed<500){
      radioBuf.right_Speed = (255-raw_right_Speed*78/500);
      raw_right_Direction = 1;
    }

    else if (raw_right_Speed>524){
      radioBuf.right_Speed = raw_right_Speed*78/500+95.256;
      raw_right_Direction = 0;
    }


    raw_left_Speed = analogRead(A1);
    if (raw_left_Speed>=1023) raw_left_Speed = 1024;
    if (raw_left_Speed>=500 && raw_left_Speed<=524) {
      radioBuf.left_Speed = 0;
    }

    else if (raw_left_Speed<500){
      radioBuf.left_Speed = (255-raw_left_Speed*78/500);
      raw_left_Direction = 1;
    }

    else if (raw_left_Speed>524){
      radioBuf.left_Speed = raw_left_Speed*78/500+95.256;
      raw_left_Direction = 0;
    }

    radioBuf.right_Direction = raw_right_Direction;
    radioBuf.left_Direction = raw_left_Direction;
    
    //Copies data from radioBuf structure to binary array
    memcpy(tx_buf, &radioBuf, sizeof(radioBuf));
    int size_radioBuf = sizeof(radioBuf);
    
    
    //Timer to send signal
    if (counter>=20){
      driver.send((uint8_t *)tx_buf, size_radioBuf);
      driver.waitPacketSent();

      Serial.print("Right Speed");
      Serial.print(radioBuf.right_Speed);
      Serial.print("    Right Direction");
      Serial.print(radioBuf.right_Direction);
      Serial.print("    Left Speed");
      Serial.print(radioBuf.left_Speed);
      Serial.print("    Left Direction");
      Serial.println(radioBuf.left_Direction);
      counter = 0;
    }
    counter = counter+1;
}
