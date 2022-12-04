#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
char *msg;
RH_ASK driver(2000,12,12,5);

void setup()
{
    Serial.begin(9600);    // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    
    float sensorValue = analogRead(A1);
    int digitalSensorValue = int(sensorValue/1024*255);
    if ((digitalSensorValue>=0) && (digitalSensorValue<=85)){
      msg = "LEFT_LOW";
    }
    else if ((digitalSensorValue>85) && (digitalSensorValue<=170)){
      msg = "LEFT_MED";
    }
    else if ((digitalSensorValue>170) && (digitalSensorValue<=255)){
      msg = "LEFT_HGH";
    }
    else{
      msg = "LEFT_ERR";
    }
    
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    Serial.println(digitalSensorValue);
    Serial.print("Msg:");
    Serial.println((char*)msg);
    delay(1000);


    
}
