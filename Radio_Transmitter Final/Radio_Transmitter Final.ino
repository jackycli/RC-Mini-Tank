#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile


//Both using pin 12, on transmitter and receiver
RH_ASK driver(2000,12,12,5);

//Counter to delay radio tramsit
int counter;

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
  radioBuf.left_Speed = 1532;
  radioBuf.left_Direction = 0;
  radioBuf.right_Direction = 1;

}

void loop()
{
    //Get analog data from pot
    radioBuf.right_Speed = analogRead(A1);
    
    //Copies data from radioBuf structure to binary array
    memcpy(tx_buf, &radioBuf, sizeof(radioBuf));
    int size_radioBuf = sizeof(radioBuf);
    
    
    //Timer to send signal
    if (counter>=5){
      driver.send((uint8_t *)tx_buf, size_radioBuf);
      driver.waitPacketSent();
      Serial.println(radioBuf.right_Speed);
    }
    counter = counter+1;
}
