//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(7,8);  // CSN,mCE

//address through which two modules communicate.
const byte address[6] = "ABCDE";

//Variables for analog values
float raw_right_Speed;
int raw_right_Direction;
float raw_left_Speed;
int raw_left_Direction;


//Create data structure to be sent over radio, 8 bytes long
struct dataStruct{
  int left_Speed; 
  int left_Direction;
  int right_Speed;
  int right_Direction;
}radioBuf;

//Used to turn int structure data into binary array to transmit
byte tx_buf[sizeof(radioBuf)] = {0};

void setup()
{
  // Debugging only
  Serial.begin(9600);    

  //Begin radio
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
  //The following calculations is to create a deadzone for the joystick, and allow direction controls using one joystick for each side.
  float left_Min_Deadzone = 500.0;
  float left_Max_Deadzone = 511.0;
  float left_front_correction_value = 255.0/(1024.0-left_Max_Deadzone);
  float left_back_correction_value = (255.0/left_Min_Deadzone);

  //Left track control
  raw_left_Speed = analogRead(A2);
  //Round up to max
  if (raw_left_Speed>=1010){
    raw_left_Speed = 1024;
  }
  else if (raw_left_Speed<=14){
    raw_left_Speed = 0;
  }
  //Deadzone
  if (raw_left_Speed>=left_Min_Deadzone && raw_left_Speed<=left_Max_Deadzone){
    radioBuf.left_Speed = 0;
  }
  //Forward
  else if (raw_left_Speed>left_Max_Deadzone){
    radioBuf.left_Speed = (raw_left_Speed-left_Max_Deadzone)*left_front_correction_value;
    raw_left_Direction = 1;
  }
  //Backward
  else if(raw_left_Speed<left_Min_Deadzone){
    radioBuf.left_Speed = (left_Min_Deadzone-raw_left_Speed)*left_back_correction_value;
    raw_left_Direction = 0;
  }


  //Joystick -> Motor value constants 
  float right_Min_Deadzone = 526.0;
  float right_Max_Deadzone = 536.0;
  float right_front_correction_value = 255.0/(1024.0-right_Max_Deadzone);
  float right_back_correction_value = (255.0/right_Min_Deadzone);

  //Right track control
  raw_right_Speed = analogRead(A0); 
  //Round up to max
  if (raw_right_Speed>=1010){
    raw_right_Speed = 1024;
  }
  else if (raw_right_Speed<=14){
    raw_right_Speed = 0;
  }

  //Deadzone
  if (raw_right_Speed>=right_Min_Deadzone && raw_right_Speed<=right_Max_Deadzone){
    radioBuf.right_Speed = 0;
  }
  //Forward
  else if (raw_right_Speed>right_Max_Deadzone){
    radioBuf.right_Speed = (raw_right_Speed-right_Max_Deadzone)*right_front_correction_value;
    raw_right_Direction = 1;
  }
  //Backward
  else if(raw_right_Speed<right_Min_Deadzone){
    radioBuf.right_Speed = (right_Min_Deadzone-raw_right_Speed)*right_back_correction_value;
    raw_right_Direction = 0;
  }

  //Direction based on the position of the pot
    radioBuf.right_Direction = raw_right_Direction;
    radioBuf.left_Direction = raw_left_Direction;
    
    //Copies data from radioBuf structure to binary array
    memcpy(tx_buf, &radioBuf, sizeof(radioBuf));
   
    
    //Sends message every 150ms
    const uint32_t radio_Delay = 150;
    static uint32_t time_Last = 0;

    if (millis()-time_Last>=radio_Delay){

      //Send array in tx_buff over radio on pipe address ABCDE
      radio.write(&tx_buf, sizeof(tx_buf));
      
      //Debug Only
      Serial.print("Left Speed");
      Serial.print(radioBuf.left_Speed);
      // Serial.print("    Left Raw Speed");
      // Serial.print(raw_left_Speed);
      Serial.print("    Left Direction");
      Serial.print(radioBuf.left_Direction);
      Serial.print("    Right Speed");
      Serial.print(radioBuf.right_Speed);
      // Serial.print("    Right Raw Speed");
      // Serial.print((right_Min_Deadzone-raw_right_Speed)*right_back_correction_value);
      Serial.print("    Right Direction");
      Serial.println(radioBuf.right_Direction);

      time_Last = millis();
    }
}
