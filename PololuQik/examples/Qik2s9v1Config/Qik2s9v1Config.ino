/*
Optionally writes, then reads, the configuration parameters on the qik 2s9v1.

Please note that the memory used to store these parameters is only rated 
for approximately 100,000 erase/write cycles, so you should avoid 
repeatedly setting configuration parameters. It is intended that these 
parameters will initially be configured as desired and then only changed 
occasionally (they are saved in non-volatile memory, which means that 
once set, these parameters will retain their values even if the unit is 
powered off). For example, you can uncomment the appropriate calls to 
setConfigShowResult() below and run this program once to initialize the 
parameters. Then, you can load your final program on your Arduino, which 
should assume that the parameters have already been set correctly. 

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

char* param_names[] = {
  "Device ID",
  "PWM Parameter",
  "Shut Down Motors on Error",
  "Serial Timeout"
};

PololuQik2s9v1 qik(2, 3, 4);

void setConfigShowResult(uint8_t parameter, uint8_t value)
{
  Serial.print("Setting ");
  Serial.print(param_names[parameter]);
  Serial.print(" to ");
  Serial.print(value);

  byte result = qik.setConfigurationParameter(parameter, value);

  switch (result)
  {
    case 0:
      Serial.println(": Command OK");
      break;

    case 1:
      Serial.println(": Bad parameter");
      break;

    case 2:
      Serial.println(": Bad value");
      break;
  }
}


void setup()
{
  Serial.begin(115200);
  Serial.println("qik 2s9v1 dual serial motor controller");
  Serial.println();

  qik.init();

  // Write configuration parameters
  // Uncomment and edit the line for any parameter you want to change.
  
  //setConfigShowResult(QIK_CONFIG_DEVICE_ID, 9);
  //setConfigShowResult(QIK_CONFIG_PWM_PARAMETER, 0);
  //setConfigShowResult(QIK_CONFIG_SHUT_DOWN_MOTORS_ON_ERROR, 1);
  //setConfigShowResult(QIK_CONFIG_SERIAL_TIMEOUT, 0);

  Serial.println();

  // Read configuration parameters

  for (int i = QIK_CONFIG_DEVICE_ID; i <= QIK_CONFIG_SERIAL_TIMEOUT; i++)
  {
    Serial.print(param_names[i]);
    Serial.print(": ");
    Serial.println(qik.getConfigurationParameter(i));
  }
}

void loop()
{
  // do nothing
}
