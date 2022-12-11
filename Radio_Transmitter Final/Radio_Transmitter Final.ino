#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
int left_Speed, right_Speed, left_Direction, right_Direction;
RH_ASK driver(2000,12,12,5);
int counter;

void setup()
{
  // put your setup code here, to run once:

  Serial.begin(9600);    // Debugging only
  if (!driver.init())
        Serial.println("init failed");
}

void loop()
{

    float sensorValue = analogRead(A1);
    int digitalSensorValue = int(sensorValue/1024*10);
    if ((digitalSensorValue>1) && (digitalSensorValue<=3)){
      left_Speed = 1111;
    }
    else if ((digitalSensorValue>3) && (digitalSensorValue<=7)){
      left_Speed = 2222;
    }
    else if ((digitalSensorValue>7) && (digitalSensorValue<=10)){
      left_Speed = 3333;
    }
    else{
      left_Speed = 0000;
    }
    int values[4]={left_Speed, right_Speed, left_Direction, right_Direction};
    //Timer to send signal
    if (counter>=5){
      driver.send((uint8_t *) values[0], sizeof(values[0]));
      driver.waitPacketSent();
      driver.send((uint8_t *) values[1], sizeof(values[1]));
      driver.waitPacketSent();
      driver.send((uint8_t *) values[2], sizeof(values[2]));
      driver.waitPacketSent();
      driver.send((uint8_t *) values[3], sizeof(values[3]));
      driver.waitPacketSent();

      Serial.println(digitalSensorValue);
      Serial.print("Msg:");
      Serial.print(values[0]);
      Serial.print(" ");
      Serial.print(values[1]);
      Serial.print(" ");
      Serial.print(values[2]);
      Serial.print(" ");
      Serial.println(values[3]);
    }
    counter = counter+1;
}
