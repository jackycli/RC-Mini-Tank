//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(7,8);  // CSN,mCE

//address through which two modules communicate.
const byte address[6] = "ABCDE";

void setup()
{
  Serial.begin(9600);
  radio.begin();
   
  //set the address
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MIN);
  //Set module as transmitter
  radio.startListening();
}
void loop()
{

  if (radio.available()){
    char text[32] = "";
    radio.read(&text,sizeof(text));
    Serial.println(text);
  }
}