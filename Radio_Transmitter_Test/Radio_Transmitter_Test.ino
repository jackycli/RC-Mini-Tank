#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
int msg = B00000000;
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
    int digitalSensorValue = int(sensorValue/1024*255);
    if ((digitalSensorValue>1) && (digitalSensorValue<=85)){
      msg = (msg & B11111000);
      msg = (msg | B00000001);
    }
    else if ((digitalSensorValue>85) && (digitalSensorValue<=170)){
      msg = (msg & B11111000);
      msg = (msg | B00000010);
    }
    else if ((digitalSensorValue>170) && (digitalSensorValue<=255)){
      msg = (msg & B11111000);
      msg = (msg | B00000100);
    }
    else{
      msg = (msg & B11111000);
    }

    //Timer to send signal
    if (counter>=5){
      driver.send((uint8_t *)msg, strlen(msg));
      driver.waitPacketSent();
      Serial.println(digitalSensorValue);
      Serial.print("Msg:");
      Serial.println(msg,BIN);
    }
    counter = counter+1;
}
