#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
char *msg;
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
      msg = "LEFT_LOWSPED";
    }
    else if ((digitalSensorValue>85) && (digitalSensorValue<=170)){
      msg = "LEFT_MEDSPED";
    }
    else if ((digitalSensorValue>170) && (digitalSensorValue<=255)){
      msg = "LEFT_HGHSPED";
    }
    else{
      msg = "LEFT_NULSPED";
    }

    //Timer to send signal
    if (counter>=5){
      driver.send((uint8_t *)msg, strlen(msg));
      driver.waitPacketSent();
      Serial.println(digitalSensorValue);
      Serial.print("Msg:");
      Serial.println((char*)msg);
    }
    counter = counter+1;
}
