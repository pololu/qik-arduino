/*
Optionally writes, then reads, the configuration parameters on the qik 2s12v10.

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

      Arduino   qik 2s12v10
---------------------------
          GND - GND
Digital Pin 2 - TX
Digital Pin 3 - RX
Digital Pin 4 - RESET

DO NOT connect the 5V output on the Arduino to the 5V output on the qik 2s12v10!
*/

#include <SoftwareSerial.h>
#include <PololuQik.h>

char* param_names[] = {
  "Device ID",
  "PWM Parameter",
  "Shut Down Motors on Error",
  "Serial Timeout",
  "Motor M0 Acceleration",
  "Motor M1 Acceleration",
  "Motor M0 Brake Duration",
  "Motor M1 Brake Duration",
  "Motor M0 Current Limit / 2",
  "Motor M1 Current Limit / 2",
  "Motor M0 Current-Limit Response",
  "Motor M1 Current-Limit Response"
};

PololuQik2s12v10 qik(2, 3, 4);

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
  Serial.println("qik 2s12v10 dual serial motor controller");
  Serial.println();

  qik.init();

  // Write configuration parameters
  // Uncomment and edit the line for any parameter you want to change.
  
  //setConfigShowResult(QIK_CONFIG_DEVICE_ID, 10);
  //setConfigShowResult(QIK_CONFIG_PWM_PARAMETER, 0);
  //setConfigShowResult(QIK_CONFIG_SHUTDOWN_MOTORS_ON_ERROR, 1);
  //setConfigShowResult(QIK_CONFIG_SERIAL_TIMEOUT, 0);
  //setConfigShowResult(QIK_CONFIG_MOTOR_M0_ACCELERATION, 0);
  //setConfigShowResult(QIK_CONFIG_MOTOR_M1_ACCELERATION, 0);
  //setConfigShowResult(QIK_CONFIG_MOTOR_M0_BRAKE_DURATION, 0);
  //setConfigShowResult(QIK_CONFIG_MOTOR_M1_BRAKE_DURATION, 0);
  //setConfigShowResult(QIK_CONFIG_MOTOR_M0_CURRENT_LIMIT_DIV_2, 0);
  //setConfigShowResult(QIK_CONFIG_MOTOR_M1_CURRENT_LIMIT_DIV_2, 0);
  //setConfigShowResult(QIK_CONFIG_MOTOR_M0_CURRENT_LIMIT_RESPONSE, 4);
  //setConfigShowResult(QIK_CONFIG_MOTOR_M1_CURRENT_LIMIT_RESPONSE, 4);

  Serial.println();

  // Read configuration parameters

  for (int i = QIK_CONFIG_DEVICE_ID; i <= QIK_CONFIG_MOTOR_M1_CURRENT_LIMIT_RESPONSE; i++)
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
