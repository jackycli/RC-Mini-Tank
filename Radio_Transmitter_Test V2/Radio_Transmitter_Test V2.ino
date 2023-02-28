//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(7,8);  // CSN,mCE

//address through which two modules communicate.
const byte address[6] = "ABCDE";

unsigned int counter;

//Data to be saved
float raw_right_Speed;
int raw_right_Direction;
float raw_left_Speed;
int raw_left_Direction;


//Create data structure to be sent over radio, 16 bytes long
struct dataStruct{
  int left_Speed; 
  int left_Direction;
  int right_Speed;
  int right_Direction;
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

  //
  radio.begin();
  
  //set the address
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH);
  //Set module as transmitter
  radio.stopListening();
  
}

void loop()
{
  //Get analog data from joystick
  //The following calculations is to create a deadzone for the potentiometer, and allow direction controls using one joystick for each side.
    
  //Left track control
  raw_left_Speed = analogRead(A1);
  //Round up to max
  if (raw_left_Speed>=1020){
    raw_left_Speed = 1024;
  }
  //Deadzone
  if (raw_left_Speed>=504 && raw_left_Speed<=507){
    radioBuf.left_Speed = 0;
  }
  //Forward
  else if (raw_left_Speed>507){
    float left_front_correction_value = 255.0/(1024.0-507.0);
    radioBuf.left_Speed = (raw_left_Speed-507)*left_front_correction_value;
    raw_left_Direction = 1;
  }
  //Backward
  else if(raw_left_Speed<504){
    float left_back_correction_value = (255.0/504.0);
    radioBuf.left_Speed = (504-raw_left_Speed)*left_back_correction_value;
    raw_left_Direction = 0;
  }
  
  //Right track control
  raw_right_Speed = analogRead(A0); 
  //Round up to max
  if (raw_right_Speed>=1020){
    raw_right_Speed = 1024;
  }
  //Deadzone
  if (raw_right_Speed>=530 && raw_right_Speed<=532){
    radioBuf.right_Speed = 0;
  }
  //Forward
  else if (raw_right_Speed>532){
    float right_front_correction_value = 255.0/(1024.0-532.0);
    radioBuf.right_Speed = (raw_right_Speed-532)*right_front_correction_value;
    raw_right_Direction = 1;
  }
  //Backward
  else if(raw_left_Speed<530){
    float right_back_correction_value = (255.0/530.0);
    radioBuf.right_Speed = (530-raw_right_Speed)*right_back_correction_value;
    raw_right_Direction = 0;
  }
  
  

  //Direction based on the position of the pot
    radioBuf.right_Direction = raw_right_Direction;
    radioBuf.left_Direction = raw_left_Direction;
    
    //Copies data from radioBuf structure to binary array
    memcpy(tx_buf, &radioBuf, sizeof(radioBuf));
   
    
    
    //Timer to send signal
    //Sends signal every 20 cycles
    if (counter>=500){
      radio.write(&tx_buf, sizeof(tx_buf));
      

      Serial.print("Left Speed");
      Serial.print(radioBuf.left_Speed);
      Serial.print("    Left Direction");
      Serial.print(radioBuf.left_Direction);
      Serial.print("    Right Speed");
      Serial.print(radioBuf.right_Speed);
      Serial.print("    Right Direction");
      Serial.println(radioBuf.right_Direction);

      counter = 0;
    }
    counter = counter+1;
}
