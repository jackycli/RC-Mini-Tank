#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile


//Both using pin 12, on transmitter and receiver
RH_ASK driver(2000,12,12,5);

//Counter to delay radio tramsit
unsigned int counter;

//Data to be saved
float raw_right_Speed;
float raw_right_Direction;
float raw_left_Speed;
float raw_left_Direction;

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
  // Debugging only
  Serial.begin(9600);    
  if (!driver.init())
        Serial.println("init failed");
  
  radioBuf.left_Direction = 0;
  radioBuf.right_Direction = 1;

}

void loop()
{
    //Get analog data from pot
    raw_right_Speed = analogRead(A1);
    
    radioBuf.right_Speed = raw_right_Speed*255/1024;

    raw_left_Speed = analogRead(A1);
   
    radioBuf.left_Speed = 255-raw_left_Speed*255/1024;
    
    
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
      Serial.print("    Right Direction");
      Serial.println(radioBuf.left_Direction);
      // if (counter>=32000) counter = 0;
    }
    counter = counter+1;
}
