#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

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
    const char *msg = digitalSensorValue;
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    Serial.println(digitalSensorValue);
    Serial.print("Msg");
    Serial.println(*msg);
    delay(1000);


    
}
