/*
Required connections between Arduino and Qik 2s15v9:

      Arduino   Qik 2s15v9
---------------------------
          GND - GND
Digital Pin 2 - TX
Digital Pin 3 - RX
Digital Pin 4 - RESET

DO NOT connect the 5V output on the Arduino to the 5V output on the Qik 2s15v9!
*/

#include <SoftwareSerial.h>
#include <PololuQik.h>

PololuQik2s15v9 qik(2, 3, 4);

void setup()
{
  Serial.begin(115200);
  Serial.println("Qik 2s15v9 dual serial motor controller");

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
    if (abs(i) % 64 == 32)
    {
      Serial.print("M0 current: ");
      Serial.println(qik.getM0CurrentMilliamps());
    }
    delay(5);
  }

  for (int i = 127; i >= -127; i--)
  {
    qik.setM0Speed(i);
    if (abs(i) % 64 == 32)
    {
      Serial.print("M0 current: ");
      Serial.println(qik.getM0CurrentMilliamps());
    }
    delay(5);
  }

  for (int i = -127; i <= 0; i++)
  {
    qik.setM0Speed(i);
    if (abs(i) % 64 == 32)
    {
      Serial.print("M0 current: ");
      Serial.println(qik.getM0CurrentMilliamps());
    }
    delay(5);
  }

  for (int i = 0; i <= 127; i++)
  {
    qik.setM1Speed(i);
    if (abs(i) % 64 == 32)
    {
      Serial.print("M1 current: ");
      Serial.println(qik.getM1CurrentMilliamps());
    }
    delay(5);
  }

  for (int i = 127; i >= -127; i--)
  {
    qik.setM1Speed(i);
    if (abs(i) % 64 == 32)
    {
      Serial.print("M1 current: ");
      Serial.println(qik.getM1CurrentMilliamps());
    }
    delay(5);
  }

  for (int i = -127; i <= 0; i++)
  {
    qik.setM1Speed(i);
    if (abs(i) % 64 == 32)
    {
      Serial.print("M1 current: ");
      Serial.println(qik.getM1CurrentMilliamps());
    }
    delay(5);
  }
}
