/*
Required connections between Arduino and qik 2s9v1:

      Arduino   qik 2s9v1
-------------------------
           5V - VCC
          GND - GND
Digital Pin 2 - TX
Digital Pin 3 - RX
Digital Pin 4 - RESET
*/

#include <SoftwareSerial.h>
#include <PololuQik.h>

PololuQik2s9v1 qik(2, 3, 4);

void setup()
{
  Serial.begin(115200);
  Serial.println("qik 2s9v1 dual serial motor controller");
  
  qik.init();
  
  Serial.print("Firmware version: ");
  Serial.write(qik.getFirmwareVersion());
  Serial.println();
}

void loop()
{
  for (int i = 0; i <= 127; i++)
  {
    qik.setM0Speed(i);
    delay(5);
  }

  for (int i = 127; i >= -127; i--)
  {
    qik.setM0Speed(i);
    delay(5);
  }

  for (int i = -127; i <= 0; i++)
  {
    qik.setM0Speed(i);
    delay(5);
  }

  for (int i = 0; i <= 127; i++)
  {
    qik.setM1Speed(i);
    delay(5);
  }

  for (int i = 127; i >= -127; i--)
  {
    qik.setM1Speed(i);
    delay(5);
  }

  for (int i = -127; i <= 0; i++)
  {
    qik.setM1Speed(i);
    delay(5);
  }
}
